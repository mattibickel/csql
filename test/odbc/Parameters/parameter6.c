//  CREATE TABLE "T1" WITH 10 FIELDS.
//  INSERT SOME TUPLES IN IT. 
//  SELECT TUPLES WITH WHERE CLAUSE


#include<stdio.h>
#include<stdlib.h>
#include<sql.h>
#include<sqlext.h>
#include<string.h>
    
//*************************************************************************
// ERROR CHECK FUNCTION
inline void checkrc(int rc,int line)
{
   if(rc)
   {
       printf("ERROR %d at line %d\n",rc,line);
       exit(1);
       
    }
}

//*************************************************************************
// FUNCTION FOR INSERTING ROWS IN IT.
int  InsertTest(SQLHANDLE env,SQLHANDLE dbc,SQLHANDLE stmt)
{
         
      int ret;
      int f1=90; // f1 field
      short int f2=20;//f2 field
      char *f3;
      f3 =NULL; //(char*)malloc(50);
      float f4 = 2.5;
      float f5 = 10.50;
      int  f9 = 5;
      long long f10 = 15000;
      int result;

      SQLINTEGER slen = SQL_NULL_DATA;
      //***********************************
      // STRUCTURE FIOR DATE DATATYPE
      SQL_DATE_STRUCT date;
      char strDate[30];
      
      date.year=2008;
      date.month=03;
      date.day=18;
     // strcpy(strDate,"{d '2008-03-18'}");  
      //*******************************
      //  STRUCTURE FOR TIME DATATYPE.
      SQL_TIME_STRUCT time;
      time.hour = 5;
      time.minute = 22;
      time.second = 10;
      //*****************************
      // STRUCTURE FOR TIMESTAMP DATATYPE
      SQL_TIMESTAMP_STRUCT timestamp;
      timestamp.year = 2008;
      timestamp.month = 03;
      timestamp.day = 18;
      timestamp.hour = 5;
      timestamp.minute = 22;
      timestamp.second = 10;
      timestamp.fraction = 764576; 
     //******************************
      // PREPARE THE STATEMENT.
      ret = SQLPrepare(stmt,(unsigned char*)"INSERT INTO T1 VALUES(?,?,?,?,?,?,?,?,?,?)",SQL_NTS);
      checkrc(ret,__LINE__);

      // BIND PARAMETER FOR ALL THE FIELD

      ret = SQLBindParameter(stmt,1,SQL_PARAM_INPUT,SQL_C_SLONG,SQL_INTEGER,0,0,&f1,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,2,SQL_PARAM_INPUT,SQL_C_SSHORT,SQL_SMALLINT,0,0,&f2,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,3,SQL_PARAM_INPUT,SQL_C_CHAR,SQL_CHAR,196,0,(void*)f3,0,&slen);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,4,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_FLOAT,0,0,&f4,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,5,SQL_PARAM_INPUT,SQL_C_FLOAT,SQL_REAL,0,0,&f5,0,NULL);
      checkrc(ret,__LINE__);
   
      ret = SQLBindParameter(stmt,6,SQL_PARAM_INPUT,SQL_C_TYPE_DATE,SQL_TYPE_DATE,196,0,&date,sizeof(date),&slen);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,7,SQL_PARAM_INPUT,SQL_C_TYPE_TIME,SQL_TYPE_TIME,196,0,&time,sizeof(time),&slen);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,8,SQL_PARAM_INPUT,SQL_C_TYPE_TIMESTAMP,SQL_TYPE_TIMESTAMP,196,0,&timestamp,sizeof(timestamp),NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,9,SQL_PARAM_INPUT,SQL_C_TINYINT,SQL_TINYINT,0,0,&f9,0,NULL);
      checkrc(ret,__LINE__);

      ret = SQLBindParameter(stmt,10,SQL_PARAM_INPUT,SQL_C_SBIGINT,SQL_BIGINT,0,0,&f10,0,NULL);
      checkrc(ret,__LINE__);

      int i,count=0;
      // EXECUTE THE STATEMENT
      for(i=0;i<10;i++)
      {
         f1++;
         f2++;
         f4++;
         ret = SQLExecute(stmt);
         checkrc(ret,__LINE__);
        
         ret = SQLTransact(env,dbc,SQL_COMMIT);
         checkrc(ret,__LINE__);
         count++;
      } 
      printf("Total row inserted=%d\n",count);
      return 0;
  }
