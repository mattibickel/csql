echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 group by f1,f2;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 group by f1,f2;
echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 group by f1,f2 having count(f4)>=2;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 group by f1,f2 having count(f4)>=2;
echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 group by f1,f2;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 group by f1,f2;
echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 group by f1,f2 having count(f8)>=1;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 group by f1,f2 having count(f8)>=1;
echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2;
echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having count(f9)>=2;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having count(f9)>=2;
echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having count(f4)>=2 and count(f8) <2;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f1<15 group by f1,f2 having count(f4)>=2 and count(f8) <2;
echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 ;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 ;
echo select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 having count(f7)>=2 and count(f8)<>2;
select f1,f2,count(f4),count(f7),count(f8),count(f9)  from t1 where f1 >= 12 and f2<130 group by f1,f2 having count(f7)>=2 and count(f8)<>2;
echo select f7,f8,f9,count(f4) from t1 group by f7,f8,f9;
select f7,f8,f9,count(f4) from t1 group by f7,f8,f9;
echo select f9,f7,f8,count(f4) from t1 group by f7,f8,f9;
select f9,f7,f8,count(f4) from t1 group by f7,f8,f9;
echo select f7,f8,f9,count(f4) from t1 group by f7,f9,f8;
select f7,f8,f9,count(f4) from t1 group by f7,f9,f8;
echo select f7,f8,f9,count(f4) from t1 group by f7,f9,f8 having count(f4)>=1 and count(f4) <2;
select f7,f8,f9,count(f4) from t1 group by f7,f9,f8 having count(f4)>=1 and count(f4) <2;
echo select f4,f8,f9,count(f7) from t1 group by f4,f8,f9;
select f4,f8,f9,count(f7) from t1 group by f4,f8,f9;
echo select f4,f8,f9,count(f7) from t1 group by f4,f8,f9 having count(f7)<=2 and count(f7) >1 ;
select f4,f8,f9,count(f7) from t1 group by f4,f8,f9 having count(f7)<=2 and count(f7) >1 ;
echo select f9,f7,f4,count(f8) from t1 group by f4,f7,f9;
select f9,f7,f4,count(f8) from t1 group by f4,f7,f9;
echo select f9,f7,f4,count(f8) from t1 group by f4,f7,f9 having count(f8)<=2 and count(f8) >=2 ;
select f9,f7,f4,count(f8) from t1 group by f4,f7,f9 having count(f8)<=2  and count(f8) >=2 ;
echo select f7,f8,f4,count(f9) from t1 group by f4,f7,f8;
select f7,f8,f4,count(f9) from t1 group by f4,f7,f8;
echo select f7,f8,f4,count(f9) from t1 group by f4,f7,f8 having count(f9)<=2 and count(f9) >=2 ;
select f7,f8,f4,count(f9) from t1 group by f4,f7,f8 having count(f9)<=2 and count(f9) >=2 ;
