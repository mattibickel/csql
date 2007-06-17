/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact: praba_tuty@databasecache.com                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
  ***************************************************************************/
#include<Config.h>
#include<ErrorType.h>
#include<Debug.h>

Config Conf::config;

int Config::readLine(FILE *fp, char * buffer)
{
  char c =0;
  int count =0;
  while ( true)
  {
      c = fgetc(fp);
      if (c == '\n') break;
      if (c == EOF) return EOF;
      buffer[count++] = c;
  }
  return count;
}
int Config::storeKeyVal(char *key, char *value)
{
    if (strcasestr(key, "PAGE_SIZE") != NULL )
           { cVal.pageSize = atoi(value);  }
    else if (strcasestr(key, "MAX_TRANS") != NULL)
           { cVal.maxTrans = atoi(value);  }
    else if (strcasestr(key, "MAX_PROCS") != NULL)
           { cVal.maxProcs = atoi(value);  }
    else if (strcasestr(key, "MAX_THREADS") != NULL)
           { cVal.maxThreads = atoi(value);  }
    else if (strcasestr(key, "MAX_SYS_DB_SIZE") != NULL)
           { cVal.maxSysSize = atol(value);  }
    else if (strcasestr(key, "MAX_DB_SIZE") != NULL)
           { cVal.maxDbSize = atol(value);  }
    else if (strcasestr(key, "SYS_DB_KEY") != NULL)
           { cVal.sysDbKey = atoi(value);  }
    else if (strcasestr(key, "USER_DB_KEY") != NULL)
           { cVal.userDbKey = atoi(value);  }
    else if (strcasestr(key, "LOG_FILE") != NULL)
           { strcpy(cVal.logFile , value);  }
    else if (strcasestr(key, "MAP_ADDRESS") != NULL)
           { cVal.mapAddr = atol(value);  }
    else if (strcasestr(key, "MUTEX_TIMEOUT_SECS") != NULL)
           { cVal.mutexSecs = atoi(value);  }
    else if (strcasestr(key, "MUTEX_TIMEOUT_USECS") != NULL)
           { cVal.mutexUSecs = atoi(value);  }
    else  return 1;
    return 0;
}
int Config::validateValues()
{
    if (cVal.pageSize < 1024 || cVal.pageSize > 1024 * 1024 * 10 )
    {
        printError(ErrBadArg,  "PAGE_SIZE should be >= 1024 and <= 10 MB");
        return 1;
    }
    if (cVal.maxTrans < 10 || cVal.maxTrans > 8192)
    {
        printError(ErrBadArg,  "MAX_TRANS should be >= 10 and <= 8192");
        return 1;
    }
    if (cVal.maxProcs < 10 || cVal.maxProcs > 8192)
    {
        printError(ErrBadArg,  "MAX_PROCS should be >= 10 and <= 8192");
        return 1;
    }
    if (cVal.maxThreads < 1 || cVal.maxThreads > 64)
    {
        printError(ErrBadArg,  "MAX_THREADS should be >= 1 and <= 64");
        return 1;
    }
    if (cVal.maxSysSize < 1024 * 1024  || cVal.maxSysSize > 1024 *1024 *1024)
    {
        printError(ErrBadArg,  "MAX_SYS_DB_SIZE should be >= 1 MB and <= 1 GB");
        return 1;
    }
    if (cVal.maxSysSize % 8192 !=0 )
    {
        printError(ErrBadArg,  "MAX_SYS_DB_SIZE should be multiples of 8192");
        return 1;
    }

    if (cVal.maxDbSize < 1024 * 1024  || cVal.maxDbSize > 1024 *1024 *1024)
    {
        printError(ErrBadArg,  "MAX_DB_SIZE should be >= 1 MB and <= 1 GB");
        return 1;
    }
    if (cVal.maxDbSize % 8192 !=0)
    {
        printError(ErrBadArg,  "MAX_DB_SIZE should be multiples of 8192");
        return 1;
    }

    if (cVal.sysDbKey < 10 || cVal.sysDbKey > 8192)
    {
        printError(ErrBadArg,  "SYS_DB_KEY should be >= 10 and <= 8192");
        return 1;
    }
    if (cVal.userDbKey < 10 || cVal.userDbKey > 8192)
    {
        printError(ErrBadArg,  "USER_DB_KEY should be >= 10 and <= 8192");
        return 1;
    }
    if ( cVal.sysDbKey == cVal.userDbKey)
    {
        printError(ErrBadArg,  "USER_DB_KEY and SYS_DB_KEY have same value %d", cVal.userDbKey);
        return 1;
    }
    if (0 == strcmp(cVal.logFile,""))
    {
        printError(ErrBadArg,  "LOG_FILE is set to NULL");
        return 1;
    }
    //TODO::Check for the existence of the log file
    if (cVal.mapAddr < 400000000 || cVal.mapAddr > 4000000000)
    {
        printError(ErrBadArg,  "MAP_ADDRESS should be >= 400000000 and <= 4000000000");
        return 1;
    }
    if (cVal.mutexSecs < 0 || cVal.mutexSecs > 360)
    {
        printError(ErrBadArg,  "MUTEX_TIMEOUT_SECS should be >= 0 and <= 360");
        return 1;
    }
    if (cVal.mutexUSecs < 0 || cVal.mutexUSecs > 1000000)
    {
        printError(ErrBadArg,  "MUTEX_TIMEOUT_USECS should be >= 0 and <= 1000000");
        return 1;
    }
    return 0;
}

int Config::readAllValues(char *fileName)
{
    FILE *fp;

    fp = fopen(fileName,"r");
    if( fp == NULL ) {
        printError(ErrSysInit, "Invalid path/filename in CSQL_CONFIG_FILE.");
	return 1;
    }

    int hasData = 1;
    char buffer[1024];
    char key[1024];
    char value[1024];
    while (hasData)
    {
        memset(buffer, 0, 1024);
        //int ret = fscanf(fp,"%s\r",buffer);
        int ret = readLine(fp, buffer);
        if (ret == EOF) break;
        bool isComment= false;
        int posEqual =0;
        for (int i = 0; i <1024; i++)
        {
              if (buffer[i] == '=' ) posEqual=i;
              if (buffer[i] == '#' ) { isComment = true; break; }
              if (buffer[i] == '\n') { break; }
              if (buffer[i] == '\0') { break; }
        }
      if (isComment) continue;
      if (!posEqual) continue;
      strncpy(key, buffer, posEqual);
      key[posEqual] = '\0';
      posEqual++;
      strcpy(value, &buffer[posEqual]);
      storeKeyVal(key, value);
    }
    fclose(fp);
    if (validateValues())
    {
        return 1;
    }

    return 0;
}




