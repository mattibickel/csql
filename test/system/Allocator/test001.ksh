#!/bin/ksh
# TestCase:
# create table with two fields and index on first field
# insert 1 tuple
# check number of tuples, totalPagesused
# check pagesUsed for storing hash bucket
# check number of index nodes, pagesUsed for storing index nodes
# delete 1 tuple
# check number of tuples, totalPagesused
# check pagesUsed for storing hash bucket
# check number of index nodes, pagesUsed for storing index nodes

# Note: spaceused for table = noOfDataNodes * sizeofTuple + noOfPages * sizeofPageInfo
#Note:Thats why we see spaceused as 16 even when no tuple exist

#Run this test only under csql/test or on this directory.
#Otherwise, it may fail
EXECUTABLE=${PWD}/system/Allocator/create
REL_PATH=.
if [ -s "$EXECUTABLE" ]
then
    REL_PATH=${PWD}/system/Allocator
fi

if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/create 2> $0.valgr
else
    ${REL_PATH}/create
    if [ $? -ne 0 ]
    then
       exit 100;
    fi
fi

echo "Tables and Indexes are created"
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/insert1 2>> $0.valgr
else
    ${REL_PATH}/insert1
    if [ $? -ne 1 ]
    then
       exit 100;
    fi
fi
echo "Tuples inserted into table"
echo "Case 1: -T option for t1: with 1 tuple"
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -T t1 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -T t1
    if [ $? -ne 0 ]
    then
       exit 1;
    fi
fi
echo "Case 2: -I option for idx1 of t1, with 1 tuple"
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -I t1idx1 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -I t1idx1
    if [ $? -ne 0 ]
    then
       exit 2;
    fi
fi

if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full ${REL_PATH}/delete1 2>> $0.valgr
else
    ${REL_PATH}/delete1
    if [ $? -ne 1 ]
    then
        exit 100;
    fi
fi

echo "Tuples deleted from table"
echo "Case 3: -T option for t1: after removing 1 tuple"
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -T t1 2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -T t1
    if [ $? -ne 0 ]
    then
       exit 3;
    fi
fi

echo "Case 4: -I option for idx1 of t1, after removing 1 tuple"
if [ $VALGRIND = "true" ]
then
    valgrind --tool=memcheck --leak-check=full $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -I t1idx1  2>> $0.valgr
else
    $CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -I t1idx1
    if [ $? -ne 0 ]
    then
       exit 4;
    fi
fi

${REL_PATH}/drop
if [ $? -ne 0 ]
then
   exit 100;
fi
echo "Tables and Indexes are dropped"

exit 0
