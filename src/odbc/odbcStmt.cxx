
// Class CSqlOdbcStmt
// Description: Statement Handle manager. 

#include "odbcCommon.h"

// Constructor
CSqlOdbcStmt::CSqlOdbcStmt( void ) :
    handleType_( SQL_HANDLE_STMT ),
    parentDbc_( 0 ),
    state_( S1 ),
    err_( SQL_HANDLE_STMT ),
    rowsAffected_( -1 ),
    isParamBound_( true ),
    isPrepared_( false ),
    apd_(SQL_DESC_APP),
    ipd_(SQL_DESC_IMP),
    ard_(SQL_DESC_APP),
    ird_(SQL_DESC_IMP),
    fsqlStmt_( NULL )
    //HACK::
    //fetchMode_(SQL_FETCH_SINGLE_TUPLE)
{
    cursorName_[0] = '\0';
}

SQLRETURN SQLAllocStmt(
    SQLHDBC ConnectionHandle,
    SQLHSTMT *StatementHandle)
{
    return( CSqlOdbcStmt::SQLAllocHandle( ConnectionHandle, StatementHandle ) );
}

SQLRETURN CSqlOdbcStmt::SQLAllocHandle(
    SQLHANDLE   inputHandle,    // IN
    SQLHANDLE   *outputHandle ) // OUT
{
    CSqlOdbcDbc *inputDbc = (CSqlOdbcDbc*) inputHandle;

    // Is Dbc valid ?
    if( isValidHandle( inputDbc, SQL_HANDLE_DBC ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    // Is Dbc connected ?
    if( inputDbc->state_ < C4 )
    {
        globalError.set( ERROR_CONNOTOPEN );
        globalError.printStr( SQL_OV_ODBC3 );
        return( SQL_ERROR );
    }
    if (NULL == outputHandle)
    {
       globalError.set(ERROR_INVARGVAL);
       return (SQL_ERROR);
    }


    // Allocate Statement object.
    *outputHandle = (SQLHANDLE*) new CSqlOdbcStmt;
    if( *outputHandle == NULL )
    {
        globalError.set( ERROR_MEMALLOC );
        globalError.printStr( SQL_OV_ODBC3 );
        return( SQL_ERROR );
    }

    // Initialize relation b/w Stmt and Dbc
    inputDbc->stmtList_.append(*outputHandle );
    inputDbc->stmtHdlList_.append(outputHandle);
    if( inputDbc->state_ <= C4 )
        inputDbc->state_ = C5;
    ((CSqlOdbcStmt*) *outputHandle)->parentDbc_ = inputDbc;
    //CSqlOdbcError::printDbg("proxy:stmt:setConnection");
    //((CSqlOdbcStmt*) *outputHandle)->fsqlStmt_->setConnection( inputDbc->fsqlConn_ ); 
     ((CSqlOdbcStmt*) *outputHandle)->fInfo = new FieldInfo();
    return( SQL_SUCCESS );
}

SQLRETURN CSqlOdbcStmt::SQLFreeHandle(
    SQLHANDLE inputHandle)      // IN
{
    CSqlOdbcStmt *inputStmt = (CSqlOdbcStmt*) inputHandle;

    // Is Stmt valid ?
    if( isValidHandle( inputStmt, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    // Can we proceed ?
    if( inputStmt->chkStateForSQLFreeHandle() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Free resultset
    inputStmt->resetStmt();

    // Remove Stmt from Parent Dbc.
    ListIterator iter = inputStmt->parentDbc_->stmtList_.getIterator();
    CSqlOdbcStmt *stmtElem = NULL;
    while (iter.hasElement()) {
        stmtElem = (CSqlOdbcStmt *) iter.nextElement();
        if( stmtElem == inputStmt ) {
            iter.reset();
            inputStmt->parentDbc_->stmtList_.remove(stmtElem);
            break;
        }
    }
    // Set Dbc state_ = no statement.
    if( inputStmt->parentDbc_->stmtList_.size() == 0 )
            inputStmt->parentDbc_->state_ = C4;

    inputStmt->handleType_ = -1; // Make object invalid.
    SQLHANDLE *elem;
    ListIterator it = inputStmt->parentDbc_->stmtHdlList_.getIterator();
    while (it.hasElement()) {
        elem = (SQLHANDLE *) it.nextElement();
        if(*elem == inputStmt) *elem = NULL;
    }
    inputStmt->parentDbc_->stmtHdlList_.remove(elem);
    delete inputStmt->fInfo;
    delete inputStmt;            // Delete Stmt.
    return( SQL_SUCCESS );
}

SQLRETURN SQLFreeStmt(
    SQLHSTMT StatementHandle,   // IN
    SQLUSMALLINT Option)        // IN
{
#ifdef DEBUG
    printError(ErrWarning, "SQLFreeStmt opt:%d", Option);
#endif
    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    // Free Handle
    if( Option == SQL_DROP )
        return( CSqlOdbcStmt::SQLFreeHandle( StatementHandle ) );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLFreeStmt( Option ) );
}

SQLRETURN CSqlOdbcStmt::SQLFreeStmt(
            SQLUSMALLINT option)
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed
    if( chkStateForSQLFreeStmt() != SQL_SUCCESS )
        return( SQL_ERROR );
    if (!fsqlStmt_) return (SQL_SUCCESS);
    switch( option )
    {
        case SQL_CLOSE:         // // Free resultset
                                // if( fsqlStmt_->isSelect() == true ) // CSQL
                                // {
                                //    //CSqlOdbcError::printDbg("proxy:stmt:getResultSet");
                                //    CSqlResultSet *resultSet_ = fsqlStmt_->getResultSet(); // CSQL
                                //    if( resultSet_ && resultSet_->isOpen() == true )
                                //    {
                                //        resultSet_->close();
                                //    }
                                // }

                                // cursor states
                                if( isPrepared_ ) 
                                {
                                    if( fsqlStmt_->isSelect() == true ) { // CSQL
                                        fsqlStmt_->close();
                                        state_ = S3;    // With Cursor
                                    }
                                    else
                                        state_ = S2;    // Without Cursor
                                }
                                else
                                {
                                    ard_.freeAllDesc();
                                    apd_.freeAllDesc();
                                    ipd_.freeAllDesc();
                                    ird_.freeAllDesc();
                                    fsqlStmt_->free(); // CSQL
                                    state_ = S1;
                                }

                                break;
                                
        case SQL_UNBIND:        ard_.freeAllDesc();
                                ird_.freeAllDesc();
                                break;
                                
        case SQL_RESET_PARAMS:  apd_.freeAllDesc();
                                ipd_.freeAllDesc();
                                //isParamBound_ = false;
                                break;

        default: err_.set( ERROR_OPTRANGE ); 
                return( SQL_ERROR );
    }
    return( SQL_SUCCESS );
}

SQLRETURN SQLBindCol(
    SQLHSTMT        StatementHandle,
    SQLUSMALLINT    ColumnNumber,
    SQLSMALLINT     TargetType,
    SQLPOINTER      TargetValue,
    SQLINTEGER      BufferLength,
    SQLINTEGER      *StrLen_or_Ind)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLBindCol");
#endif
    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLBindCol( ColumnNumber,
        TargetType, TargetValue, BufferLength, StrLen_or_Ind ) );
}

SQLRETURN CSqlOdbcStmt::SQLBindCol(
    SQLUSMALLINT columnNumber,
    SQLSMALLINT targetType,
    SQLPOINTER targetValue,
    SQLINTEGER bufferLength,
    SQLINTEGER *ind)
{
    CSqlOdbcDesc *bindDesc = 0;
    CSqlOdbcDesc *inputDesc = 0;
    SQLRETURN found = SQL_ERROR;

    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLBindCol() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Invalid Buffer Length.
    switch( targetType )
    {
        // switch is in order to support more types.
        case SQL_C_CHAR:
            if( bufferLength < 0 && bufferLength != SQL_NTS )
            {
                err_.set( ERROR_BUFLEN );
                return( SQL_ERROR );
            }
            break;
	    case SQL_C_BINARY:
           if( bufferLength < 0 && bufferLength != SQL_NTS )
            {
                err_.set( ERROR_BUFLEN );
                return( SQL_ERROR );
            }
           break;
    }

    // Invalid Column Number
    if( columnNumber < 1 )
    {
        err_.set( ERROR_COLNUM );
        return( SQL_ERROR );
    }
    
    // Get the Descriptor if already exists
    found = ard_.getDescWithColNum( columnNumber , &bindDesc );

    // UNBIND
    if( targetValue == 0 )
    {
        if( found != SQL_SUCCESS )
        {
            err_.set( ERROR_COLNUM );
            return( SQL_ERROR );
        }
        ard_.delDesc( bindDesc );    // UNBIND
        
        return( SQL_SUCCESS );
    }

    // Validate target Type, Value and Column no.
    if( targetValue == 0 || isValidCType( targetType ) != SQL_SUCCESS )
    {
        err_.set( ERROR_INVBUFTYPE );
        return( SQL_ERROR );
    }

    // Add new descriptor
    if( found != SQL_SUCCESS )
    {
        bindDesc = new CSqlOdbcDesc();
        ard_.descList_.append(bindDesc);
    }

    // Initialize Descriptor.
    bindDesc->col_ = columnNumber;
    bindDesc->cType_ = targetType;
    bindDesc->dataPtr_ = targetValue;
    bindDesc->length_ = (SQLUINTEGER) bufferLength;
    bindDesc->indPtr_ = (SQLPOINTER) ind;

    found = ird_.getDescWithColNum( columnNumber , &inputDesc );

    // Add new descriptor
    if( found != SQL_SUCCESS )
    {
        inputDesc = new CSqlOdbcDesc();
        ird_.descList_.append(inputDesc);
    }
    ResultSetPlan pl = fsqlStmt_->getResultSetPlan();
    //Get Field Information from CSQL
    fsqlStmt_->getProjFldInfo(columnNumber, fInfo);
    // Initialize input Descriptor.
    //DataType sourceType = getCSqlType( targetType );
    //char fldName[IDENTIFIER_LENGTH];
    //Table::getFieldNameAlone((char*)fInfo->fldName,fldName);
    strcpy((char *)inputDesc->colName_,(char*)fInfo->fldName);
    inputDesc->col_ = columnNumber;
    if( pl == GetColumns && columnNumber == 5) {
        inputDesc->csqlType_ = typeShort; 
        inputDesc->cType_ = typeShort;
    }
    else {
        inputDesc->csqlType_ = fInfo->type;
        inputDesc->cType_ = fInfo->type;
    }
    getInputBuffer(&inputDesc->dataPtr_ ,fInfo->type,(SQLUINTEGER) bufferLength);
    inputDesc->length_ = fInfo->length;
    inputDesc->indPtr_ = (SQLPOINTER) ind;
    return( SQL_SUCCESS );
}

SQLRETURN SQLSetParam(
    SQLHSTMT StatementHandle,
    SQLUSMALLINT ParameterNumber, 
    SQLSMALLINT ValueType,
    SQLSMALLINT ParameterType, 
    SQLUINTEGER LengthPrecision,
    SQLSMALLINT ParameterScale, 
    SQLPOINTER ParameterValue,
    SQLINTEGER *StrLen_or_Ind)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLSetParam");
#endif

    return( SQLBindParameter( StatementHandle, ParameterNumber,
        SQL_PARAM_INPUT_OUTPUT, ValueType, ParameterType, LengthPrecision,
        ParameterScale, ParameterValue, 0, StrLen_or_Ind) );
}

