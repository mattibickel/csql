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
#ifndef DATABASE_MANAGER_IMPL_H
#define DATABASE_MANAGER_IMPL_H
#include<os.h>
#include<CatalogTables.h>
#include<Lock.h>
#include<DatabaseManager.h>

class Database;
class SessionImpl;
class TableDef;
class Table;
class FieldNameList;
class ChunkIterator;
class Chunk;
class TransactionManager;


class DatabaseManagerImpl : public DatabaseManager
{
    private:
    Database* systemDatabase_;
    //pointer to system Database

    Database* db_;
    //pointer to database

    LockManager *lMgr_;

    TransactionManager *tMgr_;

    //only SessionImpl creates object of this class
    DatabaseManagerImpl() { systemDatabase_ = NULL; tMgr_ = NULL; lMgr_ =  NULL; db_ = NULL; }
    ~DatabaseManagerImpl();

    DbRetVal openSystemDatabase();
    DbRetVal closeSystemDatabase();
    ChunkIterator getSystemTableIterator(CatalogTableID id);
    Chunk* getSystemTableChunk(CatalogTableID id);

    void createLockManager();
    void createTransactionManager();

    Chunk* createUserChunk(size_t size = 0);
    DbRetVal deleteUserChunk(Chunk *chunk);


    DbRetVal createHashIndex(const char *indName, const char *tableName,
                        FieldNameList &fldList, int bucketSize);
    void initHashBuckets(Bucket *buck, int bucketSize);


    public:

    Database* db() { return db_; }
    Database* sysDb() { return systemDatabase_; }
    void setSysDb(Database *db) { systemDatabase_ = db; }
    void setDb(Database *db) { db_ = db; }

    TransactionManager* txnMgr() { return tMgr_; }
    LockManager* lockMgr() { return lMgr_; }

    //for user database file there is no limit for the number
    //of tables or chunks
    DbRetVal createDatabase(const char *name, size_t size);
    DbRetVal deleteDatabase(const char *name);

    DbRetVal openDatabase(const char *name);
    void closeDatabase();



    DbRetVal createTable(const char *name, TableDef &def);
    DbRetVal dropTable(const char *name);
    Table* openTable(const char *name);
    void closeTable(Table *table);
    DbRetVal createIndex(const char *indName, IndexInitInfo *info);
    DbRetVal dropIndex(const char *name);


    friend class SessionImpl;
};
#endif