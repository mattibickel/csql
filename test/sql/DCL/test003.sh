#!/bin/bash

#Test Case : Privileges can be granted and actions are allowed/denied accordingly

MY_PATH="$(dirname $0)"

TEST_USER="mbickel"
TEST_PW="test"

exitStatus()
{
    rm -f "${MY_PATH}/as_usr.sql" "${MY_PATH}/as_root.sql" "${MY_PATH}/cleanup.sql"
    echo "Test $1"
    exit $2;  
}

VALGRIND_RUN="valgrind --tool=memcheck --leak-check=full"
[ "$VALGRIND" = "true" ] || VALGRIND_RUN=""

echo "
create user ${TEST_USER} password '${TEST_PW}';
create table t (id integer);
grant select on t to ${TEST_USER};
insert into t values (1);
quit;" > "${MY_PATH}/as_root.sql"

echo "
insert into t values (2);
select * from t;
update t set id = 3 where id = 1;
delete from t where id = 3;
drop table t;
quit;" > "${MY_PATH}/as_usr.sql"

echo "
drop table t;
drop user ${TEST_USER};
quit;" > "${MY_PATH}/cleanup.sql"

${VALGRIND_RUN} ${CSQL_INSTALL_ROOT}/bin/csql -u root -p manager -s "${MY_PATH}/as_root.sql"
[[ $? -ne 0 ]] && exitStatus "Failed" 1

${VALGRIND_RUN} ${CSQL_INSTALL_ROOT}/bin/csql -u "${TEST_USER}" -p "${TEST_PW}" -s "${MY_PATH}/as_usr.sql"
[[ $? -ne 0 ]] && exitStatus "Failed" 2

${VALGRIND_RUN} ${CSQL_INSTALL_ROOT}/bin/csql -u root -p manager -s "${MY_PATH}/cleanup.sql"
[[ $? -ne 0 ]] && exitStatus "Failed" 3

exitStatus Passed 0;
