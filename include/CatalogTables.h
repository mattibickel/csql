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

#ifndef CATALOGTABLE_H
#define CATALOGTABLE_H

#include<DataType.h>
#include<os.h>
#include<Index.h>
#include<Debug.h>
#include<Util.h>

#include <ParserDataTypes.h>
#include "PredicateImpl.h"

extern char ChunkName[MAX_CHUNKS][CHUNK_NAME_LEN];
class FieldList;
class FieldNameList;
class FieldIterator;
class ChunkIterator;
class Predicate;

enum ObjectType
{
    Tbl  = 0,
    hIdx = 1,
    tIdx = 2,
};

struct Object
{
    char name[64];
    ObjectType type;
    void *bucketChunk;
    void *firstPage;
    void *curPage;
};

enum CatalogTableID
{
    // chunk id 0 ->userChunkTable
    //
    // chunk id 10->DATABASE
    // chunk id 11->USER
    // chunk id 12->TABLE
    // chunk id 13->FIELD
    // chunk id 14->ACCESS
    // chunk id 15->INDEX
    // chunk id 16->INDEXFIELD

    UserChunkTableId      =  0,
    LockTableHashBucketId =  1,
    LockTableMutexId      =  2,
    LockTableId           =  3,
    TransHasTableId       =  4,
    UndoLogTableID        =  5,


    DatabaseTableId  = 10,
    UserTableId      = 11,
    TableTableId     = 12,
    FieldTableId     = 13,
    AccessTableId    = 14,
    IndexTableId     = 15,
    IndexFieldTableId= 16,
    ForeignKeyTableId= 17,
    ForeignKeyFieldTableId= 18,
    GrantTableId     = 19,
    LastCatalogID = 25 //marks the end of catalog chunk ID.
};


class CTABLE
{
    public:
    char tblName_[IDENTIFIER_LENGTH];
    char owner_[IDENTIFIER_LENGTH];
    int tblID_;
    size_t length_; //length of the tuple
    int numFlds_;
    int numIndexes_;
    void* chunkPtr_;
    void* varcharChunkPtr_;
    Chunk *grantsPtr_;
};

class CatalogTableTABLE
{
    Database *systemDatabase_;
    public:
    CatalogTableTABLE(Database *db) { systemDatabase_  = db; }

    //Last argument is OUT parameter which will contain the
    //pointer to the inserted tuple
    DbRetVal insert(const char *name, int id, size_t size,
                     int numFlds, void* chunk, void *&tptr, void *vcchunk,
                     Chunk *grantsPtr, const char *ownerName);

    //Second argument is OUT parameter which will contain the
    //chunk pointer of this table
    //Third argument is OUT parameter which will contain the
    //pointer to the removed tuple
    DbRetVal remove(const char *name, void *&chunk, void *&tptr);
    DbRetVal renameTable(const char *oldName,const char *newName);
    DbRetVal renameIndex(const char *oldName,const char *newName);
    DbRetVal getChunkAndTblPtr(const char *name, void *&chunk, void *&tptr, void*&vcchunk);
    DbRetVal getGrantsPtr(const int tblId, Chunk *&grantsPtr) const;
    DbRetVal setChunkPtr(const char *name, void *firstPage, void *curPage);
    bool isOwner(int tblId, const char *userName);
    List getTableList();
};


class CFIELD
{
    public:
    char fldName_[IDENTIFIER_LENGTH];
    int tblID_;      //table id where this field resides
    void* tblPtr_;    //pointer to tuple in catalog table TABLE
    DataType type_;
    size_t length_;  //length of the field
    size_t offset_;  //offset (in bytes) into tuple
    //currently default value is supported for string and binary
    //less than length 32 bytes
    char defaultValueBuf_[DEFAULT_VALUE_BUF_LENGTH];
    long long autoVal_;//[DEFAULT_VALUE_BUF_LENGTH];
    int width_;
    int scale_;
    bool isNull_;
    bool isPrimary_;
    bool isUnique_;
    bool isDefault_;
    bool isAutoIncrement_;
};

class CatalogTableFIELD
{
    Database *systemDatabase_;
    public:
    CatalogTableFIELD(Database *db) { systemDatabase_  = db; }

    //returns -1 on error
    DbRetVal insert(FieldIterator &iter, int tblID, void *tblPtr);

    DbRetVal remove(void *tblPtr);

    //II argument is OUT parameter
    //field list is populated from the catalog table for
    // the table pointed by tblPtr
    void *getFieldInfo( void* tblPtr, FieldList &list);

    //array is OUT param
    //returns the pointer to fields for the corresponding name
    //in field name list as an array
    DbRetVal getFieldPtrs(FieldNameList &fldList,void *tptr, char **&array);
    DbRetVal renameField(const char *tableName, const char *oldName, const char *newName);
};

class CUSER
{
    public:
    char userName_[IDENTIFIER_LENGTH];
    char password_[IDENTIFIER_LENGTH];
};

class CatalogTableUSER
{
    Database *systemDatabase_;
    public:
    CatalogTableUSER(Database *db) { systemDatabase_  = db; }

    //returns -1 on error
    DbRetVal insert(const char *name, const char *pass);
    DbRetVal authenticate(const char *name, const char *pass,
                     bool &isAuthenticated, bool &isDba);
    DbRetVal remove(const char *name);
    DbRetVal changePass(const char *name, const char *pass);
    List getUserList();
};

class CACCESS
{
    public:
    char userName_[IDENTIFIER_LENGTH];
    char dbName_[IDENTIFIER_LENGTH];
};

