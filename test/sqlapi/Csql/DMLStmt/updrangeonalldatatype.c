/*
  Testing update on all datatypes using in-between-like  operators
  CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP);
  Insert 5 records into t1.
  INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');
  INSERT INTO t1 VALUES(2,22,222,2222,'CSQL2','LAKSHYA2',22.00,2222.00,'2002-02-02','02:02:02','2002-02-02 02:02:02');
  INSERT INTO t1 VALUES(3,33,333,3333,'CSQL3','LAKSHYA3',33.00,3333.00,'2003-03-03','03:03:03','2003-03-03 03:03:03');
  INSERT INTO t1 VALUES(4,44,444,4444,'CSQL4','LAKSHYA4',44.00,4444.00,'2004-04-04','04:04:04','2004-04-04 04:04:04');
  INSERT INTO t1 VALUES(5,55,555,5555,'CSQL5','LAKSHYA5',55.00,5555.00,'2005-05-05','05:05:05','2005-05-05 05:05:05');
  UPDATE t1 SET f1=f1+10, f2=f2+100, f3=f3+1000, f4=f4+10000, f5='CSQLMMDB1', f6='LAKSHYA_BANGALORE1', f7=f7+100, f8=f8+10000,f9='2001-01-11', f10='01:01:11', f11='2001-01-11 01:01:11' WHERE f1 in (20,1,30) and (f2 between 10 and 12) and f3 in (110,111) and (f4 between 1000 and 1112);
  UPDATE t1 SET f1=f1+40, f2=f2+400, f3=f3+4000, f4=f4+40000, f5='CSQLMMDB4', f6='LAKSHYA_BANGALORE4', f7=f7+400, f8=f8+40000,f9='2004-04-14', f10='04:04:14', f11='2004-04-14 04:04:14' WHERE f3<=3333 and f6<='LAKSHYA6' and not(f3 = 3333 or f3 = 555) and (f6 = 'LAKSHYA4' or f6='LAKSHYA_BANGALORE3') or f9 in ('2004/4/4','2002-02-02','2001-01-01');  
  UPDATE t1 SET f1=f1+50, f2=f2+500, f3=f3+5000, f4=f4+50000, f5='CSQLMMDB5', f6='LAKSHYA_BANGALORE5', f7=f7+500, f8=f8+50000,f9='2005-05-15', f10='05:05:15', f11='2005-05-15 05:05:15' WHERE (f1=5 and f2=55 and f3=555 and f4=5555 and f5='CSQL5' and f6 like 'LAKSHYA%' and f7=55 and f8=5555 and f9='2005/05/05' and f10 in ('05:05:05')) or f11 in ('2005/05/05 05:05:05','2004-04-14 04:04:14');
  SELECT * FROM t1;
*/
#include"common.h"

int main()
{
    DbRetVal rv = OK;
    AbsSqlConnection *con = createConnection();
    rv = con->connect("root","manager");
    if(rv !=OK) {
        delete con;
        return 1;
    }
    printf("Connection opened\n");
    AbsSqlStatement *stmt = createStatement();
    stmt->setConnection(con);
//Creating Table
    char statement[400];
    printf("CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP);\n");
    strcpy(statement,"CREATE TABLE t1(f1 TINYINT,f2 SMALLINT,f3 INT,f4 BIGINT,f5 CHAR(20),f6 VARCHAR(30),f7 FLOAT,f8 DOUBLE,f9 DATE,f10 TIME,f11 TIMESTAMP);");
    int rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 2; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 3; }
    stmt->free();
// Show all tables
    strcpy(statement,"GETALLTABLES;");
    rows=0;
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 4; }    
    stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 5; }
    while(stmt->next() !=NULL) {
	printf("Table Name is %s\n",stmt->getFieldValuePtr(2));  //stmt->getFieldValuePtr(2) returns the TABLE_NAME (src/sql/SqlStatement.cxx)
    }
    stmt->free();