//***********************************************************************
// FETCH ROWS FROM THE TABLE "T1"......select * from T1;
int FetchTest(SQLHANDLE env, SQLHANDLE dbc, SQLHANDLE stmt)
{
    
      int ret;
      int f1=10; // f1 field
      short int f2=20;//f2 field
      char f3[50]= "praba";
      float f4 = 2.5;
      float f5 = 10.50;
      int f9=5;
      long long f10=15000;
      SQLINTEGER slen = SQL_NTS;
      SQLINTEGER slen1[11];
      SQL_DATE_STRUCT  date,f6Date;
      SQL_TIME_STRUCT  time, f7Time;
      SQL_TIMESTAMP_STRUCT  timestamp, f8Timestamp;
      slen1[0]=0; 
      date.year=2008;
      date.month=03;
      date.day=18;

      time.hour=5;
      time.minute=22;
      time.second=10;

      timestamp.year=2008;
      timestamp.month=03;
      timestamp.day=18;
      timestamp.hour=5; 
      timestamp.minute = 22;
      timestamp.second = 10;
      timestamp.fraction = 764576;
      
       int f1temp,f2temp;
       char f3temp[20];
       float f4temp, f5temp;
       
       int f9temp;
       long long f10temp;
       
     ret = SQLPrepare(stmt,(unsigned char*)"SELECT *  FROM T1 ",SQL_NTS);
     checkrc(ret,__LINE__);
    //*******************************************************************************************************

    ret = SQLBindCol(stmt,1,SQL_C_SLONG,&f1,0,&slen1[1]);
    checkrc(ret,__LINE__);
    
    ret = SQLBindCol(stmt,2,SQL_C_SSHORT,&f2,0,&slen1[2]);
    checkrc(ret,__LINE__);


    ret = SQLBindCol(stmt,3,SQL_C_CHAR,f3,sizeof(f3),&slen1[3]);
    checkrc(ret,__LINE__);
 
    ret = SQLBindCol(stmt,4,SQL_C_FLOAT,&f4,0,&slen1[4]);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,5,SQL_C_FLOAT,&f5,0,&slen1[5]);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,6,SQL_C_TYPE_DATE,&date,sizeof(date),&slen1[6]);
    checkrc(ret,__LINE__);
 
    ret = SQLBindCol(stmt,7,SQL_C_TYPE_TIME,&time,sizeof(time),&slen1[7]);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,8,SQL_C_TYPE_TIMESTAMP,&timestamp,sizeof(timestamp),&slen1[8]);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,9,SQL_C_TINYINT,&f9,0,&slen1[9]);
    checkrc(ret,__LINE__);

    ret = SQLBindCol(stmt,10,SQL_C_SBIGINT,&f10,0,&slen1[10]);
    checkrc(ret,__LINE__);

    int j, count=0;
    
    f6Date=date;
    f7Time=time;
    f8Timestamp=timestamp;
      ret = SQLExecute(stmt);
      checkrc(ret,__LINE__);
      while(SQL_SUCCEEDED(ret = SQLFetch(stmt))){
          count++;
          int k=1;
          if(slen1[k++] == SQL_NULL_DATA) printf("F1=NULL  ");
          else printf("F1=%d  ",f1);
          if(slen1[k++] == SQL_NULL_DATA) printf("F2=NULL  ");
          else printf("F2=%d  ",f2);
          if(slen1[k++] == SQL_NULL_DATA) printf("F3=NULL  ");
          else printf("F3=%s",f3);
          if(slen1[k++] == SQL_NULL_DATA) printf("F4=NULL  ");
          else printf("F4=%f  ",f4);
          if(slen1[k++] == SQL_NULL_DATA) printf("F5=NULL  ");
          else printf("F5=%f  ",f5);
          if(slen1[k++] == SQL_NULL_DATA) printf("F6=NULL  ");
          else printf("F6=%d/%d/%d  ",date.year,date.month,date.day);
          if(slen1[k++] == SQL_NULL_DATA) printf("F7=NULL  ");
          else printf("F7=%d-%d-%d  ",time.hour,time.minute,time.second);
          if(slen1[k++] == SQL_NULL_DATA) printf("F8=NULL  ");
          else printf("F8=%d/%d/%d %d-%d-%d  ",timestamp.year,timestamp.month,timestamp.day,timestamp.hour,timestamp.minute,timestamp.second);
          if(slen1[k++] == SQL_NULL_DATA) printf("F9=NULL  ");
          else printf("F9=%d  ",f9);
          if(slen1[k++] == SQL_NULL_DATA) printf("F10=NULL  \n");
          else printf("F10=%lld  \n",f10);
      }
      ret = SQLCloseCursor(stmt);
      checkrc(ret,__LINE__);
        
    ret = SQLTransact(env,dbc,SQL_COMMIT);
    checkrc(ret,__LINE__);
    
    printf("Total row fetched=%d\n",count);
    return 0;
} 
 
 
int main()
{
  SQLHENV env;
  SQLHDBC dbc;
  SQLHSTMT stmt;
  SQLRETURN ret;
  SQLCHAR outstr[1024];
  SQLSMALLINT outstrlen;
  
  // Aloocate an environment handle
  ret=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
  checkrc(ret,__LINE__);
  
   //we need odbc3 support
   SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(void*)SQL_OV_ODBC3,0);
   
  //ALLOCATE A Connection handle
  ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
  checkrc(ret,__LINE__);
    
  // connect to the DSN mydsn
   ret = SQLConnect (dbc,
                   (SQLCHAR *) "test", (SQLSMALLINT) strlen ("test"),
                   (SQLCHAR *) "root",
                   (SQLSMALLINT) strlen ("root"),
                   (SQLCHAR *) "manager",
                   (SQLSMALLINT) strlen (""));


  if(SQL_SUCCEEDED(ret))
  {
     printf("\nConnected to the Data Source..\n");
     
     
  }
   else
   {
        printf("error in connection\n");
        ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
        checkrc(ret,__LINE__);

        ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
        checkrc(ret,__LINE__);
        return 1;
   }

   
   //******************************************************************
   // TABLE CREATED
   ret = SQLAllocHandle(SQL_HANDLE_STMT,dbc,&stmt);
   checkrc(ret,__LINE__);
   
   SQLCHAR table[200]=
     "CREATE TABLE T1(F1 INT,F2 SMALLINT,F3 CHAR(30),F4 FLOAT,F5 FLOAT,F6 DATE,F7 TIME,F8 TIMESTAMP,F9 TINYINT,F10 BIGINT)";
   ret = SQLPrepare(stmt,table,SQL_NTS);
   checkrc(ret,__LINE__);
   ret = SQLExecute(stmt);
   checkrc(ret,__LINE__);
   printf("\nTABLE CREATED\n"); 
   //*****************************
   InsertTest(env,dbc,stmt);  
   FetchTest(env,dbc,stmt);

   //****************************************************************      
    SQLCHAR drop[100]="DROP TABLE T1";
    ret = SQLPrepare(stmt,drop,SQL_NTS);
    checkrc(ret,__LINE__);
    
    ret = SQLExecute(stmt);
    checkrc(ret,__LINE__);
    printf("Table  'T1' dropped successfully\n");  

    ret = SQLFreeHandle(SQL_HANDLE_STMT,stmt);
   checkrc(ret,__LINE__);

   ret = SQLDisconnect(dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_DBC,dbc);
   checkrc(ret,__LINE__);
   
   ret = SQLFreeHandle(SQL_HANDLE_ENV,env);
   checkrc(ret,__LINE__);
   return 0;
}         