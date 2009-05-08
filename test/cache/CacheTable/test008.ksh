#!/bin/sh
# Test Case

# 8.load table. csqldump , 
#   unload table csqldump, insert record to mysql directly, 
#   reload table, csqldump and verify the results. 
#   reload should get the inserted record also.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail

dropAll() {
#cp $CSQL_CONFIG_FILE /tmp/csql.conf
#echo DSN=$DSN >>$CSQL_CONFIG_FILE
isql $DSN < ${REL_PATH}/drop.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
#cp /tmp/csql.conf $CSQL_CONFIG_FILE
}
input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo DSN=$DSN >>$CSQL_CONFIG_FILE
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
isql $DSN < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 > /dev/null 2>&1
if [ $? -ne 0 ]
then
   dropAll
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 1;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csqldump 

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
echo "1:t1" > /tmp/csql/csqltable.conf
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -u > /dev/null 2>&1
if [ $? -ne 0 ]
then
   dropAll
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 2;
fi

$CSQL_INSTALL_ROOT/bin/csqldump 

isql $DSN < ${REL_PATH}/insert.sql >/dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/cachetable -t t1 > /dev/null 2>&1
if [ $? -ne 0 ]
then
   dropAll
   cp /tmp/csql.conf $CSQL_CONFIG_FILE
   exit 3;
fi

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csqldump 

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
dropAll

cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

