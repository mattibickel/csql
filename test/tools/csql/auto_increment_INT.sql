echo CREATE TABLE T1(f1 INT AUTO_INCREMENT,f2 INT);
CREATE TABLE T1(f1 INT AUTO_INCREMENT,f2 INT);
echo INSERT INTO T1 values(100,1);
INSERT INTO T1 values(100,1);
echo INSERT INTO T1(f2) values(10);
INSERT INTO T1(f2) values(10);
echo INSERT INTO T1(f2) values(30);
INSERT INTO T1(f2) values(30);
echo INSERT INTO T1(f2) values(40);
INSERT INTO T1(f2) values(40);
echo INSERT INTO T1(f1,f2) values(NULL,40);
INSERT INTO T1(f1,f2) values(NULL,40);
echo INSERT INTO T1(f1,f2) values(100,40);
INSERT INTO T1(f1,f2) values(100,40);
echo SELECT * FROM T1;
SELECT * FROM T1;

echo CREATE TABLE T2(f1 INT AUTO_INCREMENT,f2 CHAR(10));
CREATE TABLE T2(f1 INT AUTO_INCREMENT,f2 CHAR(10));
echo INSERT INTO T2 values(10,'Papu');
INSERT INTO T2 values(10,'Papu');
echo INSERT INTO T2(f2) values('Jitu');
INSERT INTO T2(f2) values('Jitu');
echo INSERT INTO T2(f2) values('kishor');
INSERT INTO T2(f2) values('kishor');
echo INSERT INTO T2(f1,f2) values(NULL,'Nihar');
INSERT INTO T2(f1,f2) values(NULL,'Nihar');
echo INSERT INTO T2(f1,f2) values(100,'Suna');
INSERT INTO T2(f1,f2) values(100,'Suna');
echo SELECT * FROM T2;
SELECT * FROM T2;


echo CREATE TABLE T3(f1 CHAR(10),f2 int auto_increment);
CREATE TABLE T3(f1 CHAR(10),f2 int auto_increment);
echo INSERT INTO T3 values('Papu',10);
INSERT INTO T3 values('Papu',10);
echo INSERT INTO T3(f1) values('Jitu');
INSERT INTO T3(f1) values('Jitu');
echo INSERT INTO T3(f1) values('kishor');
INSERT INTO T3(f1) values('kishor');
echo INSERT INTO T3(f1,f2) values('Nihar',NULL);
INSERT INTO T3(f1,f2) values('Nihar',NULL);
echo INSERT INTO T3(f2,f1) values(100,NULL);
INSERT INTO T3(f2,f1) values(100,NULL);
echo INSERT INTO T3(f1,f2) values(NULL,NULL);
INSERT INTO T3(f1,f2) values(NULL,NULL);
echo SELECT * FROM T3;
SELECT * FROM T3;

echo CREATE TABLE T4(f1 INT AUTO_INCREMENT,f2 INT);
CREATE TABLE T4(f1 INT AUTO_INCREMENT,f2 INT);
echo INSERT INTO T4 VALUES(1,2);
INSERT INTO T4 VALUES(1,2);
echo INSERT INTO T4 VALUES(NULL,2);
INSERT INTO T4 VALUES(NULL,2);
echo INSERT INTO T4 VALUES(NULL,3);
INSERT INTO T4 VALUES(NULL,3);
echo INSERT INTO T4 VALUES(NULL,2);
INSERT INTO T4 VALUES(NULL,2);
echo INSERT INTO T4 VALUES(NULL,3);
INSERT INTO T4 VALUES(NULL,3);
echo SELECT * FROM T4;
SELECT * FROM T4;
echo UPDATE T4 SET f2=20 WHERE f2=2;
UPDATE T4 SET f2=20 WHERE f2=2;
echo SELECT * FROM T4;
SELECT * FROM T4;
echo UPDATE T4 SET f2=200,f1=0 WHERE f2=20;
UPDATE T4 SET f2=200,f1=0 WHERE f2=20;
echo SELECT * FROM T4;
SELECT * FROM T4;
echo UPDATE T4 SET f2=300,f1=30 WHERE f1<=2;
UPDATE T4 SET f2=300,f1=30 WHERE f1<=2;
echo SELECT * FROM T4;
SELECT * FROM T4;

echo CREATE TABLE T5(f1 INT AUTO_INCREMENT,f2 INT NOT NULL);
CREATE TABLE T5(f1 INT AUTO_INCREMENT,f2 INT NOT NULL);
echo INSERT INTO T5 VALUES(NULL,2);
INSERT INTO T5 VALUES(NULL,2);
echo INSERT INTO T5 VALUES(NULL,NULL);
INSERT INTO T5 VALUES(NULL,NULL);
echo INSERT INTO T5 VALUES(NULL,3);
INSERT INTO T5 VALUES(NULL,3);
echo INSERT INTO T5 VALUES(NULL,2);
INSERT INTO T5 VALUES(NULL,2);
echo INSERT INTO T5 VALUES(NULL,3);
INSERT INTO T5 VALUES(NULL,3);
echo SELECT * FROM T5;
SELECT * FROM T5;
echo DELETE FROM T5 WHERE f2=2;
DELETE FROM T5 WHERE f2=2;
echo SELECT * FROM T5;
SELECT * FROM T5;
echo ROLLBACK;
ROLLBACK;
echo SELECT * FROM T5;
SELECT * FROM T5;
echo DELETE FROM T5 WHERE f1<=3 AND f1!=2;
DELETE FROM T5 WHERE f1<=3 AND f1!=2;
echo SELECT * FROM T5;
SELECT * FROM T5;
echo INSERT INTO T5 VALUES(3,30);
INSERT INTO T5 VALUES(3,30);
echo SELECT * FROM T5;
SELECT * FROM T5;
echo DELETE FROM T5;
DELETE FROM T5;
echo SELECT * FROM T5;
SELECT * FROM T5;

