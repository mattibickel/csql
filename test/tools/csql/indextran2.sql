echo create table t1(f1 int,f2 int,f3 int);
create table t1(f1 int,f2 int,f3 int);
echo create index idx1 on t1(f1,f2);
create index idx1 on t1(f1,f2);
echo insert into t1 values(1,10,100);
insert into t1 values(1,10,100);
echo insert into t1 values(3,33,333);
insert into t1 values(3,33,333);
echo insert into t1 values(2,33,444); 
insert into t1 values(2,33,444); 
echo set autocommit off;
set autocommit off;
echo insert into t1 values(4,40,400);
insert into t1 values(4,40,400);
echo insert into t1 values(3,33,333);
insert into t1 values(3,33,333);
echo select * from t1;
select * from t1;
echo rollback;
rollback;
echo select * from t1;
select * from t1;
echo commit;
commit;
echo select * from t1;
select * from t1;
echo insert into t1 values(4,40,400);
insert into t1 values(4,40,400);
echo insert into t1 values(3,33,333);
insert into t1 values(3,33,333);
echo select * from t1;
select * from t1;
echo commit;
commit;
echo select * from t1;
select * from t1;
echo rollback;
rollback;
echo select * from t1;
select * from t1;
echo update t1 set f1=20 where f1=2;
update t1 set f1=20 where f1=2;
echo select * from t1 where f1=20;
select * from t1 where f1=20;
echo update t1 set f2=333 where f3=444;
update t1 set f2=333 where f3=444;
echo select * from t1 where f3=444;
select * from t1 where f3=444;
echo select * from t1;
select * from t1;
echo update t1 set f1=1,f2=10 where f1=20;
update t1 set f1=1,f2=10 where f1=20;
echo select * from t1;
select * from t1;
echo rollback;
rollback;
echo select * from t1 where f1=33;
select * from t1 where f1=33;
echo select * from t1 where f1=2;
select * from t1 where f1=2;
echo select * from t1 where f1=2 and f2=33;
select * from t1 where f1=2 and f2=33;
echo update t1 set f1=20 where f1=2;
update t1 set f1=20 where f1=2;
echo select * from t1 where f1=20;
select * from t1 where f1=20;
echo update t1 set f2=333 where f3=444;
update t1 set f2=333 where f3=444;
echo select * from t1;
select * from t1;
echo select * from t1 where f3=444;
select * from t1 where f3=444;
echo select * from t1;
select * from t1;
echo update t1 set f1=1,f2=10 where f1=20;
update t1 set f1=1,f2=10 where f1=20;
echo select * from t1;
select * from t1;
echo commit;
commit;
echo select *from t1;
select *from t1;
echo select * from t1 where f1=1;
select * from t1 where f1=1;
echo select * from t1 where f1=2;
select * from t1 where f1=2;
echo select * from t1 where f1=2 and f2=33;
select * from t1 where f1=2 and f2=33;
echo select * from t1;
select * from t1;
echo delete from t1 where f1=3 and f2=33;
delete from t1 where f1=3 and f2=33;
echo select * from t1;
select * from t1;
echo delete from t1 where f1 in(1,5) and f2 in(50,10);
delete from t1 where f1 in(1,5) and f2 in(50,10);
echo select * from t1;
select * from t1;
echo delete from t1 where f2 between 33 and 45;
delete from t1 where f2 between 33 and 45;
echo select * from t1;
select * from t1;
echo delete from t1;
delete from t1;
echo select * from t1;
select * from t1;
echo rollback;
rollback;
echo select * from t1; 
select * from t1; 
echo delete from t1 where f1=3 and f2=33;
delete from t1 where f1=3 and f2=33;
echo select * from t1;
select * from t1;
echo delete from t1 where f1 in(1,5) and f2 in(50,10);
delete from t1 where f1 in(1,5) and f2 in(50,10);
echo select * from t1;
select * from t1;
echo commit;
commit;
echo delete from t1 where f2 between 33 and 45;
delete from t1 where f2 between 33 and 45;
echo select * from t1;
select * from t1;
echo delete from t1;
delete from t1;
echo select * from t1;
select * from t1;
echo select * from t1;
select * from t1;
rollback;
echo drop table t1;
drop table t1;
echo quit;
quit;
