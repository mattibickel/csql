Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2002/1/1 1:1:1.0	2002/1/1 1:1:1.0	
	2002/1/1 1:1:1.0	2002/2/3 1:1:1.0	
	2002/1/1 1:1:1.0	2002/3/1 1:1:1.0	
	2002/1/1 1:1:1.0	2004/2/1 1:1:1.0	
	2002/1/10 1:1:1.0	2004/2/1 1:1:1.0	
	2002/1/1 1:1:1.0	2004/3/1 1:1:1.0	
	2002/1/10 1:1:1.0	2004/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_diff(month,f1,f2)=0;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2002/1/1 1:1:1.0	2002/1/1 1:1:1.0	
	
echo select * from t1 where timestamp_diff(month,f2,f1)<=2;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2002/1/1 1:1:1.0	2002/1/1 1:1:1.0	
	2002/1/1 1:1:1.0	2002/2/3 1:1:1.0	
	2002/1/1 1:1:1.0	2002/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_diff(month,f2,f1)=25;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2002/1/1 1:1:1.0	2004/2/1 1:1:1.0	
	2002/1/10 1:1:1.0	2004/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_diff(month,f2,f1)>=25;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2002/1/1 1:1:1.0	2004/2/1 1:1:1.0	
	2002/1/1 1:1:1.0	2004/3/1 1:1:1.0	
	2002/1/10 1:1:1.0	2004/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_diff(month,f2,f1)=26;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2002/1/1 1:1:1.0	2004/3/1 1:1:1.0	
	
echo select * from t1 where timestamp_diff(month,f2,f1)!=26;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	2002/1/1 1:1:1.0	2002/1/1 1:1:1.0	
	2002/1/1 1:1:1.0	2002/2/3 1:1:1.0	
	2002/1/1 1:1:1.0	2002/3/1 1:1:1.0	
	2002/1/1 1:1:1.0	2004/2/1 1:1:1.0	
	2002/1/10 1:1:1.0	2004/2/1 1:1:1.0	
	2002/1/10 1:1:1.0	2004/3/1 1:1:1.0	
	
Statement Executed