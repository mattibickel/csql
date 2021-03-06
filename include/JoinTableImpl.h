/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
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
  ***************************************************************************/
#ifndef JOINTABLE_IMPL_H
#define JOINTABLE_IMPL_H
#include<os.h>
#include<DataType.h>
#include<Transaction.h>
#include<Database.h>
#include<Index.h>
#include<CatalogTables.h>
#include<Info.h>
#include<Debug.h>
#include<DatabaseManagerImpl.h>
#include<Predicate.h>

#ifndef JOINTYPE
#define JOINTYPE
enum JoinType
{
    INNER_JOIN = 1,
    LEFT_JOIN,
    RIGHT_JOIN,
    FULL_JOIN,
    UNKNOWN_JOIN
};
#endif

class DllExport JoinProjFieldInfo
{
    public:
    char tabFieldName[IDENTIFIER_LENGTH*2];
    char tableName[IDENTIFIER_LENGTH];
    char fieldName[IDENTIFIER_LENGTH];
    DataType type;
    int length;
    void *appBuf;
    void *bindBuf;
    JoinProjFieldInfo()
    {
        strcpy(tableName,""); strcpy(fieldName, "");
        type= typeUnknown; length =0; appBuf= NULL; bindBuf=NULL;
    }
};
class DllExport JoinCondition
{
    public:
    char tableName1[IDENTIFIER_LENGTH];
    char tableName2[IDENTIFIER_LENGTH];
    char fieldName1[IDENTIFIER_LENGTH];
    char fieldName2[IDENTIFIER_LENGTH];
    DataType type1;
    DataType type2;
    int length1;
    int length2;
    void *bindBuf1;
    void *bindBuf2;
    bool alreadyBinded1;
    bool alreadyBinded2;
    ComparisionOp op;
    JoinCondition()
    {
        strcpy(tableName1,""); strcpy(fieldName1, "");
        strcpy(tableName2,""); strcpy(fieldName2, "");
        type1= typeUnknown; length1 =0; bindBuf1=NULL;
        type2= typeUnknown; length2 =0; bindBuf2=NULL;
        alreadyBinded1=false; alreadyBinded2=false;
    }
    
};
class DllExport JoinTableImpl:public Table
{
    private:
    void *curTuple; //holds the current tuple ptr. moved during fetch() calls
    List projList;
    Table *leftTableHdl;
    Table *rightTableHdl;
    bool availableLeft;
    bool isFirstFetch;
    bool isReturnNull;
    //bool isOuterJoin;
    bool isOptimized;
    bool isLeftRecOver;
    bool isFirstCall;
    bool leftSideFail;

    JoinType jType;
    ListIterator rsIter;
    bool isNestedLoop;
    bool rightExhausted;
    DbRetVal copyValuesToBindBuffer(void *tuple);
    JoinCondition jCondition;
    Predicate *pred;
    List predList;

    public:
    JoinTableImpl();
    virtual ~JoinTableImpl();

    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info);
    DbRetVal getQualifiedName(const char *fldname, char *qualName);

    void setTable(Table *left, Table *right)
    { leftTableHdl = left; rightTableHdl = right; }
    int getFldPos(char *name){ return 0;}
    DbRetVal closeScan();
    void setJoinType(JoinType type) { jType = type; }
    //binding
    DbRetVal bindFld(const char *name, void *val, bool dummy=false);
    //DbRetVal setJoinCondition(const char *fldname1, ComparisionOp op,  
    //                          const char *fldname2);

     void setCondition(Condition *p)
     { if (p) pred = p->getPredicate(); else pred = NULL;}

    DbRetVal markFldNull(const char *name){ return ErrBadCall;}
    DbRetVal markFldNull(int colpos){ return ErrBadCall;}
    bool isFldNull(const char *name);
    bool isFldNullInt(const char *name);
    bool isFldNull(int colpos){return false;}
    void clearFldNull(const char *name){}
    void clearFldNull(int colpos){}
    void resetNullinfo(){ }
    DbRetVal insertTuple() { return ErrBadCall; }
    DbRetVal updateTuple() { return ErrBadCall; }
    DbRetVal deleteTuple() { return ErrBadCall; }
    int deleteWhere() { return ErrBadCall; }
    int truncate() { return ErrBadCall; }
    long spaceUsed() { return 0; }
    int pagesUsed() { return 0; }
    DbRetVal lock(bool shared) { return ErrBadCall; }
    DbRetVal unlock(){ return ErrBadCall; }
    DbRetVal setUndoLogging(bool flag) { return ErrBadCall; }
    void printSQLIndexString(FILE *fp, int fd){ };
    void printSQLForeignString(){}
    List getFieldNameList();
    char* getName() { return NULL; }
    char* getAliasName(){ return NULL; }
    void *fetchRightFail();
    DbRetVal compact(){ return OK;}
    //bool evaluate();
    DbRetVal execute();
    void* fetch();
    void* fetchInt();
    void* fetch(DbRetVal &rv);
    void* fetchNoBind();
    void* fetchNoBind(DbRetVal &rv);
    DbRetVal close();
    
    long numTuples();
    void printInfo();
    void *getBindFldAddr(const char *name);
    bool isFKTable(){return false;}
    bool isTableInvolved(char *tblName);
    bool pushPredicate(Predicate *pred);
    void setPredicate(Predicate *pred);
    void printPlan(int space);
    DbRetVal optimize();
    void optimizeRestrict();
    ScanType getScanType();
    bool hasIndex(char *fname){ return false; }
    void* getBindedBuf(char* tName, char*fName);
};


#endif
