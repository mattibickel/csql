Statement Executed
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f0	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	t1.f6	t1.f7	t1.f8	t1.f9	
---------------------------------------------------------
	1	10	100	1000	Bijay	1000.000000	100000.000000	2009/3/1	11:59:59.0	2009/3/1 11:59:59.0	
	NULL	11	110	1100	Jitendr	NULL	200000.000000	2009/3/2	NULL	2009/3/2 11:59:59.0	
	3	12	120	1000	NULL	3000.000000	NULL	NULL	11:59:57.0	2009/3/3 11:59:59.0	
	4	NULL	NULL	1100	Kishor	4000.000000	400000.000000	2009/3/4	11:59:59.0	2009/3/4 11:59:59.0	
	5	14	100	1000	Praba	5000.000000	500000.000000	2009/3/1	NULL	2009/3/1 11:59:59.0	
	6	15	110	NULL	Sanjit	6000.000000	600000.000000	2009/3/2	11:59:57.0	2009/3/2 11:59:59.0	
	7	16	120	1000	Sanjay	7000.000000	700000.000000	NULL	11:59:59.0	2009/3/3 11:59:59.0	
	1	17	NULL	1100	Arindam	8000.000000	800000.000000	2009/3/4	NULL	2009/3/4 11:59:59.0	
	NULL	10	100	NULL	Bijay	9000.000000	900000.000000	2009/3/1	11:59:57.0	2009/3/1 11:59:59.0	
	3	11	110	1100	Jitendr	1000.000000	100000.000000	NULL	NULL	2009/3/2 11:59:59.0	
	4	12	120	1000	NULL	NULL	200000.000000	NULL	11:59:57.0	2009/3/3 11:59:59.0	
	5	NULL	NULL	NULL	NULL	3000.000000	NULL	2009/3/5	11:59:56.0	2009/3/5 11:59:59.0	
	6	14	100	1000	Praba	4000.000000	400000.000000	2009/3/1	11:59:55.0	2009/3/4 11:59:59.0	
	7	15	110	1100	Sanjit	5000.000000	500000.000000	2009/3/2	11:59:56.0	2009/3/1 11:59:59.0	
	NULL	NULL	120	1000	Sanjay	NULL	NULL	NULL	NULL	2009/3/3 11:59:59.0	
	NULL	17	130	1100	Arindam	7000.000000	700000.000000	2009/3/1	11:59:59.0	2009/3/1 11:59:59.0	
	
echo select distinct f0 from t1;
---------------------------------------------------------
	f0	
---------------------------------------------------------
	1	
	NULL	
	3	
	4	
	5	
	6	
	7	
	
echo select distinct f1 from t1;
---------------------------------------------------------
	f1	
---------------------------------------------------------
	10	
	11	
	12	
	NULL	
	14	
	15	
	16	
	17	
	
echo select distinct f2 from t1;
---------------------------------------------------------
	f2	
---------------------------------------------------------
	100	
	110	
	120	
	NULL	
	130	
	
echo select distinct f3 from t1;
---------------------------------------------------------
	f3	
---------------------------------------------------------
	1000	
	1100	
	NULL	
	
echo select distinct f4 from t1;
---------------------------------------------------------
	f4	
---------------------------------------------------------
	Bijay	
	Jitendr	
	NULL	
	Kishor	
	Praba	
	Sanjit	
	Sanjay	
	Arindam	
	
echo select distinct f5 from t1;
---------------------------------------------------------
	f5	
---------------------------------------------------------
	1000.000000	
	NULL	
	3000.000000	
	4000.000000	
	5000.000000	
	6000.000000	
	7000.000000	
	8000.000000	
	9000.000000	
	
echo select distinct f6 from t1;
---------------------------------------------------------
	f6	
---------------------------------------------------------
	100000.000000	
	200000.000000	
	NULL	
	400000.000000	
	500000.000000	
	600000.000000	
	700000.000000	
	800000.000000	
	900000.000000	
	
echo select distinct f7 from t1;
---------------------------------------------------------
	f7	
