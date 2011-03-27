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
	2003/1/3	2002/3/2	
	2004/1/1	2002/4/2	
	2005/1/1	2003/5/3	
	
echo select * from t1 where extract(day from f2) = 02;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/3	2002/3/2	
	2004/1/1	2002/4/2	
	
echo select * from t1 where extract(day from f2) < 02;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	2001/1/1	
	2002/1/1	2001/2/1	
	
echo select * from t1 where extract(day from f2)<= 02;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	2001/1/1	
	2002/1/1	2001/2/1	
	2003/1/3	2002/3/2	
	2004/1/1	2002/4/2	
	
echo select * from t1 where extract(day from f2) > 02;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2005/1/1	2003/5/3	
	
echo select * from t1 where extract(day from f2)>= 02;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2003/1/3	2002/3/2	
	2004/1/1	2002/4/2	
	2005/1/1	2003/5/3	
	
echo select * from t1 where extract(day from f2)!= 02;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2001/1/1	2001/1/1	
	2002/1/1	2001/2/1	
	2005/1/1	2003/5/3	
	
Statement Executed