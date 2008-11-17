#!/bin/sh
#This test requires kernel.shmmax to be 1GB, otherwise it may fail
#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Recovery/csql.conf
input=${PWD}/cache/Recovery/create.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Recovery
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf
cp $CSQL_CONFIG_FILE /tmp
echo DSN=$DSN >> $CSQL_CONFIG_FILE
isql $DSN < $REL_PATH/create.sql > /dev/null 2>&1

if [ $? -ne 0 ]
then
    mv /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 1;
fi
# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
for (( a=1; a<101; a++ ))
do
    echo "1:t$a NULL NULL NULL"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 60
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csqldump 
if [ $? -ne 0 ]
then
    mv /tmp/csql.conf $CSQL_CONFIG_FILE
    exit 5;
fi

kill $pid > /dev/null 2>&1
ipcrm -M 1199 
ipcrm -M 2277
isql $DSN < $REL_PATH/dropall.sql > /dev/null 2>&1
mv /tmp/csql.conf $CSQL_CONFIG_FILE
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
exit 0;
