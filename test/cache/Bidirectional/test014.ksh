#!/bin/ksh
# Test Case
# Create 100 table in target database with a integer primary key.
# Run trigger for all table. Make sure Log table is in target database
# Run cache server with bi-directional and cache flag true. Cache all tables.
# Update some record in each table in target database. Check in csql node records are inserted or not . 
# Author := Bijaya

input=${PWD}/cache/Bidirectional/mysqlcreatelogtable.sql

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Bidirectional
fi

a=1
while [[ $a -lt 101 ]];do
    echo "create table t$a(f1 int,f2 int,primary key(f1));"
    echo "insert into t$a values(1,2);"
    echo "insert into t$a values(10,20);"
    echo "insert into t$a values(11,21);"
    (( a +=1 ))
done >>$REL_PATH/create100table.sql
echo "table creation file created"

a=1
while [[ $a -lt 101 ]];do
    echo "echo select * from t$a;"
    echo "select * from t$a;"
    (( a +=1 ))
done >>$REL_PATH/selectfrom100.sql
echo "select file created"

a=1
while [[ $a -lt 101 ]];do
    echo "drop table t$a;"
    (( a +=1 ))
done >>$REL_PATH/drop100table.sql

a=1
while [[ $a -lt 101 ]];do
   echo "update t$a set f2=50 where f2 >19;"
   (( a +=1 ))
done >> $REL_PATH/update100table.sql
echo "Update file created"
rm  -f /tmp/csql1.conf
cp $REL_PATH/csql1.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql1.conf
rm -f /tmp/csql1/csqlds.conf
touch /tmp/csql1/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
DS="$DSN $DBUSER $PASSWORD"
echo DSN=$DSN >>$CSQL_CONFIG_FILE
if [ $DSN = "myodbc3" ]
then
    LOG_FILE=$REL_PATH/mysqlcreatelogtable.sql
    echo "use test;">>$REL_PATH/updatetrigger100.sql
    a=1
    while [[ $a -lt 101 ]];do
        echo "drop trigger if exists triggerupdatet$a;"
        echo "create trigger triggerupdatet$a AFTER UPDATE on t$a FOR EACH ROW BEGIN Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t$a', OLD.f1, 2,1);Insert into csql_log_int (tablename, pkid, operation,cacheid) values ('t$a', NEW.f1, 1,1); End;"
        (( a +=1 ))
    done >> $REL_PATH/updatetrigger100.sql
    echo "Trigger file generated"
       a=1
    while [[ $a -lt 101 ]];do
       echo "drop trigger if exists triggerupdatet$a;"
       (( a +=1 ))
    done >>$REL_PATH/dropupdatetrigger.sql
    echo "Drop trigger file generated"
elif [ $DSN = "psql" ]
then
   a=1
   while [[ $a -lt 101 ]];do
       echo "DROP FUNCTION IF EXISTS log_update_t$a() CASCADE ;"
       echo "CREATE OR REPLACE FUNCTION log_update_t$a() RETURNS trigger AS \$triggerupdatet$a$ BEGIN insert into csql_log_int (tablename, pkid, operation, cacheid) values ('t$a', OLD.f1, 2, 1); insert into csql_log_int (tablename, pkid, operation, cacheid) values ('t$a', NEW.f1, 1, 1); RETURN NEW; END; \$triggerupdatet$a$ LANGUAGE plpgsql;"
       echo "create trigger triggerupdatet$a AFTER UPDATE on t$a FOR EACH ROW EXECUTE PROCEDURE log_update_t$a();"
       (( a +=1 ))
   done >> $REL_PATH/updatetrigger100.sql
   echo "Trigger file generated"

   a=1
   while [[ $a -lt 101 ]];do
       echo "DROP FUNCTION IF EXISTS log_update_t$a() CASCADE ;"
       (( a +=1 ))
   done >>$REL_PATH/dropupdatetrigger.sql
   echo "Drop trigger file generated"

   LOG_FILE=$REL_PATH/psqlcreatelogtable.sql
elif [ $DSN = "oracle" ]
then
   a=1
   while [[ $a -lt 101 ]];do
       echo "CREATE OR REPLACE TRIGGER triggert$a AFTER  update on t$a FOR EACH ROW declare  rid PLS_INTEGER; begin  SELECT CSQL_ID.NEXTVAL INTO rid  FROM dual;  if updating then insert into csql_log_int values ('t$a',:old.f1,2,1,rid); SELECT CSQL_ID.NEXTVAL INTO rid  FROM dual; insert into csql_log_int values ('t$a',:new.f1,1,1,rid); end if; end;"
       (( a +=1 ))
   done >> $REL_PATH/updatetrigger100.sql
   echo "Trigger file generated"
   a=1
   while [[ $a -lt 101 ]];do
       echo "DROP TRIGGER triggert$a;"
       (( a +=1 ))
   done >>$REL_PATH/dropupdatetrigger.sql
   echo "Drop trigger file generated"

   LOG_FILE=$REL_PATH/oraclecreatelogtable.sql
   echo TARGET_DATABASE=oracle >>$CSQL_CONFIG_FILE
elif [ $DSN = "sybase" ]
then
    echo "Sybase trigger Missinf"
else
    echo "other triger"
fi
#echo $DS
isql $DS < $LOG_FILE >/dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "DSN is not set for target db"
    rm -f $REL_PATH/create100table.sql
    rm -f $REL_PATH/update100table.sql
    rm -f $REL_PATH/selectfrom100.sql
    rm -f $REL_PATH/drop100table.sql
    rm -f $REL_PATH/dropupdatetrigger.sql
    rm -f $REL_PATH/updatetrigger100.sql
    exit 1
fi
echo Log table created in target DB
isql $DS < $REL_PATH/create100table.sql >/dev/null
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS <$REL_PATH/updatetrigger100.sql >/dev/null

a=1
while [[ $a -lt 101 ]];do
    echo "1 t$a NULL NULL NULL $DSN"
    (( a +=1 ))
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 30
echo "server  started"

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectfrom100.sql
if [ $? -ne 0 ]
then
    echo "unable to locate cache 1"
    isql $DS < ${REL_PATH}/drop100table.sql >/dev/null 2>&1
    rm -f $REL_PATH/create100table.sql
    rm -f $REL_PATH/update100table.sql
    rm -f $REL_PATH/selectfrom100.sql
    rm -f $REL_PATH/drop100table.sql
    rm -f $REL_PATH/dropupdatetrigger.sql
    rm -f $REL_PATH/updatetrigger100.sql
    exit 2 
fi

echo "Update some record in target database"
isql $DS < ${REL_PATH}/update100table.sql >/dev/null 2>&1 
sleep 30
echo "Records in csql after update in target DB"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectfrom100.sql

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop100table.sql > /dev/null 2>&1
isql $DS < ${REL_PATH}/drop100table.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
isql $DS < $REL_PATH/dropupdatetrigger.sql >/dev/null 2>&1
isql $DS < $REL_PATH/mysqldeletelogtable.sql >/dev/null 2>&1
kill `ps -ef | grep csqlcacheserver | awk -F" " '{ print $2 }'`
kill -9 $pid
ipcrm -M 4000 -M 4500

rm -f $REL_PATH/create100table.sql
rm -f $REL_PATH/update100table.sql
rm -f $REL_PATH/selectfrom100.sql
rm -f $REL_PATH/drop100table.sql
rm -f $REL_PATH/updatetrigger100.sql
rm -f $REL_PATH/dropupdatetrigger.sql
exit 0;
