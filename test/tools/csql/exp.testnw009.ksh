Network CSql
echo create table t1 (f1 int,f2 date);
Statement Executed
echo insert into t1 values(1,'2008-10-29');
Statement Executed: Rows Affected = 1
echo insert into t1 values(2,'28-12-2008');
Statement prepare failed with error -16
echo insert into t1 values(3,'2008-2-30');
Statement prepare failed with error -16
echo insert into t1 values(4,'2008-3- -20');
Statement prepare failed with error -16
echo insert into t1 values(5,NULL);
Statement Executed: Rows Affected = 1
echo insert into t1 values(6,'2007-05-05');
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	2008/10/29	
	5	NULL	
	6	2007/5/5	
	
echo select * from t1 where f2<='2007-05-05';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	6	2007/5/5	
	
echo select * from t1 where f2>='2007-05-05';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1	2008/10/29	
	6	2007/5/5	
	
echo select * from t1 where f2='2007-05-05';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	6	2007/5/5	
	
echo drop table t1;
Statement Executed
