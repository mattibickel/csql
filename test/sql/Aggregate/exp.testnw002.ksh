Network CSql
echo select count(f1) from t1;
---------------------------------------------------------
	COUNT(t1.f1)	
---------------------------------------------------------
	5	
	
echo select count(*) from t1 where f4='AAA';
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	2	
	
echo select sum(f1) from t1;
---------------------------------------------------------
	SUM(t1.f1)	
---------------------------------------------------------
	500	
	
echo select avg(f1) from t1;
---------------------------------------------------------
	AVG(t1.f1)	
---------------------------------------------------------
	100.000000	
	
echo select min(t1.f1) from t1;
---------------------------------------------------------
	MIN(t1.f1)	
---------------------------------------------------------
	98	
	
echo select min(f4) from t1;
---------------------------------------------------------
	MIN(f4)	
---------------------------------------------------------
	AAA	
	
echo select max(t1.f1) from t1;
---------------------------------------------------------
	MAX(t1.f1)	
---------------------------------------------------------
	102	
	
echo select max(f4) from t1;
---------------------------------------------------------
	MAX(f4)	
---------------------------------------------------------
	CCC	
	
