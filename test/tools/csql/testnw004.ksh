#!/bin/ksh
# Test Case
# Creating table with primary key constraint on the int field
# check basic SELECT with All types of Predicate
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager -s ${REL_PATH}/csql3.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
