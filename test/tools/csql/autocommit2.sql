echo set autocommit off;
set autocommit off;
echo update t1 set f2='k' where f1=2;
update t1 set f2='k' where f1=2;
echo select * from t1;
select * from t1;
echo rollback;
rollback;
echo select * from t1;
select * from t1;
echo insert into t1 values(3,'k');
insert into t1 values(3,'k');
echo insert into t1 values(4,'p');
insert into t1 values(4,'p');
echo commit;
commit;
echo insert into t1 values(5,'t');
insert into t1 values(5,'t');
echo rollback;
rollback;
