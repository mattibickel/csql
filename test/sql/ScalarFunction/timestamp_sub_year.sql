echo Create table t1(f1 timestamp, f2 timestamp);
Create table t1(f1 timestamp, f2 timestamp);
insert into t1 values('2001-01-01 01:01:01', '2001-01-01 02:01:01');
insert into t1 values('2002-01-01 01:01:01', '2001-02-01 01:01:01');
insert into t1 values('2003-01-01 01:01:01', '2001-03-01 01:01:01');
insert into t1 values('2004-01-01 01:01:01', '2002-04-01 01:01:01');
insert into t1 values('2005-01-01 01:01:01', '2002-05-01 01:01:01');
echo select * from t1;
select * from t1;
echo select * from t1 where timestamp_sub(f1 interval 5 year) ='1998-01-01 01:01:01'; 
select * from t1 where timestamp_sub(f1 interval 5 year) ='1998-01-01 01:01:01'; 
echo select * from t1 where timestamp_sub(f1 interval 5 year)<='1998-01-01 01:01:01'; 
select * from t1 where timestamp_sub(f1 interval 5 year)<='1998-01-01 01:01:01'; 
echo select * from t1 where timestamp_sub(f1 interval 5 year) >'1998-01-01 01:01:01'; 
select * from t1 where timestamp_sub(f1 interval 5 year) >'1998-01-01 01:01:01'; 
echo select * from t1 where timestamp_sub(f1 interval 5 year)!='1998-01-01 01:01:01'; 
select * from t1 where timestamp_sub(f1 interval 5 year)!='1998-01-01 01:01:01'; 
