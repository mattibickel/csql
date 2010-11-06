echo Create table t1(f1 date, f2 date);
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
	2001/1/1	2001/1/1	
	2002/1/1	2001/2/1	
	2003/1/1	2001/3/1	
	2004/1/1	2001/4/1	
	2005/1/1	2001/5/1	
	
echo select * from t1 where date_sub(f2 interval  6 month)  = '2000-09-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/1	2001/3/1	
	
echo select * from t1 where date_sub(f2 interval  6 month) <= '2000-09-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	2001/1/1	
	2002/1/1	2001/2/1	
	2003/1/1	2001/3/1	
	
echo select * from t1 where date_sub(f2 interval  6 month) >= '2000-09-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/1	2001/3/1	
	2004/1/1	2001/4/1	
	2005/1/1	2001/5/1	
	
echo select * from t1 where date_sub(f2 interval 18 month)  = '1999-09-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/1	2001/3/1	
	
echo select * from t1 where date_sub(f2 interval 18 month) <= '1999-09-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	2001/1/1	
	2002/1/1	2001/2/1	
	2003/1/1	2001/3/1	
	
echo select * from t1 where date_sub(f2 interval 18 month) >= '1999-09-01';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/1	2001/3/1	
	2004/1/1	2001/4/1	
	2005/1/1	2001/5/1	
	
Statement Executed
