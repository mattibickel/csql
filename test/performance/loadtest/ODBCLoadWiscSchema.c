
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sql.h>
#include <sqlext.h>
#include "NanoTimer.h"
//#define START 70000001 
//#define END 1010000000
using namespace std;

int START=0;
int END=0;

NanoTimer timer;

void extract_error(
    char *fn,
    SQLHANDLE handle,
    SQLSMALLINT type)
{
    SQLINTEGER	 i = 0;
    SQLINTEGER	 native;
    SQLCHAR	 state[ 7 ];
    SQLCHAR	 text[256];
    SQLSMALLINT	 len;
    SQLRETURN	 ret;

    fprintf(stderr,
            "\n"
            "The driver reported the following diagnostics whilst running "
            "%s\n\n",
            fn);

    do
    {
        ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
                            sizeof(text), &len );
        if (SQL_SUCCEEDED(ret))
            printf("%s:%ld:%ld:%s\n", state, i, native, text);
    }
    while( ret == SQL_SUCCESS );
}

inline void
check_error (SQLSMALLINT handleType, SQLHANDLE handle, int rc, int line)
{
  if (rc)
    {
      cout << "Error " << rc << " at line: " << line << endl;
      SQLCHAR state[10];
      SQLINTEGER native;
      SQLCHAR mesg[300];
      int i=0;
      while (SQLGetDiagRec (handleType, handle, i++, state, &native, mesg, 300,
			    NULL) == SQL_SUCCESS)
	{
	  mesg[299] = '\0';
	  cout << "state: " << state << endl;
	  cout << "native: " << native << endl;
	  cout << "mesg: " << mesg << endl;
	}
      exit (1);
    }
}


inline void
checkrc (int rc, int line)
{
  if (rc)
    {
      cout << "Error " << rc << " at line: " << line << endl;
      exit (1);
    }
}

void
readWriteTrans (SQLHDBC hdbc)
{
  int rc = SQLSetConnectAttr (hdbc, SQL_ATTR_ACCESS_MODE,
			      (SQLPOINTER) SQL_MODE_READ_WRITE, 0);
  checkrc (rc, __LINE__);
  rc = SQLEndTran (SQL_HANDLE_DBC, hdbc, SQL_COMMIT);
  checkrc (rc, __LINE__);
}

void
readOnlyTrans (SQLHDBC hdbc)
{
  int rc = SQLSetConnectAttr (hdbc, SQL_ATTR_ACCESS_MODE,
			      (SQLPOINTER) SQL_MODE_READ_ONLY, 0);
  checkrc (rc, __LINE__);
  rc = SQLEndTran (SQL_HANDLE_DBC, hdbc, SQL_COMMIT);
  checkrc (rc, __LINE__);
}

int
runInsertTest (SQLHANDLE henv, SQLHANDLE hdbc, SQLHANDLE hstmt)
{
  int rc;
  int iHolder;
  char sHolder[200];
  char sData[200];
  iHolder = 0;
  strcpy (sData, "0123456789012345678901234567890123456789");
  rc = SQLPrepare (hstmt, (unsigned char *) "insert into t1 values(?,12,13,14,15,16,17,18,19,20,21,100,100,'AXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXX','GXXXXXXXXXXXXXXXXXXXXXXXXXCXXXXXXXXXXXXXXXXXXXXXXXXA','OXXXXXXXXXXXXXXXXXXXXXXXXXOXXXXXXXXXXXXXXXXXXXXXXXXO')",SQL_NTS);
  checkrc (rc, __LINE__);
  rc = SQLBindParameter (hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER,
			 0, 0, &iHolder, 0, NULL);
  checkrc (rc, __LINE__);
  SQLINTEGER sLen = SQL_NTS;
/*  rc = SQLBindParameter (hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR,
			 196, 0, (void *) sHolder, 0, &sLen);*/
  checkrc (rc, __LINE__);
  int i, j, k;
  int tCount=0;


  /* Run 1per Test */
  int commit=0;
  for (i = START; i <= END; i++)
    {
	  iHolder = i ;
	  strcpy (sHolder, sData);
	  rc = SQLExecute (hstmt);
	  checkrc (rc, __LINE__);
	  if(commit==1000){
	     rc = SQLTransact (henv, hdbc, SQL_COMMIT);
	     checkrc (rc, __LINE__);
		 commit=0;
	  }else {commit++;}
	  tCount++;
    }
  printf("Total Record Inserted %d\n",tCount);
  return 0;

}

