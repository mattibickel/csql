echo create table t1(f1 int,f2 int);
Statement Executed
echo create table t2(f1 int,f2 int);
Statement Executed
echo create table t3(f1 int,f2 int);
Statement Executed
echo create index idx1 on t1(f1) hash;
Statement Executed
echo create index idx2 on t2(f1) hash;
Statement Executed
echo create index idx3 on t3(f1) hash;
Statement Executed
echo insert into t1 values(101,100);
Statement Executed: Rows Affected = 1
echo insert into t1 values(303,333);
Statement Executed: Rows Affected = 1
echo insert into t1 values(505,555);
Statement Executed: Rows Affected = 1
echo insert into t2 values(505,100);
Statement Executed: Rows Affected = 1
echo insert into t2 values(404,444);
Statement Executed: Rows Affected = 1
echo insert into t2 values(101,110);
Statement Executed: Rows Affected = 1
echo insert into t3 values(303,333);
Statement Executed: Rows Affected = 1
echo insert into t3 values(101,110);
Statement Executed: Rows Affected = 1
echo insert into t3 values(222,200);
Statement Executed: Rows Affected = 1
echo select * from t1,t2,t3 where t1.f1 = t2.f1 and t3.f1=100;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	t3.f1	t3.f2	
---------------------------------------------------------
	100	100	100	110	100	200	
	505	555	505	100	100	200	
	
echo select * from t2,t1,t3 where t1.f1 = t2.f1 and t3.f1=100;
---------------------------------------------------------
	t2.f1	t2.f2	t1.f1	t1.f2	t3.f1	t3.f2	
---------------------------------------------------------
	505	100	505	555	100	200	
	100	110	100	100	100	200	
	
echo select * from t3,t1,t2 where t1.f1 = t2.f1 and t3.f1=100;
---------------------------------------------------------
	t3.f1	t3.f2	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	100	200	100	100	100	110	
	100	200	505	555	505	100	
	
Statement Executed
Statement Executed
Statement Executed
