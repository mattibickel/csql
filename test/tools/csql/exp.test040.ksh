echo binary data type testing;
Statement Executed
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
	10	12FE	
	11	245AF	
	12	245AF	
	13	12FE	
	-2147483648	DC23	
	2147483647	323A34	
	
echo select * from t1 where f2 = '12fe';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	12FE	
	13	12FE	
	
echo select * from t1 where f2 != '323a34' AND f1 = 13;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	13	12FE	
	
echo select * from t1 where f1 = 12 AND f2 >= '245af';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary

echo select * from t1 where f1 = 12 OR  f2 > 'dc23';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	11	245AF	
	12	245AF	
	2147483647	323A34	
	
echo select * from t1 where f1 = 12 OR f2 < 'dc23';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	12FE	
	12	245AF	
	13	12FE	
	
echo select * from t1 where f1 = 12 OR f2 <> '245af';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	12FE	
	12	245AF	
	13	12FE	
	-2147483648	DC23	
	2147483647	323A34	
	
echo select * from t1 where NOT f2 ='12fe';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	11	245AF	
	12	245AF	
	-2147483648	DC23	
	2147483647	323A34	
	
echo select * from t1 where f2 != '12fe';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	11	245AF	
	12	245AF	
	-2147483648	DC23	
	2147483647	323A34	
	
echo select * from t1 where NOT  f2 != '12fe';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	12FE	
	13	12FE	
	
echo select * from t1 where f1 = f2;
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	
echo select * from t1 where f2 in ('245af','12fe');
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	12FE	
	11	245AF	
	12	245AF	
	13	12FE	
	
echo select * from t1 where f2 between '00000000' and 'ffffffff';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary

echo select * from t1 where f2 between '122' and '12a2';
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary
Illegal Operator:Not Supported for Binary

echo update t1 set f2 = '435f3' where f1 != 13 and  f2='323a34' ;
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	12FE	
	11	245AF	
	12	245AF	
	13	12FE	
	-2147483648	DC23	
	2147483647	435F3	
	
echo update t1 set f2 = '23abc' where f2 = '245af';
Statement Executed: Rows Affected = 2
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	10	12FE	
	11	23ABC	
	12	23ABC	
	13	12FE	
	-2147483648	DC23	
	2147483647	435F3	
	
echo delete from t1 where f2 = '12fe';
Statement Executed: Rows Affected = 2
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	11	23ABC	
	12	23ABC	
	-2147483648	DC23	
	2147483647	435F3	
	
Statement Executed
