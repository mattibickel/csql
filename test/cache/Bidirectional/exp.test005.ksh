table csql_log_int is created with records in target db
server 1 started
cache node 2
echo select * from t1;
---------------------------------------------------------
	t1f1	t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
echo select * from t2;
---------------------------------------------------------
	t2f1	t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
server 2 started
cache node 1
echo select * from t1;
---------------------------------------------------------
	t1f1	t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
echo select * from t2;
---------------------------------------------------------
	t2f1	t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	
echo select * from t1;
---------------------------------------------------------
	t1f1	t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	12	123	
	
echo select * from t2;
---------------------------------------------------------
	t2f1	t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	15	125	
	
cache node 2
echo select * from t1;
---------------------------------------------------------
	t1f1	t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	12	123	
	
echo select * from t2;
---------------------------------------------------------
	t2f1	t2f2	
---------------------------------------------------------
	1	11	
	2	21	
	3	31	
	4	41	
	5	51	
	6	61	
	7	71	
	8	81	
	9	91	
	10	101	
	15	125	
	
