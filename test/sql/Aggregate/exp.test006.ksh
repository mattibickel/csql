echo select * from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	98	1	10	
	99	2	20	
	100	3	30	
	101	4	40	
	102	5	50	
	
echo select min(t1.f2) from t1 group by t1.f1;
---------------------------------------------------------
		
---------------------------------------------------------
	1	
	2	
	3	
	4	
	5	
	
echo select avg(t1.f2) from t1 group by t1.f1;
---------------------------------------------------------
		
---------------------------------------------------------
	1	
	2	
	3	
	4	
	5	
	
echo select sum(t1.f2) from t1 group by notexist;
Statement prepare failed with error -19
echo select sum(t1.f2) from t1 group by t1.notexist;
Statement prepare failed with error -19
echo select sum(t1.f2) from t1 group by notexist.f1;
Statement prepare failed with error -19