---------------------------------------------------------
	2009/3/1	
	2009/3/2	
	NULL	
	2009/3/4	
	2009/3/5	
	
echo select distinct f8 from t1;
---------------------------------------------------------
	f8	
---------------------------------------------------------
	11:59:59.0	
	NULL	
	11:59:57.0	
	11:59:56.0	
	11:59:55.0	
	
echo select distinct f9 from t1;
---------------------------------------------------------
	f9	
---------------------------------------------------------
	2009/3/1 11:59:59.0	
	2009/3/2 11:59:59.0	
	2009/3/3 11:59:59.0	
	2009/3/4 11:59:59.0	
	2009/3/5 11:59:59.0	
	
echo select distinct f1,f2,f3 from t1;
---------------------------------------------------------
	f1	f2	f3	
---------------------------------------------------------
	10	100	1000	
	11	110	1100	
	12	120	1000	
	NULL	NULL	1100	
	14	100	1000	
	15	110	NULL	
	16	120	1000	
	17	NULL	1100	
	10	100	NULL	
	NULL	NULL	NULL	
	15	110	1100	
	NULL	120	1000	
	17	130	1100	
	
echo select distinct f0,f1,f2,f3 from t1;
---------------------------------------------------------
	f0	f1	f2	f3	
---------------------------------------------------------
	1	10	100	1000	
	NULL	11	110	1100	
	3	12	120	1000	
	4	NULL	NULL	1100	
	5	14	100	1000	
	6	15	110	NULL	
	7	16	120	1000	
	1	17	NULL	1100	
	NULL	10	100	NULL	
	3	11	110	1100	
	4	12	120	1000	
	5	NULL	NULL	NULL	
	6	14	100	1000	
	7	15	110	1100	
	NULL	NULL	120	1000	
	NULL	17	130	1100	
	
echo select distinct f2,f3 from t1;
---------------------------------------------------------
	f2	f3	
---------------------------------------------------------
	100	1000	
	110	1100	
	120	1000	
	NULL	1100	
	110	NULL	
	100	NULL	
	NULL	NULL	
	130	1100	
	
echo select distinct f2,f3,f4,f5 from t1;
---------------------------------------------------------
	f2	f3	f4	f5	
---------------------------------------------------------
	100	1000	Bijay	1000.000000	
	110	1100	Jitendr	NULL	
	120	1000	NULL	3000.000000	
	NULL	1100	Kishor	4000.000000	
	100	1000	Praba	5000.000000	
	110	NULL	Sanjit	6000.000000	
	120	1000	Sanjay	7000.000000	
	NULL	1100	Arindam	8000.000000	
	100	NULL	Bijay	9000.000000	
	110	1100	Jitendr	1000.000000	
	120	1000	NULL	NULL	
	NULL	NULL	NULL	3000.000000	
	100	1000	Praba	4000.000000	
	110	1100	Sanjit	5000.000000	
	120	1000	Sanjay	NULL	
	130	1100	Arindam	7000.000000	
	
echo select distinct f2,f3,f4,f5,f6 from t1;
---------------------------------------------------------
	f2	f3	f4	f5	f6	
---------------------------------------------------------
	100	1000	Bijay	1000.000000	100000.000000	
	110	1100	Jitendr	NULL	200000.000000	
	120	1000	NULL	3000.000000	NULL	
	NULL	1100	Kishor	4000.000000	400000.000000	
	100	1000	Praba	5000.000000	500000.000000	
	110	NULL	Sanjit	6000.000000	600000.000000	
	120	1000	Sanjay	7000.000000	700000.000000	
	NULL	1100	Arindam	8000.000000	800000.000000	
	100	NULL	Bijay	9000.000000	900000.000000	
	110	1100	Jitendr	1000.000000	100000.000000	
	120	1000	NULL	NULL	200000.000000	
	NULL	NULL	NULL	3000.000000	NULL	
	100	1000	Praba	4000.000000	400000.000000	
	110	1100	Sanjit	5000.000000	500000.000000	
	120	1000	Sanjay	NULL	NULL	
	130	1100	Arindam	7000.000000	700000.000000	
	
