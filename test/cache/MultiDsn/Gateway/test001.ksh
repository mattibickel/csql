#!/bin/ksh

# 1.Make sure Default DSN is myodbc3(CACHE_TABLE=myodbc3)
#   DSN entries in csqlds.conf file for MySQL and Postgres.
#   Create table 't1'and 't2' in MySQL with all supported 
#   data types in it with 5 records.
#   Create table 'tt1' and 'tt2' in Postgres with all supported 
#   data type with 5 records.
#   cache 't1' from MySQL and 'tt1' from Postgres. 
#   Select records from 't1' and 'tt1' table using Gateway,
#   it should fetch the records from csql.
#   Select records from 't2' and 'tt2' using gateway, 
#   it should fetch the records from their respective TDB.

# Run thsi test only under csql/test or on this directory,
# Otherwise it may fail.

input=${PWD}/cache/MultiDsn/Gateway/mysqltable.sql
REL_PATH=.
if [ -s "$input" ]
then
  REL_PATH=${PWD}/cache/MultiDsn/Gateway
fi

rm -f /tmp/csql.conf
cp $REL_PATH/csql.conf /tmp
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo DSN=$MYSQL_DSN >>$CSQL_CONFIG_FILE

rm -f /tmp/csql/csqlds.conf
touch /tmp/csql/csqlds.conf

        ##########  csqlds.conf entries  #########

$CSQL_INSTALL_ROOT/bin/csqlds -U $MYSQL_USER -P $MYSQL_PASSWORD -D $MYSQL_DSN -N $MYSQL_TDB -a
if [ $? -ne 0 ]
then
   exit 1;
fi
echo "Entries made for $MYSQL_DSN  in csqlds.conf file."

$CSQL_INSTALL_ROOT/bin/csqlds -U $POSTGRES_USER -P $POSTGRES_PASSWORD -D $POSTGRES_DSN -N $POSTGRES_TDB -a
if [ $? -ne 0 ]
then
   exit 2;
fi
echo "Entries made for $POSTGRES_DSN in csqlds.conf file."

                 ##########  END  #########

#Drop the table both in Mysql and Postgres if exists
isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1


     ########## Table in MYSQL and POSTGRES #######

isql $DS1 < ${REL_PATH}/mysqltable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   exit 3;
fi
echo "Table 't1 and t2' is created in $MYSQL_DSN"

echo "SELECT records from $MYSQL_DSN"
isql $DS1 < ${REL_PATH}/mysqlselect.sql
if [ $? -ne 0 ]
then
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 4;
fi

isql $DS2 < ${REL_PATH}/psqltable.sql >/dev/null 2>&1
if [ $? -ne 0 ]
then
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 5;
fi
echo "Table 'tt1 and tt2' is created in $POSTGRES_DSN"

echo "SELECT records from $POSTGRES_DSN"
isql $DS2 < ${REL_PATH}/psqlselect.sql
if [ $? -ne 0 ]
then
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 6;
fi

                 ######### END #########


rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 5

            ######### Cache t1 and tt1 table ########## 


$CSQL_INSTALL_ROOT/bin/cachetable -t t1  >/dev/null 2>&1
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 7;
fi
echo "Table t1 is cached from $MYSQL_DSN."

$CSQL_INSTALL_ROOT/bin/cachetable -t tt1 -d $POSTGRES_DSN > /dev/null 2>&1
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 8;
fi
echo "Table 'tt1' is cached from $POSTGRES_DSN."

                 ######## END ########


        ####### Fetch cached tables and non-cache table ######

echo ""
echo "Select records using Gateway(csql -g)"
echo "select records from t1 and t2"
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/mysqlselect.sql
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 9;
fi

echo "select records from tt1 and tt2."
$CSQL_INSTALL_ROOT/bin/csql -g -s $REL_PATH/psqlselect.sql
if [ $? -ne 0 ]
then
   kill -9 $pid
   ipcrm -M 1199 -M 2277
   isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1
   exit 10;
fi

rm -f /tmp/csql/csqltable.conf
touch /tmp/csql/csqltable.conf

isql $DS1 < ${REL_PATH}/drop.sql >/dev/null 2>&1
isql $DS2 < ${REL_PATH}/drop.sql >/dev/null 2>&1


$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop.sql > /dev/null 2>&1
kill -9 $pid
ipcrm -M 1199 -M 2277
exit 0;

                     ######### END #########
