Table t1 and t2 created in target DB.
cachetable -t t5 -D
cachetable -t t6 -D
select query on t1 and t2 table
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
---------------------------------------------------------
	t5.f1	t5.f2	
---------------------------------------------------------
	
---------------------------------------------------------
	t6.f1	t6.f2	
---------------------------------------------------------
	
+---------------------------------------+
| Connected!                            |
|                                       |
| sql-statement                         |
| help [tablename]                      |
| quit                                  |
|                                       |
+---------------------------------------+
[?1034hSQL> select * from t5;
+-----------+-----------+
| f1        | f2        |
+-----------+-----------+
| 15        | 20        |
| 16        | 21        |
+-----------+-----------+
SQLRowCount returns 2
2 rows fetched
SQL> select * from t6;
+-----------+-----------+
| f1        | f2        |
+-----------+-----------+
| 15        | 20        |
| 16        | 21        |
+-----------+-----------+
SQLRowCount returns 2
2 rows fetched
SQL> 