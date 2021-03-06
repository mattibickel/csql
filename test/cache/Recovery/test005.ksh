#!/bin/ksh

#  Table recovery with composite index.
#  Start TDB and create table in TDB t1 (f1 int,f2 int,f3 int,f4 char(10),i
#    primary key(f1,f2)), Add entry for t1 table in csqltable.conf file.
#  Recover with csqlserver -c option. 
#  Verify that it recovers the table with both the index information i
#    and all the records using csqldump tool 

CSQL_CONF=${PWD}/cache/Recovery/csql.conf
input=${PWD}/cache/Recovery/createt1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Recovery
fi
rm -f /tmp/csql.conf
if [ $DSN = "db2" ]
then
    echo "create table t1(f1 int not null, f2 int not null,f3 int,f4 char(10),primary key(f1,f2));">$REL_PATH/t1.sql
else
    echo "create table t1(f1 int , f2 int,f3 int,f4 char(10),primary key(f1,f2));">$REL_PATH/t1.sql
fi
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   rm -f $REL_PATH/t1.sql
   exit 1;
fi

isql $DS < $REL_PATH/t1.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    rm -f $REL_PATH/t1.sql
    exit 2;
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
echo "1 t1 NULL NULL NULL $DSN" >> /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 5

rm -f /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf
touch /tmp/csql/csqltable.conf /tmp/csql/csqlds.conf

$CSQL_INSTALL_ROOT/bin/csqldump 
if [ $? -ne 0 ]
then
    rm -f $REL_PATH/t1.sql
    exit 5;
fi

kill -9 $pid > /dev/null 2>&1
echo "drop table t1;">>$REL_PATH/drt1.sql
isql $DSN < $REL_PATH/drt1.sql > /dev/null 2>&1
rm -f $REL_PATH/t1.sql
rm -f $REL_PATH/drt1.sql
ipcrm -M 1199 -M 2277
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
exit 0;

