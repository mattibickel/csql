#!/bin/ksh
#Test case
#create table t1(f1 int not null,f2 int,f3 int,primary key(f1));
# create index idx1 on t1(f1) unique;
#It should be failed saying "Index on this field  already exists". 
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree15.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/tree15.sql
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump -T t1 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump -T t1
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/drop.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

exit 0;
