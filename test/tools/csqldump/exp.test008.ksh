CREATE TABLE kishor (fld1 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX kishor_idx1_Primary on kishor ( fld1 )  UNIQUE;
CREATE TABLE ravi (fld2 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX ravi_idx1_Primary on ravi ( fld2 )  UNIQUE;
CREATE TABLE kiran (fld3 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX kiran_idx1_Primary on kiran ( fld3 )  UNIQUE;
CREATE TABLE anand (fld4 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX anand_idx1_Primary on anand ( fld4 )  UNIQUE;
CREATE TABLE vikas (fld5 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX vikas_idx1_Primary on vikas ( fld5 )  UNIQUE;
CREATE TABLE vikram (fld6 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX vikram_idx1_Primary on vikram ( fld6 )  UNIQUE;
CREATE TABLE vinod (fld7 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX vinod_idx1_Primary on vinod ( fld7 )  UNIQUE;
CREATE TABLE jayant (fld8 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX jayant_idx1_Primary on jayant ( fld8 )  UNIQUE;
CREATE TABLE rahul (fld9 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX rahul_idx1_Primary on rahul ( fld9 )  UNIQUE;
CREATE TABLE ramesh (fld10 INT  NOT NULL , name1 CHAR (30));
CREATE INDEX ramesh_idx1_Primary on ramesh ( fld10 )  UNIQUE;
SET AUTOCOMMIT OFF;
INSERT INTO kishor VALUES(11, 'raksha1');
INSERT INTO kishor VALUES(2, 'Laxkshya2');
INSERT INTO kishor VALUES(32, 'Laksxhya3');
INSERT INTO kishor VALUES(4, 'Lakhya4');
INSERT INTO kishor VALUES(5, 'Laka5');
INSERT INTO kishor VALUES(63, 'shya6');
INSERT INTO kishor VALUES(7, 'Laksya7');
INSERT INTO kishor VALUES(18, 'Lakya8');
INSERT INTO kishor VALUES(97, 'Lakhya9');
INSERT INTO kishor VALUES(104, 'Laa10');
COMMIT;
INSERT INTO ravi VALUES(11, 'Lakshy');
INSERT INTO ravi VALUES(22, 'raksha2');
INSERT INTO ravi VALUES(33, 'raksha3');
INSERT INTO ravi VALUES(44, 'Lak4');
INSERT INTO ravi VALUES(55, 'raksha5');
INSERT INTO ravi VALUES(66, 'Lakya6');
INSERT INTO ravi VALUES(77, 'raksha7');
INSERT INTO ravi VALUES(88, 'Laksa8');
INSERT INTO ravi VALUES(99, 'Laksya9');
INSERT INTO ravi VALUES(100, 'Lashya10');
COMMIT;
INSERT INTO kiran VALUES(31, 'raksha1');
INSERT INTO kiran VALUES(42, 'Lakshya2');
INSERT INTO kiran VALUES(53, 'raksha3');
INSERT INTO kiran VALUES(64, 'Lakshya4');
INSERT INTO kiran VALUES(58, 'raksha5');
INSERT INTO kiran VALUES(63, 'Lakshya6');
INSERT INTO kiran VALUES(74, 'raksha7');
INSERT INTO kiran VALUES(87, 'Lakshya8');
INSERT INTO kiran VALUES(94, 'raksha9');
INSERT INTO kiran VALUES(10, 'Lakshya10');
COMMIT;
INSERT INTO anand VALUES(12, 'Lakshya1');
INSERT INTO anand VALUES(23, 'raksha2');
INSERT INTO anand VALUES(35, 'Lakshya3');
INSERT INTO anand VALUES(48, 'Lakshya4');
INSERT INTO anand VALUES(53, 'raksha5');
INSERT INTO anand VALUES(66, 'Lakshya6');
INSERT INTO anand VALUES(79, 'Lakshya7');
INSERT INTO anand VALUES(81, 'raksha8');
INSERT INTO anand VALUES(94, 'Lakshya9');
INSERT INTO anand VALUES(105, 'Lakshya10');
COMMIT;
INSERT INTO vikas VALUES(1, 'Lakshya1');
INSERT INTO vikas VALUES(2, 'Lakshya2');
INSERT INTO vikas VALUES(3, 'raksha3');
INSERT INTO vikas VALUES(4, 'Lakshya4');
INSERT INTO vikas VALUES(5, 'Lakshya5');
INSERT INTO vikas VALUES(6, 'Lakshya6');
INSERT INTO vikas VALUES(7, 'Lakshya7');
INSERT INTO vikas VALUES(8, 'Lakshya8');
INSERT INTO vikas VALUES(9, 'raksha9');
INSERT INTO vikas VALUES(10, 'Lakshya10');
COMMIT;
INSERT INTO vikram VALUES(1, 'Lakshya1');
INSERT INTO vikram VALUES(2, 'raksha2');
INSERT INTO vikram VALUES(3, 'Lakshya3');
INSERT INTO vikram VALUES(4, 'raksha4');
INSERT INTO vikram VALUES(5, 'Lakshya5');
INSERT INTO vikram VALUES(6, 'Lakshya6');
INSERT INTO vikram VALUES(7, 'raksha7');
INSERT INTO vikram VALUES(8, 'Lakshya8');
INSERT INTO vikram VALUES(9, 'Lakshya9');
INSERT INTO vikram VALUES(10, 'Lakshya10');
COMMIT;
INSERT INTO vinod VALUES(1, 'Lakshya1');
INSERT INTO vinod VALUES(2, 'raksha2');
INSERT INTO vinod VALUES(3, 'Lakshya3');
INSERT INTO vinod VALUES(4, 'Lakshya4');
INSERT INTO vinod VALUES(5, 'raksha5');
INSERT INTO vinod VALUES(6, 'Lakshya6');
INSERT INTO vinod VALUES(7, 'Lakshya7');
INSERT INTO vinod VALUES(8, 'raksha8');
INSERT INTO vinod VALUES(9, 'Lakshya9');
INSERT INTO vinod VALUES(10, 'Lakshya10');
COMMIT;
INSERT INTO jayant VALUES(1, 'Lakshya1');
INSERT INTO jayant VALUES(2, 'raksha2');
INSERT INTO jayant VALUES(3, 'Lakshya3');
INSERT INTO jayant VALUES(4, 'Lakshya4');
INSERT INTO jayant VALUES(5, 'raksha5');
INSERT INTO jayant VALUES(6, 'Lakshya6');
INSERT INTO jayant VALUES(7, 'Lakshya7');
INSERT INTO jayant VALUES(8, 'raksha8');
INSERT INTO jayant VALUES(9, 'Lakshya9');
INSERT INTO jayant VALUES(10, 'Lakshya10');
COMMIT;
INSERT INTO rahul VALUES(1, 'Lakshya1');
INSERT INTO rahul VALUES(2, 'Lakshya2');
INSERT INTO rahul VALUES(3, 'raksha3');
INSERT INTO rahul VALUES(4, 'Lakshya4');
INSERT INTO rahul VALUES(5, 'Lakshya5');
INSERT INTO rahul VALUES(6, 'raksha6');
INSERT INTO rahul VALUES(7, 'Lakshya7');
INSERT INTO rahul VALUES(8, 'Lakshya8');
INSERT INTO rahul VALUES(9, 'Lakshya9');
INSERT INTO rahul VALUES(10, 'Lakshya10');
COMMIT;
INSERT INTO ramesh VALUES(1, 'Lakshya1');
INSERT INTO ramesh VALUES(2, 'Lakshya2');
INSERT INTO ramesh VALUES(3, 'Lakshya3');
INSERT INTO ramesh VALUES(4, 'Lakshya4');
INSERT INTO ramesh VALUES(5, 'Lakshya5');
INSERT INTO ramesh VALUES(6, 'raksha6');
INSERT INTO ramesh VALUES(7, 'raksha7');
INSERT INTO ramesh VALUES(8, 'raksha8');
INSERT INTO ramesh VALUES(9, 'raksha9');
INSERT INTO ramesh VALUES(10, 'Lakshya10');
COMMIT;