#include<CSql.h>
#include "common.h"
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("praba", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    if ( createTable(dbMgr) != 0 ) { conn.close(); return 3; }
    if ( createIndex(dbMgr, true) != 0 ) { dbMgr->dropTable("t1");conn.close(); return 4;
 }
    int inscount =  insertTupleWithSameValue(dbMgr, conn);
    if (inscount != 1 ) { dbMgr->dropTable("t1"); conn.close(); return 5; }
    dbMgr->dropTable("t1");
    conn.close();
    return 0;

}
