select COUNT(*) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
select SUM(T1.f1) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
select MIN(T1.f1) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
select AVG(T1.f1) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
select MAX(T1.f1) from T1,T2,T3,T4,T5 where T1.f2=T2.f2 and T1.f3=T3.f3 and T1.f4=T4.f4 and T1.f5=T5.f5;
