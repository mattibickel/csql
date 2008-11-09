#!/bin/sh
#Test Case
#5.	Create table t1 with 5 records in csql database.
#	select query with count,sum,avg,min,max.and Group By.

#	Author : Jitendra Lenka

QUITFILE=${PWD}/sql/Aggregate/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
  REL_PATH=`pwd`/sql/Aggregate
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/createt1t2.sql > /dev/null 2>&1
if [ $? -ne 0 ]
 then
   exit 1;
fi

echo "select max(t1.f1), sum(t2.f1) from t1, t2 where t1.f1 = t2.f1 and t1.f1 <100 group by t1.f1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/groupby1.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
     exit 2;
fi 

echo "select max(t1.f1), sum(t2.f1) from t1, t2 where t1.f1 = t2.f1 and t1.f1 <100 group by t1.f1, t2.f1 :"
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/groupby2.sql 
if [ $? -ne 0 ]
  then
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
    exit 3;
fi  

      

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
exit 0;
