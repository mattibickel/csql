Entries made for myodbc3  in csqlds.conf file.
Entries made for psql in csqlds.conf file.
Table 't1 and t2' is created in myodbc3
SELECT records from myodbc3
+---------------------------------------+
| Connected!                            |
|                                       |
| sql-statement                         |
| help [tablename]                      |
| quit                                  |
|                                       |
+---------------------------------------+
[?1034hSQL> select * from t1;
+-----------+---------------------+
| f1        | f2                  |
+-----------+---------------------+
| 1         | Hi                  |
| 2         | Hello               |
| 3         | Hi All              |
+-----------+---------------------+
SQLRowCount returns 3
3 rows fetched
SQL> select * from t2;
+-----------+---------------------+
| f1        | f2                  |
+-----------+---------------------+
| 10        | mysql               |
| 20        | open                |
| 30        | source              |
+-----------+---------------------+
SQLRowCount returns 3
3 rows fetched
SQL> 
Table 'tt1 and tt2' is created in psql
SELECT records from psql
+---------------------------------------+
| Connected!                            |
|                                       |
| sql-statement                         |
| help [tablename]                      |
| quit                                  |
|                                       |
+---------------------------------------+
[?1034hSQL> select * from tt1;
+------------+-----------+
| f1         | f2        |
+------------+-----------+
| 11         | one       |
| 22         | two       |
| 33         | three     |
+------------+-----------+
SQLRowCount returns 3
3 rows fetched
SQL> select * from tt2;
+------------+-----------+
| f1         | f2        |
+------------+-----------+
| 1111       | psql      |
| 2222       | open      |
| 3333       | source    |
+------------+-----------+
SQLRowCount returns 3
3 rows fetched
SQL> 
Table t1 is cached from myodbc3.
Table 'tt1' is cached from psql.

DELETE records from tables using Gateway(csql -g)
DELETE records from t1 and t2 table.
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
DELETE records from tt1 and tt2 table.
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1

SELECT records from cached and non-cached tables using Gateway(csql -g)
select 't1' and 't2' table.
---------------------------------------------------------
	t1.f1	t1.f2	
---------------------------------------------------------
	3	Hi All	
	
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	30	source	
	
select 'tt1' and 'tt2' table.
---------------------------------------------------------
	tt1.f1	tt1.f2	
---------------------------------------------------------
	33	three	
	
---------------------------------------------------------
	f1	f2	
---------------------------------------------------------
	3333	source    	
	
