echo "<<<<<<<<<<<<<<<<<<<<<<<< UPDATE t1 SET f1=f1+NULL >>>>>>>>>>>>>>>>>>>>>>";
echo create table t1(f1 int not null,f2 int,f3 int);
create table t1(f1 int not null,f2 int,f3 int);
echo insert into t1 values(1,2,3);
insert into t1 values(1,2,3);
echo insert into t1 values(2,NULL,4);
insert into t1 values(2,NULL,4);
echo insert into t1 values(3,4,NULL);
insert into t1 values(3,4,NULL);
echo insert into t1 values(10,20,30);
insert into t1 values(10,20,30);
echo insert into t1 values(11,NULL,NULL);
insert into t1 values(11,NULL,NULL);
echo commit;
commit;
echo select * from t1;
select * from t1;
