create table t1(f1 smallint,f2 int,f3 bigint,f4 char(10),f5 float,f6 double,f7 date,f8 time,f9 timestamp);
insert into t1 values(10,100 ,1000,   'Bijay',1000,100000,'2009-03-01','11:59:59','2009-03-01 11:59:59');
insert into t1 values(11,110 ,1100, 'Jitendr',2000,200000,'2009-03-02','11:59:58','2009-03-02 11:59:59');
insert into t1 values(12,120 ,1000,   'Nihar',3000,300000,'2009-03-03','11:59:57','2009-03-03 11:59:59');
insert into t1 values(13,130 ,1500,  'Kishor',4000,400000,'2009-03-04','11:59:59','2009-03-04 11:59:59');
insert into t1 values(14,100 ,1000,   'Praba',5000,500000,'2009-03-01','11:59:58','2009-03-01 11:59:59');
create table t2(f1 smallint,f2 int,f3 bigint,f4 char(10),f5 float,f6 double,f7 date,f8 time,f9 timestamp);
insert into t2 values(13,130 ,1500,  'Kishor',4000,400000,'2009-03-04','11:59:59','2009-03-04 11:59:59');
insert into t2 values(16,120 ,1000,  'Sanjay',6500,700000,'2009-03-03','11:59:59','2009-03-03 11:59:59');
insert into t2 values(10,100 ,1000,   'Bijay',1000,100000,'2009-03-01','11:59:59','2009-03-01 11:59:59');
insert into t2 values(17,130 ,1100, 'Arindam',8000,800000,'2009-03-04','11:59:58','2009-03-04 11:59:59');
insert into t2 values(11,110 ,1100, 'Jitendr',2000,200000,'2009-03-02','11:59:58','2009-03-02 11:59:59');
create table t3(f1 smallint,f2 int,f3 bigint,f4 char(10),f5 float,f6 double,f7 date,f8 time,f9 timestamp);
insert into t3 values(12,120 ,1000,   'Nihar',3000,300000,'2009-03-03','11:59:57','2009-03-03 11:59:59');
insert into t3 values(14,100 ,1000,   'Praba',4000,400000,'2009-03-01','11:59:55','2009-03-04 11:59:59');
insert into t3 values(13,130 ,1500,  'Kishor',4000,400000,'2009-03-04','11:59:59','2009-03-04 11:59:59');
insert into t3 values(11,110 ,1100, 'Jitendr',2000,200000,'2009-03-02','11:59:58','2009-03-02 11:59:59');
insert into t3 values(16,120 ,1000,  'Sanjay',6000,600000,'2009-03-03','11:59:55','2009-03-03 11:59:59');
echo select * from t1;
select * from t1;
echo select * from t2;
select * from t2;
echo select * from t3;
select * from t3;
