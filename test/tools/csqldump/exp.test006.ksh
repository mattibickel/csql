CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT  DEFAULT '10' );
CREATE INDEX indx1 on t1 (  f1  )  HASH ;
CREATE INDEX indx2 on t1 (  f2  )  HASH ;
SET AUTOCOMMIT OFF;
INSERT INTO t1 VALUES(131,10);
INSERT INTO t1 VALUES(141,10);
INSERT INTO t1 VALUES(13,41);
INSERT INTO t1 VALUES(143,41);
INSERT INTO t1 VALUES(153,41);
INSERT INTO t1 VALUES(163,41);
INSERT INTO t1 VALUES(151,10);
INSERT INTO t1 VALUES(1631,10);
INSERT INTO t1 VALUES(163,41);
INSERT INTO t1 VALUES(13,41);
INSERT INTO t1 VALUES(23,41);
INSERT INTO t1 VALUES(551,10);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(43,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(33,41);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(4,41);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(41,10);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(43,41);
INSERT INTO t1 VALUES(53,41);
INSERT INTO t1 VALUES(63,41);
INSERT INTO t1 VALUES(51,10);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(63,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(51,10);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(4,41);
INSERT INTO t1 VALUES(41,10);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(43,41);
INSERT INTO t1 VALUES(53,41);
INSERT INTO t1 VALUES(63,41);
INSERT INTO t1 VALUES(51,10);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(63,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(51,10);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(4,41);
INSERT INTO t1 VALUES(41,10);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(43,41);
INSERT INTO t1 VALUES(53,41);
INSERT INTO t1 VALUES(63,41);
INSERT INTO t1 VALUES(51,10);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(63,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(51,10);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(31,10);
INSERT INTO t1 VALUES(4,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(43,41);
INSERT INTO t1 VALUES(53,41);
INSERT INTO t1 VALUES(63,41);
INSERT INTO t1 VALUES(51,10);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(63,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(51,10);
INSERT INTO t1 VALUES(6317,10);
INSERT INTO t1 VALUES(3,41);
INSERT INTO t1 VALUES(3,413);
INSERT INTO t1 VALUES(3,431);
INSERT INTO t1 VALUES(3,941);
INSERT INTO t1 VALUES(631,10);
INSERT INTO t1 VALUES(431,10);
INSERT INTO t1 VALUES(14,41);
COMMIT;
