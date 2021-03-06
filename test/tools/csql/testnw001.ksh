#!/bin/ksh
# Test Case
# check no option, ? 
# check whether authentication is working
#
QUITFILE=${PWD}/tools/csql/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
    REL_PATH=`pwd`/tools/csql
fi
echo "Case 1: With no option:"
$CSQL_INSTALL_ROOT/bin/csql < ${REL_PATH}/quit.sql
if [ $? -ne 0 ]
then
   exit 1;
fi
echo "Case 2: With ? option:"
$CSQL_INSTALL_ROOT/bin/csql -? 
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "Case 3: With wrong username and wrong password :" 
$CSQL_INSTALL_ROOT/bin/csql -o 4 -u wronguser -p password < ${REL_PATH}/quit.sql >/dev/null 2>&1
if [ $? -eq 0 ]
then
   echo passed
   exit 3;
fi
echo failed

echo "Case 4: With wrong username :" 
$CSQL_INSTALL_ROOT/bin/csql -o 4 -u wronguser -p manager < ${REL_PATH}/quit.sql >/dev/null 2>&1
if [ $? -eq 0 ]
then
   echo Passed 
   exit 4;
fi
echo Failed

echo "Case 5: With wrong password :" 
$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p password < ${REL_PATH}/quit.sql >/dev/null 2>&1
if [ $? -eq 0 ]
then
   echo passed
   exit 5;
fi
echo failed

echo "Case 6: With correct user name  and password :"
$CSQL_INSTALL_ROOT/bin/csql -o 4 -u root -p manager < ${REL_PATH}/quit.sql
if [ $? -ne 0 ]
then
   echo failed 
   exit 6;
fi
echo passed
exit 0;
