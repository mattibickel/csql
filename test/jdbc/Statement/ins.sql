CREATE TABLE T1 (f1 int, f2 smallint, f3 tinyint, f4 bigint, f5 float, f6 char(10), f7 date, f8 time, f9 timestamp);
INSERT INTO T1 VALUES(100,10,1,1000,1000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(200,20,1,1000,2000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(300,30,1,1000,3000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(100,40,1,1000,4000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(200,50,1,1000,5000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(400,60,1,1000,5000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(100,70,1,1000,6000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(200,80,1,1000,7000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(300,90,1,1000,8000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
INSERT INTO T1 VALUES(1000,100,1,1000,9000.00,'Nihar','2008-03-21','18:00:00','2008-03-21 18:00:00');
echo Select f1,f5 from T1 order by f1;
Select f1,f5 from T1 order by f1;
