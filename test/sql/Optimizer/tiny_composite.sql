echo create table t1(f1 tinyint, f2 tinyint, f3 tinyint, f4 tinyint);
create table t1(f1 tinyint, f2 tinyint, f3 tinyint, f4 tinyint);
echo create index hashtinyf1f2f3 on t1(f2,f3,f1) hash;
create index hashtinyf1f2f3 on t1(f2,f3,f1) hash;
echo explain plan select * from t1;
explain plan select * from t1;
echo explain plan select * from t1 where f1 = 2;
explain plan select * from t1 where f1 = 2;
echo explain plan select * from t1 where f1 = 2 and f2=2;
explain plan select * from t1 where f1 = 2 and f2=2;
echo explain plan select * from t1 where f1 = 2 and f2=2 and f3=2;
explain plan select * from t1 where f1 = 2 and f2=2 and f3=2;
echo explain plan select * from t1 where f1 = 2 or f2=2 or f3=2;
explain plan select * from t1 where f1 = 2 or f2=2 or f3=2;
echo explain plan select * from t1 where f1 = 2 and f2=2 or f3=2;
explain plan select * from t1 where f1 = 2 and f2=2 or f3=2;
echo explain plan select * from t1 where f1 = 2 and f2=2 and not(f3=2);
explain plan select * from t1 where f1 = 2 and f2=2 and not(f3=2);
echo explain plan select * from t1 where f1 in(1,2,3) and f2=2 and not(f3=2);
explain plan select * from t1 where f1 in(1,2,3) and f2=2 and not(f3=2);
echo explain plan select * from t1 where f1 in(1,2,3) and (f2 between 2 and 4) and not(f3=2);
explain plan select * from t1 where f1 in(1,2,3) and (f2 between 2 and 4) and not(f3=2);
echo explain plan select * from t1 where f1 in(1,2,3) or (f2 between 2 and 4) or not(f3=2);
explain plan select * from t1 where f1 in(1,2,3) or (f2 between 2 and 4) or not(f3=2);
echo explain plan select * from t1 where f1 in(1,2,3) or (f2 between 2 and 4) and not(f3=2);
explain plan select * from t1 where f1 in(1,2,3) or (f2 between 2 and 4) and not(f3=2);

