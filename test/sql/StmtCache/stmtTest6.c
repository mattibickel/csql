#include <SqlFactory.h>

int main(int argc, char **argv)
{
    DbRetVal rv = OK;
    struct timeval timeout;
    struct timeval timeStamp;
    AbsSqlConnection *con = SqlFactory::createConnection(CSql);
    rv = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = SqlFactory::createStatement(CSql);
    stmt->setConnection(con);
    AbsSqlStatement *dropstmt = SqlFactory::createStatement(CSql);
    dropstmt->setConnection(con);
    char statement[200];
    int rows =0;
    // insert into table
    strcpy(statement,"INSERT INTO t1 VALUES(?, 1234, 'CSQL');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 4; }
    rv = con->beginTrans();
    stmt->setIntParam(1, 100);
    rv = stmt->execute(rows);
    if (rv != OK) { 
        printError(rv, "Insert failed with ret val %d", rv);
        con->rollback(); 
    }
    else con->commit();
    stmt->free(); 
    printf("AFTER INSERT FREE\n");
    con->display();
    printf("Dropping table\n");
    strcpy(statement, "DROP TABLE t2");
    rv = dropstmt->prepare(statement);
    if (rv != OK) {
        printf("DROP table failed\n");
        con->disconnect();delete stmt; delete con; return -1; 
    }
    dropstmt->execute(rows);
    dropstmt->free();
    printf("After drop \n");
    con->display();

    strcpy(statement,"INSERT INTO t1 VALUES(?, 1234, 'CSQL');");
    rv = stmt->prepare(statement);
    printf("After second time prepare \n");
    con->display();
        rv = con->beginTrans();
        stmt->setIntParam(1, 200);
        rv = stmt->execute(rows);
        if (rv != OK) { 
            printError(rv, "Insert failed with ret val %d", rv);
            con->rollback(); 
        }
        else con->commit();
    stmt->free(); 
    printf("After reusing cached insert stmt\n");
    con->display();

    con->disconnect();
    delete stmt; 
    delete con;
}
