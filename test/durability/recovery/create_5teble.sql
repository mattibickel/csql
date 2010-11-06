echo CREATE TABLE t1(f1 int,f2 char(20));
CREATE TABLE t1(f1 int,f2 char(20));
echo CREATE TABLE t2(f1 int,f2 char(20));
CREATE TABLE t2(f1 int,f2 char(20));
echo CREATE INDEX idx1 ON t2(f1) HASH UNIQUE;
CREATE INDEX idx1 ON t2(f1) HASH UNIQUE;
echo CREATE TABLE t3(f1 int,f2 char(20));
CREATE TABLE t3(f1 int,f2 char(20));
echo CREATE INDEX idx2 ON t3(f1) TREE UNIQUE;
CREATE INDEX idx2 ON t3(f1) TREE UNIQUE;
echo CREATE TABLE t4(f1 int,f2 char(20),PRIMARY KEY(f1));
CREATE TABLE t4(f1 int,f2 char(20),PRIMARY KEY(f1));
echo CREATE TABLE t5(f1 int,f2 char(20),PRIMARY KEY(f2));
CREATE TABLE t5(f1 int,f2 char(20),PRIMARY KEY(f2));
