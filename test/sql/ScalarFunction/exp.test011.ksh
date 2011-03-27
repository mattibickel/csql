echo Create table t1(f1 time, f2 time);
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1:1:1.0	1:30:1.0	
	2:1:1.0	2:30:1.0	
	3:1:1.0	3:30:1.0	
	4:1:1.0	4:30:1.0	
	5:1:1.0	5:30:1.0	
	
echo select * from t1 where time_add(f2 interval 1800 second)  = '04:00:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	3:1:1.0	3:30:1.0	
	
echo select * from t1 where time_add(f2 interval 1800 second) <= '04:00:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1:1:1.0	1:30:1.0	
	2:1:1.0	2:30:1.0	
	3:1:1.0	3:30:1.0	
	
echo select * from t1 where time_add(f2 interval 1800 second) >= '04:00:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	3:1:1.0	3:30:1.0	
	4:1:1.0	4:30:1.0	
	5:1:1.0	5:30:1.0	
	
echo select * from t1 where time_add(f2 interval 14400 second)  = '07:30:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	3:1:1.0	3:30:1.0	
	
echo select * from t1 where time_add(f2 interval 14400 second) <= '07:30:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1:1:1.0	1:30:1.0	
	2:1:1.0	2:30:1.0	
	3:1:1.0	3:30:1.0	
	
echo select * from t1 where time_add(f2 interval 72000 second) >= '21:30:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	1:1:1.0	1:30:1.0	
	2:1:1.0	2:30:1.0	
	3:1:1.0	3:30:1.0	
	
echo select * from t1 where time_add(f2 interval 72000 second) < '21:30:01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	4:1:1.0	4:30:1.0	
	5:1:1.0	5:30:1.0	
	
Statement Executed