#!/bin/ksh
# Composite Primary Key test
# Testing All the operation in CSQl ((After Each Operation Kill the server and Restart the server again for Another Operation)
# set DURABILITY to true in csql.conf
# Start csqlserver. Then create a table (Composite Primary Key on 3 fields) in CSQL Client.Insert 5 Records. 
# kill the currently running Server. 
# Again Restart the Server by setting DURABILITY=true and Open CSQL Client.
# Continue The same For All Operations in CSQL.
# All should work Fine
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
echo "DURABILITY=true" >>/tmp/csql.conf
export CSQL_CONFIG_FILE=/tmp/csql.conf

echo "Durablity = TRUE"
echo "Server Started"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
sleep 2
echo "CREATING TABLE"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_pri_10.sql 2> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/create_pri_10.sql
   if [ $? -ne 0 ]
    then
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 1;
   fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/show_t1.sql 2>> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/show_t1.sql
   if [ $? -ne 0 ]
    then
      $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 2;
   fi
fi

kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"

echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
echo "INSERTING INTO TABLE"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insert_10.sql 2>> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/insert_10.sql
   if [ $? -ne 0 ]
    then
      $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 3;
   fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_10.sql 2>> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_10.sql
   if [ $? -ne 0 ]
    then
      $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 4;
   fi
fi

kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"

echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
echo "UPDATING RECORDS IN TABLE"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/update_10.sql 2>> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/update_10.sql
   if [ $? -ne 0 ]
    then
      $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 5;
   fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_10.sql 2>> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_10.sql
   if [ $? -ne 0 ]
    then
      $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 6;
   fi
fi

kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"
echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
echo "DELETING RECORDS FROM TABLE"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/delete_10.sql 2>> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/delete_10.sql
   if [ $? -ne 0 ]
    then
      $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 7;
   fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_10.sql 2>> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/select_10.sql
   if [ $? -ne 0 ]
    then
      $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 8;
   fi
fi

kill -9 $pid
ipcrm -M 4444 -M 6666
echo "Server Killed"

echo "Durablity = TRUE"
echo "Checking Durability"
$CSQL_INSTALL_ROOT/bin/csqlserver >/dev/null 2>&1 &
pid=$!
echo "Server Started"
sleep 2
echo "DROPPING TABLE"
if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql 2>> $0.valgr
else
   $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop_10.sql
   if [ $? -ne 0 ]
    then
      kill -9 $pid
      ipcrm -M 4444 -M 6666
    exit 9;
   fi
fi

kill -9 $pid
ipcrm -M 4444 -M 6666
exit 0;
