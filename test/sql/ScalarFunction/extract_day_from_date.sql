echo Create table t1(f1 date, f2 date);
Create table t1(f1 date, f2 date);
insert into t1 values('2001-01-01', '2001-01-01');
insert into t1 values('2002-01-01', '2001-02-01');
insert into t1 values('2003-01-03', '2002-03-02');
insert into t1 values('2004-01-01', '2002-04-02');
insert into t1 values('2005-01-01', '2003-05-03');
echo select * from t1;
select * from t1;
echo select * from t1 where extract(day from f2) = 02;
select * from t1 where extract(day from f2) = 02;
echo select * from t1 where extract(day from f2) < 02;
select * from t1 where extract(day from f2) < 02;
echo select * from t1 where extract(day from f2)<= 02;
select * from t1 where extract(day from f2)<= 02;
echo select * from t1 where extract(day from f2) > 02;
select * from t1 where extract(day from f2) > 02;
echo select * from t1 where extract(day from f2)>= 02;
select * from t1 where extract(day from f2)>= 02;
echo select * from t1 where extract(day from f2)!= 02;
select * from t1 where extract(day from f2)!= 02;
