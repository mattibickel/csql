echo Create table client_master(clientno char(6), name char(20) NOT NULL, address1 char(30), address2 char(30), city char(15), pincode int, state char(15), baldue float,PRIMARY KEY(clientno));
Create table client_master(clientno char(6), name char(20) NOT NULL, address1 char(30), address2 char(30), city char(15), pincode int, state char(15), baldue float,PRIMARY KEY(clientno));
echo Create table product_master(productno char(6), description char(15) NOT NULL,profitpercent float NOT NULL,unitmeasure char(10) NOT NULL,qtyonhand int NOT NULL,reorderlvl int NOT NULL,selprice float NOT NULL,costprice float NOT NULL, PRIMARY KEY(productno));
Create table product_master(productno char(6), description char(15) NOT NULL,profitpercent float NOT NULL,unitmeasure char(10) NOT NULL,qtyonhand int NOT NULL,reorderlvl int NOT NULL,selprice float NOT NULL,costprice float NOT NULL, PRIMARY KEY(productno));
echo Create table salesman_master(salesmanno char(6),salesmanname char(20) NOT NULL,address1 char(30) NOT NULL,address2 char(30),city char(20),pincode char(8),state char(20),salamt float NOT NULL,tgttoget float NOT NULL,ytdsales float NOT NULL,remarks char(30),PRIMARY KEY(salesmanno));
Create table salesman_master(salesmanno char(6),salesmanname char(20) NOT NULL,address1 char(30) NOT NULL,address2 char(30),city char(20),pincode char(8),state char(20),salamt float NOT NULL,tgttoget float NOT NULL,ytdsales float NOT NULL,remarks char(30),PRIMARY KEY(salesmanno));
echo Create table sales_order(orderno char(6),orderdate date,clientno char(6),delyaddr char(25),delytype char(1),billedyn char(1),salesmanno char(6),delydate date,orderstatus char(10),PRIMARY KEY(orderno),FOREIGN KEY(clientno) REFERENCES client_master(clientno),FOREIGN KEY(salesmanno) REFERENCES salesman_master(salesmanno));
Create table sales_order(orderno char(6),orderdate date,clientno char(6),delyaddr char(25),delytype char(1),billedyn char(1),salesmanno char(6),delydate date,orderstatus char(10),PRIMARY KEY(orderno),FOREIGN KEY(clientno) REFERENCES client_master(clientno),FOREIGN KEY(salesmanno) REFERENCES salesman_master(salesmanno));
echo Create table sales_order_details(orderno char(6),productno char(6),qtyordered int,qtydisp int,productrate float,FOREIGN KEY(orderno) REFERENCES sales_order(orderno),FOREIGN KEY(productno) REFERENCES product_master(productno));
Create table sales_order_details(orderno char(6),productno char(6),qtyordered int,qtydisp int,productrate float,FOREIGN KEY(orderno) REFERENCES sales_order(orderno),FOREIGN KEY(productno) REFERENCES product_master(productno));
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00001','Ivan Bayross','Mumbai',400054,'Maharastra',15000);
insert into client_master(clientno,name,city,pincode,state,baldue) values('C00001','Ivan Bayross','Mumbai',400054,'Maharastra',15000);
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00002','mamta Muzumdar','Madras',780001,'Tamil Nadu',0);
insert into client_master(clientno,name,city,pincode,state,baldue) values('C00002','mamta Muzumdar','Madras',780001,'Tamil Nadu',0);
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00003','Chhaya Bankar','Mumbai',400057,'Maharastra',5000);
insert into client_master(clientno,name,city,pincode,state,baldue) values('C00003','Chhaya Bankar','Mumbai',400057,'Maharastra',5000);
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00004','Ashwini Joshi','Bangalore',560001,'MKarnataka',0);
insert into client_master(clientno,name,city,pincode,state,baldue) values('C00004','Ashwini Joshi','Bangalore',560001,'MKarnataka',0);
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00005','Hansel Colaco','Mumbai',400060,'Maharastra',2000);
insert into client_master(clientno,name,city,pincode,state,baldue) values('C00005','Hansel Colaco','Mumbai',400060,'Maharastra',2000);
echo insert into client_master(clientno,name,city,pincode,state,baldue) values('C00006','Deepak Sharma','Mangalore',560050,'Karnatakaa',0);
insert into client_master(clientno,name,city,pincode,state,baldue) values('C00006','Deepak Sharma','Mangalore',560050,'Karnatakaa',0);
echo insert into product_master values('P00001','T-Shirts',5,'Piece',200,50,350,250);
insert into product_master values('P00001','T-Shirts',5,'Piece',200,50,350,250);
echo insert into product_master values('P03453','Shirts',6,'Piece',150,50,500,350);
insert into product_master values('P03453','Shirts',6,'Piece',150,50,500,350);
echo insert into product_master values('P06734','Cotton Jeans',5,'Piece',100,20,60,450);
insert into product_master values('P06734','Cotton Jeans',5,'Piece',100,20,60,450);
echo insert into product_master values('P07865','Jeans',5,'Piece',100,20,750,500);
insert into product_master values('P07865','Jeans',5,'Piece',100,20,750,500);
echo insert into product_master values('P07868','Trousers',2,'Piece',150,50,850,550);
insert into product_master values('P07868','Trousers',2,'Piece',150,50,850,550);
echo insert into product_master values('P07885','Pull Overs',2.5,'Piece',80,30,700,450);
insert into product_master values('P07885','Pull Overs',2.5,'Piece',80,30,700,450);
echo insert into product_master values('P07965','Denim Shirts',4,'Piece',100,40,350,250);
insert into product_master values('P07965','Denim Shirts',4,'Piece',100,40,350,250);
echo insert into product_master values('P07975','Lycra Tops',5,'Piece',70,30,300,175);
insert into product_master values('P07975','Lycra Tops',5,'Piece',70,30,300,175);
echo insert into product_master values('P08865','Skirts',5,'Piece',75,30,450,300);
insert into product_master values('P08865','Skirts',5,'Piece',75,30,450,300);
echo insert into salesman_master values('S00001','Aman','A/14','Worli','Mumbai',400002,'Maharastra',3000,100,50,'Good');
insert into salesman_master values('S00001','Aman','A/14','Worli','Mumbai',400002,'Maharastra',3000,100,50,'Good');
echo insert into salesman_master values('S00002','Omkar','65','Nariman','Mumbai',400001,'maharastra',3000,200,100,'Good');
insert into salesman_master values('S00002','Omkar','65','Nariman','Mumbai',400001,'maharastra',3000,200,100,'Good');
echo insert into salesman_master values('S00003','Raj','P-7','Banfra','Mumbai',400032,'Maharastra',3000,200,100,'Good');
insert into salesman_master values('S00003','Raj','P-7','Banfra','Mumbai',400032,'Maharastra',3000,200,100,'Good');
echo insert into salesman_master values('S00004','Ashish','A/5','Juhu','Bombay',400044,'Maharastra',3500,200,150,'Good');
insert into salesman_master values('S00004','Ashish','A/5','Juhu','Bombay',400044,'Maharastra',3500,200,150,'Good');
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19001','2002-06-12','C00001','F','N','S00001','2002-07-20','In Process');
insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19001','2002-06-12','C00001','F','N','S00001','2002-07-20','In Process');
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19002','2002-06-25','C00002','P','N','S00002','2002-06-27','Cancelled');
insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19002','2002-06-25','C00002','P','N','S00002','2002-06-27','Cancelled');
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O46865','2002-02-18','C00003','F','Y','S00003','2002-02-20','Fulfilled');
insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O46865','2002-02-18','C00003','F','Y','S00003','2002-02-20','Fulfilled');
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19003','2002-04-03','C00001','F','Y','S00001','2002-04-07','Fulfilled');
insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19003','2002-04-03','C00001','F','Y','S00001','2002-04-07','Fulfilled');
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O46866','2002-05-20','C00004','P','N','S00002','2002-05-22','Cancelled');
insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O46866','2002-05-20','C00004','P','N','S00002','2002-05-22','Cancelled');
echo insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19008','2002-05-24','C00005','F','N','S00004','2002-07-26','In Process');
insert into sales_order (orderno,orderdate,clientno,delytype,billedyn,salesmanno,delydate,orderstatus) values('O19008','2002-05-24','C00005','F','N','S00004','2002-07-26','In Process');
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P00001',4,4,525);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P00001',4,4,525);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P07965',2,1,8400);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P07965',2,1,8400);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P07885',2,1,5250);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19001','P07885',2,1,5250);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19002','P00001',10,0,525);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19002','P00001',10,0,525);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P07868',3,3,3150);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P07868',3,3,3150);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P07885',3,1,5250);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P07885',3,1,5250);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P00001',10,10,525);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P00001',10,10,525);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P03453',4,4,1050);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46865','P03453',4,4,1050);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19003','P03453',2,2,1050);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19003','P03453',2,2,1050);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19003','P06734',1,1,12000);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19003','P06734',1,1,12000);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46866','P07965',1,0,8400);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46866','P07965',1,0,8400);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46866','P07975',1,0,1050);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O46866','P07975',1,0,1050);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19008','P00001',10,5,525);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19008','P00001',10,5,525);
echo insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19008','P07975',5,3,1050);
insert into sales_order_details(orderno,productno,qtyordered,qtydisp,productrate) values('O19008','P07975',5,3,1050);
echo select * from client_master;
select * from client_master;
echo select * from product_master;
select * from product_master;
echo select * from salesman_master;
select * from salesman_master;
echo select * from sales_order;
select * from sales_order;
echo select * from sales_order_details;
select * from sales_order_details;