//Inserting Records
    con->beginTrans();
    rows=0;
    printf("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');\n");
    stmt->prepare("INSERT INTO t1 VALUES(1,11,111,1111,'CSQL1','LAKSHYA1',11.00,1111.00,'2001-01-01','01:01:01','2001-01-01 01:01:01');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(2,22,222,2222,'CSQL2','LAKSHYA2',22.00,2222.00,'2002-02-02','02:02:02','2002-02-02 02:02:02');\n");
    stmt->prepare("INSERT INTO t1 VALUES(2,22,222,2222,'CSQL2','LAKSHYA2',22.00,2222.00,'2002-02-02','02:02:02','2002-02-02 02:02:02');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(3,33,333,3333,'CSQL3','LAKSHYA3',33.00,3333.00,'2003-03-03','03:03:03','2003-03-03 03:03:03');\n");
    stmt->prepare("INSERT INTO t1 VALUES(3,33,333,3333,'CSQL3','LAKSHYA3',33.00,3333.00,'2003-03-03','03:03:03','2003-03-03 03:03:03');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(4,44,444,4444,'CSQL4','LAKSHYA4',44.00,4444.00,'2004-04-04','04:04:04','2004-04-04 04:04:04');\n");
    stmt->prepare("INSERT INTO t1 VALUES(4,44,444,4444,'CSQL4','LAKSHYA4',44.00,4444.00,'2004-04-04','04:04:04','2004-04-04 04:04:04');");
    stmt->execute(rows);
    printf("INSERT INTO t1 VALUES(5,55,555,5555,'CSQL5','LAKSHYA5',55.00,5555.00,'2005-05-05','05:05:05','2005-05-05 05:05:05');\n");
    stmt->prepare("INSERT INTO t1 VALUES(5,55,555,5555,'CSQL5','LAKSHYA5',55.00,5555.00,'2005-05-05','05:05:05','2005-05-05 05:05:05');");
    stmt->execute(rows);
    con->commit();
    stmt->free();

    char f1var;
    short int f2var;
    int f3var;
    long long f4var;
    char f5var[20];
    char f6var[32];
    float f7var;
    double f8var;
    Date f9var;
    Time f10var;
    TimeStamp f11var;
    
//Fetching records after insert
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 6; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    stmt->bindField(11,&f11var);
    int count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 7;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1(tinyint)=NULL | ");
        else printf("f1(tinyint)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(smallint)=NULL | ");
        else printf("f2(smallint)=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(int)=NULL | ");
        else printf("f3(int)=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(bigint)=NULL | ");
        else printf("f4(bigint)=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5(char)=NULL | ");
        else printf("f5(char)=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6(varchar)=NULL | ");
        else printf("f6(varchar)=%s | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(float)=NULL | ");
        else printf("f7(float)=%f | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(double)=NULL | ");
        else printf("f8(double)=%lf | ", f8var);
	if(stmt->isFldNull(9)) printf("f9(date)=NULL | ");
        else printf("f9(date)=%02d-%02d-%02d | ", f9var.year(),f9var.month(),f9var.dayOfMonth());
	if(stmt->isFldNull(10)) printf("f10(time)=NULL | ");
        else printf("f10(time)=%02d:%02d:%02d | ", f10var.hours(),f10var.minutes(),f10var.seconds());
	if(stmt->isFldNull(11)) printf("f11(timestamp)=NULL | ");
        else printf("f11(timestamp)=%d-%d-%d %d:%d:%d | ", f11var.year(),f11var.month(),f11var.dayOfMonth(),f11var.hours(),f11var.minutes(),f11var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);
      
//Updating records.
    con->beginTrans();
    printf("UPDATE t1 SET f1=f1+10, f2=f2+100, f3=f3+1000, f4=f4+10000, f5='CSQLMMDB1', f6='LAKSHYA_BANGALORE1', f7=f7+100, f8=f8+10000,f9='2001-01-11', f10='01:01:11', f11='2001-01-11 01:01:11' WHERE f1 in (20,1,30) and (f2 between 10 and 12) and f3 in (110,111) and (f4 between 1000 and 1112);\n");
    strcpy(statement,"UPDATE t1 SET f1=f1+10, f2=f2+100, f3=f3+1000, f4=f4+10000, f5='CSQLMMDB1', f6='LAKSHYA_BANGALORE1', f7=f7+100, f8=f8+10000,f9='2001-01-11', f10='01:01:11', f11='2001-01-11 01:01:11' WHERE f1 in (20,1,30) and (f2 between 10 and 12) and f3 in (110,111) and (f4 between 1000 and 1112);");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 8; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 9; }

    con->beginTrans();
    printf("UPDATE t1 SET f1=f1+40, f2=f2+400, f3=f3+4000, f4=f4+40000, f5='CSQLMMDB4', f6='LAKSHYA_BANGALORE4', f7=f7+400, f8=f8+40000,f9='2004-04-14', f10='04:04:14', f11='2004-04-14 04:04:14' WHERE f3<=3333 and f6<='LAKSHYA6' and not(f3 = 3333 or f3 = 555) and (f6 = 'LAKSHYA4' or f6='LAKSHYA_BANGALORE3') or f9 in ('2004/4/4','2002-02-02','2001-01-01');\n");
    strcpy(statement,"UPDATE t1 SET f1=f1+40, f2=f2+400, f3=f3+4000, f4=f4+40000, f5='CSQLMMDB4', f6='LAKSHYA_BANGALORE4', f7=f7+400, f8=f8+40000,f9='2004-04-14', f10='04:04:14', f11='2004-04-14 04:04:14' WHERE f3<=3333 and f6<='LAKSHYA6' and not(f3 = 3333 or f3 = 555) and (f6 = 'LAKSHYA4' or f6='LAKSHYA_BANGALORE3') or f9 in ('2004/4/4','2002-02-02','2001-01-01');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 10; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 11; }

    con->beginTrans();
    printf("UPDATE t1 SET f1=f1+50, f2=f2+500, f3=f3+5000, f4=f4+50000, f5='CSQLMMDB5', f6='LAKSHYA_BANGALORE5', f7=f7+500, f8=f8+50000,f9='2005-05-15', f10='05:05:15', f11='2005-05-15 05:05:15' WHERE (f1=5 and f2=55 and f3=555 and f4=5555 and f5='CSQL5' and f6 like 'LAKSHYA_' and f7=55 and f8=5555 and f9='2005/05/05' and f10 in ('05:05:05')) or f11 in ('2005/05/05 05:05:05','2004-04-14 04:04:14');\n");
    strcpy(statement,"UPDATE t1 SET f1=f1+50, f2=f2+500, f3=f3+5000, f4=f4+50000, f5='CSQLMMDB5', f6='LAKSHYA_BANGALORE5', f7=f7+500, f8=f8+50000,f9='2005-05-15', f10='05:05:15', f11='2005-05-15 05:05:15' WHERE (f1=5 and f2=55 and f3=555 and f4=5555 and f5='CSQL5' and f6 like 'LAKSHYA_' and f7=55 and f8=5555 and f9='2005/05/05' and f10 in ('05:05:05')) or f11 in ('2005/05/05 05:05:05','2004-04-14 04:04:14');");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 12; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 13; }

