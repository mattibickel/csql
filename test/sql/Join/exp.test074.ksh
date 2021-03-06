echo create table t1(f1 int,f2 int);
Statement Executed
echo create index idx1 on t1(f1,f2) hash;
Statement Executed
echo create table t2(f1 int,f2 int);
Statement Executed
echo create index idx2 on t2(f2,f1) hash;
Statement Executed
echo insert into t1 values(101,100);
Statement Executed: Rows Affected = 1
echo insert into t1 values(303,333);
Statement Executed: Rows Affected = 1
echo insert into t1 values(505,555);
Statement Executed: Rows Affected = 1
echo insert into t2 values(505,100);
Statement Executed: Rows Affected = 1
echo insert into t2 values(100,101);
Statement Executed: Rows Affected = 1
echo insert into t2 values(404,444);
Statement Executed: Rows Affected = 1
echo insert into t2 values(303,333);
Statement Executed: Rows Affected = 1
echo insert into t2 values(101,100);
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	101	100	
	303	333	
	505	555	
	
echo select * from t2;
---------------------------------------------------------
	t2.f1	t2.f2	
---------------------------------------------------------
	505	100	
	100	101	
	404	444	
	303	333	
	101	100	
	
echo select * from t1,t2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	505	100	
	101	100	100	101	
	101	100	404	444	
	101	100	303	333	
	101	100	101	100	
	303	333	505	100	
	303	333	100	101	
	303	333	404	444	
	303	333	303	333	
	303	333	101	100	
	505	555	505	100	
	505	555	100	101	
	505	555	404	444	
	505	555	303	333	
	505	555	101	100	
	
echo select * from t1,t2 where t1.f1=t2.f1 and t1.f2=t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	101	100	
	303	333	303	333	
	
echo select * from t1,t2 where t1.f2=t2.f2 and t1.f1=t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	101	100	
	303	333	303	333	
	
echo select * from t1,t2 where t1.f1>t2.f1 and t1.f2>t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	303	333	100	101	
	303	333	101	100	
	505	555	100	101	
	505	555	404	444	
	505	555	303	333	
	505	555	101	100	
	
echo select * from t1,t2 where t1.f2<t2.f2 and t1.f1<=t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	404	444	
	101	100	303	333	
	303	333	404	444	
	
echo select * from t1,t2 where t1.f1=t2.f1 or t1.f2=t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	505	100	
	101	100	101	100	
	303	333	303	333	
	505	555	505	100	
	
echo select * from t1,t2 where t1.f2=t2.f2 or t1.f1=t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	505	100	
	101	100	101	100	
	303	333	303	333	
	505	555	505	100	
	
echo select * from t1,t2 where t1.f1>t2.f1 or t1.f2>=t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	505	100	
	101	100	100	101	
	101	100	101	100	
	303	333	505	100	
	303	333	100	101	
	303	333	303	333	
	303	333	101	100	
	505	555	505	100	
	505	555	100	101	
	505	555	404	444	
	505	555	303	333	
	505	555	101	100	
	
echo select * from t1,t2 where t1.f2<t2.f2 or t1.f1<t2.f1;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	505	100	
	101	100	100	101	
	101	100	404	444	
	101	100	303	333	
	303	333	505	100	
	303	333	404	444	
	
echo select * from t1,t2 where t1.f1>t2.f1 or t1.f2>t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	100	101	
	303	333	505	100	
	303	333	100	101	
	303	333	101	100	
	505	555	505	100	
	505	555	100	101	
	505	555	404	444	
	505	555	303	333	
	505	555	101	100	
	
echo select * from t1,t2 where t1.f1=t2.f1 and not(t1.f2=t2.f2);
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	505	555	505	100	
	
echo select * from t1,t2 where t1.f2=t2.f2 and not(t1.f1=t2.f1);
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	505	100	
	
echo select * from t1,t2 where not(t1.f1>t2.f1) and t1.f2>t2.f2;
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	303	333	505	100	
	505	555	505	100	
	
echo select * from t1,t2 where not(t1.f2<t2.f2) and not(t1.f1<t2.f1);
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	101	100	
	303	333	100	101	
	303	333	303	333	
	303	333	101	100	
	505	555	505	100	
	505	555	100	101	
	505	555	404	444	
	505	555	303	333	
	505	555	101	100	
	
echo select * from t1,t2 where not(t1.f1=t2.f1) or not(t1.f2=t2.f2);
---------------------------------------------------------
	t1.f1	t1.f2	t2.f1	t2.f2	
---------------------------------------------------------
	101	100	505	100	
	101	100	100	101	
	101	100	404	444	
	101	100	303	333	
	303	333	505	100	
	303	333	100	101	
	303	333	404	444	
	303	333	101	100	
	505	555	505	100	
	505	555	100	101	
	505	555	404	444	
	505	555	303	333	
	505	555	101	100	
	
Statement Executed
Statement Executed
