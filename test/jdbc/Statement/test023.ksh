#!/bin/ksh
TESTFILE=${PWD}/jdbc/Statement/AggPara.java
REL_PATH=.
if [ -s "$TESTFILE" ]
then
    REL_PATH=`pwd`/jdbc/Statement
fi
export CLASSPATH=$CLASSPATH:${REL_PATH}
java InnerJoinPara
if [ $? -ne 0 ]
then
   exit 1;
fi
exit 0;
