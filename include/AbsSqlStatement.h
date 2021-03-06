/***************************************************************************
 *                                                                         *
 *    Copyright (C) Lakshya Solutions Ltd. All rights reserved.            *
 *                                                                         *
 ***************************************************************************/

#ifndef ABSSQLSTATEMENT_H
#define ABSSQLSTATEMENT_H
#include<AbsSqlConnection.h>
#include<Info.h>
#include<DataType.h>
class Statement;
class ParsedData;
#ifndef STMT_TYPE
#define STMT_TYPE
enum StatementType
{
    UnknownStatement,
    SelectStatement,
    InsertStatement,
    UpdateStatement,
    DeleteStatement,
    CreateTableStatement,
    DropTableStatement,
    CreateIndexStatement,
    DropIndexStatement,
    CacheTableStatement,
    CompactTableStatement,
    CopyTableStatement,
    MetaStatement,
    UserStatement,
    MgmtStatement
};
#endif


/**
* @class AbsSqlStatement
*
* @brief Handle to the sql statement.
* It is used to execute queries and return the values from the database<br>
* Sql Statement is fed to the prepare method first and then it should be executed. <br/>
* Functionality: <br/>
*     1.Input values for insert statement <br/>
*     2.Iterator for retrieving rows from the table <br/>
*     3.Parameter support for performance.<br/>
* <br/>
* 
*/
class DllExport AbsSqlStatement
{
    protected:
    AbsSqlStatement(){}
    AbsSqlStatement *innerStmt;
    AbsSqlConnection *con;
    public:
    void setInnerStatement(AbsSqlStatement *stmt) { innerStmt = stmt; }
    AbsSqlStatement *getInnerStatement() { return innerStmt; }
    /** sets connection handle to be used for subsequent operations
    *   @param con SqlConnection*
    */
    virtual void setConnection(AbsSqlConnection *conn) { con = conn; }

    /** compiles the sql statement. It calls the parser and tokenizes the statement 
    * into logical plan. This method sets the statement string which needs to be executed.
    * free method needs to be called, if application wants to use the same handle to compile
    * another sql statement.
    * @param stmt sql statement string
    * @returns DbRetVal
    */
    virtual DbRetVal prepare(char *stmt) = 0;
    
    /** Executes directly for non parameterized statements **/
    virtual DbRetVal executeDirect(char *stmt) = 0;

    /** Retrieves the tablename of the prepared statement
    * Used internally to get the tablename of the non select DML stmts
    * @returns char* tablename
    */
    virtual char* getTableName()=0;

    /** executes the sql statement. For insert, update, delete queries execute performs the
    * required operation on the table. 
    * For Select queries, application should call execute before they start fetching
    * the values from the table.This starts scan on the table.
    * @param rowsAffect number of rows affected by the sql statement
    * @returns DbRetVal
    */
    virtual DbRetVal execute(int &rowsAffect)=0;

    /**fetches the next tuple from the result of the execution of sql select query.
    * execute should be called before calling this method. Application buffer should be 
    * binded to get the tuple values.
    * @returns void* NULL if there is no tuple.
    */
    virtual void* fetch() = 0;
    virtual void* fetch(DbRetVal &rv) = 0; 

    /**fetches the next tuple from the result of the execution of sql select query 
    * and prints it to stdout.
    * execute should be called before calling this method.
    * @returns void* NULL if there is no tuple.
    */
    virtual void* fetchAndPrint(bool SQL) = 0;


    /** binds application buffer to the specified parameter position in the sql statement. 
    * This method should be called for all the parameters in the sql statement.
    * Parameters shall be specified for predicate for select, update, delete statements.
    * Parameters shall be specified for field list value in SET of update statements. 
    * If value is not set for all parameters, execute will return error.
    * <br/>
    *   @param pos  position of the parameter in the statement
    *   @param val  address of the application buffer. Memory should be allocated by
    *               the application before binding the buffer.
    */
    virtual DbRetVal bindParam(int pos, void*) = 0;

    /** binds application buffer to the specified field position of the projection list 
    *  in the select query or for fields in the insert statement. 
    *  This method should be called for select queries, insert, update statements.
    *  Before executing select queries, required fields must be binded first.
    *  Before executing insert statement, required fields must be binded first.
    *  Before executing update statement, required fields to be updated must be 
    *  binded first.
    * <br/>
    *   @param pos  position in the projection list
    *   @param val  address of the application buffer. Memory should be allocated by
    *               the application before binding the buffer.
    */
    virtual DbRetVal bindField(int pos, void* val) = 0;

    /** same as fetch, but does not populate bindFieldValues
    * @returns address void*
    */
    virtual void* next() = 0;

    /**Closes the iterator and makes the statement ready for another execution
    * @returns DbRetVal
    */
    virtual DbRetVal close() = 0;