SQLRETURN SQLBindParam(
    SQLHSTMT StatementHandle,
    SQLUSMALLINT ParameterNumber, 
    SQLSMALLINT ValueType,
    SQLSMALLINT ParameterType, 
    SQLUINTEGER LengthPrecision,
    SQLSMALLINT ParameterScale,
    SQLPOINTER ParameterValue,
    SQLINTEGER *StrLen_or_Ind)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLBindParam");
#endif

    return( SQLBindParameter( StatementHandle, ParameterNumber,
        SQL_PARAM_INPUT_OUTPUT, ValueType, ParameterType, LengthPrecision,
        ParameterScale, ParameterValue, 0, StrLen_or_Ind) );
}

SQLRETURN SQLBindParameter(
    SQLHSTMT StatementHandle,
    SQLUSMALLINT ParameterNumber,
    SQLSMALLINT InputOutputType,
    SQLSMALLINT ValueType,
    SQLSMALLINT ParameterType,
    SQLUINTEGER LengthPrecision,
    SQLSMALLINT ParameterScale,
    SQLPOINTER ParameterValue,
    SQLINTEGER BufferLength,
    SQLINTEGER *StrLen_or_Ind)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLBindParameter");
#endif
    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLBindParameter( ParameterNumber,
        InputOutputType, ValueType,
        ParameterType, LengthPrecision,
        ParameterScale, ParameterValue,
        BufferLength, StrLen_or_Ind ) );
}

SQLRETURN CSqlOdbcStmt::SQLBindParameter(
    SQLUSMALLINT parameterNumber,
    SQLSMALLINT inputOutputType,
    SQLSMALLINT valueType,
    SQLSMALLINT parameterType,
    SQLUINTEGER lengthPrecision,
    SQLSMALLINT parameterScale,
    SQLPOINTER parameterValue,
    SQLINTEGER bufferLength,
    SQLINTEGER *ind)
{
    CSqlOdbcDesc *bindDesc = 0;
    CSqlOdbcDesc *inputDesc =0;
    SQLRETURN found;

    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLBindParameter() != SQL_SUCCESS )
        return( SQL_ERROR );
    // Invalid Buffer Length.
    switch( valueType )
    {
        // switch is in order to support more types.
        case SQL_C_CHAR:
            if( bufferLength < 0 && bufferLength != SQL_NTS )
            {
                err_.set( ERROR_BUFLEN );
                return( SQL_ERROR );
            }
            break;
        case SQL_C_BINARY:
            if( bufferLength < 0 && bufferLength != SQL_NTS )
            {
                err_.set( ERROR_BUFLEN );
                return( SQL_ERROR );
            }
            break;
    }

    // Validate parameters
    switch( inputOutputType )
    {
        case SQL_PARAM_INPUT:
        case SQL_PARAM_OUTPUT:
        case SQL_PARAM_INPUT_OUTPUT: break;
        default: err_.set( ERROR_INV_PARAMTYPE );
                 return( SQL_ERROR );
    }
    if( isValidCType( valueType ) != SQL_SUCCESS )
//        || isValidSQLType( parameterType ) != SQL_SUCCESS )
    {
        err_.set( ERROR_INVBUFTYPE );
        return( SQL_ERROR );
    }
    if( parameterNumber < 1 )
    {
        err_.set( ERROR_COLNUM );
        return( SQL_ERROR );
    }

    // Get the Descriptor if already exists
    found = apd_.getDescWithColNum( parameterNumber , &bindDesc );
    if( found != SQL_SUCCESS )
    {
        bindDesc = new CSqlOdbcDesc();
        apd_.descList_.append(bindDesc);
        // Initialize Descriptor.
        bindDesc->col_ = parameterNumber;
        bindDesc->paramType_ = inputOutputType;
        bindDesc->cType_ = valueType;
        bindDesc->sqlType_ = parameterType;
        bindDesc->dataPtr_ = parameterValue;
        bindDesc->length_ = (SQLUINTEGER) bufferLength;
        bindDesc->precision_ =(short) lengthPrecision;
        bindDesc->scale_ = parameterScale;
        bindDesc->indPtr_ = (SQLPOINTER) ind;
    }
    found = ipd_.getDescWithColNum (parameterNumber, &inputDesc);
    if( found != SQL_SUCCESS )
    {
        inputDesc =  new CSqlOdbcDesc();
        ipd_.descList_.append(inputDesc);
        //Initialize inputDescriptor
        DataType destType=getCSqlType(valueType);
        inputDesc->col_ = parameterNumber;
        inputDesc->paramType_ = inputOutputType;
        inputDesc->cType_ = valueType;
        inputDesc->sqlType_ = parameterType;
        inputDesc->dataPtr_= NULL;
        //getInputBuffer(&inputDesc->dataPtr_,destType,(SQLUINTEGER)bufferLength);
        inputDesc->length_ = (SQLUINTEGER) bufferLength;
        inputDesc->precision_ = (short)lengthPrecision;
        inputDesc->scale_ = parameterScale;
        inputDesc->indPtr_ = (SQLPOINTER) ind;
    }
    //isParamBound_ = false;
    return( SQL_SUCCESS );
}

SQLRETURN SQLExecDirect(
    SQLHSTMT StatementHandle,   // IN
    SQLCHAR *StatementText,     // IN
    SQLINTEGER TextLength)      // IN
{
#ifdef DEBUG
    printError(ErrWarning, "SQLExecDirect: %s", StatementText);
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    // Prepare
    return( ((CSqlOdbcStmt*) StatementHandle)->SQLExecDirect( StatementText, TextLength ) );
}

