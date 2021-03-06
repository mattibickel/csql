/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SQLSTATEMENT_H
#define SQLSTATEMENT_H
#include <AbsSqlStatement.h>
#include <SqlConnection.h>
#include <SqlFactory.h>
#include "Statement.h"
//#include<CSql.h>
class Statement;
class ParsedData;

class DllExport SqlStatement: public AbsSqlStatement
{
    public:
    SqlStatement();
    ~SqlStatement();
    /** sets connection handle to be used for subsequent operations
    *   @param con SqlConnection*
    */
    void setConnection(AbsSqlConnection *con);
    void setSqlConnection(SqlConnection *con);

    /** compiles the sql statement. It calls the parser and tokenizes the statement 
    * into logical plan. This method sets the statement string which needs to be executed.
    * free method needs to be called, if application wants to use the same handle to compile
    * another sql statement.
    * @param stmt sql statement string
    * @returns DbRetVal
    */
    DbRetVal prepare(char *stmt);

    /** Executes directly for the non parameterized statements **/
    DbRetVal executeDirect(char *stmt);

    char* getTableName();

    /** executes the sql statement. For insert, update, delete queries execute performs the
    * required operation on the table. 
    * For Select queries, application should call execute before they start fetching
    * the values from the table.This starts scan on the table.
    * @param rowsAffect number of rows affected by the sql statement
    * @returns DbRetVal
    */
    DbRetVal execute(int &rowsAffect);

    /**fetches the next tuple from the result of the execution of sql select query.
    * execute should be called before calling this method. Application buffer should be 
    * binded to get the tuple values.
    * @returns void* NULL if there is no tuple.
    */
    void* fetch();
    void* fetch(DbRetVal &rv);
    

    /**fetches the next tuple from the result of the execution of sql select query 
    * and prints it to stdout.
    * execute should be called before calling this method.
    * @returns void* NULL if there is no tuple.
    */
    void* fetchAndPrint(bool SQL);


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
    DbRetVal bindParam(int pos, void*);

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
    DbRetVal bindField(int pos, void* val);

    /** same as fetch, but does not populate bindFieldValues
    * @returns address void*
    */
    void* next();

    /**Closes the iterator and makes the statement ready for another execution
    * @returns DbRetVal
    */
    DbRetVal close();

    /** get FieldValue->value ptr after fetch is done.
    * @returns address void*
    */
    void* getFieldValuePtr( int pos );
    void* getFieldValuePtr( char *name );

    /**Frees all the resources held for the sql statement. Needs to be called before calling prepare again on the same statement handle.
    * @returns DbRetVal
    */
    DbRetVal free();

    /**Retrieves the total number of projection fields in the statement
    * @returns int no of projection fields
    */
    int noOfProjFields();

     /** get Param value pointer after fetch is done.
     * @returns address void*
     */
     void* getParamValuePtr( int pos );

     /** get FieldValue->type
     * @returns DataType
     */
     DataType getFieldType( int pos );

     /** get FieldValue->length
     * @returns int
     */
     int getFieldLength( int pos );

     /** get FieldName
     * @returns address char*
     */
     char* getFieldName ( int pos );

    /**Retrieves the total number of parameters in the statement
    * @returns int no of parameters
    */
    int noOfParamFields();

    /**Retrieves the field info for the required projection field position in statement
    * @param projPos int - projection field position
    * @param info FieldInfo*& - OUT parameter
    * @returns DbRetVal
    */
    DbRetVal getProjFldInfo(int projPos, FieldInfo *&info);

