#!/bin/ksh

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
input=${PWD}/tools/csqldump/inputtest004.sql
REL_PATH=.
if [ -s "$input" ]
then
    REL_PATH=${PWD}/tools/csqldump
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/inputtest004.sql 2> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/inputtest004.sql > /dev/null 2>&1
    if [ $? -ne 0 ]
    then 
        exit 1;
    fi
fi

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csqldump -n 30 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/csqldump -n 30 
    if [ $? -ne 0 ]
    then
        exit 2;
    fi
fi

cnt=`$CSQL_INSTALL_ROOT/bin/csqldump | grep VALUES | wc -l`
if [ $? -ne 0 -a $cnt -ne 99 ]
then
    exit 3;
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s $REL_PATH/drop.sql > /dev/null 2>&1
if [ $? -ne 0 ]
then
    exit 4;
fi

exit 0;
