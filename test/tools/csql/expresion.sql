echo create table t1 (f1 int, f2 int,f3 int);
create table t1 (f1 int, f2 int,f3 int);
echo insert into t1 values(10,10,10);
insert into t1 values(10,10,10);
echo insert into t1 values(20,10,10);
insert into t1 values(20,10,10);
echo insert into t1 values(30,10,10);
insert into t1 values(30,10,10);
echo insert into t1 values(40,10,10);
insert into t1 values(40,10,10);
echo insert into t1 values(50,10,10);
insert into t1 values(50,10,10);
echo insert into t1 values(60,10,10);
insert into t1 values(60,10,10);
echo select * from t1;
select * from t1;
echo update t1 set f1=f1+f2+f3+7,f2=f3+23+f1,f3=12;
update t1 set f1=f1+f2+f3+7,f2=f3+23+f1,f3=12;
echo select * from t1;
select * from t1;
echo update t1 set f1=f2/f3+7,f2=f3+23+f1,f3=f2 where f3=12;
update t1 set f1=f2/f3+7,f2=f3+23+f1,f3=f2 where f3=12;
echo select * from t1;
select * from t1;
echo create table t2 (f1 tinyint, f2 bigint,f3 int);
create table t2 (f1 tinyint, f2 bigint,f3 int);
echo insert into t2 values(60,1110,5110);
insert into t2 values(60,1110,5110);
echo insert into t2 values(70,1115,1510);
insert into t2 values(70,1115,1510);
echo insert into t2 values(80,1150,1150);
insert into t2 values(80,1150,1150);
echo insert into t2 values(90,1510,1115);
insert into t2 values(90,1510,1115);
echo insert into t2 values(50,5110,1110);
insert into t2 values(50,5110,1110);
echo select * from t2;
select * from t2;
echo update t2 set f1=NULL,f2=f1+f2+f3+10 where f2>1122;
update t2 set f1=NULL,f2=f1+f2+f3+10 where f2>1122;
echo select * from t2;
select * from t2;
echo update t2 set f2=f2+123 ,f3=23+f2;
update t2 set f2=f2+123 ,f3=23+f2;
echo select * from t2;
select * from t2;
echo drop table t1;
drop table t1;
echo drop table t2;
drop table t2;

