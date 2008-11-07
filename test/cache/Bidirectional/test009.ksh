#!/bin/sh
# Test Case

# Bi-directional mutiple cache node test
# Two Cache Node and t1 and t2 table to be cached
# Update in Target database

input=${PWD}/cache/Bidirectional/mysqlcreatelogtable.sql

REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/Bidirectional
fi

#cp $CSQL_CONFIG_FILE /tmp/csql.conf
#echo DSN=$DSN >>$CSQL_CONFIG_FILE
isql $DSN < $REL_PATH/mysqlcreatelogtable.sql >/dev/null 2>&1 &
echo table csql_log_int is created with records in target db

isql $DSN < $REL_PATH/create.sql >/dev/null 2>&1 
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
isql $DSN < $REL_PATH/trigger.sql >/dev/null
isql $DSN < $REL_PATH/trigger1.sql  >/dev/null


export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE

for (( a=1; a<3; a++ ))
do
    echo "1:t$a NULL NULL NULL"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 & 
pid=$!
sleep 5
echo "server 1 started"

echo "cache node 2"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql 
if [ $? -ne 0 ]
then
    echo "unable to locate cache 1"
  #  cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 3
fi
mkdir /tmp/csql1 >/dev/null 2>&1 
rm -f /tmp/csql1/csqltable.conf /tmp/csql1/csql.db
touch /tmp/csql1/csqltable.conf /tmp/csql1/csql.db

export CSQL_CONFIG_FILE=$REL_PATH/conf/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE

for (( a=1; a<3; a++ ))
do
    echo "1:t$a NULL NULL NULL"
done >> /tmp/csql1/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid1=$!
sleep 5
echo "server 2 started"

echo "cache node 1"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql
if [ $? -ne 0 ]
then
    kill -2 $pid
    ipcrm -M 4000 -M 4500
    echo "unable to locate cache 1"
 #   cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 4
fi
echo "update some record in target database"
isql $DSN < ${REL_PATH}/update.sql > /dev/null 2>&1 
sleep 15 
echo "cache node 1"
$CSQL_INSTALL_ROOT/bin/csql  -s $REL_PATH/select.sql

export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
echo "cache node 2"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/select.sql

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
rm -f /tmp/csql1/csqltable.conf /tmp/csql1/csql.db
touch /tmp/csql1/csqltable.conf /tmp/csql1/csql.db
isql $DSN < $REL_PATH/mysqldeletelogtable.sql >/dev/null 2>&1 
kill -2 $pid
ipcrm -M 4000 -M 4500
kill -2 $pid1
ipcrm -M 5000 -M 5500
#    cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

