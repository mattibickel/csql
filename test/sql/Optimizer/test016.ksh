#!/bin/ksh
# Composite hash index on mixed datatypes and testing explain plan
# Create table with 6 fields (f1 smallint, f2 int, f3 bigint, f4 char, f5 date, f6 timestamp).
# create composite hash indexes in different combinations.
# Apply explain plan using select with multiple predicates(Hash lookup).
# Apply explain plan using select with multiple predicates(range lookup).
#
QUITFILE=${PWD}/sql/Optimizer/drop.sql
REL_PATH=.
if [ -s "$QUITFILE" ]
then
REL_PATH=`pwd`/sql/Optimizer
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/composite_mixdatatype.sql
else
    $CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/composite_mixdatatype.sql
    if [ $? -ne 0 ]
    then
      rm -f ${REL_PATH}/dropt1.sql
      exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s $REL_PATH/dropt1.sql 
rm -f ${REL_PATH}/dropt1.sql
exit 0;

