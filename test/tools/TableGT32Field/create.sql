echo CREATE TABLE t1 (f1 INT , f2 INT , f3 INT , f4 INT , f5 INT , f6 INT , f7 INT , f8 INT , f9 INT , f10 INT , f11 INT , f12 INT , f13 INT , f14 INT , f15 INT , f16 INT , f17 INT , f18 INT , f19 INT , f20 INT , f21 INT , f22 INT , f23 INT , f24 INT , f25 INT , f26 INT , f27 INT , f28 INT , f29 INT , f30 INT , f31 INT , f32 INT , f33 INT , f34 INT , f35 INT , f36 INT , f37 INT );
CREATE TABLE t1 (f1 INT , f2 INT , f3 INT , f4 INT , f5 INT , f6 INT , f7 INT , f8 INT , f9 INT , f10 INT , f11 INT , f12 INT , f13 INT , f14 INT , f15 INT , f16 INT , f17 INT , f18 INT , f19 INT , f20 INT , f21 INT , f22 INT , f23 INT , f24 INT , f25 INT , f26 INT , f27 INT , f28 INT , f29 INT , f30 INT , f31 INT , f32 INT , f33 INT , f34 INT , f35 INT , f36 INT , f37 INT );
echo insert into t1 values(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
insert into t1 values(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
echo insert into t1 values(2,2,3,4,5,6,7,8,9,10,NULL,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
insert into t1 values(2,2,3,4,5,6,7,8,9,10,NULL,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
echo insert into t1 values(3,2,3,4,5,6,7,8,9,10,11,NULL,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
insert into t1 values(3,2,3,4,5,6,7,8,9,10,11,NULL,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
echo insert into t1 values(4,2,3,4,5,6,7,8,9,10,11,12,NULL,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
insert into t1 values(4,2,3,4,5,6,7,8,9,10,11,12,NULL,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
echo insert into t1 values(5,2,3,4,5,6,7,8,9,10,11,12,13,NULL,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
insert into t1 values(5,2,3,4,5,6,7,8,9,10,11,12,13,NULL,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
echo insert into t1 values(6,2,3,4,5,6,7,8,9,10,11,12,13,14,NULL,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
insert into t1 values(6,2,3,4,5,6,7,8,9,10,11,12,13,14,NULL,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37);
echo select * from t1;
select * from t1;
echo select * from t1 where f11 is NOT NULL;
select * from t1 where f11 is NOT NULL;
echo select * from t1 where f13 is NULL;
select * from t1 where f13 is NULL;
echo update t1 set f33=NULL where f14 is NOT NULL;
update t1 set f33=NULL where f14 is NOT NULL;
echo select * from t1;
select * from t1;
echo update t1 set f3=NULL where f13 is NULL;
update t1 set f3=NULL where f13 is NULL;
echo select * from t1;
select * from t1;
echo drop table t1;
drop table t1;
