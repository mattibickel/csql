#!/bin/sh
#Test Case

#18. load t1 table with records in target DB,
#    create a t1 table in CSQL without record. 
#    load with -s option, it should pass.

#   AUTHOR : Jitendra Lenka

input=${PWD}/cache/CacheTable/inputtest4.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

isql myodbc3 < ${REL_PATH}/inputtest4.sql >/dev/null 2>&1

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/csqlinput.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    exit 2;
fi
  
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

# caching with -s option
$CSQL_INSTALL_ROOT/bin/cachetable -t t1 -s >/dev/null 2>&1
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 3;
fi

echo "select * from t1;"
$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/selectt1.sql 
if [ $? -ne 0 ]
then
    rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
    touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
    isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
    exit 4;
fi
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db


$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/drop.sql > /dev/null 2>&1
isql myodbc3 < ${REL_PATH}/drop.sql >/dev/null 2>&1
exit 0;
