//Testing NOT with OR operator with all comparision operator on int data type.
//Five tuples are inserted and then selected by setting predicates
//with OR operator with NOT operator

#include "common.h"
int main()
{
    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK) return 1;
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}

    if ( createTable(dbMgr) != 0 ) { conn.close(); return 3; }
#ifdef WITHF1INDEX
    if (createIndex(dbMgr, "f1", "idx1") != 0) {dbMgr->dropTable("t1");
                                        conn.close();
                                        return 4;
                                       }
#endif
#ifdef WITHF1TREEINDEX
    if (createIndex(dbMgr, "f1", "idx1", true) != 0) {dbMgr->dropTable("t1");
                                        conn.close();
                                        return 4;
                                       }
#endif

#ifdef WITHF2INDEX
    if (createIndex(dbMgr, "f2","idx2") != 0) {dbMgr->dropTable("t1");
                                        conn.close();
                                        return 4;
                                       }
#endif
#ifdef WITHF2TREEINDEX
    if (createIndex(dbMgr, "f2","idx2", true) != 0) {dbMgr->dropTable("t1");
                                        conn.close();
                                        return 4;
                                       }
#endif

    int inscount =  insertTuple(dbMgr, conn);
    //check the inscount and return error

    Table *table = dbMgr->openTable("t1");
    if (table == NULL)
    {
        printf("Unable to open table\n");
        return 0;
    }


    Condition p1,p2,p3,p4,p5;
    int val1 = 2, val2 = 3, val3 = 4;
    p1.setTerm("f1", OpEquals, &val3);
    p2.setTerm("f2", OpGreaterThan, &val2);
    p3.setTerm("f2", OpEquals, &val3);
    p4.setTerm("f1", OpLessThan, &val3);
    p5.setTerm("f1", OpGreaterThan, &val1);


    Condition cond1, cond1a;
    cond1.setTerm(p1.getPredicate(), OpOr, p2.getPredicate());
    cond1a.setTerm(cond1.getPredicate(), OpNot);
    table->setCondition(&cond1a);
    printf("Predicate: NOT(f1 ==4 OR f2 >3) \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();

    Condition cond2, cond2a;
    cond2.setTerm(p1.getPredicate(), OpOr, p3.getPredicate());
    cond2a.setTerm(cond2.getPredicate(), OpNot);
    table->setCondition(&cond2a);
    printf("Predicate: NOT( f1 ==4 OR f2 ==4) \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();

    Condition cond3, cond3a;
    cond3.setTerm(p4.getPredicate(), OpOr, p5.getPredicate());
    cond3a.setTerm(cond3.getPredicate(), OpNot);
    table->setCondition(&cond3a);
    printf("Predicate: NOT( f1 <4 OR f1 >2) \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();


    Condition cond4, cond4a;
    cond4.setTerm(p4.getPredicate(), OpOr, p2.getPredicate());
    cond4a.setTerm(cond4.getPredicate(), OpNot);
    table->setCondition(&cond4a);
    printf("Predicate: NOT( f1 <4 OR f2 >3) \n");
    conn.startTransaction();
    execAndPrint(table);
    conn.commit();

    Condition cond5, cond5a;
    cond5.setTerm(p2.getPredicate(), OpNot);
    cond5a.setTerm(p4.getPredicate(), OpOr, cond5.getPredicate());
    table->setCondition(&cond5a);
    printf("Predicate: ( f1 <4 OR (NOT(f2 >3)) \n");
    conn.startTransaction();
    execAndPrint(table);

    conn.commit();
    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");
    conn.close();
    return 0;

}

