echo Create table t1(f1 date, f2 date);
Create table t1(f1 date, f2 date);
insert into t1 values('2008-01-20', '2010-01-01');
insert into t1 values('2009-04-20', '2011-02-01');
insert into t1 values('2010-02-27', '2012-03-01');
insert into t1 values('2011-02-28', '2013-03-01');
insert into t1 values('2012-02-29', '2014-01-01');
echo select * from t1;
select * from t1;
echo select * from t1 where date_sub(f2 interval 2 day) = '2012-02-28';
select * from t1 where date_sub(f2 interval 2 day) = '2012-02-28';
echo select * from t1 where date_sub(f2 interval 15 day) <= '2012-02-28';
select * from t1 where date_sub(f2 interval 15 day) <= '2012-02-28';
echo select * from t1 where date_sub(f2 interval 15 day) >= '2012-02-15';
select * from t1 where date_sub(f2 interval 15 day) >= '2012-02-15';
echo select * from t1 where date_sub(f2 interval 40 day) <= '2012-01-21';
select * from t1 where date_sub(f2 interval 40 day) <= '2012-01-21';
echo select * from t1 where date_sub(f2 interval 40 day) != '2012-01-21';
select * from t1 where date_sub(f2 interval 40 day) != '2012-01-21';
echo select * from t1 where date_sub(f2 interval 365 day) <= '2011-03-02';
select * from t1 where date_sub(f2 interval 365 day) <= '2011-03-02';
echo select * from t1 where date_sub(f2 interval 366 day) >= '2011-03-02';
select * from t1 where date_sub(f2 interval 366 day) >= '2011-03-02';
echo select * from t1 where date_sub(f2 interval 366 day) != '2011-03-02';
select * from t1 where date_sub(f2 interval 366 day) != '2011-03-02';
