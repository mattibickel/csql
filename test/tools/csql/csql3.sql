echo Same as csql2 but with primary key;

create table t1 (f1 int, f2 int, primary key (f1));
insert into t1 values (10, 20);
insert into t1 values (11, 21);
insert into t1 values (12, 22);
insert into t1 values (13, 23);
insert into t1 values (14, 24);
insert into t1 values (50, 50);
echo select * from t1;
select * from t1;
echo select * from t1 where f1 = 100;
select * from t1 where f1 = 100;
echo select * from t1 where f1 = 10;
select * from t1 where f1 = 10;
echo select f1 from t1 where f1 = 11;
select f1 from t1 where f1 = 11;
echo select f2 from t1 where f1 = 11;
select f2 from t1 where f1 = 11;
echo select f1, f2 from t1 where f1 = 12;
select f1, f2 from t1 where f1 = 12;
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
echo select * from t1 where NOT (f1 = 12 AND f2 =22);
select * from t1 where NOT (f1 = 12 AND f2 =22);
echo select * from t1 where NOT (f1 = 12 OR f2 = 23);
select * from t1 where NOT (f1 = 12 OR f2 = 23);
echo select * from t1 where f1 = 12 OR f2 = 23 OR f2 = 22;
select * from t1 where f1 = 12 OR f2 = 23 OR f2 = 22;
echo select * from t1 where  f1+12 = 20;
select * from t1 where  f1+12 = 20;
echo select * from t1 where f1 = 12 + f2;
select * from t1 where f1 = 12 + f2;
echo select * from t1 where f1 =  f2;
select * from t1 where f1 = f2;
drop table t1;
