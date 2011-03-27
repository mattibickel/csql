echo create table T1 ( f1 int, f2 bigint, f3 smallint,f4 tinyint);
create table T1 ( f1 int, f2 bigint, f3 smallint,f4 tinyint);
echo create index idx1 on T1(f1) unique;
create index idx1 on T1(f1) unique;
echo create index idx2 on T1(f2) unique;
create index idx2 on T1(f2) unique;
echo create index idx3 on T1(f3) unique;
create index idx3 on T1(f3) unique;
echo create index idx4 on T1(f4) unique;
create index idx4 on T1(f4) unique;
echo create index idx5 on T1(f1,f1) unique;
create index idx5 on T1(f1,f1) unique;
echo create index idx6 on T1(f1,f2) unique;
create index idx6 on T1(f1,f2) unique;
echo create index idx7 on T1(f1,f3) unique;
create index idx7 on T1(f1,f3) unique;
echo create index idx8 on T1(f1,f4) unique;
create index idx8 on T1(f1,f4) unique;
echo create index idx9 on T1(f2,f1) unique;
create index idx9 on T1(f2,f1) unique;
echo create index idx10 on T1(f2,f2) unique;
create index idx10 on T1(f2,f2) unique;
echo create index idx11 on T1(f2,f3) unique;
create index idx11 on T1(f2,f3) unique;
echo create index idx12 on T1(f2,f4) unique;
create index idx12 on T1(f2,f4) unique;
echo create index idx13 on T1(f3,f1) unique;
create index idx13 on T1(f3,f1) unique;
echo create index idx14 on T1(f3,f2) unique;
create index idx14 on T1(f3,f2) unique;
echo create index idx15 on T1(f3,f3) unique;
create index idx15 on T1(f3,f3) unique;
echo create index idx16 on T1(f3,f4) unique;
create index idx16 on T1(f3,f4) unique;
echo create index idx17 on T1(f4,f1) unique;
create index idx17 on T1(f4,f1) unique;
echo create index idx18 on T1(f4,f2) unique;
create index idx18 on T1(f4,f2) unique;
echo create index idx19 on T1(f4,f3) unique;
create index idx19 on T1(f4,f3) unique;
echo create index idx20 on T1(f4,f4) unique;
create index idx20 on T1(f4,f4) unique;
echo create index idx21 on T1(f1,f2,f3) unique;
create index idx21 on T1(f1,f2,f3) unique;
echo create index idx22 on T1(f1,f2,f4) unique;
create index idx22 on T1(f1,f2,f4) unique;
echo create index idx23 on T1(f1,f3,f2) unique;
create index idx23 on T1(f1,f3,f2) unique;
echo create index idx24 on T1(f1,f3,f4) unique;
create index idx24 on T1(f1,f3,f4) unique;
echo create index idx25 on T1(f1,f4,f1) unique;
create index idx25 on T1(f1,f4,f1) unique;
echo create index idx26 on T1(f1,f4,f3) unique;
create index idx26 on T1(f1,f4,f3) unique;
echo create index idx27 on T1(f2,f1,f3) unique;
create index idx27 on T1(f2,f1,f3) unique;
echo create index idx28 on T1(f2,f1,f4) unique;
create index idx28 on T1(f2,f1,f4) unique;
echo create index idx29 on T1(f2,f3,f1) unique;
create index idx29 on T1(f2,f3,f1) unique;
echo create index idx30 on T1(f2,f3,f4) unique;
create index idx30 on T1(f2,f3,f4) unique;
echo create index idx31 on T1(f2,f4,f1) unique;
create index idx31 on T1(f2,f4,f1) unique;
echo create index idx32 on T1(f2,f4,f3) unique;
create index idx32 on T1(f2,f4,f3) unique;
echo create index idx33 on T1(f3,f1,f2) unique;
create index idx33 on T1(f3,f1,f2) unique;
echo create index idx34 on T1(f3,f1,f4) unique;
create index idx34 on T1(f3,f1,f4) unique;
echo create index idx35 on T1(f3,f1,f2) unique;
create index idx35 on T1(f3,f1,f2) unique;
echo create index idx36 on T1(f3,f1,f4) unique;
create index idx36 on T1(f3,f1,f4) unique;
echo create index idx37 on T1(f3,f2,f1) unique;
create index idx37 on T1(f3,f2,f1) unique;
echo create index idx38 on T1(f3,f2,f4) unique;
create index idx38 on T1(f3,f2,f4) unique;
echo create index idx39 on T1(f4,f2,f1) unique;
create index idx39 on T1(f4,f2,f1) unique;
echo create index idx40 on T1(f4,f2,f3) unique;
create index idx40 on T1(f4,f2,f3) unique;
echo create index idx41 on T1(f4,f3,f1) unique;
create index idx41 on T1(f4,f3,f1) unique;
echo create index idx42 on T1(f4,f3,f2) unique;
create index idx42 on T1(f4,f3,f2) unique;
echo create index idx43 on T1(f4,f1,f2) unique;
create index idx43 on T1(f4,f1,f2) unique;
echo create index idx44 on T1(f4,f1,f3) unique;
create index idx44 on T1(f4,f1,f3) unique;
echo create index idx45 on T1(f1,f2,f3,f4) unique;
create index idx45 on T1(f1,f2,f3,f4) unique;
echo create index idx46 on T1(f2,f1,f4,f3) unique;
create index idx46 on T1(f2,f1,f4,f3) unique;
echo create index idx47 on T1(f1,f4,f3,f2) unique;
create index idx47 on T1(f1,f4,f3,f2) unique;
echo create index idx48 on T1(f4,f3,f1,f2) unique;
create index idx48 on T1(f4,f3,f1,f2) unique;
echo "Tree Index";
echo create index idx01 on T1(f1) tree unique;
create index idx01 on T1(f1) tree unique;
echo create index idx02 on T1(f2) tree unique;
create index idx02 on T1(f2) tree unique;
echo create index idx03 on T1(f3) tree unique;
create index idx03 on T1(f3) tree unique;
echo create index idx04 on T1(f4) tree unique;
create index idx04 on T1(f4) tree unique;
echo create index idx05 on T1(f1,f1) tree unique;
create index idx05 on T1(f1,f1) tree unique;
echo create index idx06 on T1(f1,f2) tree unique;
create index idx06 on T1(f1,f2) tree unique;
echo create index idx07 on T1(f1,f3) tree unique;
create index idx07 on T1(f1,f3) tree unique;
echo create index idx08 on T1(f1,f4) tree unique;
create index idx08 on T1(f1,f4) tree unique;
echo create index idx09 on T1(f2,f1) tree unique;
create index idx09 on T1(f2,f1) tree unique;
echo DROP TABLE T1;
DROP TABLE T1;