    /**Retrieves the field info for the required parameter position in statement
    * @param projPos int - parameter position
    * @param info FieldInfo*& - OUT parameter
    * @returns DbRetVal
    */
    DbRetVal getParamFldInfo(int paramPos, FieldInfo *&info);

    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value short - value to be set 
    */
    void setShortParam(int paramPos, short value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value int - value to be set 
    */
    void setIntParam(int paramPos, int value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value long - value to be set 
    */
    void setLongParam(int paramPos, long value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value long long - value to be set 
    */
    void setLongLongParam(int paramPos, long long value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value ByteInt - value to be set 
    */
    void setByteIntParam(int paramPos, ByteInt value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value float - value to be set 
    */
    void setFloatParam(int paramPos, float value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value double - value to be set 
    */
    void setDoubleParam(int paramPos, double value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value char* - value to be set 
    */
    void setStringParam(int paramPos, char *value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value Date - value to be set 
    */
    void setDateParam(int paramPos, Date value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value Time - value to be set 
    */
    void setTimeParam(int paramPos, Time value);
    /**Sets the value for the required parameter position in statement
    * @param paramPos int - parameter position
    * @param value TimeStamp - value to be set 
    */
    void setTimeStampParam(int paramPos, TimeStamp value);
    /**Sets the value for the required parameter position in statement
	* @param paramPos int - parameter position
	* @param value Binary - value to be set 
	*/
	void setBinaryParam(int paramPos, void *value, int length);

    /**Returns whether the statement prepared is select statement
    * @return bool true if it is select stmt, false otherwise
    */
    bool isSelect();
    
    /**Returns whether the statement is prepared or not
    * @return bool true if it is prepared, false otherwise
    */
    List getTableNameList();
    List getFieldNameList(const char *tblName, DbRetVal &rv);
    DbRetVal getFieldInfo(const char *tblName, const char *fldName, FieldInfo *&info);
    bool isPrepared();
    StatementType getStmtType() { return pData.getStmtType(); }
    bool isFldNull(int pos); 
    bool isFldNull(char *name); 
    void setNull(int pos);
    int getFldPos(char *name);
    ResultSetPlan getResultSetPlan(){ return stmt->getResultSetPlan();}
    List getAllTableNames(DbRetVal &ret);
    List getAllUserNames(DbRetVal &ret);
    int getNoOfPagesForTable(char *tblName);
    DbRetVal loadRecords(char *tblName, void *buffer);
    DbRetVal pasteRecords(char *tblName, void *buffer);
    void setLoading(bool flag);
    void getProjFieldType(int *data);
    void setCachedStmt(bool flag){ isCachedStmt= flag; }
    void flushCacheStmt();
    long long getLastInsertedVal(DbRetVal &rv);
    void setStmtString(char *ststr);
    DbRetVal prepare();
    DbRetVal prepareInt(char *ststr);
    void resetStmtString();
    static void setParamValues(AbsSqlStatement *sqlStmt, int parampos,
                                       DataType type, int length, void *value);
    static void *fillBindBuffer(TDBInfo tdbName, DataType type, void *&valBuf, 
                                                   int length, int nRecords=1);
    static void addToHashTable(int stmtID, AbsSqlStatement* sHdl,
                                             void *stmtBuckets, char *stmtstr);
    static void removeFromHashTable(int stmtID, void *stmtBuckets);
    static AbsSqlStatement *getStmtFromHashTable(int stmtId, void *stmtBuckets);
    static bool isStmtInHashTable(int stmtID, void *stmtBuckets);
    static void freeAllStmtHandles(void *stmtBuckets);
    static DbRetVal filterAndWriteStmtLogs(void *stmtBuckets);
    static DbRetVal readAndPopulateStmts(AbsSqlConnection *conn, void *&stmtBuckets, bool list = false, bool interactive = false);
    static DbRetVal iterateStmtLogs(AbsSqlConnection *conn, void *startAddr, int size, void *stmtBuckets, bool list=false, bool interactive = false);
    void setDontCache(bool dntCache) { dontCache = dntCache; }
    bool getDontCache() { return dontCache; }
    private:
    bool dontCache;
    bool isMgmtStatement;
    SqlConnection *sqlCon;
    Statement *stmt;
    ParsedData pData;
    bool isPrepd;
    bool isCachedStmt;
    char *sqlStmtString;
    friend class SqlFactory;
};

#endif
