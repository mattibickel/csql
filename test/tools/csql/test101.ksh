#!/bin/sh
# Test Case
# Script to check all data type valid value.
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/csql101.sql 
if [ $? -ne 0 ]
then
   exit 1;
fi

