/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
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
#include <os.h>
#include <Statement.h>
#include <Info.h>

DbRetVal DmlStatement::getFieldInfo(const char *tname, const char *fname, FieldInfo *& info)
{
    if (table) {
        if (strcmp(tname, table->getName())==0)
            return table->getFieldInfo(fname, info);
    }
    return ErrNotExists;
}

List DmlStatement::getFieldNameList(const char *tname, DbRetVal &rv)
{
    if (table) {
        if (strcmp(tname, table->getName())==0)
            return table->getFieldNameList();
    }
    rv = ErrNotExists;
}

InsStatement::InsStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
    table = NULL;
    params = NULL;
    paramValues = NULL;
    totalParams = 0;
}

InsStatement::~InsStatement()
{
    if (table) { table->close(); table = NULL; }
    if (totalParams) {
        free(params);
        params =  NULL;
        free(paramValues);
        paramValues = NULL;
    }
}

DbRetVal InsStatement::getParamFldInfo(int paramPos, FieldInfo *&info)
{
    if (paramPos >totalParams ) return ErrBadCall;
    FieldValue *value = (FieldValue*)params[paramPos-1];
    if (value == NULL)
    {
        printError(ErrSysFatal, "param ptr is null: should never happen\n");
        return ErrBadArg;
    }
    table->getFieldNameAlone(value->fldName,info->fldName);
    info->type = value->type;
    info->length = value->length;
    info->isNull = value->isNullable;
    return OK;
}

DbRetVal InsStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    //copy param values to binded buffer
    FieldValue *value;
    for (int i = 0; i < totalParams; i ++)
    {
        value = (FieldValue*) params[i];
        if (paramValues[i] == NULL) 
        {
            //printError(ErrBadCall, "param values not set");
            continue;
            //return ErrBadCall;
        }
        AllDataType::copyVal(value->value, paramValues[i], value->type, value->length);
    }
    rv = table->insertTuple();
    if (rv ==OK) rowsAffected = 1;
    table-> resetNullinfo();
    return rv;
}

DbRetVal InsStatement::setParam(int paramNo, void *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    paramValues[paramNo -1] = (char*) value; 
    return OK;
}

DbRetVal InsStatement::setShortParam(int paramNo, short value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *fValue = (FieldValue*) params [paramNo-1];
    if (NULL == fValue)
    {
        printError(ErrSysFatal, "field value is null. Should never happen");
        return ErrSysFatal;
    }
    *(short*)fValue->value = value; 
    return OK;
}

DbRetVal InsStatement::setIntParam(int paramNo, int value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }

    *(int*)cValue->value = value; 
    return OK;
}
DbRetVal InsStatement::setNull(int paramNo)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "FieldValue is null. Should never happen");
        return ErrSysFatal;
    }
    char name[IDENTIFIER_LENGTH];
    table->getFieldNameAlone(cValue->fldName,name);
    table->markFldNull(name);
    return OK;
}
DbRetVal InsStatement::setLongParam(int paramNo, long value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(long*)cValue->value = value; 
    return OK;
}

DbRetVal InsStatement::setLongLongParam(int paramNo, long long value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(long long*)cValue->value = value; 
    return OK;
}
DbRetVal InsStatement::setByteIntParam(int paramNo, ByteInt value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(ByteInt*)cValue->value = value; 
    return OK;
}
DbRetVal InsStatement::setFloatParam(int paramNo, float value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(float*)cValue->value = value; 
    return OK;
}
DbRetVal InsStatement::setDoubleParam(int paramNo, double value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(double*)cValue->value = value; 
    return OK;
}
DbRetVal InsStatement::setStringParam(int paramNo, char *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    //TODO::check if the strlen(value) is greater than field length
    //do in all stmts
    strcpy((char*)cValue->value, value);
    return OK;
}
DbRetVal InsStatement::setDateParam(int paramNo, Date value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(Date*)cValue->value = value; 
    return OK;
}
DbRetVal InsStatement::setTimeParam(int paramNo, Time value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(Time*)cValue->value = value; 
    return OK;
}
 void* InsStatement::getParamValuePtr( int pos )
 {
     FieldValue *p = (FieldValue*) params [pos-1];
     return ( (void*) p->value );
 }

DbRetVal InsStatement::setTimeStampParam(int paramNo, TimeStamp value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *cValue = (FieldValue*) params [paramNo-1];
    if (NULL == cValue)
    {
        printError(ErrSysFatal, "condition value is null. Should never happen");
        return ErrSysFatal;
    }
    *(TimeStamp*)cValue->value = value;
    return OK;
}

DbRetVal InsStatement::setBinaryParam(int paramNo, void *value, int length)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    FieldValue *fValue = (FieldValue*) params [paramNo-1];
    if (NULL == fValue)
    {
        printError(ErrSysFatal, "field value is null. Should never happen");
        return ErrSysFatal;
    }
    memcpy(fValue->value, value, 2 * fValue->length);
    return OK;
}

long long InsStatement::getLastInsertedVal(DbRetVal &rv)
{
    if(table)
        return ((TableImpl*)table)->getLastInsertedVal(rv);
    else{
        rv = ErrBadCall;
        return 0;
    }
}

