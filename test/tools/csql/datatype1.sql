echo int data type testing;

create table t1 (f1 int, f2 int, primary key (f1));
insert into t1 values (10, 1);
insert into t1 values (11, 1);
insert into t1 values (12, 1);
insert into t1 values (13, 1);
insert into t1 values (-2147483648, 1);
insert into t1 values (2147483647, 1);
echo select * from t1;
select * from t1;
echo select * from t1 where f1 = 10;
select * from t1 where f1 = 10;
echo select * from t1 where f1 != 12 AND f2 <= 13;
select * from t1 where f1 != 12 AND f2 <= 13;
echo select * from t1 where f1 = 12 AND f2 >= 22;
select * from t1 where f1 = 12 AND f2 >= 22;
echo select * from t1 where f1 = 12 OR  f1 > 13;
select * from t1 where f1 = 12 OR  f1 > 13;
echo select * from t1 where f1 = 12 OR f2 < 13;
select * from t1 where f1 = 12 OR f2 < 13;
echo select * from t1 where f1 = 12 OR f2 <> 22;
select * from t1 where f1 = 12 OR f2 <> 22;
echo select * from t1 where NOT f1 = 12;
select * from t1 where NOT f1 = 12;
echo select * from t1 where f1 != 12;
select * from t1 where f1 != 12;
echo select * from t1 where NOT f1 != 12;
select * from t1 where NOT f1 != 12;
echo select * from t1 where f1 = f2;
select * from t1 where f1 = f2;

echo select * from t1 where f1 between 2147483646 and 2147483647;
select * from t1 where f1 between 2147483646 and 2147483647;
echo select * from t1 where f1 between -2147483647 and -2147483648;
select * from t1 where f1 between -2147483647 and -2147483648;

echo update t1 set f2 = 2 where f1 != f2;
update t1 set f2 = 2 where f1 != f2;
select * from t1;

echo update t1 set f2 = 3 where f1 = 12;
update t1 set f2 = 3 where f1 = 12;
select * from t1;

delete from t1 where f1 = 12;
select * from t1;
drop table t1;