echo CREATE TABLE T6(f1 INT AUTO_INCREMENT,f2 INT);
CREATE TABLE T6(f1 INT AUTO_INCREMENT,f2 INT);
echo INSERT INTO T6 VALUES(1,2);
INSERT INTO T6 VALUES(1,2);
echo INSERT INTO T6 VALUES(NULL,2);
INSERT INTO T6 VALUES(NULL,2);
echo INSERT INTO T6 VALUES(NULL,3);
INSERT INTO T6 VALUES(NULL,3);
echo INSERT INTO T6 VALUES(NULL,2);
INSERT INTO T6 VALUES(NULL,2);
echo INSERT INTO T6 VALUES(NULL,3);
INSERT INTO T6 VALUES(NULL,3);
echo SELECT * FROM T6;
SELECT * FROM T6;
echo UPDATE T6 SET f2=20 WHERE f2=2;
UPDATE T6 SET f2=20 WHERE f2=2;
echo SELECT * FROM T6;
SELECT * FROM T6;
echo UPDATE T6 SET f2=200,f1=0 WHERE f2=20;
UPDATE T6 SET f2=200,f1=0 WHERE f2=20;
echo SELECT * FROM T6;
SELECT * FROM T6;
echo UPDATE T6 SET f2=300,f1=30 WHERE f1<=2;
UPDATE T6 SET f2=300,f1=30 WHERE f1<=2;
echo SELECT * FROM T6;
SELECT * FROM T6;
echo DELETE FROM T6 WHERE f2=2;
DELETE FROM T6 WHERE f2=2;
echo SELECT * FROM T6;
SELECT * FROM T6;
echo ROLLBACK;
ROLLBACK;
echo SELECT * FROM T6;
SELECT * FROM T6;
echo DELETE FROM T6 WHERE f1<=3 AND f1!=2;
DELETE FROM T6 WHERE f1<=3 AND f1!=2;
echo SELECT * FROM T6;
SELECT * FROM T6;
echo INSERT INTO T6 VALUES(3,30);
INSERT INTO T6 VALUES(3,30);
echo SELECT * FROM T6;
SELECT * FROM T6;
echo DELETE FROM T6;
DELETE FROM T6;
echo SELECT * FROM T6;
SELECT * FROM T6;

echo CREATE TABLE T7(f1 INT AUTO_INCREMENT,f2 INT,f3 INT);
CREATE TABLE T7(f1 INT AUTO_INCREMENT,f2 INT,f3 INT);
echo INSERT INTO T7 VALUES(1,2,3);
INSERT INTO T7 VALUES(1,2,3);
echo SELECT * FROM T7;
SELECT * FROM T7;
echo UPDATE T7 SET f3=30,f2=20,f1=0 where f1=1;
UPDATE T7 SET f3=30,f2=20,f1=0 where f1=1;
echo UPDATE T7 SET f3=30,f2=20 where f1=1;
UPDATE T7 SET f3=30,f2=20 where f1=1;
echo SELECT * FROM T7;
SELECT * FROM T7;
echo INSERT INTO T7 VALUES(2,4,3);
INSERT INTO T7 VALUES(2,4,3);
echo DELETE FROM T7 WHERE f3<=3;
DELETE FROM T7 WHERE f3<=3;

echo CREATE TABLE T9(f1 INT AUTO_INCREMENT,f2 INT,f3 INT);
CREATE TABLE T9(f1 INT AUTO_INCREMENT,f2 INT,f3 INT);
echo CREATE INDEX idx1 ON T9(f1,f2) UNIQUE;
CREATE INDEX idx1 ON T9(f1,f2) UNIQUE;
echo INSERT INTO T9 VALUES(1,2,3);
INSERT INTO T9 VALUES(1,2,3);
echo SELECT * FROM T9;
SELECT * FROM T9;
echo UPDATE T9 SET f3=30,f2=20,f1=0 where f1=1;
UPDATE T9 SET f3=30,f2=20,f1=0 where f1=1;
echo UPDATE T9 SET f3=30,f2=20 where f1=1;
UPDATE T9 SET f3=30,f2=20 where f1=1;
echo SELECT * FROM T9;
SELECT * FROM T9;
echo INSERT INTO T9 VALUES(2,4,3);
INSERT INTO T9 VALUES(2,4,3);
echo DELETE FROM T9 WHERE f3<=3;
DELETE FROM T9 WHERE f3<=3;

echo CREATE TABLE T10(f1 INT AUTO_INCREMENT,f2 INT,f3 INT,PRIMARY KEY(f3,f1));
CREATE TABLE T10(f1 INT AUTO_INCREMENT,f2 INT,f3 INT,PRIMARY KEY(f3,f1));
echo INSERT INTO T10 VALUES(1,2,3);
INSERT INTO T10 VALUES(1,2,3);
echo SELECT * FROM T10;
SELECT * FROM T10;
echo UPDATE T10 SET f3=30,f2=20,f1=0 where f1=1;
UPDATE T10 SET f3=30,f2=20,f1=0 where f1=1;
echo UPDATE T10 SET f3=30,f2=20 where f1=1;
UPDATE T10 SET f3=30,f2=20 where f1=1;
echo SELECT * FROM T10;
SELECT * FROM T10;
echo INSERT INTO T10 VALUES(2,4,3);
INSERT INTO T10 VALUES(2,4,3);
echo DELETE FROM T10 WHERE f3<=3;
DELETE FROM T10 WHERE f3<=3;