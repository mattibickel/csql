#include<CSql.h>
int main()
{
    Connection conn;
    DbRetVal rv = OK;
    //check whether connection open fails for non existing user
    rv = conn.open("user1", "passwd");
    if (rv == OK) return 1;

    printf("connection open failed \n");

    //open with dba to create new user
    rv = conn.open("root", "manager");
    if (rv != OK) return 2;
    UserManager *uMgr = conn.getUserManager();
    uMgr->createUser("user1", "passwd");
    rv = conn.close();
    if (rv != OK) return 3;
    printf("New user created \n");
    //check whether the newly created user name works
    rv = conn.open("user1", "passwd");
    if (rv != OK) return 4;
    rv = conn.close();
    if (rv != OK) return 5;
    printf("New user login worked \n");

    //check whether the newly created user name fails if 
    //wrong password is passed
    rv = conn.open("user1", "wrongpasswd");
    if (rv == OK) return 6;

    //open with dba to delete the newly created user
    rv = conn.open("root", "manager");
    if (rv != OK) return 7;
    uMgr = conn.getUserManager();
    uMgr->deleteUser("user1");
    rv = conn.close();
    if (rv != OK) return 8;
    printf("New user deleted \n");

    //check whether it is deleted by connecting with that user
    //name and password. It should fail
    rv = conn.open("user1", "passwd");
    if (rv == OK) return 9;

    return 0;
}
