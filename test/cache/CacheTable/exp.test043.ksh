
(1). cachetable -S

=================================================================================================================
|Mode|	Table Name	|	Primary Key	|	Condition	|	Field List	|	DSN	|
=================================================================================================================
| 1  |              t1	|            NULL	|            NULL	|            NULL	|   myodbc3	|
-----------------------------------------------------------------------------------------------------------------
| 2  |              t2	|            NULL	|         t2f1=11	|            NULL	|   myodbc3	|
-----------------------------------------------------------------------------------------------------------------
| 4  |              t3	|            NULL	|            NULL	|            t3f1	|   myodbc3	|
-----------------------------------------------------------------------------------------------------------------
| 8  |              t4	|            NULL	|            NULL	|            NULL	|   myodbc3	|
-----------------------------------------------------------------------------------------------------------------
|14  |              t5	|            NULL	|         t5f1=11	|            t5f2	|   myodbc3	|
-----------------------------------------------------------------------------------------------------------------

(2). cachetable -t t5 -S

=================================================================================================================
|Mode|	Table Name	|	Primary Key	|	Condition	|	Field List	|	DSN	|
=================================================================================================================
|14  |              t5	|            NULL	|         t5f1=11	|            t5f2	|   myodbc3	|
-----------------------------------------------------------------------------------------------------------------

(3). cachetable -S (Cross Verification)

=================================================================================================================
|Mode|	Table Name	|	Primary Key	|	Condition	|	Field List	|	DSN	|
=================================================================================================================
|                                Cached table does not exist.                                                   |
=================================================================================================================