echo select distinct f4,f6,f2,f5,f3,f7,f8 from t1;
---------------------------------------------------------
	f4	f6	f2	f5	f3	f7	f8	
---------------------------------------------------------
	Bijay	100000.000000	100	1000.000000	1000	2009/3/1	11:59:59.0	
	Jitendr	200000.000000	110	NULL	1100	2009/3/2	NULL	
	NULL	NULL	120	3000.000000	1000	NULL	11:59:57.0	
	Kishor	400000.000000	NULL	4000.000000	1100	2009/3/4	11:59:59.0	
	Praba	500000.000000	100	5000.000000	1000	2009/3/1	NULL	
	Sanjit	600000.000000	110	6000.000000	NULL	2009/3/2	11:59:57.0	
	Sanjay	700000.000000	120	7000.000000	1000	NULL	11:59:59.0	
	Arindam	800000.000000	NULL	8000.000000	1100	2009/3/4	NULL	
	Bijay	900000.000000	100	9000.000000	NULL	2009/3/1	11:59:57.0	
	Jitendr	100000.000000	110	1000.000000	1100	NULL	NULL	
	NULL	200000.000000	120	NULL	1000	NULL	11:59:57.0	
	NULL	NULL	NULL	3000.000000	NULL	2009/3/5	11:59:56.0	
	Praba	400000.000000	100	4000.000000	1000	2009/3/1	11:59:55.0	
	Sanjit	500000.000000	110	5000.000000	1100	2009/3/2	11:59:56.0	
	Sanjay	NULL	120	NULL	1000	NULL	NULL	
	Arindam	700000.000000	130	7000.000000	1100	2009/3/1	11:59:59.0	
	
echo select distinct f2,f3,f4,f5,f8,f7,f9,f6 from t1;
---------------------------------------------------------
	f2	f3	f4	f5	f8	f7	f9	f6	
---------------------------------------------------------
	100	1000	Bijay	1000.000000	11:59:59.0	2009/3/1	2009/3/1 11:59:59.0	100000.000000	
	110	1100	Jitendr	NULL	NULL	2009/3/2	2009/3/2 11:59:59.0	200000.000000	
	120	1000	NULL	3000.000000	11:59:57.0	NULL	2009/3/3 11:59:59.0	NULL	
	NULL	1100	Kishor	4000.000000	11:59:59.0	2009/3/4	2009/3/4 11:59:59.0	400000.000000	
	100	1000	Praba	5000.000000	NULL	2009/3/1	2009/3/1 11:59:59.0	500000.000000	
	110	NULL	Sanjit	6000.000000	11:59:57.0	2009/3/2	2009/3/2 11:59:59.0	600000.000000	
	120	1000	Sanjay	7000.000000	11:59:59.0	NULL	2009/3/3 11:59:59.0	700000.000000	
	NULL	1100	Arindam	8000.000000	NULL	2009/3/4	2009/3/4 11:59:59.0	800000.000000	
	100	NULL	Bijay	9000.000000	11:59:57.0	2009/3/1	2009/3/1 11:59:59.0	900000.000000	
	110	1100	Jitendr	1000.000000	NULL	NULL	2009/3/2 11:59:59.0	100000.000000	
	120	1000	NULL	NULL	11:59:57.0	NULL	2009/3/3 11:59:59.0	200000.000000	
	NULL	NULL	NULL	3000.000000	11:59:56.0	2009/3/5	2009/3/5 11:59:59.0	NULL	
	100	1000	Praba	4000.000000	11:59:55.0	2009/3/1	2009/3/4 11:59:59.0	400000.000000	
	110	1100	Sanjit	5000.000000	11:59:56.0	2009/3/2	2009/3/1 11:59:59.0	500000.000000	
	120	1000	Sanjay	NULL	NULL	NULL	2009/3/3 11:59:59.0	NULL	
	130	1100	Arindam	7000.000000	11:59:59.0	2009/3/1	2009/3/1 11:59:59.0	700000.000000	
	
Statement Executed