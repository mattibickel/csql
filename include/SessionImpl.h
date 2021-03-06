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
#ifndef SESSION_IMPL_H
#define SESSION_IMPL_H
#include<DatabaseManager.h>
#include<UserManager.h>
#include<Session.h>

class DatabaseManagerImpl;
class Database;

class DllExport SessionImpl : public Session
{
    DatabaseManagerImpl *dbMgr;
    UserManager *uMgr;

    char userName[IDENTIFIER_LENGTH];
    bool isAuthenticated;
    bool isDba;
    bool isXTaken;
#if (defined MMDB && defined EMBED)
    static int noOfThreads;
#endif
    public:
    SessionImpl()
    {
        dbMgr = NULL; uMgr = NULL; 
        isXTaken = false;
    }
    ~SessionImpl()
    {
        close();
    }
    //This is used by the server process to initialize and create
    //system and user database->create shared memory segment
    DbRetVal initSystemDatabase();
    //Removes the shared memory segment->deletes both the databases
    DbRetVal destroySystemDatabase();

    DbRetVal open(const char*username, const char*password);
    DbRetVal close();
    
    DatabaseManager* getDatabaseManager();
    UserManager* getUserManager();

    DbRetVal startTransaction(IsolationLevel level);
    DbRetVal commit();
    DbRetVal rollback();
    char * getUserName() { return userName;}
    DbRetVal readConfigFile();
    Database* getSystemDatabase();
    DbRetVal getExclusiveLock();
    private:
#if (defined MMDB && defined EMBED)
    DbRetVal openEmbeddedConnection(const char *uname, const char *password);
    DbRetVal closeEmbeddedConnection();
#endif
    DbRetVal authenticate(const char *username, const char *password);
};

#endif
