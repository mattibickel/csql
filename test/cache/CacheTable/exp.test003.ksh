CREATE TABLE t1 (f1 SMALLINT  NOT NULL , f2 INT );
CREATE INDEX t1_idx1_Primary on t1 ( f1 )  UNIQUE;
SET AUTOCOMMIT OFF;
INSERT INTO t1 VALUES(1,1111);
INSERT INTO t1 VALUES(2,2222);
COMMIT;