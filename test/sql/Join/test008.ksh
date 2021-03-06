#!/bin/ksh
# Test Case 
# Create t11 table with 5 fields & t12 table with 3 fields and insert 3 records in each. 
#(a)select * from t11,t12 where t11.f5=t12.f1;
#(b)select * from t11,t12 where t11.f5 > t12.f1;
#(c) select * from t11,t12 where t12.f1 <= t11.f5;
#(d)select * from t11,t12 where t12.f1 != t11.f5;
#(e)select * from t11,t12 where t12.f1 > 20;

# AUTHOR : Jitendra Lenka

QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

  
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/tablet11t12.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
  exit 1;
fi



 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/join8.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t12.sql > /dev/null 2>&1
     exit 2;
fi



$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt11t12.sql > /dev/null 2>&1
exit 0;