SQLRETURN CSqlOdbcStmt::SQLExecDirect(
    SQLCHAR *statementText,     // IN
    SQLINTEGER textLength)      // IN
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLPrepare() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Invalid Buffer Length.
    if( textLength < 0  && textLength != SQL_NTS )
    {
        err_.set( ERROR_BUFLEN );
        return( SQL_ERROR );
    }
    if (NULL == statementText)
    {
       err_.set(ERROR_INVARGVAL);
       return (SQL_ERROR);
    }

    // If Stmt is already prepared.
    if( state_ >= S2 ) {
        resetStmt();
    }

    if (parentDbc_->mode_ ==1)
        fsqlStmt_ = SqlFactory::createStatement(CSql);
    else if (parentDbc_->mode_ ==2)
        fsqlStmt_ = SqlFactory::createStatement(CSqlAdapter);
    else if (parentDbc_->mode_ ==3)
        fsqlStmt_ = SqlFactory::createStatement(CSqlGateway);
    else if (parentDbc_->mode_ ==4)
        fsqlStmt_ = SqlFactory::createStatement(CSqlNetwork);
    else if (parentDbc_->mode_ ==5)
        fsqlStmt_ = SqlFactory::createStatement(CSqlNetworkAdapter);
    else if (parentDbc_->mode_ ==6)
        fsqlStmt_ = SqlFactory::createStatement(CSqlNetworkGateway);
    fsqlStmt_->setConnection( parentDbc_->fsqlConn_ ); 
    // Prepare
    //CSqlOdbcError::printDbg("proxy:stmt:prepare");
    DbRetVal rv=OK;
    if( (rv=fsqlStmt_->executeDirect( (char*) statementText ))!= OK) // CSQL
    {
        state_ = S1;
        resetStmt();
        //err_.set(ERROR_GENERAL);
        switch(rv)
        {
            case ErrNotExists: err_.set( ERROR_TBLNOTFOUND); break;                                        
            case ErrNotFound: err_.set( ERROR_NO_COLEXISTS); break;                                        
            case ErrAlready: err_.set( ERROR_TBLEXISTS); break;                                        
            case ErrSyntaxError:err_.set(ERROR_SQL_SYNTAX);break;
            case ErrSyntax:err_.set(ERROR_SQL_SYNTAX);break;
            /*case csqlSqlErrSchNotFound:  err_.set( ERROR_SCHNOTFOUND); break;
            case csqlSqlErrIndexNotFound: err_.set( ERROR_NO_IDXEXISTS); break;                                        
            case csqlSqlErrViewNotFound: err_.set( ERROR_TBLNOTFOUND); break;                                        
            case csqlSqlErrFldExists: err_.set( ERROR_COLEXISTS); break;                                        
            case csqlSqlErrIndexExists: err_.set( ERROR_IDXEXISTS); break;                                        
            case csqlSqlErrViewExists: err_.set( ERROR_TBLEXISTS); break;                                        
            case csqlSqlErrTooManyVals:err_.set(ERROR_MANY_VALS);break;
            case csqlSqlErrTooFewVals:err_.set(ERROR_FEW_VALS);break; 
            case csqlSqlErrIncompatibleType:err_.set(ERROR_TYPE_INCMP);break;
            case csqlSqlErrInvalidFormat:err_.set(ERROR_DATA_FORMAT);break;
            case csqlSqlErrDuplicateFld:err_.set(ERROR_DUP_COL);break;
            case csqlSqlErrSqlInternal:err_.set(ERROR_SQL_INT);break;*/
            default: err_.set(ERROR_GENERAL);
        }
        return( SQL_ERROR );
    }
    // Set Stmt State
    if( fsqlStmt_->isSelect() )
    {
         rowsAffected_ = -1;
         state_ = S5;
    }
    else
    {
         rowsAffected_ = 1; //TODO::It should get this from SqlStatement
         state_ = S4;
    }
    // Set Dbc State to Transaction Mode.
    parentDbc_->state_ = C6;
    // AutoCommit Mode
    if( parentDbc_->autoCommit_ == SQL_AUTOCOMMIT_ON )
          parentDbc_->SQLEndTran( SQL_COMMIT );

    isPrepared_ = true;
    return( SQL_SUCCESS );
}

SQLRETURN SQLPrepare(
    SQLHSTMT StatementHandle,   // IN
    SQLCHAR *StatementText,     // IN
    SQLINTEGER TextLength)      // IN
{
#ifdef DEBUG
    printError(ErrWarning, "SQLPrepare: %s", StatementText);
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    // Prepare
    return( ((CSqlOdbcStmt*) StatementHandle)->SQLPrepare( StatementText, TextLength ) );
}

SQLRETURN CSqlOdbcStmt::SQLPrepare(
    SQLCHAR *statementText,     // IN
    SQLINTEGER textLength)      // IN
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLPrepare() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Invalid Buffer Length.
    if( textLength < 0  && textLength != SQL_NTS )
    {
        err_.set( ERROR_BUFLEN );
        return( SQL_ERROR );
    }
    if (NULL == statementText)
    {
       err_.set(ERROR_INVARGVAL);
       return (SQL_ERROR);
    }


    // If Stmt is already prepared.
    if( state_ >= S2 ) {
        resetStmt();
    }

    if (parentDbc_->mode_ ==1)
        fsqlStmt_ = SqlFactory::createStatement(CSql);
    else if (parentDbc_->mode_ ==2)
        fsqlStmt_ = SqlFactory::createStatement(CSqlAdapter);
    else if (parentDbc_->mode_ ==3)
        fsqlStmt_ = SqlFactory::createStatement(CSqlGateway);
    else if (parentDbc_->mode_ ==4)
        fsqlStmt_ = SqlFactory::createStatement(CSqlNetwork);
    else if (parentDbc_->mode_ ==5)
        fsqlStmt_ = SqlFactory::createStatement(CSqlNetworkAdapter);
    else if (parentDbc_->mode_ ==6)
        fsqlStmt_ = SqlFactory::createStatement(CSqlNetworkGateway);
    fsqlStmt_->setConnection( parentDbc_->fsqlConn_ ); 
    // Prepare
    //CSqlOdbcError::printDbg("proxy:stmt:prepare");
    DbRetVal rv=OK;
    if( (rv=fsqlStmt_->prepare( (char*) statementText ))!= OK) // CSQL
    {
        state_ = S1;
        resetStmt();
        //err_.set(ERROR_GENERAL);
        switch(rv)
        {
            case ErrNotExists: err_.set( ERROR_TBLNOTFOUND); break;                                        
            case ErrNotFound: err_.set( ERROR_NO_COLEXISTS); break;                                        
            case ErrAlready: err_.set( ERROR_TBLEXISTS); break;                                        
            case ErrSyntaxError:err_.set(ERROR_SQL_SYNTAX);break;
            case ErrSyntax:err_.set(ERROR_SQL_SYNTAX);break;
            /*case csqlSqlErrSchNotFound:  err_.set( ERROR_SCHNOTFOUND); break;
            case csqlSqlErrIndexNotFound: err_.set( ERROR_NO_IDXEXISTS); break;                                        
            case csqlSqlErrViewNotFound: err_.set( ERROR_TBLNOTFOUND); break;                                        
            case csqlSqlErrFldExists: err_.set( ERROR_COLEXISTS); break;                                        
            case csqlSqlErrIndexExists: err_.set( ERROR_IDXEXISTS); break;                                        
            case csqlSqlErrViewExists: err_.set( ERROR_TBLEXISTS); break;                                        
            case csqlSqlErrTooManyVals:err_.set(ERROR_MANY_VALS);break;
            case csqlSqlErrTooFewVals:err_.set(ERROR_FEW_VALS);break; 
            case csqlSqlErrIncompatibleType:err_.set(ERROR_TYPE_INCMP);break;
            case csqlSqlErrInvalidFormat:err_.set(ERROR_DATA_FORMAT);break;
            case csqlSqlErrDuplicateFld:err_.set(ERROR_DUP_COL);break;
            case csqlSqlErrSqlInternal:err_.set(ERROR_SQL_INT);break;*/
            default: err_.set(ERROR_GENERAL);
        }
        return( SQL_ERROR );
    }
    if( fsqlStmt_->isSelect() != true ) // CSQL
        state_ = S2;    // With cursor
    else
        state_ = S3;    // Without cursor

    //parentDbc_->state_ = C6;
    isPrepared_ = true;
    return( SQL_SUCCESS );
}

SQLRETURN SQLExecute(SQLHSTMT StatementHandle) // IN
{
#ifdef DEBUG
    printError(ErrWarning, "SQLExecute");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLExecute() );
}

