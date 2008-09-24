echo tinyint data type testing;
Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo select * from t1;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	1	
	11	1	
	12	1	
	13	1	
	-128	1	
	127	1	
	
echo select * from t1 where f1 = 10;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	1	
	
echo select * from t1 where f1 != 12 AND f2 <= 13;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	1	
	11	1	
	13	1	
	-128	1	
	127	1	
	
echo select * from t1 where f1 = 12 AND f2 >= 22;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1 = 12 OR  f1 > 13;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	12	1	
	127	1	
	
echo select * from t1 where f1 = 12 OR f2 < 13;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	1	
	11	1	
	12	1	
	13	1	
	-128	1	
	127	1	
	
echo select * from t1 where f1 = 12 OR f2 <> 22;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	1	
	11	1	
	12	1	
	13	1	
	-128	1	
	127	1	
	
echo select * from t1 where NOT f1 = 12;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	1	
	11	1	
	13	1	
	-128	1	
	127	1	
	
echo select * from t1 where f1 != 12;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	1	
	11	1	
	13	1	
	-128	1	
	127	1	
	
echo select * from t1 where NOT f1 != 12;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	12	1	
	
echo select * from t1 where f1 = f2;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo select * from t1 where f1 between 126 and 127;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	127	1	
	
echo select * from t1 where f1 between -127 and -128;
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	
echo update t1 set f2 = 2 where f1 != f2;
Statement Executed: Rows Affected = 6
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	2	
	11	2	
	12	2	
	13	2	
	-128	2	
	127	2	
	
echo update t1 set f2 = 3 where f1 = 12;
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	2	
	11	2	
	12	3	
	13	2	
	-128	2	
	127	2	
	
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	10	2	
	11	2	
	13	2	
	-128	2	
	127	2	
	
Statement Executed
