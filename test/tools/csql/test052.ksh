#!/bin/ksh
# Test Case
#  Create table (f1 int, f2 int, f3 int); 
#  Insert 5 tuples (1, 1, 1), (2, 2, 2), (1, 2, 3)
#  create index idx1 on t1(f1) tree unique; 
#  Should fail with unique key violation error.

QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/uniquetreeindontuples.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/uniquetreeindontuples.sql 
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