SQLRETURN CSqlOdbcStmt::SQLExecute() // TODO
{
    // Start with NO_ERR
    err_.set( NO_ERR );
    // Can we proceed ?
    if( chkStateForSQLExecute() != SQL_SUCCESS )
        return( SQL_ERROR );

    if( fsqlStmt_->noOfParamFields() > 0 )
    {

        // Iterate through all apd_;
        CSqlOdbcDesc *appParamDesc;
        ListIterator apdIter = apd_.descList_.getIterator();
        CSqlOdbcDesc *csqlParamDesc;
        ListIterator ipdIter = ipd_.descList_.getIterator();

        //Get the source and the destination type
        DataType sourceType = typeUnknown,destType = typeUnknown;
        int paramNum=1,sourceLength=-1,destLength=-1;
        bool nullFlag=false;

        while(apdIter.hasElement() || ipdIter.hasElement()) {
            appParamDesc= (CSqlOdbcDesc *) apdIter.nextElement();
            csqlParamDesc=(CSqlOdbcDesc *) ipdIter.nextElement();
            if(paramNum <= fsqlStmt_->noOfParamFields())
            {
		if( fsqlStmt_->getParamFldInfo(paramNum, fInfo ) != OK ) return( SQL_ERROR );
                sourceType=getCSqlType(appParamDesc->cType_);
                destType=fInfo->type;
                sourceLength=(int)appParamDesc->length_;
                destLength=fInfo->length;
                if(sourceType != typeUnknown && destType != typeUnknown)
                {
                    //Check if NULL is inserted
                    if((appParamDesc->indPtr_ != NULL ) && (*(SQLINTEGER *)appParamDesc->indPtr_) == SQL_NULL_DATA)
                    {
                        fsqlStmt_->setNull(paramNum);
                    }
                    else
                    {
                        //Only if both types are not the same, then we need to copy it onto intermediate buffer
                        //Else no need
                        if( (sourceType == typeString || sourceType == typeBinary) && (sourceLength <= 0))
                        {
                            if((appParamDesc->indPtr_!= NULL) && *(SQLINTEGER *)appParamDesc->indPtr_ > 0)
                                sourceLength=(int)(*(SQLINTEGER *)appParamDesc->indPtr_);
                            else if (appParamDesc->precision_ > 0)
                                sourceLength=appParamDesc->precision_;
                            else 
                            {
                                err_.set( ERROR_BUFLEN );
                                return SQL_ERROR;
                            }
                        }
                        if(destType == typeString) //|| destType == typeVarString)
                        {
                            //fsqlStmt_->allocParam(paramNum,sourceLength); // CSQL TODO
                            destLength=sourceLength;
                        }
                        if(sourceType == destType) 
				//|| (sourceType == typeString && destType == typeVarString) 
				//|| (sourceType == typeBinary && destType == typeVarBinary))
                        {
                            copyFromOdbc(fsqlStmt_, paramNum, destLength, appParamDesc->dataPtr_, sourceLength,destType); // CSQL TODO
                        } else 
                        {
                            getInputBuffer(&csqlParamDesc->dataPtr_ ,destType,destLength);
                            convertFromOdbc(sourceType,appParamDesc->dataPtr_,destType,csqlParamDesc->dataPtr_, destLength); 
                            copyFromOdbc(fsqlStmt_, paramNum, destLength, csqlParamDesc->dataPtr_, destLength, destType);
                        }
                    }
                }
                else
                {
                    err_.set(ERROR_GENERAL);
                    return SQL_ERROR;
                }
            }
            paramNum++;
        }
    }


    // Get the result
    int rowsAffected=0;
    DbRetVal rv = fsqlStmt_->execute( rowsAffected );
    
    if( rowsAffected < 0 || rv!=OK )
    {
        if( isPrepared_ ) state_ = S2; else resetStmt();
        err_.set( ERROR_GENERAL );
        /*switch(rv)
        {
            case csqlSqlErrOverflow:err_.set(ERROR_OVERFLOW);break;
            case csqlSqlErrUnderflow:err_.set(ERROR_UNDERFLOW);break;
            case csqlSqlErrTooManyTpl:err_.set(ERROR_MANY_TUP);break;
            case csqlSqlErrProjCnt:err_.set(ERROR_NUM_PROJ);break;
            case csqlSqlErrStorageAttr:err_.set(ERROR_STORAGE_ATTR);break;
            case csqlSqlErrFldCntMismatch:err_.set(ERROR_FLDCNT_MISMATCH);break;
            case csqlSqlErrSqlInternal:err_.set(ERROR_SQL_INT);break;
            case csqlSqlErrNoMatchKeyFound:err_.set(ERROR_MATCHKEY_NOTFOUND);break;
            default:
                   err_.set( ERROR_GENERAL );break;
        } */
        return( SQL_ERROR );
    }

    // Set Stmt State
    if( fsqlStmt_->isSelect() == true )
    {
        rowsAffected_ = -1;
        state_ = S5;
    }
    else 
    {
        rowsAffected_ = rowsAffected;
        state_ = S4;
    }

    // Set Dbc State to Transaction Mode.
    parentDbc_->state_ = C6;

    // AutoCommit Mode
    if( parentDbc_->autoCommit_ == SQL_AUTOCOMMIT_ON )
        parentDbc_->SQLEndTran( SQL_COMMIT );

    return( SQL_SUCCESS );
}
/*
SQLRETURN SQLExecDirect(
    SQLHSTMT StatementHandle,
    SQLCHAR *StatementText,
    SQLINTEGER TextLength)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLExecDirect");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLExecDirect( StatementText, TextLength ) );
}

SQLRETURN CSqlOdbcStmt::SQLExecDirect(
    SQLCHAR *statementText,
    SQLINTEGER textLength)
{
    SQLRETURN ret;

    // Can we proceed ?
    if( chkStateForSQLExecDirect() != SQL_SUCCESS )
        return( SQL_ERROR );

    // SQLExecDirect = SQLPrepare + SQLExecute.
    if( SQLPrepare( statementText, textLength ) != SQL_SUCCESS )
        return( SQL_ERROR );

    ret = SQLExecute();
    isPrepared_ = false;         // Set Stmt as non-prepared stmt.

    if( ret != SQL_SUCCESS )
        return( SQL_ERROR );

    return( SQL_SUCCESS );
}
*/
SQLRETURN SQLSetStmtOption(
    SQLHSTMT StatementHandle,
    SQLUSMALLINT Option,
    SQLUINTEGER Value)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLSetStmtOption");
#endif

    return  (SQLSetStmtAttr(StatementHandle, Option, (SQLPOINTER) Value, 0));
}

SQLRETURN  SQL_API SQLSetStmtAttr(SQLHSTMT StatementHandle,
           SQLINTEGER Attribute, SQLPOINTER Value,
           SQLINTEGER StringLength)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLSetStmtAttr");
#endif

    return (((CSqlOdbcStmt*)StatementHandle)->SQLSetStmtAttr(Attribute, Value,StringLength));
}

SQLRETURN CSqlOdbcStmt::SQLSetStmtAttr(
    SQLINTEGER Attribute, 
    SQLPOINTER Value,
    SQLINTEGER stringLength)
{
    CSqlOdbcError::printDbg("proxy:stmt:SQLSetStmtAttr");
    //HACK
    /*switch(Attribute)
    {
        //Values: SQL_FETCH_SINGLE_TUPLE or SQL_FETCH_MULTIPLE_TUPLES
        //Default is SQL_FETCH_SINGLE_TUPLE.
        //In SQL_FETCH_SINGLE_TUPLE mode, only a single tuple 
        //is sent from server to client in a single packet whatever be
        //the packet size. If a tuple size is 50 and network packet size
        //is 500, the remaining 450 bytes can also be used to send more 
        //in a single packet so that in the next SQLFetch call one network
        //packet transfer overhead is reduced.
	 case SQL_FETCH_MODE:
	        if(state_ <= S5)
	        //state_ > S5 means Fetch has already started on this statement.
                fetchMode_ = (SQLINTEGER)Value;
	        else
		        printf("ODBC:Error in setting fetch mode, can't set after fetch is started.\n");
	        break;
	    default:
		    printf("ODBC: Error, Stmt Option %d is not supported.\n", Attribute);
    }*/
    return (SQL_SUCCESS);
}

SQLRETURN SQLFetch(SQLHSTMT StatementHandle)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLFetch");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLFetch() );
}

