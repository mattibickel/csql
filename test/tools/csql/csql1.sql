echo create table and constraints with integer fields
create table t1 (f1 int, f2 int);
insert into t1 values (10, 20);
insert into t1 (f1, f2) values (11, 21);
insert into t1 (f2, f1) values (22, 12);
insert into t1 (f1) values (13);
insert into t1 (f2) values (24);
select * from t1;

create table t2 (f1 int not null, f2 int);
insert into t2 values (10, 20);
insert into t2 (f1, f2) values (11, 21);
insert into t2 (f2, f1) values (22, 12);
insert into t2 (f1) values (13);
insert into t2 (f2) values (24);
select * from t2;

create table t3 (f1 int, f2 int, primary key(f1));
insert into t3 values (10, 20);
insert into t3 (f1, f2) values (11, 21);
insert into t3 (f2, f1) values (22, 12);
insert into t3 (f1) values (13);
insert into t3 (f2) values (24);
select * from t3;