DbRetVal InsStatement::resolve()
{
    if (dbMgr == NULL) return ErrNoConnection;
    //check whether the table exists
    table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL) 
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }

    if (!usrMgr->isAuthorized(PRIV_INSERT, ((TableImpl*)table)->getId()))
    {
        dbMgr->closeTable(table);
        table = NULL;
        printError(ErrNoPrivilege, "User is not authorized to insert into table.");
        return ErrNoPrivilege;
    }
    
    List fieldNameList;
    //check whether filed list is specified
    if( 0 == parsedData->getFieldNameList().size() )
        fieldNameList = table->getFieldNameList();
    else
        fieldNameList = parsedData->getFieldNameList();

    //check whether the total number of field name in the list is same as the total 
    //number of values provided in the values list.
    if ( fieldNameList.size() != 
                               parsedData->getFieldValueList().size())
    {
        dbMgr->closeTable(table);
        table = NULL;
        printError(ErrSyntaxError, "Field Name list and field values do not match");
        return ErrSyntaxError;
    }

    //get the fieldname list and validate field names
    ListIterator iter = fieldNameList.getIterator();
    ListIterator valIter = parsedData->getFieldValueList().getIterator();
    FieldName *name; FieldValue *value;
    FieldInfo *fInfo = new FieldInfo();
    int paramPos =1;
    DbRetVal rv = OK;
    while (iter.hasElement())
    {
        name = (FieldName*)iter.nextElement();
        value = (FieldValue*) valIter.nextElement();
        if (NULL == name || NULL == value) 
        {
            dbMgr->closeTable(table);
            table = NULL;
            delete fInfo;
            printError(ErrSyntaxError, "Field Name list and field values do not match");
            return ErrSyntaxError;
        }
        rv = table->getFieldInfo(name->fldName, fInfo);
        if (ErrNotFound == rv)
        {
            dbMgr->closeTable(table);
            table = NULL;
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        name->fldName);
            return ErrSyntaxError;
        }
        strcpy(value->fldName,name->fldName);
        value->type = fInfo->type;
        value->length = fInfo->length;
        value->isNullable = fInfo->isNull;
		// for binary datatype input buffer size should be 2 times the length 
	if (fInfo->type == typeBinary) 
            value->value = AllDataType::alloc(fInfo->type, 2 * fInfo->length);
        else value->value = AllDataType::alloc(fInfo->type, fInfo->length);
        value->isAllocVal = true;
        if (value->parsedString == NULL) {
            table->bindFld(name->fldName, NULL, true);
            continue;
        }
        table->bindFld(name->fldName, value->value);
        if (value->parsedString[0] == '?')
        {
            value->paramNo = paramPos++;
        }
        if (!value->paramNo) {
             // Checking Integer value
	     if((value->type == typeInt) || (value->type==typeShort) || (value->type==typeByteInt) || (value->type==typeLongLong) || (value->type==typeLong)){
	         int len=strlen(value->parsedString);
	         for(int n=0;n<len;n++){
	            int p=value->parsedString[n];
	            if(!(p>=48 && p<=57 || p==45) ) {
                        delete fInfo;
	                return ErrBadArg;
                    }
	         }
	     }
	    // for binary datatype buffer is just strcpy'd. 
            //It will be converted into binary datatype in copyValuesToBindBuffer in DBAPI
                if (value->type == typeBinary)
                   strncpy((char *)value->value, value->parsedString, 2 * fInfo->length);   
                else {
                   rv = AllDataType::strToValue(value->value, value->parsedString, fInfo->type, fInfo->length);
                   if (OK != rv) {
                       delete fInfo;
                       return ErrBadArg;
                   }
                }

                 /* Checking range for char data type 8kb(8000) */
                 if(value->type==typeString){
                   int len=strlen(value->parsedString);
                   if(len > 8000){
                       printError(ErrBadRange,"Char data type length should be less than 8kb(8000).");
                       delete fInfo;
                       return ErrBadRange;
                   }
                }

       }
    }
    delete fInfo;
    totalParams = paramPos -1;
    if (0 == totalParams) {
        if( 0 == parsedData->getFieldNameList().size() ) {
            iter.reset();
            while(iter.hasElement())
                delete (Identifier *) iter.nextElement();
            fieldNameList.reset();
        }
	return OK;
    }	
    params = (void**) malloc ( totalParams * sizeof(FieldValue*));
    paramValues = (char**) malloc( totalParams * sizeof(char*));
    memset(params, 0, totalParams * sizeof(FieldValue*));
    memset(paramValues, 0, totalParams * sizeof(char*));
    valIter.reset();
    while(valIter.hasElement())
    {
        value = (FieldValue*) valIter.nextElement();
        if (value == NULL) 
        {
            dbMgr->closeTable(table);
            table = NULL;
            free(params); params = NULL;
            free(paramValues); paramValues = NULL;
            printError(ErrSysFatal, "Should never happen. value NULL after iteration");
            return ErrSysFatal;
        }
        if (value->paramNo == 0) continue;
        params[value->paramNo -1 ] = value;
    }
   // memory to be deallocated created by table->getFieldNameList
    if( 0 == parsedData->getFieldNameList().size() ) {
        iter.reset();
        while(iter.hasElement())
            delete (Identifier *) iter.nextElement();
        fieldNameList.reset();
    }
    return OK;
}
int InsStatement::getFldPos(char *name)
{
    return table->getFldPos(name);
}