SQLRETURN CSqlOdbcStmt::SQLFetch()
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLFetch() != SQL_SUCCESS )
        return( SQL_ERROR );

    void *tuple;
    tuple = fsqlStmt_->next();

    if( ! tuple ) // IF Row not found.
    {
        rowsAffected_ = 0;
        state_ = S6;
        return( SQL_NO_DATA_FOUND );
    }
    /*else if( rowsAffected != SQL_SUCCESS ) // IF Error
    {
        rowsAffected_ = -1;
        err_.set( ERROR_GENERAL );
        return( SQL_ERROR );
    }*/
    else // IF Row found.
    {
        rowsAffected_ = 1;
        if (ard_.descList_.size() > 0) {
          // Iterate through all ard_;
          CSqlOdbcDesc *appColDesc;
          ListIterator ardIter = ard_.descList_.getIterator();
          //Get the input parameter data
          CSqlOdbcDesc *csqlColDesc;
          ListIterator irdIter = ird_.descList_.getIterator();

          DataType sourceType = typeUnknown,destType = typeUnknown;
          int colNum=-1,sourceLength=-1,destLength=-1;
          SQLINTEGER ind;
          void* sourceData = NULL;
          while(ardIter.hasElement() || irdIter.hasElement()) {
            appColDesc = (CSqlOdbcDesc *) ardIter.nextElement();
            csqlColDesc = (CSqlOdbcDesc *) irdIter.nextElement();
            
            colNum = appColDesc->col_ - 1;
            sourceType = (DataType)csqlColDesc->cType_;  
            destType = getCSqlType(appColDesc->cType_);
            sourceLength = (int)csqlColDesc->length_;
            destLength = (int)appColDesc->length_;
            if( sourceType != typeUnknown && destType != typeUnknown )
            {
                sourceData = fsqlStmt_->getFieldValuePtr( colNum );
                if(fsqlStmt_->isFldNull((char*)csqlColDesc->colName_) || 
                                                     sourceData == NULL )
                {
                    if (appColDesc->indPtr_ != NULL)
                        *((SQLINTEGER *)(appColDesc->indPtr_))=SQL_NULL_DATA;
                }
                else
                {
                    /*if( sourceType == csqlSqlTvarBinary)
                        sourceLength=resultSet_->getDataLength(colNum); */
                    if (sourceType == typeString ) // CSQL TODO - handle varchar also
		    {
                        sourceLength=(int)(strlen((char *) sourceData ));
                        if(appColDesc->indPtr_ != NULL)
                            *((SQLINTEGER *)(appColDesc->indPtr_))=copyToOdbc(appColDesc->dataPtr_,destLength,
                              sourceData,sourceLength, sourceType, destType);
                        else
                            copyToOdbc(appColDesc->dataPtr_,destLength,sourceData,
                                    sourceLength, sourceType, destType);
                    }
                    else
                    {
                        //convert(sourceType,sourceData,destType, csqlColDesc->dataPtr_,sourceLength,destLength);
                        if(appColDesc->indPtr_ != NULL){
                            *((SQLINTEGER *)(appColDesc->indPtr_))=
			    copyToOdbc(appColDesc->dataPtr_,destLength, sourceData, sourceLength, sourceType, destType);
                            }
                        else
                            copyToOdbc(appColDesc->dataPtr_,destLength, sourceData, sourceLength, sourceType,destType);
                    } 

		    // CSQL TODO - handle varstring, binary, varbinary
                    if( sourceType == typeString && sourceLength > destLength )
                        err_.set( ERROR_DATATRUNC );
                }
            }
          }
        }
        state_ = S6;
    }
    if(err_.csqlErrCode ==  ERROR_DATATRUNC)
        return (SQL_SUCCESS_WITH_INFO);
        
    return( SQL_SUCCESS );
}

SQLRETURN SQLCloseCursor(SQLHSTMT StatementHandle)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLCloseCursor");
#endif
    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLCloseCursor() );
}

SQLRETURN CSqlOdbcStmt::SQLCloseCursor()
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLCloseCursor() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Close the cursor
    fsqlStmt_->close();
    state_ = S3;   
    return( SQL_SUCCESS );
}

SQLRETURN SQLSetCursorName(
    SQLHSTMT StatementHandle,
    SQLCHAR *CursorName,
    SQLSMALLINT NameLength)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLSetCursorName");
#endif
    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLSetCursorName( CursorName, NameLength ) );
}

SQLRETURN CSqlOdbcStmt::SQLSetCursorName(
    SQLCHAR *cursorName,
    SQLSMALLINT nameLength)
{
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLSetCursorName() != SQL_SUCCESS )
        return( SQL_ERROR );

    // Invalid Stmt Length.
    if( nameLength < 0  && nameLength != SQL_NTS )
    {
        err_.set( ERROR_INVARGVAL );
        return( SQL_ERROR );
    }

    // Validate Parameters
    if( cursorName == 0 || cursorName[0] == '\0' || strlen( (char*) cursorName ) > SQL_MAX_CURSOR_NAME_LEN ||
        nameLength > SQL_MAX_CURSOR_NAME_LEN )
    {
        err_.set( ERROR_CURNAME );
        return( SQL_ERROR );
    }

    // Check for duplicate Name
    ListIterator iter = parentDbc_->stmtList_.getIterator();
    CSqlOdbcStmt *stmtElem = NULL;
    while (iter.hasElement()) {
        stmtElem = (CSqlOdbcStmt *) iter.nextElement();
        if(stmtElem != this ) {
            if( strcmp((char*)cursorName, (char*)stmtElem->cursorName_) == 0) {
                err_.set( ERROR_DUP_CURNAME );
                return( SQL_ERROR );
            }
        }
    }
    // Copy name
    strcpy( (char*) cursorName_, (char*) cursorName );
    return( SQL_SUCCESS );
}

SQLRETURN SQLGetCursorName(
    SQLHSTMT StatementHandle,
    SQLCHAR *CursorName,
    SQLSMALLINT BufferLength,
    SQLSMALLINT *NameLength)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLGetCursorName");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLGetCursorName( CursorName, BufferLength, NameLength ) );
}
SQLRETURN CSqlOdbcStmt::SQLGetCursorName(
    SQLCHAR *cursorName,
    SQLSMALLINT bufferLength,
    SQLSMALLINT *nameLength)
{
    // Can we proceed ?
    if( chkStateForSQLGetCursorName() != SQL_SUCCESS )
        return( SQL_ERROR );
    if (NULL == cursorName || NULL == nameLength)
    {
       err_.set(ERROR_INVARGVAL);
       return (SQL_ERROR);
    }

    if( cursorName_[0] == '\0' )
    {
        err_.set( ERROR_NOCURNAME );
        return( SQL_ERROR );
    }
    
    // Copy
    *nameLength = (short)strlen( (char*) cursorName_ );
    if( *nameLength > bufferLength )    *nameLength = bufferLength;
    strncpy( (char*) cursorName, (char*) cursorName_, *nameLength );
    cursorName[ *nameLength ] = '\0';

    // Did truncate ?
    if( bufferLength < strlen( (char*) cursorName_ ) )
    {
        err_.set( ERROR_DATATRUNC );
        return( SQL_SUCCESS_WITH_INFO );
    }

    return( SQL_SUCCESS );
}

SQLRETURN SQLNumResultCols(
    SQLHSTMT StatementHandle,   // IN
    SQLSMALLINT *ColumnCount)   // OUT
{
#ifdef DEBUG
    printError(ErrWarning, "SQLNumResultCols");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLNumResultCols( ColumnCount ) );
}

SQLRETURN CSqlOdbcStmt::SQLNumResultCols(
    SQLSMALLINT *columnCount)   // OUT
{
    // Start with NO_ERR
    err_.set( NO_ERR );
    // Can we proceed ?
    if( chkStateForSQLNumResultCols() != SQL_SUCCESS )
        return( SQL_ERROR );
    if (NULL == columnCount)
    {
       err_.set(ERROR_INVARGVAL);
       return (SQL_ERROR);
    }

    // If DML
    if( fsqlStmt_->isSelect() == false )
    {
        *columnCount=0;
        return (SQL_SUCCESS);
    }
    ResultSetPlan pl = fsqlStmt_->getResultSetPlan();
    if(pl != Normal)
    {
        *columnCount =getNumResultset(pl);
        return( SQL_SUCCESS );
    }
    // If Select
    SQLSMALLINT count = fsqlStmt_->noOfProjFields();
    if( count < 1 ) // Assume atleast one column is projected
        return( SQL_ERROR );

    // Fill Column Count
    *columnCount = count;

    return( SQL_SUCCESS );
}

SQLRETURN  SQL_API SQLRowCount(
    SQLHSTMT StatementHandle,   // IN
    SQLINTEGER *RowCount)       // OUT
{
#ifdef DEBUG
    printError(ErrWarning, "SQLRowCount");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLRowCount( RowCount ) );
}

