echo CREATE TABLE t1(f1 int,f2 int,f3 int,primary key(f1,f2));
CREATE TABLE t1(f1 int,f2 int,f3 int,primary key(f1,f2));
echo CREATE TABLE t2(f1 int,f2 int,f3 int,foreign key(f1,f3) references t1(f1,f2));
CREATE TABLE t2(f1 int,f2 int,f3 int,foreign key(f1,f3) references t1(f1,f2));
echo INSERT INTO t1 VALUES(1,10,100);
INSERT INTO t1 VALUES(1,10,100);
echo INSERT INTO t1 VALUES(1,20,100);
INSERT INTO t1 VALUES(1,20,100);
echo INSERT INTO t1 VALUES(3,20,100);
INSERT INTO t1 VALUES(3,20,100);
echo INSERT INTO t1 VALUES(4,30,300);
INSERT INTO t1 VALUES(4,30,300);

echo SELECT * FROM t1;
SELECT * FROM t1;

echo INSERT INTO t2 VALUES(1,1000,10);
INSERT INTO t2 VALUES(1,1000,10);
echo INSERT INTO t2 VALUES(1,1000,20);
INSERT INTO t2 VALUES(1,1000,20);
echo INSERT INTO t2 VALUES(1,1000,10);
INSERT INTO t2 VALUES(1,1000,10);
echo INSERT INTO t2 VALUES(4,1000,30);
INSERT INTO t2 VALUES(4,1000,30);

echo SELECT * FROM t2;
SELECT * FROM t2;
echo UPDATE t2 SET f1=3,f3=20 WHERE f1=1;
UPDATE t2 SET f1=3,f3=20 WHERE f1=1;
echo SELECT * FROM t2;
SELECT * FROM t2;
echo UPDATE t2 SET f3=20 WHERE f1=4;
UPDATE t2 SET f3=20 WHERE f1=4;