struct CGRANT
{
    char userName_[IDENTIFIER_LENGTH];
    unsigned char privileges; /* a bit mask of PrivilegeType, consider using bitset<> here to allow more than 8 privileges */
    unsigned char grantablePrivs; /* a bit mask of PrivilegeType as above, but these can be granted to other users */
    int tblID_; /* table id of the table */
    void *predPtr; /* containing PredicateImpls and ConditionValues for an additional WHERE clause */
    
    CGRANT() : privileges(0), grantablePrivs(0), tblID_(-1), predPtr(NULL) {}
};

class CatalogTableGRANT
{
    Database *systemDatabase_;

    DbRetVal createPredicateChunk(const PredicateImpl *rootPred, List conditionValues,
                Chunk *predChunk, void *&dataPtr);

    public:
    CatalogTableGRANT(Database *db) : systemDatabase_(db) {}

    /* returns -1 on error */
    DbRetVal insert(unsigned char priv, bool grantable, int tblId, std::string userName, const PredicateImpl *rootPred, List conditionValues);
    DbRetVal remove(unsigned char priv, int tblId, std::string userName);
    DbRetVal dropAllForTable(int tblId);
    DbRetVal dropAllForUser(const char *userName);
    
    /* predicate and conditionValues are OUT (and OUT only!) parameters */
    DbRetVal getPredicate(int tblID, const char *userName, Predicate *&pred, List &cVals) const;
    unsigned char getPrivileges(int tblId, const char *userName);
    unsigned char getGrantablePrivs(int tblId, const char *userName);
};

class CDATABASEFILE
{
    public:
    int dbID_;
    char dbName_[IDENTIFIER_LENGTH];
    int maxChunks_;
    size_t maxSize_;  //maximum size of database
    caddr_t dbStart_; //address where the database is mapped
};


class CINDEX
{
    public:
    char indName_[IDENTIFIER_LENGTH];
    int tblID_;      //table id of the table
    void* tblPtr_;    //pointer to tuple in catalog table TABLE
    IndexType indexType_;
    void* chunkPtr_; //pointer to the index chunk
    int numFlds_;
    int noOfBuckets_;
    bool isUnique_;
    void *hashNodeChunk_;
    void *fstIndFld_;//pointer to fisrt index field 
};

class CatalogTableINDEX
{
    Database *systemDatabase_;
    public:
    CatalogTableINDEX(Database *db) { systemDatabase_  = db; }


    //last arg is OUT parameter which will give the pointer to
    //the index tuple
    DbRetVal insert(const char *name, void *tblPtr, int numFlds, bool isUnique,
                     void* chunk, int bucketSize, void *hChunk, void *&tupleptr);

    //Second argument is OUT parameter which will contain the
    //chunk pointer of this table
    //Third argument is OUT parameter which will contain the
    //pointer to the removed tuple
    DbRetVal remove(const char *name, void *&chunk, void *&hchunk, void *&iptr);
    DbRetVal get(const char *name, void *&chunk, void *&hchunk, void *&iptr);
    DbRetVal setChunkPtr(const char *name, ObjectType tp, void *chunk, void *firstPage, void *curPage);

    //get the number of indexes on table pointed by tblPtr
    int getNumIndexes(void *tblPtr);

    char* getIndexName(void *tblPtr, int pos);

    //gets all the index ptrs as array for the table pointed by tblPtr
    void getIndexPtrs(void *tblPtr, char **&array);

    static ChunkIterator getIterator(void *iptr);
    static int getNoOfBuckets(void *iptr);
    static int getUnique(void *iptr);
    static char* getName(void *iptr);
    static int getOffsetOfFirstField(void *iptr);
    static IndexType getType(void *iptr);
};


class CINDEXFIELD
{
    public:
    void* indexPtr; //pointer to tuple in catalog table INDEX
    void* tablePtr; //pointer to tuple in catalog table TABLE
    void* fieldPtr; //pointer to tuple in catalog table FIELD
    CINDEXFIELD *next;
};

class CatalogTableINDEXFIELD
{
    Database *systemDatabase_;
    public:
    CatalogTableINDEXFIELD(Database *db) { systemDatabase_  = db; }

    DbRetVal insert(FieldNameList &fldList, void *indexPtr,
                               void *tblPtr, char **&fptr);

    DbRetVal remove(void *iptr);

    DbRetVal getFieldNameAndType(void *iptr, char *&name, DataType &type);
    DbRetVal getFieldInfo(void *index, FieldList &list);
    void printAllIndex();
    ListIterator getIndexListIterater(char *name);

};

class CFK
{
    public:
    char fkName_[IDENTIFIER_LENGTH];
    void* pkTblPtr_;
    void* fkTblPtr_;
};

class CatalogTableFK
{
    Database *systemDatabase_;
    public:
    CatalogTableFK(Database *db) { systemDatabase_  = db; }
    DbRetVal insert(char *name, void *tFkPtr,void *tPkPtr);
    DbRetVal remove(void *tptr);
    void *getFkCTable(void* tptr);
    int getNumFkTable(void *ctptr);
    bool isFkTable(void *ctptr);
    void getPkTableName(void *ctptr, char **&array);
    void getFkTableName(void *ctptr, char **&array);
    int getNoOfPkTable(void *ctptr);
    int getNoOfFkTable(void *ctptr);
    DbRetVal getPkFkFieldInfo(void *cpkptr, void *cfkptr, FieldNameList &pklist,FieldNameList &pklist1);
};

class CFKFIELD
{
   public:
   void* fkPtr_;//pointer to tuple in catalog table CFK
   void* pfFldPtr_;
   void* fkFldPtr_;    
};

class CatalogTableFKFIELD
{
    Database *systemDatabase_;
    public:
    CatalogTableFKFIELD(Database *db) { systemDatabase_  = db; }
    DbRetVal insert(char *cFKName, char **fkFldPtrs, char **pkFldPtrs,int totalFld);
    DbRetVal remove(void *fptr);
};

#endif
