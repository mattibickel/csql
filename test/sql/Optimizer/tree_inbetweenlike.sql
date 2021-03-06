echo create table t1(f1 tinyint, f2 smallint, f3 int, f4 bigint, f5 char(10), f6 varchar(10), f7 date, f8 time, f9 float, f10 double, f11 timestamp);
create table t1(f1 tinyint, f2 smallint, f3 int, f4 bigint, f5 char(10), f6 varchar(10), f7 date, f8 time, f9 float, f10 double, f11 timestamp);
echo create index treetiny on t1(f1) tree;
create index treetiny on t1(f1) tree;
echo create index treesmall on t1(f2) tree;
create index treesmall on t1(f2) tree;
echo create index treeint on t1(f3) tree;
create index treeint on t1(f3) tree;
echo create index treebig on t1(f4) tree;
create index treebig on t1(f4) tree;
echo create index treechar on t1(f5) tree;
create index treechar on t1(f5) tree;
echo create index treevarchar on t1(f6) tree;
create index treevarchar on t1(f6) tree;
echo create index treedate on t1(f7) tree;
create index treedate on t1(f7) tree;
echo create index treetime on t1(f8) tree;
create index treetime on t1(f8) tree;
echo create index treefloat on t1(f9) tree;
create index treefloat on t1(f9) tree;
echo create index treedouble on t1(f10) tree;
create index treedouble on t1(f10) tree;
echo create index treetimestamp on t1(f11) tree;
create index treetimestamp on t1(f11) tree;
echo explain plan select * from t1;  
explain plan select * from t1;  
echo explain plan select * from t1 where f1 in (0,2,4);
explain plan select * from t1 where f1 in (0,2,4) ;
echo explain plan select * from t1 where f1 between 2 and 4;
explain plan select * from t1 where f1  between 2 and 4;
echo explain plan select * from t1 where f2 in (0,2,4);;
explain plan select * from t1 where f2 in (0,2,4);
echo explain plan select * from t1 where f2 between 2 and 4;
explain plan select * from t1 where f2 between 2 and 4;
echo explain plan select * from t1 where f3 in (1,2);
explain plan select * from t1 where f3 in (1,2) ;
echo explain plan select * from t1 where f3 between 1 and 4;
explain plan select * from t1 where f3 between 1 and 4;
echo explain plan select * from t1 where f4 in (1,2);
explain plan select * from t1 where f4 in (1,2) ;
echo explain plan select * from t1 where f4 between 1 and 4;
explain plan select * from t1 where f4 between 1 and 4;
echo explain plan select * from t1 where f5 in ('1','2');
explain plan select * from t1 where f5 in ('1','2') ;
echo explain plan select * from t1 where f5 like 'N%';
explain plan select * from t1 where f5 like 'N%';
echo explain plan select * from t1 where f5 like 'N_h';
explain plan select * from t1 where f5 like 'N_h';
echo explain plan select * from t1 where f6 in ('1','2');
explain plan select * from t1 where f6 in ('1','2') ;
echo explain plan select * from t1 where f6 like 'N%';
explain plan select * from t1 where f6 like 'N%';
echo explain plan select * from t1 where f6 like 'N_h';
explain plan select * from t1 where f6 like 'N_h';
echo explain plan select * from t1 where f7 in ('2003-11-12','2003-11-15');
explain plan select * from t1 where f7 in ('2003-11-12','2003-11-15');
echo explain plan select * from t1 where f7 between '2003-11-12' and '2003-11-15';
explain plan select * from t1 where f7 between '2003-11-12' and '2003-11-15';
echo explain plan select * from t1 where f8 in ('03:21:00','03:21:08');
explain plan select * from t1 where f8 in ('03:21:00','03:21:08');
echo explain plan select * from t1 where f8 between '03:21:00' and '03:21:08';
explain plan select * from t1 where f8 between '03:21:00' and '03:21:08';
echo explain plan select * from t1 where f9 in ('2.7','3.7');
explain plan select * from t1 where f9 in ('2.7','3.7');
echo explain plan select * from t1 where f9 between '2.7' and '3.7';
explain plan select * from t1 where f9 between '2.7' and '3.7';
echo explain plan select * from t1 where f10 in ('2.7','3.7');
explain plan select * from t1 where f10 in ('2.7','3.7');
echo explain plan select * from t1 where f10 between '2.7' and '3.7';
explain plan select * from t1 where f10 between '2.7' and '3.7';
echo explain plan select * from t1 where f11 in ('2003-11-12 01:01:01','2003-11-18 01:01:01');
explain plan select * from t1 where f11 in ('2003-11-12 01:01:01','2003-11-18 01:01:01');
echo explain plan select * from t1 where f11 between '2003-11-12 01:01:01' and '2003-11-18 01:01:01';
explain plan select * from t1 where f11 between '2003-11-12 01:01:01' and '2003-11-18 01:01:01';