int
main (int ac, char **av)
{
  int rc;
  char *dsn;
  START = atoi(getenv("START"));
  END = atoi(getenv("END"));
  SQLHENV henv;
  SQLHDBC hdbc;
  SQLHSTMT hstmt;
  bool ddl=false;
  if (ac ==2) ddl = true;

  dsn = (char *) "DSN=myodbc3;";

  rc = SQLAllocHandle (SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
  checkrc (rc, __LINE__);
  SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);

  rc = SQLAllocHandle (SQL_HANDLE_DBC, henv, &hdbc);
  checkrc (rc, __LINE__);
  rc = SQLConnect (hdbc,
		   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
		   (SQLCHAR *) "root",
		   (SQLSMALLINT) strlen ("root"),
		   (SQLCHAR *) "manager",
		   (SQLSMALLINT) strlen ("manager"));
 
  SQLCHAR outstr[1024];
  SQLSMALLINT outstrlen;
/*  rc = SQLDriverConnect(hdbc, NULL, (SQLCHAR*)"DSN=myodbc3;UID=root;PWD=root123;", SQL_NTS, outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_NOPROMPT);
*/
  if (SQL_SUCCEEDED(rc)) {
    printf("Connected\n");
    //printf("Returned connection string was:\n\t%s\n", outstr);
    if (rc == SQL_SUCCESS_WITH_INFO) {
      printf("Driver reported the following diagnostics\n");
      extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
    }
  } else {
    fprintf(stderr, "Failed to connect\n");
    extract_error("SQLDriverConnect", hdbc, SQL_HANDLE_DBC);
  }

  //check_error (SQL_HANDLE_DBC, hdbc, rc, __LINE__);
  checkrc (rc, __LINE__);
  rc = SQLSetConnectOption (hdbc, SQL_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF);
  checkrc (rc, __LINE__);
  rc = SQLAllocHandle (SQL_HANDLE_STMT, hdbc, &hstmt);
  checkrc (rc, __LINE__);
  if(ddl){
  rc = SQLExecDirect(hstmt, (SQLCHAR*) "CREATE TABLE t1 (f1 INT  NOT NULL , f2 INT  NOT NULL , f3 INT  NOT NULL , four INT  NOT NULL , ten INT  NOT NULL , twenty INT  NOT NULL , onepercent INT  NOT NULL , tenpercent INT  NOT NULL , twentypercent INT  NOT NULL , fiftypercent INT  NOT NULL , unique3 INT  NOT NULL , evenonepercent INT  NOT NULL , oddonepercent INT  NOT NULL , stringu1 CHAR (52) NOT NULL , stringu2 CHAR (52) NOT NULL , string4 CHAR (52) NOT NULL );", SQL_NTS );
  checkrc (rc, __LINE__);
  rc = SQLExecDirect(hstmt, (SQLCHAR*)"create index idx1 on t1(f1) tree unique;"
,SQL_NTS );
  checkrc (rc, __LINE__);
}
      runInsertTest (henv, hdbc, hstmt);
 /*
  rc = SQLExecDirect(hstmt, (SQLCHAR*) "DROP TABLE t1;", SQL_NTS );
  checkrc (rc, __LINE__);
  rc = SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_COMMIT );
  checkrc (rc, __LINE__);
*/
  rc = SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
  checkrc (rc, __LINE__);
  rc = SQLDisconnect (hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_DBC, hdbc);
  checkrc (rc, __LINE__);
  rc = SQLFreeHandle (SQL_HANDLE_ENV, henv);
  checkrc (rc, __LINE__);
  exit (0);
}
