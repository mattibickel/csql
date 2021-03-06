echo create table t1(f1 date, f2 date, f3 date, f4 date);
create table t1(f1 date, f2 date, f3 date, f4 date);
echo create index hashdatef1f2f3 on t1(f2,f3,f1) hash;
create index hashdatef1f2f3 on t1(f2,f3,f1) hash;
echo explain plan select * from t1;
explain plan select * from t1;
echo explain plan select * from t1 where f1 = '2003-03-03';
explain plan select * from t1 where f1 = '2003-03-03';
echo explain plan select * from t1 where f1 = '2003-03-03' and f2='2003-03-03';
explain plan select * from t1 where f1 = '2003-03-03' and f2='2003-03-03';
echo explain plan select * from t1 where f1 = '2003-03-03' and f2='2003-03-03' and f3='2003-03-03';
explain plan select * from t1 where f1 = '2003-03-03' and f2='2003-03-03' and f3='2003-03-03';
echo explain plan select * from t1 where f1 = '2003-03-03' or f2='2003-03-03' or f3='2003-03-03';
explain plan select * from t1 where f1 = '2003-03-03' or f2='2003-03-03' or f3='2003-03-03';
echo explain plan select * from t1 where f1 = '2003-03-03' and f2='2003-03-03' or f3='2003-03-03';
explain plan select * from t1 where f1 = '2003-03-03' and f2='2003-03-03' or f3='2003-03-03';
echo explain plan select * from t1 where f1 = '2003-03-03' and f2='2003-03-03' and not(f3='2003-03-03');
explain plan select * from t1 where f1 = '2003-03-03' and f2='2003-03-03' and not(f3='2003-03-03');
echo explain plan select * from t1 where f1 in('2003-03-03','2003-03-03','2003-03-03') and f2='2003-03-03' and not(f3='2003-03-03');
explain plan select * from t1 where f1 in('2003-03-03','2003-03-03','2003-03-03') and f2='2003-03-03' and not(f3='2003-03-03');
echo explain plan select * from t1 where f1 in('2003-03-03','2003-03-08','2003-03-12') and (f2 between '2003-03-03' and '2003-03-03') and not(f3='2003-03-03');
explain plan select * from t1 where f1 in('2003-03-03','2003-03-08','2003-03-12') and (f2 between '2003-03-03' and '2003-03-03') and not(f3='2003-03-03');
echo explain plan select * from t1 where f1 in('2003-03-08','2003-03-12','2003-03-03') or (f2 between '2003-03-03' and '2003-03-03') or not(f3='2003-03-03');
explain plan select * from t1 where f1 in('2003-03-08','2003-03-12','2003-03-03') or (f2 between '2003-03-03' and '2003-03-03') or not(f3='2003-03-03');
echo explain plan select * from t1 where f1 in('2003-03-03','2003-03-12','2003-03-08') or (f2 between '2003-03-03' and '2003-03-03') and not(f3='2003-03-03');
explain plan select * from t1 where f1 in('2003-03-03','2003-03-12','2003-03-08') or (f2 between '2003-03-03' and '2003-03-03') and not(f3='2003-03-03');

