/*   prepare,execute,prepare....,
 *   second prepare should pass.

 *   Author : Jitendra Lenka
 */

#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv  = con->connect("root","manager");
    if(rv!=OK)return 1;
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
    char statement[200];
    strcpy(statement,"CREATE TABLE T1(F1 INT,F2 CHAR(20));");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 1; }
    printf("Prepared the statement\n");
    rv  = stmt->execute(rows);
    if(rv!=OK) { delete stmt; delete con; return 2; }
    printf("Execute the statement\n");
    //again prepare
    strcpy(statement,"DROP TABLE T1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { 
        printf("Test script failed\n"); 
        delete stmt; delete con; return 3;
    }
    printf("Test script passed\n");
    stmt->execute(rows);
    stmt->free(); delete stmt; delete con; 
    return 0;
}
