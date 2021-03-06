/**********************************************************
* Test Case
* create table t1
* create index if specified
* insert 10 tuples
* start new transaction
* update 10 tuples
* check transaction statistics 
* abort transation
* check transaction statistics
*/
#include "common.h"
#include <DatabaseManagerImpl.h>
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManagerImpl *dbMgr = (DatabaseManagerImpl*) conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    int ret =0, rc =0;
    if (createTable(dbMgr, "t1") != 0 ) { ret = 3; }
#ifdef WITHINDEX
    if (createIndex(dbMgr, "t1","f1", "idx1") != 0 ) { ret = 4; }
#endif
    rv = conn.startTransaction();
    if (rv != OK) ret = 5; 
    rc = insertTuple(dbMgr, conn, "t1", 10);
    if (rc != 10) ret = 6;
    conn.commit();
 
    rv = conn.startTransaction();
    if (rv != OK) ret = 5; 
    rc = updateTuple(dbMgr, conn, "t1", 10);
    if (rc != 10) ret = 6;

    printf("Before abort\n");
    dbMgr->printDebugTransInfo();
    conn.rollback(); 
    printf("After abort\n");
    dbMgr->printDebugTransInfo();
    dropTable(dbMgr ,"t1");
    conn.close();
    return ret;
}
