echo Create table t1(f1 date, f2 date);
Create table t1(f1 date, f2 date);
insert into t1 values('2001-01-01', '2001-01-03');
insert into t1 values('2001-01-01', '2001-02-01');
insert into t1 values('2001-01-01', '2001-03-01');
insert into t1 values('2001-01-01', '2002-01-01');
insert into t1 values('2001-01-01', '2002-02-02');
echo select * from t1;
select * from t1;
echo select * from t1 where date_diff(f2,f1)=2;
select * from t1 where date_diff(f2,f1)=2;
echo select * from t1 where date_diff(f1,f2)=2;
select * from t1 where date_diff(f1,f2)=2;
echo select * from t1 where date_diff(f2,f1)=31;
select * from t1 where date_diff(f2,f1)=31;
echo select * from t1 where date_diff(f2,f1)=59;
select * from t1 where date_diff(f2,f1)=59;
echo select * from t1 where date_diff(f2,f1)=365;
select * from t1 where date_diff(f2,f1)=365;
echo select * from t1 where date_diff(f2,f1)=397;
select * from t1 where date_diff(f2,f1)=397;
echo select * from t1 where date_diff(f2,f1)<59;
select * from t1 where date_diff(f2,f1)<59;
echo select * from t1 where date_diff(f2,f1)<=59;
select * from t1 where date_diff(f2,f1)<=59;
echo select * from t1 where date_diff(f2,f1)>59;
select * from t1 where date_diff(f2,f1)>59;
echo select * from t1 where date_diff(f2,f1)>=59;
select * from t1 where date_diff(f2,f1)>=59;
echo select * from t1 where date_diff(f2,f1)!=59;
select * from t1 where date_diff(f2,f1)!=59;
echo select * from t1 where date_diff(f2,'2001-01-01')=2;
select * from t1 where date_diff(f2,'2001-01-01')=2;
echo select * from t1 where date_diff(f2,'2001-01-01')>=59;
select * from t1 where date_diff(f2,'2001-01-01')>=59;
echo select * from t1 where date_diff(f2,'2001-01-01')!=365;
select * from t1 where date_diff(f2,'2001-01-01')!=365;
echo select * from t1 where datediff('2001-01-02','2001-01-01')=1;
select * from t1 where date_diff('2001-01-02','2001-01-01')=1;
