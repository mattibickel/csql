#!/bin/ksh
# Test Case

# Create table t1 and t2 in mysql and insert 10 records each.
# Run $ cachetable -R
# Both the tables should be cached into csql with all the records intact.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
dropAll() {
rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf
#cp $CSQL_CONFIG_FILE /tmp/csql.conf
#echo DSN=$DSN >>$CSQL_CONFIG_FILE
isql $DS < ${REL_PATH}/dropall.sql >/dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropall.sql > /dev/null 2>&1
#cp /tmp/csql.conf $CSQL_CONFIG_FILE
}


input=${PWD}/cache/CacheTable/create.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/cache/CacheTable
fi

cp $CSQL_CONFIG_FILE /tmp/csql.conf
echo CACHE_TABLE=true >>$CSQL_CONFIG_FILE
echo DSN=$DSN >>$CSQL_CONFIG_FILE
DS="$DSN $DBUSER $PASSWORD"
rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf
$CSQL_INSTALL_ROOT/bin/csqlds -U $DBUSER -P $PASSWORD -D $DSN -N $TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi

isql $DS < ${REL_PATH}/create.sql >/dev/null 2>&1
echo table t1 and t2 are created with records in target db

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

# write to the file
echo "1 t1 NULL NULL NULL $DSN" > /tmp/csql/csqltable.conf
echo "2 t2 NULL t2f1<5 NULL $DSN" >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/cachetable -R 
if [ $? -ne 0 ]
then
    dropAll
cp /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/selectstar.sql
dropAll
cp /tmp/csql.conf $CSQL_CONFIG_FILE
exit 0;

