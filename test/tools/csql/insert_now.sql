echo CREATE TABLE t1(f1 INT AUTO_INCREMENT,f2 DATE DEFAULT 'NOW',f3 TIME DEFAULT 'NOW',f4 TIMESTAMP DEFAULT 'NOW');
CREATE TABLE t1(f1 INT AUTO_INCREMENT,f2 DATE DEFAULT 'NOW',f3 TIME DEFAULT 'NOW',f4 TIMESTAMP DEFAULT 'NOW');
echo INSERT INTO t1(f1) VALUES(10);
INSERT INTO t1(f1) VALUES(10);
echo INSERT INTO t1(f2) VALUES('NOW');
INSERT INTO t1(f2) VALUES('NOW');
echo INSERT INTO t1(f3) VALUES('NOW');
INSERT INTO t1(f3) VALUES('NOW');
echo INSERT INTO t1(f4) VALUES('NOW');
INSERT INTO t1(f4) VALUES('NOW');
echo SELECT * FROM t1;
SELECT * FROM t1;
drop table t1;
