echo CREATE TABLE t1(f1 INT, f2 CHAR(10), f3 DOUBLE, f4 DATE, f5 TIMESTAMP);
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
echo SELECT * FROM t1;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	90000	Pitter	90000.555555	2009/7/30	2009/7/29 11:29:0.0	
	60000	Simran	60000.555555	2006/7/30	2006/7/29 11:29:0.0	
	40000	Jemini	40000.555555	2004/7/30	NULL	
	60000	PRITAM	60000.555555	2006/7/30	2006/7/29 11:29:0.0	
	65000	PITTER	65000.555555	2065/7/30	2065/7/29 11:29:0.0	
	40000	JASMIN	40000.555555	2004/7/30	NULL	
	45000	jasmin	45000.555555	2045/7/30	2045/7/29 11:29:0.0	
	60000	Pitter	60000.555555	2006/7/30	NULL	
	40000	kishor	40000.555555	2004/7/30	2004/7/29 11:29:0.0	
	50000	Jemini	50000.555555	2005/7/30	2004/8/29 11:29:0.0	
	40000	Jemini	60000.555555	2006/7/30	2004/7/29 11:29:0.0	
	50000	Jemini	70000.555555	NULL	2004/6/29 11:29:0.0	
	40000	Sitala	80000.555555	2008/7/30	2004/5/29 11:29:0.0	
	
echo SELECT * FROM t1 WHERE f1 = 40000 OR f1 <= 50000 OR f2 = 'Jemini';
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	40000	Jemini	40000.555555	2004/7/30	NULL	
	40000	JASMIN	40000.555555	2004/7/30	NULL	
	45000	jasmin	45000.555555	2045/7/30	2045/7/29 11:29:0.0	
	40000	kishor	40000.555555	2004/7/30	2004/7/29 11:29:0.0	
	50000	Jemini	50000.555555	2005/7/30	2004/8/29 11:29:0.0	
	40000	Jemini	60000.555555	2006/7/30	2004/7/29 11:29:0.0	
	50000	Jemini	70000.555555	NULL	2004/6/29 11:29:0.0	
	40000	Sitala	80000.555555	2008/7/30	2004/5/29 11:29:0.0	
	
echo SELECT * FROM t1 WHERE f1 = 40000 OR f1 <= 50000 OR f2 = 'Jemini' OR f2 LIKE 'Pi%';
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	90000	Pitter	90000.555555	2009/7/30	2009/7/29 11:29:0.0	
	40000	Jemini	40000.555555	2004/7/30	NULL	
	40000	JASMIN	40000.555555	2004/7/30	NULL	
	45000	jasmin	45000.555555	2045/7/30	2045/7/29 11:29:0.0	
	60000	Pitter	60000.555555	2006/7/30	NULL	
	40000	kishor	40000.555555	2004/7/30	2004/7/29 11:29:0.0	
	50000	Jemini	50000.555555	2005/7/30	2004/8/29 11:29:0.0	
	40000	Jemini	60000.555555	2006/7/30	2004/7/29 11:29:0.0	
	50000	Jemini	70000.555555	NULL	2004/6/29 11:29:0.0	
	40000	Sitala	80000.555555	2008/7/30	2004/5/29 11:29:0.0	
	
echo SELECT * FROM t1 WHERE (f1 = 40000 OR f1 <= 50000 OR f2 = 'Jemini' OR f2 LIKE 'Pi%') AND f3 BETWEEN 44999 AND 89999;
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	45000	jasmin	45000.555555	2045/7/30	2045/7/29 11:29:0.0	
	60000	Pitter	60000.555555	2006/7/30	NULL	
	50000	Jemini	50000.555555	2005/7/30	2004/8/29 11:29:0.0	
	40000	Jemini	60000.555555	2006/7/30	2004/7/29 11:29:0.0	
	50000	Jemini	70000.555555	NULL	2004/6/29 11:29:0.0	
	40000	Sitala	80000.555555	2008/7/30	2004/5/29 11:29:0.0	
	
echo SELECT * FROM t1 WHERE (f1 = 40000 OR f1 <= 50000 OR f2 = 'Jemini' OR f2 LIKE 'Pi%') AND (f3 BETWEEN 44999 AND 89999) AND f4 IN ('2045-07-30', '2006-07-30', '2007-07-30');
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	45000	jasmin	45000.555555	2045/7/30	2045/7/29 11:29:0.0	
	60000	Pitter	60000.555555	2006/7/30	NULL	
	40000	Jemini	60000.555555	2006/7/30	2004/7/29 11:29:0.0	
	
echo SELECT * FROM t1 WHERE (f1 = 40000 OR f1 <= 50000 OR f2 = 'Jemini' OR f2 LIKE 'Pi%') AND (f3 BETWEEN 44999 AND 89999) AND (f4 IN ('2045-07-30', '2006-07-30', '2007-07-30') AND f5 IS NOT NULL);
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	45000	jasmin	45000.555555	2045/7/30	2045/7/29 11:29:0.0	
	40000	Jemini	60000.555555	2006/7/30	2004/7/29 11:29:0.0	
	
echo SELECT * FROM t1 WHERE (f1 = 40000 OR f1 <= 50000 OR f2 = 'Jemini' OR f2 LIKE 'Pi%') AND (f3 BETWEEN 44999 AND 89999) AND (f4 IN ('2045-07-30', '2006-07-30', '2007-07-30') AND f4 IS NULL AND f5 IS NOT NULL);
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	t1.f4	t1.f5	
---------------------------------------------------------
	
Statement Executed