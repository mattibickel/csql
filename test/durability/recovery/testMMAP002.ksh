#!/bin/ksh
# Testing Durability in MMAP architecture
# set DURABILITY=true and MMAP=true in csql.conf
# Start csqlserver. Then create a table using CSQL Client.
# kill the currently running Server. 
# Again Restart the Server by setting DURABILITY=true and Open CSQL Client.
# SHOW TABLES; Statement  should display the table.
#
CSQL_CONF=${PWD}/durability/recovery/csql.conf
REL_PATH=.
if [ -s "$CSQL_CONF" ]
then
    REL_PATH=${PWD}/durability/recovery
fi

rm -f /tmp/csql.conf
rm -f /tmp/csql/db/*
mkdir -p /tmp/csql/db
cp -f $REL_PATH/csql.conf /tmp
echo SYS_DB_KEY=4444 >>/tmp/csql.conf
echo USER_DB_KEY=6666 >>/tmp/csql.conf
echo DURABILITY=true >>/tmp/csql.conf
echo MMAP=true >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2

echo "CREATE TABLE laks(f1 int);" >${REL_PATH}/create.sql
echo "DROP TABLE laks;" >${REL_PATH}/drop.sql

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql
if [ $? -ne 0 ]
 then
   kill -9 $pid
   ipcrm -M 4444 
   rm -f ${REL_PATH}/create.sql
   rm -f ${REL_PATH}/drop.sql
 exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csqldump >before.sql

kill -9 $pid
ipcrm -M 4444 
echo "Server Killed"
echo ""
echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2

$CSQL_INSTALL_ROOT/bin/csqldump >after.sql
echo ""
diff before.sql after.sql

rm -f ${REL_PATH}/create.sql
rm -f ${REL_PATH}/drop.sql
rm -f before.sql after.sql
kill -9 $pid
ipcrm -M 4444 
exit 0;
