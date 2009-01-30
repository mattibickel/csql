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
#ifndef AGGTABLE_IMPL_H
#define AGGTABLE_IMPL_H
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
enum AggType
{
    AGG_MIN = 1,
    AGG_MAX,
    AGG_SUM,
    AGG_AVG,
    AGG_COUNT,
    AGG_UNKNOWN
};
#include<TableImpl.h>
class AggFldDef
{
    public:
    char fldName[IDENTIFIER_LENGTH];
    DataType type;
    int length;
    void *bindBuf;
    void *appBuf;
    AggType atype;
    bool alreadyBinded;
    AggFldDef()
    {
        strcpy(fldName, "");
        type=typeUnknown;
        length=0;
        bindBuf=NULL;
        appBuf=NULL;
        atype=AGG_UNKNOWN;
        alreadyBinded=false;
    }
};
class HashMapNode
{
   public:
   void *elem;
   HashMapNode *next;
   HashMapNode() { elem = NULL; next = NULL; }
};
class HashMap
{
    void **bucket;
    int keySize;
    int bucketSize;
    public:
    HashMap(){ keySize = 0; bucketSize = 1009;
               bucket = (void**) malloc(bucketSize * sizeof(void*));
               memset(bucket, 0, bucketSize * sizeof(void*));
             }
    void setKeySize(int size);
    DbRetVal insert(void *elem);
    void* find(void *elem);
    void removeAll();
};

class AggTableImpl:public Table
{
    private:
    char tblName_[IDENTIFIER_LENGTH];
    void *curTuple; //holds the current tuple ptr. moved during fetch() calls
    List fldList;
    AggFldDef groupFld;
    Table *tableHdl;
    List aggNodes; //change this list to some other data structure
    ListIterator aggNodeIter;
    HashMap aggNodeMap; //for faster lookup

    int aggNodeSize;
    DbRetVal copyValuesToBindBuffer(void *tuple);
    public:
    AggTableImpl();
    virtual ~AggTableImpl();
    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info)
        { return tableHdl->getFieldInfo(fieldName, info); }
    bool isGroupSet()
        {
        if (groupFld.type == typeUnknown) return false; else return true;
        }
    void* insertOrGet();
    void setTable(Table *impl){ tableHdl = impl;}
    Table* getTableHdl(){ return tableHdl; }
    DbRetVal closeScan();
    void *getBindFldAddr(const char *name);
    DbRetVal bindFld(const char *name, void *val);
    DbRetVal bindFld(const char *name, AggType aggType, void *val);
    DbRetVal setGroup(const char *name, void *val);
    void setCondition(Condition *p){}
    DbRetVal markFldNull(const char *name){}
    DbRetVal markFldNull(int colpos){}
    bool isFldNull(const char *name){return false;}
    bool isFldNull(int colpos){return false;}
    void clearFldNull(const char *name){}
    void clearFldNull(int colpos){}
    int getFldPos(char *name){}
    void resetNullinfo(){}
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
    void printSQLIndexString(){ };
    char* getName() { return tableHdl->getName(); }
    List getFieldNameList(){ List list; return list;}
    DbRetVal execute();
    void* fetch();
    void* fetch(DbRetVal &rv);
    void* fetchNoBind();
    void* fetchNoBind(DbRetVal &rv);
    DbRetVal close();
    long numTuples();
    void printInfo();
    bool pushPredicate(Predicate *pred)
        { printf("Wrong call\n"); return false; }
    void setPredicate(Predicate *pred) 
        { printf("Wrong call\n"); }
    bool isTableInvolved(char *tableName)
        { printf("Wrong call\n"); return false; }
    void printPlan(int space){printf("AGG-PLAN-TODO\n");}
    DbRetVal optimize()
        { printf("Wrong call\n"); return OK; }
    ScanType getScanType(){ return unknownScan;}
};

#endif