SQLRETURN CSqlOdbcStmt::SQLRowCount(
    SQLINTEGER *rowCount)   // OUT
{ // TODO
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLRowCount() != SQL_SUCCESS )
        return( SQL_ERROR );

    if(rowCount == NULL)
        return SQL_SUCCESS;

    if( state_ == S4 ) // For INSERT/DELETE/UPDATE
        *rowCount = (SQLINTEGER) rowsAffected_;
    else if( state_ == S5 ) // For SELECT before SQLFetch()
    {
        *rowCount = (SQLINTEGER) 0;  
	// CSQL TODO - Think if you really want to do this!!!

        /*CSqlOdbcError::printDbg("proxy:stmt:getResultSet");
        CSqlResultSet *resultSet_ = fsqlStmt_.getResultSet();
        if( resultSet_->next() != csqlSqlErrNoTuple )
           *rowCount = (SQLINTEGER) 1;

        resultSet_->close();
        resultSet_->open(); */
    }
    else if( state_ == S6 )   // For SELECT after SQLFetch();
        *rowCount = (SQLINTEGER) rowsAffected_;

    return( SQL_SUCCESS );
}

SQLRETURN  SQLDescribeCol(
    SQLHSTMT     StatementHandle,
    SQLUSMALLINT ColumnNumber, 
    SQLCHAR      *ColumnName,
    SQLSMALLINT  BufferLength, 
    SQLSMALLINT  *NameLength,
    SQLSMALLINT  *DataType, 
    SQLUINTEGER  *ColumnSize,
    SQLSMALLINT  *DecimalDigits, 
    SQLSMALLINT  *Nullable)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLDescribeCol");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLDescribeCol( ColumnNumber, ColumnName, BufferLength, 
            NameLength, DataType, ColumnSize, DecimalDigits, Nullable) );
}

SQLRETURN  CSqlOdbcStmt::SQLDescribeCol(
    SQLUSMALLINT columnNumber, 
    SQLCHAR      *columnName,
    SQLSMALLINT  bufferLength, 
    SQLSMALLINT  *nameLength,
    SQLSMALLINT  *dataType, 
    SQLUINTEGER  *columnSize,
    SQLSMALLINT  *decimalDigits, 
    SQLSMALLINT  *nullable)
{
    int     nameLen;
    int     type;
    int     colSize;
    int     deciDigits;
    int     isNullable;
    
    // Start with NO_ERR
    err_.set( NO_ERR );
    // Can we proceed ?
    if( chkStateForSQLDescribeCol() != SQL_SUCCESS )
        return( SQL_ERROR );
    
    if( columnNumber < 1 )
    {
        err_.set( ERROR_COLNUM );
        return( SQL_ERROR );
    }

    if(columnName == NULL) {
        err_.set( ERROR_INVARGVAL );
        return( SQL_ERROR );
    }

    DbRetVal rv = fsqlStmt_->getProjFldInfo(columnNumber, fInfo);
    if (rv != OK) {
        err_.set( ERROR_COLNUM );
        return( SQL_ERROR );
    }
    if (bufferLength <IDENTIFIER_LENGTH) {
       //strncpy( (char*)columnName, (char*)fInfo->fldName, bufferLength );
       //columnName[bufferLength-1] ='\0';
       err_.set (ERROR_BUFLEN);
       return (SQL_ERROR);
    }else {
       Table::getFieldNameAlone((char*)fInfo->fldName, (char*)columnName);
    }

    if(nameLength != NULL)
        *nameLength=(short)strlen((const char*)columnName); // HARDCODED - TO DO, need support for n/w layer & sql layer
    if(dataType != NULL)
        *dataType = (SQLSMALLINT) getSQLType(fInfo->type); // Need to convert from SQL<->ODBC - TO DO
    if(columnSize != NULL)
    {
        *columnSize = (SQLUINTEGER) fInfo->length;
        SQLSMALLINT sqlType=getSQLType(fInfo->type);
        if(sqlType == SQL_CHAR )
            *columnSize = *columnSize -1;
    }
    
    /*if(decimalDigits != NULL) // CSQL TODO
        *decimalDigits = (SQLSMALLINT) fsqlStmt_->getPrecision( columnNumber-1 );*/ 
    if (decimalDigits !=NULL) *decimalDigits = 0; 
    if(nullable != NULL)
    {
        if (fInfo->isNull) 
            *nullable = SQL_NO_NULLS ;
        else 
            *nullable = SQL_NULLABLE ;
    }
    return( SQL_SUCCESS );
}

SQLRETURN  SQLColAttributes(
        SQLHSTMT     StatementHandle,
        SQLUSMALLINT ColumnNumber, 
        SQLUSMALLINT     FieldIdentifier,
        SQLPOINTER     CharacterAttributePtr,
        SQLSMALLINT     BufferLength,
        SQLSMALLINT *StringLengthPtr,
        SQLINTEGER *NumericAttributePtr)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLColAttributes");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLColAttribute(ColumnNumber ,FieldIdentifier , 
            CharacterAttributePtr, BufferLength, StringLengthPtr, (SQLPOINTER)NumericAttributePtr) );
}

SQLRETURN  SQLColAttribute(
        SQLHSTMT     StatementHandle,
        SQLUSMALLINT ColumnNumber, 
        SQLUSMALLINT     FieldIdentifier,
        SQLPOINTER     CharacterAttributePtr,
        SQLSMALLINT     BufferLength,
        SQLSMALLINT *     StringLengthPtr,
        SQLPOINTER NumericAttributePtr)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLColAttribute");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLColAttribute(ColumnNumber ,FieldIdentifier , 
            CharacterAttributePtr, BufferLength, StringLengthPtr, NumericAttributePtr) );
}

SQLRETURN  CSqlOdbcStmt::SQLColAttribute(
        SQLUSMALLINT columnNumber, 
        SQLUSMALLINT     fieldIdentifier,
        SQLPOINTER     characterAttributePtr,
        SQLSMALLINT     bufferLength,
        SQLSMALLINT *     stringLengthPtr,
        SQLPOINTER numericAttributePtr)
{
    int     nameLen;
    int     type;
    int     colSize;
    int     deciDigits;
    int     isNullable;
    
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLDescribeCol() != SQL_SUCCESS )
        return( SQL_ERROR );
    
    if( columnNumber < 1 )
    {
        err_.set( ERROR_COLNUM );
        return( SQL_ERROR );
    }
    // If DML
    if( fsqlStmt_->isSelect() == false )
        return( SQL_ERROR );

    fsqlStmt_->getProjFldInfo(columnNumber, fInfo);

    // If SELECT
    if(columnNumber > fsqlStmt_->noOfProjFields())
    {
        err_.set( ERROR_COLNUM );
        return( SQL_ERROR );
    }
    
    switch(fieldIdentifier)
    {
        case SQL_DESC_NAME:
        case SQL_COLUMN_LABEL:
        case SQL_COLUMN_NAME:
            if(characterAttributePtr != NULL)
            {
                strncpy( (char*)characterAttributePtr, (char*)fInfo->fldName, bufferLength);
                if(stringLengthPtr != NULL)
                    *stringLengthPtr=(short)strlen((char*)fInfo->fldName);
            }
            break;
        case SQL_DESC_COUNT:
        case SQL_COLUMN_COUNT:
            if(numericAttributePtr != NULL)
                *(SQLINTEGER*)numericAttributePtr=fsqlStmt_->noOfProjFields();
            break;
        case SQL_DESC_TYPE:
        case SQL_COLUMN_TYPE:
            if(numericAttributePtr != NULL)
                *(SQLINTEGER *)numericAttributePtr=getSQLType(fInfo->type);
            break;
        case SQL_DESC_LENGTH:
        case SQL_COLUMN_LENGTH:
            if(numericAttributePtr != NULL)
            {
                SQLSMALLINT sqlType=getSQLType(fInfo->type);
                *(SQLINTEGER *)numericAttributePtr=(SQLUINTEGER) fInfo->length;
                if(sqlType == SQL_CHAR)
                    *(SQLINTEGER *)numericAttributePtr=*(SQLINTEGER *)numericAttributePtr -1;
            }
            break;
        case SQL_DESC_PRECISION:
        case SQL_COLUMN_PRECISION:
            /*if(numericAttributePtr != NULL) // CSQL TODO
                *(SQLINTEGER *)numericAttributePtr=(SQLSMALLINT) rsMetaData->getPrecision( columnNumber-1 ); */
            break;
        case SQL_DESC_SCALE:
        case SQL_COLUMN_SCALE:
            /*if(numericAttributePtr != NULL) // CSQL TODO
                *(SQLINTEGER*)numericAttributePtr=(SQLSMALLINT) rsMetaData->getScale( columnNumber-1 );*/
            break;
        case SQL_DESC_NULLABLE:
        case SQL_COLUMN_NULLABLE:
            /*if(numericAttributePtr != NULL) // CSQL TODO 
                *(SQLINTEGER*)numericAttributePtr=(SQLSMALLINT) rsMetaData->isNullable( columnNumber-1 )?SQL_NULLABLE_N:SQL_NO_NULLS_N;*/
            break;
        case SQL_DESC_UNSIGNED:
            if(numericAttributePtr != NULL)
            {
                SQLSMALLINT sqlType=getSQLType(fInfo->type);
                if((sqlType != SQL_TIME) && (sqlType != SQL_DATE) && (sqlType != SQL_TIMESTAMP)
                    && (sqlType != SQL_CHAR) && (sqlType != SQL_VARCHAR) && (sqlType != SQL_BINARY)
                    && (sqlType != SQL_VARBINARY) && (sqlType != SQL_BIT))
                    *(SQLINTEGER*)numericAttributePtr=SQL_FALSE;
                else
                    *(SQLINTEGER*)numericAttributePtr=SQL_TRUE;
            }
            break;
        case SQL_DESC_FIXED_PREC_SCALE:
            if(numericAttributePtr != NULL)
                *(SQLINTEGER*)numericAttributePtr=SQL_FALSE;
            break;
        case SQL_DESC_TYPE_NAME:
            if(characterAttributePtr != NULL)
            {
                SQLSMALLINT sqlType=getSQLType(fInfo->type);
                strncpy((char*)characterAttributePtr,(char *)(getSQLTypeName(sqlType)),bufferLength);
                if(stringLengthPtr != NULL)
                    *stringLengthPtr=(int)strlen((char *)getSQLTypeName(sqlType));
            }
            break;
        case SQL_DESC_UPDATABLE:
                if(numericAttributePtr != NULL)
                    *(SQLINTEGER*)numericAttributePtr=SQL_ATTR_READWRITE_UNKNOWN;
            break;
        case SQL_DESC_AUTO_UNIQUE_VALUE:  
            if(numericAttributePtr != NULL)
                *(SQLINTEGER*)numericAttributePtr=SQL_FALSE;
            break;
        case SQL_DESC_CASE_SENSITIVE:  
            if(numericAttributePtr != NULL)
            {
                SQLSMALLINT sqlType=getSQLType(fInfo->type);
                if((sqlType != SQL_CHAR) && (sqlType != SQL_VARCHAR))
                    *(SQLINTEGER*)numericAttributePtr=SQL_FALSE;
                else
                    *(SQLINTEGER*)numericAttributePtr=SQL_TRUE;
            }
            break;
        case SQL_DESC_SEARCHABLE:
            if(numericAttributePtr != NULL)
            {
                SQLSMALLINT sqlType=getSQLType(fInfo->type);
                if((sqlType != SQL_CHAR) && (sqlType != SQL_VARCHAR))
                    *(SQLINTEGER*)numericAttributePtr=SQL_PRED_BASIC;
                else
                    *(SQLINTEGER*)numericAttributePtr=SQL_PRED_SEARCHABLE;
            }
            break;
       case SQL_COLUMN_DISPLAY_SIZE: {
            SQLSMALLINT sqlType=getSQLType(fInfo->type);
            if(numericAttributePtr != NULL) {
                 if(sqlType == SQL_CHAR || sqlType == SQL_BINARY)
                    *(SQLINTEGER *)numericAttributePtr=fInfo->length;
                 else
                    *(SQLINTEGER *)numericAttributePtr=20;
            }
            break;
            }
       default:
            break;
    }
    if(stringLengthPtr != NULL)
    {
        if(*stringLengthPtr > bufferLength)
        {
            err_.set( ERROR_DATATRUNC );
            return( SQL_SUCCESS_WITH_INFO );
        }
    }
    return( SQL_SUCCESS );
}

