echo binary data type testing with primary key;

create table t1 (f1 int, f2 binary(4) ,primary key(f2));
insert into t1 values (10, '12fe');
insert into t1 values (11, '245af');
insert into t1 values (12, '2423fe');
insert into t1 values (13, '12fe');
insert into t1 values (-2147483648,'dc23' );
insert into t1 values (2147483647, '323a34');
echo select * from t1;
select * from t1;
echo select * from t1 where f2 = '12fe';
select * from t1 where f2 = '12fe';
echo select * from t1 where f2 != '323a34' AND f1 = 13;
select * from t1 where f2 != '323a34' AND f1 = 13;
echo select * from t1 where f1 = 12 AND f2 >= '245af';
select * from t1 where f1 = 12 AND f2 >= '245af';
echo select * from t1 where f1 = 12 OR  f2 > 'dc23';
select * from t1 where f1 = 12 OR  f2 > 'dc23';
echo select * from t1 where f1 = 12 OR f2 < 'dc23';
select * from t1 where f1 = 12 OR f2 < 'dc23';
echo select * from t1 where f1 = 12 OR f2 <> '245af';
select * from t1 where f1 = 12 OR f2 <> '245af';
echo select * from t1 where NOT f2 ='12fe';
select * from t1 where NOT f2 ='12fe';
echo select * from t1 where f2 != '12fe';
select * from t1 where  f2 != '12fe';
echo select * from t1 where NOT  f2 != '12fe';
select * from t1 where NOT  f2 != '12fe';
echo select * from t1 where f1 = f2;
select * from t1 where f1 = f2;
echo select * from t1 where f2 in ('245af','12fe');
select * from t1 where f2 in ('245af','12fe');
echo select * from t1 where f2 between '00000000' and 'ffffffff';
select * from t1 where f2 between '00000000' and 'ffffffff';
echo select * from t1 where f2 between '122' and '12a2';
select * from t1 where f2 between '122' and '12a2';

echo update t1 set f2 = '435f3' where f1 != 13 and  f2='323a34' ;
update t1 set f2 ='435f3'  where f1 != 13 and  f2='323a34';
select * from t1;


echo update t1 set f2 = '23abc' where f2 = '245af';
update t1 set f2 = '23abc' where f2 = '245af';
select * from t1;


echo delete from t1 where f2 = '23abc';
delete from t1 where f2 = '23abc';
select * from t1;
drop table t1;