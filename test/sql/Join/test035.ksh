#!/bin/ksh
#
QUITFILE=${PWD}/sql/Join/quit.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
 REL_PATH=`pwd`/sql/Join
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/noindex_t1_t2_t3.sql
if [ $? -ne 0 ]
then
  exit 1;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/hashon_t1f1_t2f1_t3f1.sql
if [ $? -ne 0 ]
then
  exit 2;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/insert_t1_t2_t3.sql
if [ $? -ne 0 ]
then
  exit 3;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/equijoin_t1_t2_t3.sql
if [ $? -ne 0 ]
then
  exit 4;
fi
$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/drop_t1_t2_t3.sql
if [ $? -ne 0 ]
then
  exit 5;
fi