SQLRETURN SQLNumParams(
        SQLHSTMT     StatementHandle,
        SQLSMALLINT *     ParameterCountPtr)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLNumParams");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLNumParams(ParameterCountPtr) );
}

SQLRETURN CSqlOdbcStmt::SQLNumParams(
        SQLSMALLINT *     ParameterCount)
{
    // Start with NO_ERR
    err_.set( NO_ERR );
    // Can we proceed ?
    if( chkStateForSQLNumParams() != SQL_SUCCESS )
        return( SQL_ERROR );
    if(ParameterCount == NULL)
        return (SQL_ERROR);
    *ParameterCount=fsqlStmt_->noOfParamFields();

    return SQL_SUCCESS;
}

SQLRETURN SQLDescribeParam(
        SQLHSTMT     StatementHandle,
        SQLUSMALLINT     ParameterNumber,
        SQLSMALLINT *     DataTypePtr,
        SQLUINTEGER *     ParameterSizePtr,
        SQLSMALLINT *     DecimalDigitsPtr,
        SQLSMALLINT *     NullablePtr)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLDescribeParam");
#endif

    // Is Stmt valid ?
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLDescribeParam(ParameterNumber,DataTypePtr,
                ParameterSizePtr,DecimalDigitsPtr,NullablePtr ) );
}
SQLRETURN CSqlOdbcStmt::SQLDescribeParam(
         SQLUSMALLINT     paramNumber,
         SQLSMALLINT *     dataType,
          SQLUINTEGER *     paramSize,
          SQLSMALLINT *     decimalDigits,
           SQLSMALLINT *     isNullable)
{
    
    // Start with NO_ERR
    err_.set( NO_ERR );

    // Can we proceed ?
    if( chkStateForSQLDescribeParam() != SQL_SUCCESS )
        return( SQL_ERROR );
    
    if( paramNumber < 1 )
    {
        err_.set( ERROR_PARAMNUM);
        return( SQL_ERROR );
    }

    //CSqlOdbcError::printDbg("proxy:stmt:getMetaData");
    //CSqlParamMetaData *paramMetaData = fsqlStmt_->getParamMetaData();
    if(paramNumber > fsqlStmt_->noOfParamFields())
    {
        err_.set( ERROR_PARAMNUM );
        return( SQL_ERROR );
    }

    if( fsqlStmt_->getParamFldInfo( paramNumber, fInfo ) != OK ) {
       return( SQL_ERROR );
    }
    if(dataType != NULL)
        *dataType = (SQLSMALLINT) getSQLType(fInfo->type); 
    if(paramSize != NULL)
    {
        *paramSize = (SQLUINTEGER) fInfo->length;
        SQLSMALLINT sqlType=getSQLType(fInfo->type);
        if(sqlType == SQL_CHAR )
            *paramSize= *paramSize -1;
    }
    /*if(decimalDigits != NULL) // CSQL TODO
        *decimalDigits = (SQLSMALLINT) paramMetaData->getPrecision( paramNumber-1 );*/
    if (NULL != decimalDigits) *decimalDigits = 0;
    if(isNullable) {
        if (fInfo->isNull) 
            *isNullable = SQL_NO_NULLS ;
        else
            *isNullable = SQL_NULLABLE ;
    }

    return( SQL_SUCCESS );
}

// Resets the Stmt to initial state. As if newly allocated.
void CSqlOdbcStmt::resetStmt( void ) // TO DO
{
    SQLFreeStmt( SQL_CLOSE );
    SQLFreeStmt( SQL_UNBIND );
    SQLFreeStmt( SQL_RESET_PARAMS );
    if (fsqlStmt_) { fsqlStmt_->free(); delete fsqlStmt_; fsqlStmt_ = NULL; }
    isPrepared_ = false;
    state_ = S1;
}

SQLRETURN SQLTables(
     SQLHSTMT     StatementHandle,
     SQLCHAR *     CatalogName,
     SQLSMALLINT     NameLength1,
     SQLCHAR *     SchemaName,
     SQLSMALLINT     NameLength2,
     SQLCHAR *     TableName,
     SQLSMALLINT     NameLength3,
     SQLCHAR *     TableType,
     SQLSMALLINT     NameLength4)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLTables");
#endif

 if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLTables(CatalogName,SchemaName,TableName,TableType ) );
}

SQLRETURN CSqlOdbcStmt::SQLTables( 
     SQLCHAR *     CatalogName,
     SQLCHAR *     SchemaName,
     SQLCHAR *     TableName,
     SQLCHAR *     TableType )
{
   // Start with NO_ERR
    err_.set( NO_ERR );
    SQLRETURN ret = SQL_SUCCESS;
    ret = SQLPrepare((SQLCHAR *)"GetAllTables",  strlen("GetAllTables"));  
    if( ret != SQL_SUCCESS )  return (ret);
    ret = SQLExecute();   
    if( ret != SQL_SUCCESS )  return (ret);
    return( SQL_SUCCESS );
 
}

SQLRETURN SQLColumns(
     SQLHSTMT     StatementHandle,
     SQLCHAR *     CatalogName,
     SQLSMALLINT     NameLength1,
     SQLCHAR *     SchemaName,
     SQLSMALLINT     NameLength2,
     SQLCHAR *     TableName,
     SQLSMALLINT     NameLength3,
     SQLCHAR *     ColumnName,
     SQLSMALLINT     NameLength4)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLColumns");
