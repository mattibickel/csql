#!/bin/sh
#Test case
#Create table with table name adding special character and field name with special character.
#It should fail for name other than alphanumeric and underscore .
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi

$CSQL_INSTALL_ROOT/bin/csql -u root -p manager -s ${REL_PATH}/dbobjname.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -i
if [ $? -ne 0 ]
then
   exit 1;
fi
