Network CSql
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement execute failed with error -21
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	200	
	11	210	
	20	500	
	13	230	
	14	240	
	50	500	
	5	500	
	12	240	
	
echo select count(*) from t1;
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	8	
	
echo select count(f1) from t1;
---------------------------------------------------------
	COUNT(f1)	
---------------------------------------------------------
	8	
	
echo select count(f2) from t1;
---------------------------------------------------------
	COUNT(f2)	
---------------------------------------------------------
	8	
	
echo select * from t1 where f1 =11;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	11	210	
	
echo select count(*) from t1 where f1 = 11;
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	1	
	
echo select count(f1) from t1 where f1=20;
---------------------------------------------------------
	COUNT(f1)	
---------------------------------------------------------
	1	
	
echo select count(f2) from t1 where f2=500;
---------------------------------------------------------
	COUNT(f2)	
---------------------------------------------------------
	3	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	200	
	11	210	
	20	500	
	13	230	
	14	240	
	50	500	
	5	500	
	12	240	
	
echo select min(f1) from t1;
---------------------------------------------------------
	MIN(f1)	
---------------------------------------------------------
	5	
	
echo select min(f2) from t1;
---------------------------------------------------------
	MIN(f2)	
---------------------------------------------------------
	200	
	
echo select min(f1) from t1 where f1=20;
---------------------------------------------------------
	MIN(f1)	
---------------------------------------------------------
	20	
	
echo select min(f2) from t1 where f2=500;
---------------------------------------------------------
	MIN(f2)	
---------------------------------------------------------
	500	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	200	
	11	210	
	20	500	
	13	230	
	14	240	
	50	500	
	5	500	
	12	240	
	
echo select max(f1) from t1;
---------------------------------------------------------
	MAX(f1)	
---------------------------------------------------------
	50	
	
echo select max(f2) from t1;
---------------------------------------------------------
	MAX(f2)	
---------------------------------------------------------
	500	
	
echo select max(f1) from t1 where f1=20;
---------------------------------------------------------
	MAX(f1)	
---------------------------------------------------------
	20	
	
echo select max(f2) from t1 where f2=500;
---------------------------------------------------------
	MAX(f2)	
---------------------------------------------------------
	500	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	200	
	11	210	
	20	500	
	13	230	
	14	240	
	50	500	
	5	500	
	12	240	
	
echo select avg(f1) from t1;
---------------------------------------------------------
	AVG(f1)	
---------------------------------------------------------
	16.875000	
	
echo select avg(f2) from t1;
---------------------------------------------------------
	AVG(f2)	
---------------------------------------------------------
	327.500000	
	
echo select avg(f1) from t1 where f1=20;
---------------------------------------------------------
	AVG(f1)	
---------------------------------------------------------
	20.000000	
	
echo select avg(f2) from t1 where f2=500;
---------------------------------------------------------
	AVG(f2)	
---------------------------------------------------------
	500.000000	
	
echo select * from t1;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	200	
	11	210	
	20	500	
	13	230	
	14	240	
	50	500	
	5	500	
	12	240	
	
echo select sum(f1) from t1;
---------------------------------------------------------
	SUM(f1)	
---------------------------------------------------------
	135	
	
echo select sum(f2) from t1;
---------------------------------------------------------
	SUM(f2)	
---------------------------------------------------------
	2620	
	
echo select sum(f1) from t1 where f1=20;
---------------------------------------------------------
	SUM(f1)	
---------------------------------------------------------
	20	
	
echo select sum(f2) from t1 where f2=500;
---------------------------------------------------------
	SUM(f2)	
---------------------------------------------------------
	1500	
	
echo drop table t1;
Statement Executed
