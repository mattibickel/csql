#include<CSql.h>

char  id[30];
char name[196] = "PRABAKARAN";
int select(Table *table, ComparisionOp op)
{
    printf("Operator test for %d\n", op);
    Condition p1;
    char val1[30] = "Value3";
    p1.setTerm("f1", op, &val1);
    table->setCondition(&p1);
    table->execute();
    void *tuple;
    while ((tuple = (char*) table->fetch())) {
        printf("tuple value is %s %s \n", id, name);
    }
    table->closeScan();
    return 0;
}

int main()
{

    Connection conn;
    DbRetVal rv = conn.open("root", "manager");
    if (rv != OK)
    {
       printf("Error during connection %d\n", rv);
       return 1;
    }
    DatabaseManager *dbMgr = conn.getDatabaseManager();
    if (dbMgr == NULL) { printf("Auth failed\n"); return 2;}
    TableDef tabDef;
    tabDef.addField("f1", typeString, 30, NULL, true);
    tabDef.addField("f2", typeString, 196);
    rv = dbMgr->createTable("t1", tabDef);
    if (rv != OK) { printf("Table creation failed\n"); return 3; }
    printf("Table created\n");
#ifdef WITHINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->isUnique = true;
    idxInfo->isPrimary = true;
    idxInfo->indType = hashIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    delete idxInfo;
#endif
#ifdef WITHTREEINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = treeIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    delete idxInfo;
#endif
#ifdef WITHTRIEINDEX
    HashIndexInitInfo *idxInfo = new HashIndexInitInfo();
    strcpy(idxInfo->tableName, "t1");
    idxInfo->list.append("f1");
    idxInfo->indType = trieIndex;
    rv = dbMgr->createIndex("indx1", idxInfo);
    if (rv != OK) { printf("Index creation failed\n"); return -1; }
    printf("Index created\n");
    delete idxInfo;
#endif


    Table *table = dbMgr->openTable("t1");
    if (table == NULL) { printf("Unable to open table\n"); return 4; }
    table->bindFld("f1", id);
    table->bindFld("f2", name);
    char *tuple;
    int ret;
    int i;
    rv =conn.startTransaction();
    for(i = 0; i< 5; i++)
    {
        if (rv != OK) exit(5);
      //  id= i;
        sprintf(id, "Value%d",i);
        strcpy(name, "PRABAKARAN0123456750590");
        ret = table->insertTuple();
        if (ret != 0) break;
    }
    conn.commit();

    conn.startTransaction();
    select(table, OpEquals);
    conn.commit();

    conn.startTransaction();
    select(table, OpNotEquals);
    conn.commit();

    conn.startTransaction();
    select(table, OpLessThan);
    conn.commit();

    conn.startTransaction();
    select( table, OpLessThanEquals);
    conn.commit();

    conn.startTransaction();
    select( table, OpGreaterThan);
    conn.commit();

    conn.startTransaction();
    select( table, OpGreaterThanEquals);
    conn.commit();

    dbMgr->closeTable(table);
    dbMgr->dropTable("t1");

    conn.close();
    return 0;
}
