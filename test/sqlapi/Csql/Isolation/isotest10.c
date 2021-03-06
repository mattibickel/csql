#include "common.h"
//READ_COMMITTED isolation testing 
//           T1                 T2
//        -------------------------
//         Read
//                  Update
//         Read
// T1 second read should fail saying "tuple not found
void* runTest1(void *p);
void* runTest2(void *p);
int *p1RetVal = NULL;
int *p2RetVal = NULL;
int selectDone = 0, updateDone =0, allDone = 0;

int main()
{

    AbsSqlConnection *conn = createConnection();
    DbRetVal rv = conn->connect("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return 1; }
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(conn);

    char statement[1024]="create table t1 (f1 int, f2 char(196), primary key(f1));";
    int ret = executeDdlQuery(conn, stmt, statement);
    if (ret != 0) { return 1; }
    rv = conn->beginTrans(READ_COMMITTED);
    if (rv != OK) return 2;
    rv = insert(stmt, 100, false);
    if (rv != OK) { printf("Error in inserting the record\n"); return 3; }
    conn->commit();
    printf("Tuple inserted\n");

    pthread_t thr[2];
    int *status1, *status2;
    pthread_create (&thr[0], NULL, &runTest1,  NULL);
    pthread_create (&thr[1], NULL, &runTest2,  NULL);
    printf("All threads started\n");

    pthread_join(thr[0], (void**)&status1);
    pthread_join(thr[1], (void**)&status2);
    strcpy(statement, "drop table t1;");
    ret = executeDdlQuery(conn, stmt, statement);
    if (ret != 0) { return 3; }
    conn->disconnect();
    stmt->free(); delete stmt; delete conn;
    if (*status1 != 0 || *status2 != 0) return 4;
    if (p1RetVal) { delete p1RetVal; p1RetVal = NULL; }
    if (p2RetVal) { delete p2RetVal; p2RetVal = NULL; }
    return 0;
}

void* runTest1(void *message)
{
    AbsSqlConnection *conn = createConnection();
    DbRetVal rv = conn->connect("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return NULL; }
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(conn);
    rv = conn->beginTrans(READ_COMMITTED);
    if (rv != OK) return NULL;
    printf("Thread and pid is %d %lu\n", os::getpid(), os::getthrid());
    p1RetVal = new int();
    *p1RetVal = 0;

    rv = select(stmt, 100, true);
    if (rv != OK) { printf("Test Failed:first thread failed to select\n"); *p1RetVal = 1; }
    selectDone = 1;
    while (updateDone != 1) {::sleep(1); }
    rv = select(stmt, 100, true, true);
    if (rv == OK) { printf("Test Failed:first thread read succeeded \n"); *p1RetVal = 1; }
    allDone = 1;
    conn->commit();
    rv = conn->disconnect();
    stmt->free(); delete stmt; delete conn;
    printf("conn closed %d for Thread and pid is %d %lu\n", rv, os::getpid(), os::getthrid());
    pthread_exit(p1RetVal);
}

void* runTest2(void *message)
{
    AbsSqlConnection *conn = createConnection();
    DbRetVal rv = conn->connect("root", "manager");
    if (rv != OK) { printf("Error during connection %d\n", rv); return NULL; }
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(conn);
    rv = conn->beginTrans(READ_COMMITTED);
    if (rv != OK) return NULL;
    printf("Thread and pid is %d %lu\n", os::getpid(), os::getthrid());
    while (selectDone != 1) {::sleep(1); }
    p2RetVal = new int();
    *p2RetVal = 0;
    rv = update(stmt, 100, true);
    if (rv != OK) { 
        printf("Test Failed:second thread failed to update\n"); 
        *p2RetVal = 1; 
    }
    updateDone = 1;
    while (allDone !=1) ::sleep(1);
    rv = conn->commit();
    rv = conn->disconnect();
    stmt->free(); delete stmt; delete conn;
    printf("conn closed %d for Thread and pid is %d %lu\n", rv, os::getpid(), os::getthrid());
    pthread_exit(p2RetVal);
}
