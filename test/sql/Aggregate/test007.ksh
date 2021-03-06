#!/bin/ksh
#Test Case
# Create table t1 with 5 records in csql database.
# Test "select count(*),min(f1),sum(f1) from t1"

#	Author : Jitendra Lenka

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
  REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1.sql > /dev/null 2>&1
if [ $? -ne 0 ]
 then
   exit 1;
fi


echo "select count(*),min(f1),sum(f1) from t1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/agg1.sql 
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
    exit 2;
fi  

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql > /dev/null 2>&1
exit 0 ;

