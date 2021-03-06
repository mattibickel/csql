#!/bin/ksh
# Testing Relational Operators(,<,>,<,>=,!=) with varchar in Delete statement. ( )
# CREATE TABLE t1 (f1 INT , f2 VARCHAR (12));
# INSERT INTO t1 VALUES(1, 'ABCDE');
# INSERT INTO t1 VALUES(2, 'ABCDF');
# INSERT INTO t1 VALUES(3, 'ABCDG');
# INSERT INTO t1 VALUES(4, 'ABCDH');
# INSERT INTO t1 VALUES(5, 'ABCDI');
# INSERT INTO t1 VALUES(6, 'NBCDE');
# INSERT INTO t1 VALUES(7, 'NBCDF');
# INSERT INTO t1 VALUES(8, 'NBCDG');
# INSERT INTO t1 VALUES(9, 'NBCDH');
# INSERT INTO t1 VALUES(10, 'NBCDI');
# Test the below Update statements return proper result set or not.
# select * from t1;
# delete from t1 where f2='NBCDI';
# delete from t1 where f2>'NBCDG';
# delete from t1 where f2>='NBCDF';
# delete from t1 where f2<'ABCDF';
# delete from t1 where f2<='ABCDH';
# delete from t1 where f2!='NBCDE';
#
CREATEFILE=${PWD}/sql/Predicate/csql.conf
REL_PATH=.
if [ -s "$CREATEFILE" ]
then
    REL_PATH=`pwd`/sql/Predicate
fi

echo "drop table t1;" >${REL_PATH}/dropt1.sql

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql >/dev/null 2>&1

if [ "$VALGRIND" = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_relational_del.sql
else 
    $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/varchar_relational_del.sql 
    if [ $? -ne 0 ]
    then
       $CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
       rm -f ${REL_PATH}/dropt1.sql
       exit 1;
    fi
fi

$CSQL_INSTALL_ROOT/bin/csql -s ${REL_PATH}/dropt1.sql
if [ $? -ne 0 ]
then
   exit 2;
fi

rm -f ${REL_PATH}/dropt1.sql
exit 0;
