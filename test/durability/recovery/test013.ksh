#!/bin/ksh
# set DURABILITY = true in csql.conf
# Start csqlserver. 
# Then create a table t1 in CSQL Client.
# create the same table t1 again.
# kill the currently running Server. 
# Restart the server.
# csqldump should dump the database with table and index information
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
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2

echo "CREATE TABLE laks(f1 int);" >${REL_PATH}/create.sql
echo "DROP TABLE laks;" >${REL_PATH}/drop.sql

echo "CREATE TABLE laks(f1 int);"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
     then
       kill -9 $pid
       ipcrm -M 4444 -M 6666
       rm -f ${REL_PATH}/create.sql
       rm -f ${REL_PATH}/drop.sql
     exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create.sql >/dev/null 2>&1
    if [ $? -ne 0 ]
     then
       kill -9 $pid
       ipcrm -M 4444 -M 6666
       rm -f ${REL_PATH}/create.sql
       rm -f ${REL_PATH}/drop.sql
     exit 2;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump >before.sql
fi

kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"
echo ""
echo DURABILITY=true >>/tmp/csql.conf
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
if [ $? -ne 0 ]
 then
   echo "Server could not be Started"
   rm -rf /tmp/csql/db
   mkdir -p /tmp/csql/db
   kill -9 $pid
   ipcrm -M 4444 -M 6666
   rm -f ${REL_PATH}/create.sql
   rm -f ${REL_PATH}/drop.sql
 exit 3;
fi
pid=$!
echo "Server Started"
sleep 2
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump >after.sql
fi

echo ""
diff before.sql after.sql >/dev/null 2>&1
if [ $? -eq 0 ]
    then
        echo Durability Works Fine
fi

rm -f ${REL_PATH}/create.sql
rm -f ${REL_PATH}/drop.sql
rm -f before.sql after.sql
kill -9 $pid
ipcrm -M 4444 -M 6666
exit 0;