    /** get FieldValue->value ptr after fetch is done.
    * @returns address void*
    */
    virtual void* getFieldValuePtr( int pos )  = 0;
    virtual void* getFieldValuePtr( char *name )  = 0;

    /**Frees all the resources held for the sql statement. Needs to be called before calling prepare again on the same statement handle.
    * @returns DbRetVal
    */
    virtual DbRetVal free() = 0;

    /**Retrieves the total number of projection fields in the statement
    * @returns int no of projection fields
    */
    virtual int noOfProjFields() = 0;

    /**Retrieves the total number of parameters in the statement
    * @returns int no of parameters
    */
    virtual int noOfParamFields() = 0;

    /**Retrieves the field info for the required projection field position in statement
    * @param projPos int - projection field position
    * @param info FieldInfo*& - OUT parameter
    * @returns DbRetVal
    */
    virtual DbRetVal getProjFldInfo(int projPos, FieldInfo *&info) = 0;

    /**Retrieves the field info for the required parameter position in statement
    * @param projPos int - parameter position
    * @param info FieldInfo*& - OUT parameter
    * @returns DbRetVal
    */
    virtual DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info) = 0;

    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value short - value to be set 
    */
    virtual void setShortParam(int paramPos, short value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value int - value to be set 
    */
    virtual void setIntParam(int paramPos, int value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value long - value to be set 
    */
    virtual void setLongParam(int paramPos, long value)  =0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value long long - value to be set 
    */
    virtual void setLongLongParam(int paramPos, long long value)  =0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value ByteInt - value to be set 
    */
    virtual void setByteIntParam(int paramPos, ByteInt value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value float - value to be set 
    */
    virtual void setFloatParam(int paramPos, float value)  = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value double - value to be set 
    */
    virtual void setDoubleParam(int paramPos, double value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value char* - value to be set 
    */
    virtual void setStringParam(int paramPos, char *value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value Date - value to be set 
    */
    virtual void setDateParam(int paramPos, Date value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value Time - value to be set 
    */
    virtual void setTimeParam(int paramPos, Time value) = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value TimeStamp - value to be set 
    */
    virtual void setTimeStampParam(int paramPos, TimeStamp value)  = 0;
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value Binary - value to be set 
    */
    virtual void setBinaryParam(int paramPos, void *value, int length) = 0;

    /**Returns whether the statement prepared is select statement
    * @return bool true if it is select stmt, false otherwise
    */
    virtual List getTableNameList(){ List dummy; return dummy;}
    virtual int getNoOfPagesForTable(char *tblName)=0;
    virtual DbRetVal loadRecords(char *tblName, void *buf)=0;
    virtual ResultSetPlan getResultSetPlan()=0;
    virtual bool isSelect() = 0;
    virtual bool isFldNull(int pos)=0;
    virtual bool isFldNull(char *name)=0;
    virtual void setNull(int pos)=0;
    virtual int getFldPos(char *name)=0;
    virtual List getAllTableNames(DbRetVal &ret)=0;
    virtual List getAllUserNames(DbRetVal &ret)=0;
    virtual StatementType getStmtType()=0;
    virtual void getProjFieldType( int *data )=0;
    virtual long long getLastInsertedVal(DbRetVal &ret)=0;
    virtual ~AbsSqlStatement()
    {
        if (innerStmt) { delete innerStmt; innerStmt = NULL; }
    }
};

//used to store the binded field values and parameters from derived clases of
//AbsSqlStatement class
class DllExport BindSqlField
{
    public:
    char fName[IDENTIFIER_LENGTH];
    DataType type;
    int length;
    int offset;
    char defaultValueBuf[DEFAULT_VALUE_BUF_LENGTH];
    bool isNull;
    bool isPrimary;
    bool isDefault;
    bool isUnique;
    void *value;
    void *targetvalue;
    BindSqlField(){ value = NULL; targetvalue = NULL; }
};

class DllExport BindSqlProjectField
{
    public:
    char fName[IDENTIFIER_LENGTH];
    DataType type;
    int length;
    int offset;
    char defaultValueBuf[DEFAULT_VALUE_BUF_LENGTH];
    AggType aType;
    bool isNull;
    bool isPrimary;
    bool isDefault;
    bool isUnique;
    bool isFreed;
    void *value;
    void *targetvalue;
    void *jdbcBindValue; //For DATE ,TIME, TIMESTAMP
    BindSqlProjectField()
    { 
        value = NULL; targetvalue = NULL; jdbcBindValue = NULL; isFreed = false; aType = AGG_UNKNOWN;
    }
};

class DllExport StmtBucket
{
    public:
    List bucketList;
};

class DllExport StmtNode
{
    public:
    int stmtId;
    AbsSqlStatement *stmt;
    char stmtstr[1024];
};
#endif
