echo create table t1 (f1 int,f2 char(10),f3 int,f4 int,f5 bigint,primary key(f1) size 1500);
create table t1 (f1 int,f2 char(10),f3 int,f4 int,f5 bigint,primary key(f1) size 1500);
echo create index ind1 on t1(f2) hash size 750;
create index ind1 on t1(f2) hash size 750;
echo create index ind2 on t1(f3) tree size 10000;
create index ind2 on t1(f3) tree size 10000;
echo create table t2 (f1 int,f2 char(10),f3 int,f4 int,f5 bigint,primary key(f2) size 1500);
create table t2 (f1 int,f2 char(10),f3 int,f4 int,f5 bigint,primary key(f2) size 1500);
echo create index ind3 on t2(f1) hash unique size 750;
create index ind3 on t2(f1) hash unique size 750;