//Fetching records after Update
    strcpy(statement,"SELECT * FROM t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; delete con; return 14; }
    stmt->bindField(1,&f1var);
    stmt->bindField(2,&f2var);
    stmt->bindField(3,&f3var);
    stmt->bindField(4,&f4var);
    stmt->bindField(5,f5var);
    stmt->bindField(6,f6var);
    stmt->bindField(7,&f7var);
    stmt->bindField(8,&f8var);
    stmt->bindField(9,&f9var);
    stmt->bindField(10,&f10var);
    stmt->bindField(11,&f11var);
    count=0;
    rv = con->beginTrans();
    if(rv!=OK)return 15;
    stmt->execute(rows);
    while(stmt->fetch() !=NULL) {
	if(stmt->isFldNull(1)) printf("f1(tinyint)=NULL | ");
        else printf("f1(tinyint)=%d | ", f1var);
	if(stmt->isFldNull(2)) printf("f2(smallint)=NULL | ");
        else printf("f2(smallint)=%d | ", f2var);
	if(stmt->isFldNull(3)) printf("f3(int)=NULL | ");
        else printf("f3(int)=%d | ", f3var);
	if(stmt->isFldNull(4)) printf("f4(bigint)=NULL | ");
        else printf("f4(bigint)=%lld | ", f4var);
	if(stmt->isFldNull(5)) printf("f5(char)=NULL | ");
        else printf("f5(char)=%s | ", f5var);
	if(stmt->isFldNull(6)) printf("f6(varchar)=NULL | ");
        else printf("f6(varchar)=%s | ", f6var);
	if(stmt->isFldNull(7)) printf("f7(float)=NULL | ");
        else printf("f7(float)=%f | ", f7var);
	if(stmt->isFldNull(8)) printf("f8(double)=NULL | ");
        else printf("f8(double)=%lf | ", f8var);
	if(stmt->isFldNull(9)) printf("f9(date)=NULL | ");
        else printf("f9(date)=%02d-%02d-%02d | ", f9var.year(),f9var.month(),f9var.dayOfMonth());
	if(stmt->isFldNull(10)) printf("f10(time)=NULL | ");
        else printf("f10(time)=%02d:%02d:%02d | ", f10var.hours(),f10var.minutes(),f10var.seconds());
	if(stmt->isFldNull(11)) printf("f11(timestamp)=NULL | ");
        else printf("f11(timestamp)=%d-%d-%d %d:%d:%d | ", f11var.year(),f11var.month(),f11var.dayOfMonth(),f11var.hours(),f11var.minutes(),f11var.seconds());
        printf("\n");
        count++;
    }
    stmt->free();
    rv = con->commit();    
    printf("%d rows selected\n",count);

//Droping table
    strcpy(statement,"DROP TABLE t1;");
    rv = stmt->prepare(statement);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 16; }
    rv = stmt->execute(rows);
    if(rv!=OK) { delete stmt; con->disconnect(); delete con; return 17; }
    printf("Table dropped\n");
    stmt->free();
    con->disconnect();
    printf("Connection Closed\n");

    delete stmt; delete con;
    return 0;
}

