#!/bin/sh

#  11.Table there in csql and mysql and not cached. select should return records in csql table.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Gateway/csql.conf
input=${PWD}/cache/Gateway/mysqlinputtest1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Gateway
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

isql myodbc3 < $REL_PATH/mysqlinputtest1.sql > /dev/null 2>&1
isql myodbc3 < $REL_PATH/selectstar.sql
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/csqlinputtest10.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/selectstar.sql
isql myodbc3 < $REL_PATH/dropall.sql > /dev/null 2>&1
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
kill -9 $pid 
ipcrm -M 1199 -M 2277
exit 0;