#endif

     if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLColumns(CatalogName,SchemaName,TableName,ColumnName ) );

}

SQLRETURN CSqlOdbcStmt::SQLColumns( 
     SQLCHAR *     CatalogName,
     SQLCHAR *     SchemaName,
     SQLCHAR *     TableName,
     SQLCHAR *     ColumnName )
{
    SQLRETURN ret = SQL_SUCCESS;
    if (NULL == TableName)
    {
       err_.set(ERROR_INVARGVAL);
       return (SQL_ERROR);
    }
    char str[256]="describe ";
    strcat(str,(char*)TableName); 
    ret = SQLPrepare((SQLCHAR *)str,  strlen(str));
    if( ret != SQL_SUCCESS )  return (ret);
    ret = SQLExecute();
    if( ret != SQL_SUCCESS )  return (ret);
    return( SQL_SUCCESS );
}

SQLRETURN SQLPrimaryKeys(
     SQLHSTMT     StatementHandle,
     SQLCHAR *     CatalogName,
     SQLSMALLINT     NameLength1,
     SQLCHAR *     SchemaName,
     SQLSMALLINT     NameLength2,
     SQLCHAR *     TableName,
     SQLSMALLINT     NameLength3)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLPrimaryKeys");
#endif

    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLPrimaryKeys(CatalogName,SchemaName,TableName ) );

}
SQLRETURN CSqlOdbcStmt::SQLPrimaryKeys(
     SQLCHAR *     CatalogName,
     SQLCHAR *     SchemaName,
     SQLCHAR *     TableName)
{
    SQLRETURN ret = SQL_SUCCESS;
    char str[256]="getprimarykey  ";
    if (NULL == TableName)
    {
       err_.set(ERROR_INVARGVAL);
       return (SQL_ERROR);
    }
    strcat(str,(char*)TableName);
    ret = SQLPrepare((SQLCHAR *)str,  strlen(str));
    if( ret != SQL_SUCCESS )  return (ret);
    ret = SQLExecute();
    if( ret != SQL_SUCCESS )  return (ret);
    return( SQL_SUCCESS );
}

int CSqlOdbcStmt::getNumResultset(ResultSetPlan plan)
{
    switch(plan)
    {
        case GetTables:
            return 5;
        case GetColumns:
            return 18;
        case GetIndexes:
            return 13;
        case GetPriIndex:
            return 6;
        default :
            break; 
    };
}

SQLRETURN SQLGetData(SQLHSTMT     StatementHandle,  SQLUSMALLINT  ColumnNumber, SQLSMALLINT   TargetType,  SQLPOINTER  TargetValuePtr, SQLLEN     BufferLength, SQLLEN * StrLen_or_IndPtr)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLGetData");
#endif

     if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLGetData(ColumnNumber,TargetType,TargetValuePtr,BufferLength,StrLen_or_IndPtr) );

}

SQLRETURN CSqlOdbcStmt::SQLGetData(SQLUSMALLINT     ColumnNumber, SQLSMALLINT     TargetType, SQLPOINTER     TargetValuePtr,SQLLEN     BufferLength, SQLLEN *     StrLen_or_IndPtr)
{
     if(fsqlStmt_->isFldNull(ColumnNumber)){
          if(NULL != StrLen_or_IndPtr)
              *((SQLINTEGER *)StrLen_or_IndPtr ) = SQL_NULL_DATA;
         return (SQL_SUCCESS);
     }
     if (NULL == TargetValuePtr)
     {
        err_.set(ERROR_INVARGVAL);
        return (SQL_ERROR);
     }
     void* sourceData = NULL;
     DataType sourceType = typeUnknown, destType = typeUnknown;
     DbRetVal rv = fsqlStmt_->getProjFldInfo(ColumnNumber, fInfo);
     if (rv != OK) {
         return SQL_INVALID_HANDLE;
     }
     sourceType = fInfo->type;
     sourceData = fsqlStmt_->getFieldValuePtr(ColumnNumber-1);
     destType = getCSqlType( TargetType );
     int sourceLength=-1;
     if(sourceType == typeString)
     {
         sourceLength=strlen((char *)sourceData);
         if (NULL != StrLen_or_IndPtr)
             *((SQLINTEGER *)StrLen_or_IndPtr) = copyToOdbc(TargetValuePtr,
                      BufferLength,sourceData,sourceLength,sourceType,destType);
     } else
     {
         copyToOdbc(TargetValuePtr,BufferLength,sourceData,sourceLength,sourceType,destType);
     }
     return (SQL_SUCCESS);
}


SQLRETURN SQLGetTypeInfo(
     SQLHSTMT     StatementHandle,
     SQLSMALLINT     DataType)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLGetTypeInfo");
#endif

    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLGetTypeInfo(DataType));

}
SQLRETURN CSqlOdbcStmt::SQLGetTypeInfo(SQLSMALLINT     DataType)
{
     return (SQL_SUCCESS);
}


SQLRETURN SQLStatistics(
     SQLHSTMT     StatementHandle,
     SQLCHAR *     CatalogName,
     SQLSMALLINT     NameLength1,
     SQLCHAR *     SchemaName,
     SQLSMALLINT     NameLength2,
     SQLCHAR *     TableName,
     SQLSMALLINT     NameLength3,
     SQLUSMALLINT     Unique,
     SQLUSMALLINT     Reserved)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLStatistics");
#endif

     if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLStatistics(CatalogName,SchemaName,TableName,Unique,Reserved));

}
SQLRETURN CSqlOdbcStmt::SQLStatistics(
     SQLCHAR *     CatalogName,
     SQLCHAR *     SchemaName,
     SQLCHAR *     TableName,
     SQLUSMALLINT     Unique,
     SQLUSMALLINT     Reserved)
{
    SQLRETURN ret = SQL_SUCCESS;
    if(Unique != SQL_INDEX_ALL ) { printf("NOT SUPPORTED "); return (SQL_ERROR);}
    if (NULL == TableName)
    {
       err_.set(ERROR_INVARGVAL);
       return (SQL_ERROR);
    }

    char str[256]="describe index ";
    strcat(str,(char*)TableName);
    ret = SQLPrepare((SQLCHAR *)str,  strlen(str));
    if( ret != SQL_SUCCESS )  return (ret);
    ret = SQLExecute();
    if( ret != SQL_SUCCESS )  return (ret);
    return( SQL_SUCCESS );
}

SQLRETURN SQLForeignKeys(
     SQLHSTMT     StatementHandle,
     SQLCHAR *     PKCatalogName,
     SQLSMALLINT     NameLength1,
     SQLCHAR *     PKSchemaName,
     SQLSMALLINT     NameLength2,
     SQLCHAR *     PKTableName,
     SQLSMALLINT     NameLength3,
     SQLCHAR *     FKCatalogName,
     SQLSMALLINT     NameLength4,
     SQLCHAR *     FKSchemaName,
     SQLSMALLINT     NameLength5,
     SQLCHAR *     FKTableName,
     SQLSMALLINT     NameLength6)
{
#ifdef DEBUG
    printError(ErrWarning, "SQLForeignKeys");
#endif
    if( PKCatalogName!=NULL || FKCatalogName!=NULL ){
            if(strcmp((char*)PKCatalogName,"csql")!=0 || strcmp((char*)PKCatalogName,"csql")!=0){
                //error
                printf("Error\n");
            }
    }
    if( isValidHandle( (CSqlOdbcStmt*) StatementHandle, SQL_HANDLE_STMT ) != SQL_SUCCESS )
        return( SQL_INVALID_HANDLE );

    return( ((CSqlOdbcStmt*) StatementHandle)->SQLForeignKeys(PKTableName, FKTableName));
}

SQLRETURN CSqlOdbcStmt::SQLForeignKeys(
     SQLCHAR *     PKTableName,
     SQLCHAR *     FKTableName)
{
    SQLRETURN ret = SQL_SUCCESS;
    if(PKTableName!=NULL && FKTableName!=NULL) { 
        printf("NOT SUPPORTED "); 
        return (SQL_ERROR);
    }
    char str[256];
    if(PKTableName!=NULL && FKTableName==NULL){
        sprintf(str,"ExportedKey %s;",(char*)PKTableName);
    }
    else if(NULL == PKTableName && FKTableName!=NULL){
        sprintf(str,"ImportedKey %s;",(char*)FKTableName);
    }
    ret = SQLPrepare((SQLCHAR *)str,  strlen(str));
    if( ret != SQL_SUCCESS )  return (ret);
    ret = SQLExecute();
    if( ret != SQL_SUCCESS )  return (ret);
    return( SQL_SUCCESS );
}

