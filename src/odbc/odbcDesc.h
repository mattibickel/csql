// Class CSqlOdbcDescList, CSqlOdbcDesc
// Description: Generic descriptor manager. 
//              Used as ARD, IRD, APD, IPD.

#ifndef _ODBC_DESCLIST_H_
#define _ODBC_DESCLIST_H_

#define SQL_DESC_APP 0
#define SQL_DESC_IMP 1

// Bound Column/Parameter Descriptor
class CSqlOdbcDesc
{
    public:
        SQLSMALLINT     col_;            // Which column/param number is bound. ?

        // Metadata Info
        SQLCHAR         schemaName_[ SQL_MAX_SCHEMA_NAME_LEN ];     // Schema Name.
        SQLCHAR         tableName_[ SQL_MAX_TABLE_NAME_LEN ];       // Table Name.
        SQLCHAR         colName_[ SQL_MAX_COLUMN_NAME_LEN ];        // Column Name.
        SQLSMALLINT     paramType_;     // SQL_PARAM_INPUT/OUTPUT/INPUT_OUTPUT.

        // Data at node.
        SQLPOINTER      dataPtr_;       // Data at column.
        SQLUINTEGER     length_;        // No. of bytes in data.
        SQLSMALLINT     precision_;
        SQLSMALLINT     scale_;
        SQLPOINTER      indPtr_;        // Indicator variable supplied in SQLBindParameter()
        SQLSMALLINT     nullable_;      // Indicator variable supplied in SQLBindParameter()

        // DataType info.
        SQLSMALLINT     cType_;         // C datatype identifier.
        SQLSMALLINT     csqlType_;       // Equivalent CSQL Type.
        SQLSMALLINT     sqlType_;
    
    // METHODS
        CSqlOdbcDesc( void );
};

class CSqlOdbcDescList 
{
    public:
        int type_;
    public:
        List descList_;
        CSqlOdbcDescList ( int descType);
        SQLRETURN delDesc( CSqlOdbcDesc *node );   
        void freeAllDesc( void );
        SQLRETURN getDescWithColNum( int colNum, CSqlOdbcDesc **out );
};

#endif // _ODBC_DESCLIST_H_