create table t1 ( f1 int, f2 bigint, f3 smallint,f4 tinyint);
insert into t1 values(1, 2, 3, 4);
insert into t1 values(1, 3, 5, 6);
insert into t1 values(1, 3, 7, 8);
insert into t1 values(1, 3, 7, 8);
echo "Hash Index";
create index idx1 on t1(f1) unique;
create index idx2 on t1(f2) unique;
create index idx3 on t1(f3) unique;
create index idx4 on t1(f4) unique;
create index idx5 on t1(f1,f1) unique;
create index idx6 on t1(f1,f2) unique;
create index idx7 on t1(f1,f3) unique;
create index idx8 on t1(f1,f4) unique;
create index idx9 on t1(f2,f1) unique;
create index idx10 on t1(f2,f2) unique;
create index idx11 on t1(f2,f3) unique;
create index idx12 on t1(f2,f4) unique;
create index idx13 on t1(f3,f1) unique;
create index idx14 on t1(f3,f2) unique;
create index idx15 on t1(f3,f3) unique;
create index idx16 on t1(f3,f4) unique;
create index idx17 on t1(f4,f1) unique;
create index idx18 on t1(f4,f2) unique;
create index idx19 on t1(f4,f3) unique;
create index idx20 on t1(f4,f4) unique;
create index idx21 on t1(f1,f2,f3) unique;
create index idx22 on t1(f1,f2,f4) unique;
create index idx23 on t1(f1,f3,f2) unique;
create index idx24 on t1(f1,f3,f4) unique;
create index idx25 on t1(f1,f4,f1) unique;
create index idx26 on t1(f1,f4,f3) unique;
create index idx27 on t1(f2,f1,f3) unique;
create index idx28 on t1(f2,f1,f4) unique;
create index idx29 on t1(f2,f3,f1) unique;
create index idx30 on t1(f2,f3,f4) unique;
create index idx31 on t1(f2,f4,f1) unique;
create index idx32 on t1(f2,f4,f3) unique;
create index idx33 on t1(f3,f1,f2) unique;
create index idx34 on t1(f3,f1,f4) unique;
create index idx35 on t1(f3,f1,f2) unique;
create index idx36 on t1(f3,f1,f4) unique;
create index idx37 on t1(f3,f2,f1) unique;
create index idx38 on t1(f3,f2,f4) unique;
create index idx39 on t1(f4,f2,f1) unique;
create index idx40 on t1(f4,f2,f3) unique;
create index idx41 on t1(f4,f3,f1) unique;
create index idx42 on t1(f4,f3,f2) unique;
create index idx43 on t1(f4,f1,f2) unique;
create index idx44 on t1(f4,f1,f3) unique;
create index idx45 on t1(f1,f2,f3,f4) unique;
create index idx46 on t1(f2,f1,f4,f3) unique;
create index idx47 on t1(f1,f4,f3,f2) unique;
create index idx48 on t1(f4,f3,f1,f2) unique;
echo "Tree Index";
create index idx01 on t1(f1) tree unique;
create index idx02 on t1(f2) tree unique;
create index idx03 on t1(f3) tree unique;
create index idx04 on t1(f4) tree unique;
create index idx05 on t1(f1,f1) tree unique;
create index idx06 on t1(f1,f2) tree unique;
create index idx07 on t1(f1,f3) tree unique;
create index idx08 on t1(f1,f4) tree unique;
create index idx09 on t1(f2,f1) tree unique;



