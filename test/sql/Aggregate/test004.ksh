#!/bin/ksh
#Test Case
# create table t1(f1 int,f2 int,f3 int,primary key(f1));
# create table t2(f1 int,f2 int,f3 int,primary key(f1));
# Insert 5 records in each.
# Test all aggregate functions applying conditions
# Test all aggregate functions applying conditions and group by.
# 
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

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/aggregate4.sql 
if [ $? -ne 0 ]
  then
     $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
     exit 2;
fi 
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1t2.sql > /dev/null 2>&1
exit 0;

