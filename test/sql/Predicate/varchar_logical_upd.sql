echo Create table t1(f1 varchar(10), f2 char(10), f3 varchar(10), f4 int);
Create table t1(f1 varchar(10), f2 char(10), f3 varchar(10), f4 int);
Insert into t1 values('CSQL1', 'LAKS1','BBSR1',10);
Insert into t1 values('CSQL1', 'LAKS1','BBSR2',20);
Insert into t1 values('CSQL1', 'LAKS2','BBSR3',30);
Insert into t1 values('CSQL1', 'LAKS2','BBSR4',40);
Insert into t1 values('CSQL2', 'LAKS3','BBSR5',50);
Insert into t1 values('CSQL2', 'LAKS3','BBSR6',60);
Insert into t1 values('CSQL2', 'LAKS4','BBSR7',70);
Insert into t1 values('CSQL2', 'LAKS4','BBSR8',80);
echo select * from t1;
select * from t1;
echo update t1 set f3='Orissa1',f4=100 where f3='BBSR1' and f1='CSQL1';
update t1 set f3='Orissa1',f4=100 where f3='BBSR1' and f1='CSQL1';
echo select * from t1;
select * from t1;
echo update t1 set f3='Orissa1',f4=100 where not(f3='BBSR1') and f1='CSQL2';
update t1 set f3='Orissa1',f4=100 where not(f3='BBSR1') and f1='CSQL2';
echo select * from t1;
select * from t1;
echo update t1 set f3='Orissa2',f4=200 where f3='BBSR2' or f1='CSQL1';
update t1 set f3='Orissa2',f4=200 where f3='BBSR2' or f1='CSQL1';
echo select * from t1;
select * from t1;
echo update t1 set f3='Orissa3',f4=300 where f1='CSQL1' and f3 like '__issa2';
update t1 set f3='Orissa3',f4=300 where f1='CSQL1' and f3 like '__issa2';
echo select * from t1;
select * from t1;
echo update t1 set f3='Orissa4',f4=400 where f2='LAKS2' and f3 like '_r%3';
update t1 set f3='Orissa4',f4=400 where f2='LAKS2' and f3 like '_r%3';
echo select * from t1;
select * from t1;
echo update t1 set f3='Orissa4',f4=400 where not(f3='Orissa1') or f2 in ('LAKS3','LAKS5');
update t1 set f3='Orissa4',f4=400 where not(f3='Orissa1') or f2 in ('LAKS3','LAKS5');
echo select * from t1;
select * from t1;
echo update t1 set f3='Orissa4',f4=400 where not(f3='Orissa1') or f2 in ('LAKS3',NULL);
update t1 set f3='Orissa4',f4=400 where not(f3='Orissa1') or f2 in ('LAKS3',NULL);
echo select * from t1;
select * from t1;
echo update t1 set f3='Orissa5',f2='LAKS5' where f1='CSQL1' and f3 like 'O_is_a4';
update t1 set f3='Orissa5',f2='LAKS5' where f1='CSQL1' and f3 like 'O_is_a4';
echo select * from t1;
select * from t1;
