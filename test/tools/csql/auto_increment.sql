echo create table t1(f1 int,f2 int auto_increment);
create table t1(f1 int,f2 int auto_increment);
echo insert into t1 values(12,NULL);
insert into t1 values(12,NULL);
echo insert into t1 (f1)values(12);
insert into t1 (f1)values(12);
echo insert into t1 values(12,232);
insert into t1 values(12,232);
echo select * from t1;
select * from t1;
echo create table t2(f1 int,f2 int auto_increment);
create table t2(f1 int,f2 int auto_increment);
echo insert into t2 values(12,200);
insert into t2 values(12,200);
echo insert into t2 values(12,NULL);
insert into t2 values(12,NULL);
echo insert into t2 (f1) values(12);
insert into t2 (f1) values(12);
echo select * from t2;
select * from t2;
echo drop table t1;
drop table t1;
echo drop table t2;
drop table t2;
echo create table t1(f1 int auto_increment, f2 int auto_increment);
create table t1(f1 int auto_increment, f2 int auto_increment);
echo create table t1(f1 int , f2 char(10) auto_increment);
create table t1(f1 int , f2 char(10) auto_increment);
