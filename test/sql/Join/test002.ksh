#!/bin/ksh
# Test Case 
# 4.	Create t1 and t2 table with 5 records each.
# 	select t1.f1, t2.f1, t1.f2, t2.f2 from t1,t2
#	select * from t1,t2 where t1.f1 = t2.f1 and t1.f1 >100

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi


$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join2.sql  
if [ $? -ne 0 ]
then 
  $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
  exit 2;
fi
  

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
  exit 0;

