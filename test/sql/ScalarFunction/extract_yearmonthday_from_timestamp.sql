echo Create table t1(f1 timestamp, f2 timestamp);
Create table t1(f1 timestamp, f2 timestamp);
insert into t1 values('2001-01-01 01:01:01', '2001-01-05 01:01:01');
insert into t1 values('2002-01-01 01:01:01', '2002-04-10 02:02:02');
insert into t1 values('2003-01-03 01:01:01', '2003-07-15 12:30:30');
insert into t1 values('2004-01-01 01:01:01', '2004-10-20 22:58:58');
insert into t1 values('2005-01-01 01:01:01', '2005-12-25 23:59:59');
echo select * from t1;
select * from t1;
echo select * from t1 where extract(year from f2) =2003;
select * from t1 where extract(year from f2) =2003;
echo select * from t1 where extract(year from f2)<=2003;
select * from t1 where extract(year from f2)<=2003;
echo select * from t1 where extract(year from f2) >2003;
select * from t1 where extract(year from f2) >2003;
echo select * from t1 where extract(year from f2)!=2003;
select * from t1 where extract(year from f2)!=2003;
echo select * from t1 where extract(month from f2) =7;
select * from t1 where extract(month from f2) =7;
echo select * from t1 where extract(month from f2) <7;
select * from t1 where extract(month from f2) <7;
echo select * from t1 where extract(month from f2)>=7;
select * from t1 where extract(month from f2)>=7;
echo select * from t1 where extract(month from f2)!=7;
select * from t1 where extract(month from f2)!=7;
echo select * from t1 where extract(day from f2) =15;
select * from t1 where extract(day from f2) =15;
echo select * from t1 where extract(day from f2) <15;
select * from t1 where extract(day from f2) <15;
echo select * from t1 where extract(day from f2) >15;
select * from t1 where extract(day from f2) >15;
echo select * from t1 where extract(day from f2)<>15;
select * from t1 where extract(day from f2)<>15;
