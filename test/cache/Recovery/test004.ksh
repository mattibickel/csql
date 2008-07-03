#!/bin/sh

#  4. Create table t1(f1 int, f2 int, primary key (f1)); in mysql
#     insert into t1 values(1, 11);
#     Cache the table in CSQL.
#     Insert the same tuple in csql.
#     It should fail with unique key violation.

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
CSQL_CONF=${PWD}/cache/Recovery/csql.conf
input=${PWD}/cache/Recovery/createt1.sql
REL_PATH=.
if [ -s "$input" -a -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/cache/Recovery
fi
export CSQL_CONFIG_FILE=$REL_PATH/csql.conf

isql myodbc3 < $REL_PATH/createt1.sql > /dev/null 2>&1

if [ $? -ne 0 ]
then
    exit 1;
fi

# edit /tmp/csql/csqltable.conf
rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
for (( a=1; a<2; a++ ))
do
    echo "1:t$a"
done >> /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver -c >/dev/null 2>&1 &
pid=$!
sleep 5

$CSQL_INSTALL_ROOT/bin/csql -s insert.sql >/dev/null 2>&1 

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db

$CSQL_INSTALL_ROOT/bin/csqldump 

if [ $? -ne 0 ]
then
    exit 5;
fi

kill $pid > /dev/null 2>&1

isql myodbc3 < $REL_PATH/drop.sql > /dev/null 2>&1
$CSQL_INSTALL_ROOT/bin/csql -s drop.sql >/dev/null 2>&1 

rm -f /tmp/csql/csqltable.conf /tmp/csql/csql.db
touch /tmp/csql/csqltable.conf /tmp/csql/csql.db
exit 0;

