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
#ifndef TABLE_IMPL_H
#define TABLE_IMPL_H
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
#include<AggTableImpl.h>//for AggType
#ifndef SCANTYPE
enum ScanType
{
    fullTableScan = 0,
    hashIndexScan,
    treeIndexScan,
    unknownScan
};
#define SCANTYPE
#endif

static char ScanTypeNames[][10] =
{
    "TableScan", "HashScan", "TreeScan", "Invalid"
};

class Predicate;

class TupleIterator
{
    Predicate *pred_;
    ScanType scanType_;
    ChunkIterator *cIter;
    BucketIter *bIter;
    TreeIter *tIter;
    IndexInfo *info;
    void *chunkPtr_;
    int procSlot;
    bool isBetween;
    bool isPointLook;
    
    TupleIterator(){}
    public:
    TupleIterator(Predicate *p, ScanType t, IndexInfo *i, void *cptr, int pslot,bool between , bool isPtLook)
    { bIter = NULL; pred_ = p ; scanType_ = t; info = i; chunkPtr_ = cptr; procSlot =pslot; isBetween=between; isPointLook=isPtLook; }
    
    ~TupleIterator() 
	{ 
        if (bIter) delete bIter; 
        bIter = NULL; 
    }
    bool isBetInvolved(){ return isBetween;}
    void setBetInvolved(bool between){ isBetween=between;}
    bool isPointLookInvolved(){return isPointLook;}
    DbRetVal open();
    void* next();
    void* prev();//used only for tree iter during deleteTuple
    void reset();
    DbRetVal close();

};
class TableImpl:public Table
{
    private:


    LockManager *lMgr_;
    Transaction **trans;
    //This is pointer to the pointer stored in the
    //Transaction manager.
    //If the transaction commits/aborts this pointer changes
    //and this will get that newly allocated transaction

    char tblName_[IDENTIFIER_LENGTH];
    int tblID_;
    size_t length_; //length of the tuple
    int numFlds_;
    void* chunkPtr_;
    void *curTuple_; //holds the current tuple ptr. moved during fetch() calls

    Predicate *pred_;
    ScanType scanType_;
    //ChunkIterator *iter;
    //BucketIter *bIter;

    TupleIterator *iter;

    bool undoFlag;

    public:
    FieldList fldList_;
    int numIndexes_;
    char** indexPtr_; // array of index ptrs to the catalog table for the indexes of this table.
    IndexInfo **idxInfo;
    int useIndex_;//offet in the above array indexPtr_ for scan
    bool isPlanCreated;
    bool isPointLook;
    bool isBetween;
    Database *db_;
    Database *sysDB_;

    //Either one of the below is populated based on the no of fields and 
    //is used for tuple insertions
    bool isIntUsedForNULL;
    int iNullInfo;
    char *cNullInfo;
    int iNotNullInfo;
    char *cNotNullInfo;
 
    private:

    //copy Values from binded buffer to tuple pointed by arg
    DbRetVal copyValuesFromBindBuffer(void *tuple, bool isInsert=true);
    DbRetVal copyValuesToBindBuffer(void *tuple);
    void setNullBit(int fldpos);
    void clearNullBit(int fldpos);
    DbRetVal insertIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);
    DbRetVal updateIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);
    DbRetVal deleteIndexNode(Transaction *trans, void *indexPtr, IndexInfo *info, void *tuple);

    DbRetVal createPlan();
    Chunk* getSystemTableChunk(CatalogTableID id)
    {
        return sysDB_->getSystemDatabaseChunk(id);
    }

    public:
    TableImpl() { db_ = NULL; chunkPtr_ = NULL; iter = NULL;
        idxInfo = NULL; indexPtr_ = NULL; scanType_ = unknownScan; 
        pred_ = NULL; useIndex_ = -1; numFlds_ = 0;
        iNullInfo = 0; cNullInfo = NULL; isIntUsedForNULL = true; 
        iNotNullInfo = 0; cNotNullInfo = NULL; curTuple_ = NULL;
        isPlanCreated = false; undoFlag = true;}
    ~TableImpl();

    void setDB(Database *db) { db_ = db; }
    Database* getDB() { return db_;}
    void setSystemDB(Database *db) { sysDB_ = db; }
    void setLockManager(LockManager *lmgr) { lMgr_ = lmgr; }
    void setTrans(Transaction **t) { trans = t; }
    void setCurTuple(void *tuple){ curTuple_=tuple; }
    DataType getFieldType(const char *name)
        { return fldList_.getFieldType(name);   }
    int getFieldOffset(const char *name)
        { return fldList_.getFieldOffset(name); }
    size_t getFieldLength(const char *name)
        { return fldList_.getFieldLength(name); }

    DbRetVal getFieldInfo(const char *fieldName,  FieldInfo *&info)
    { 
        char tblName[IDENTIFIER_LENGTH];
        char fldName[IDENTIFIER_LENGTH];
        getTableNameAlone((char*)fieldName, tblName);
        getFieldNameAlone((char*)fieldName, fldName);
        if (0 == strcmp(tblName, "") || 0 ==strcmp(tblName, getName()))
            return fldList_.getFieldInfo(fldName, info); 
        else
            return ErrNotExists;
    }

    List getFieldNameList();

    // search predicate
     void setCondition(Condition *p) 
     { isPlanCreated = false; if (p) pred_ = p->getPredicate(); else pred_ = NULL;}

    //binding
    DbRetVal bindFld(const char *name, void *val);
    void *getBindFldAddr(const char *name);
    int getFldPos(char *name);
    DbRetVal markFldNull(const char *name);
    DbRetVal markFldNull(int colpos);
    bool isFldNull(const char *name);
    bool isFldNull(int colpos);

    void clearFldNull(const char *name);
    void clearFldNull(int colpos);
    void resetNullinfo();
    DbRetVal insertTuple();
    DbRetVal updateTuple();

    DbRetVal deleteTuple();
    int deleteWhere();
    int truncate();

    DbRetVal execute();

    void* fetch();
    void* fetch(DbRetVal &rv);
    void* fetchNoBind();
    void* fetchNoBind(DbRetVal &rv);
    DbRetVal fetchAgg(const char *fldName, AggType aType, void *buf);

    DbRetVal close();
    DbRetVal closeScan();


    long spaceUsed();
    long numTuples();
    int pagesUsed();
    void printInfo();
    void printPlan(int space);

    DbRetVal lock(bool shared);
    DbRetVal unlock();
   
    DbRetVal setUndoLogging(bool flag) { undoFlag = flag; }

    void printSQLIndexString();

    DbRetVal optimize();
    bool isTableInvolved(char *tblName);
    bool pushPredicate(Predicate *pred);
    void setPredicate(Predicate *pred);
    ScanType getScanType() { return scanType_; }

    char* getName() { return tblName_; }
    void setTableInfo(char *name, int tblid, size_t  length,
                       int numFld, int numIdx, void *chunk);
    friend class DatabaseManagerImpl;
};


#endif
