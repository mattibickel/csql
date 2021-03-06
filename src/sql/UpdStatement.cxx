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

#include "PredicateImpl.h"

UpdStatement::UpdStatement()
{
    parsedData = NULL; 
    dbMgr = NULL; 
    table = NULL;
    params = NULL;
    paramValues = NULL;
    totalParams = 0;
    totalAssignParams =0;
}

UpdStatement::~UpdStatement() {
    if (table) { table->close(); table = NULL; }
    if (totalParams) {
        //TODO::below free cause memory corruption.
        free(params);
        params =  NULL;
        free(paramValues);
        paramValues = NULL;
	}
}
void* UpdStatement::getParamValuePtr( int pos )
{
    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (pos <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[pos-1];
      return( (void*) uValue->value );
    } else {
        cValue = (ConditionValue*) params[pos-1];
      return( (void*) cValue->value );
    }
}

DbRetVal UpdStatement::getParamFldInfo(int paramPos, FieldInfo *&info)
{
    if (paramPos <=0 || paramPos > totalParams) return ErrBadArg;
    if (NULL == params[paramPos-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramPos <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramPos-1];
        table->getFieldNameAlone(uValue->fldName,info->fldName);
        info->type = uValue->type;
        info->length = uValue->length;
        info->isNull = uValue->isNullable;
    } else {
        cValue = (ConditionValue*) params[paramPos-1];
        table->getFieldNameAlone(cValue->fName,info->fldName);
        info->type = cValue->type;
        info->length = cValue->length;
        info->isNull = cValue->isNullable;
    }
    return OK;

}
DbRetVal UpdStatement::execute(int &rowsAffected)
{
    DbRetVal rv = OK;
    //copy param values to binded buffer
    ConditionValue *cValue;
    UpdateFieldValue *uValue;

    for (int i = 0; i < totalParams; i ++)
    {
        if (i < totalAssignParams) {
            uValue = (UpdateFieldValue*) params[i];
            if (paramValues[i] == NULL) 
            {
                continue;
                //printError(ErrBadCall, "param values not set");
                //return ErrBadCall;
            }
            AllDataType::copyVal(uValue->value, paramValues[i], uValue->type, uValue->length);
        } else {
            cValue = (ConditionValue*) params[i];
            if (paramValues[i] == NULL) 
            {
                continue;
                //printError(ErrBadCall, "param values not set");
                //return ErrBadCall;
            }
            AllDataType::copyVal(cValue->value, paramValues[i], cValue->type, cValue->length);
        }
    }
    rv = table->execute();
    if (rv != OK) return rv;
    rowsAffected = 0;
    void *tuple;
    ListIterator iter = parsedData->getUpdateFieldValueList().getIterator();
    bool nullFlag;
    while(true)
    {
        tuple = (char*)table->fetchNoBind(rv);
        if (rv != OK) break;
        if (tuple == NULL) {break;}
        iter.reset();
        while (iter.hasElement())
        {
            uValue = (UpdateFieldValue*) iter.nextElement();
            if(uValue->expre!=NULL)
            {
                nullFlag=false;
                uValue->expre->setTuple(tuple);
                uValue->expre->setTable(table);
                AllDataType::copyVal(uValue->value,(uValue->expre)->evaluate(uValue->type,nullFlag),uValue->type, uValue->length);
                uValue->expre->memFree();
                if(nullFlag)
                { 
                    rv=table->markFldNull(uValue->fldName);
                    if(rv==ErrNullViolation){return ErrNullViolation;}
                }
            }
        }
        rv = table->updateTuple();
        if (rv != OK) break;
        rowsAffected++;
    }
    table->closeScan();
    return rv;
}


DbRetVal UpdStatement::setParam(int paramNo, void *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == value) return ErrBadArg;
    paramValues[paramNo -1] = (char*) value; 
    return OK;
}

DbRetVal UpdStatement::setShortParam(int paramNo, short value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(short*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(short*)cValue->value = value;
    }
    return OK;
}


DbRetVal UpdStatement::setIntParam(int paramNo, int value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }
    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(int*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(int*)cValue->value = value;
    }
    return OK;
}
DbRetVal UpdStatement::setNull(int paramNo)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }
    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        table->markFldNull(uValue->fldName);
    } else { 
        printf("paramerise for predicate nullset not supported\n");
    }
}
DbRetVal UpdStatement::setLongParam(int paramNo, long value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(long*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(long*)cValue->value = value;
    }
    return OK;
}

DbRetVal UpdStatement::setLongLongParam(int paramNo, long long value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(long long*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(long long*)cValue->value = value;
    }
    return OK;
}

DbRetVal UpdStatement::setByteIntParam(int paramNo, ByteInt value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(ByteInt*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(ByteInt*)cValue->value = value;
    }
    return OK;
}

DbRetVal UpdStatement::setFloatParam(int paramNo, float value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(float*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(float*)cValue->value = value;
    }
    return OK;
}


DbRetVal UpdStatement::setDoubleParam(int paramNo, double value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(double*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(double*)cValue->value = value;
    }
    return OK;
}

DbRetVal UpdStatement::setStringParam(int paramNo, char *value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        strcpy((char*)uValue->value, value); 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        strcpy((char*)cValue->value, value);
    }
    return OK;
}


DbRetVal UpdStatement::setDateParam(int paramNo, Date value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(Date*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(Date*)cValue->value = value;
    }
    return OK;
}

DbRetVal UpdStatement::setTimeParam(int paramNo, Time value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(Time*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(Time*)cValue->value = value;
    }
    return OK;
}


DbRetVal UpdStatement::setTimeStampParam(int paramNo, TimeStamp value)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        *(TimeStamp*)uValue->value = value; 
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        *(TimeStamp*)cValue->value = value;
    }
    return OK;
}

DbRetVal UpdStatement::setBinaryParam(int paramNo, void *value, int length)
{
    if (paramNo <=0 || paramNo > totalParams) return ErrBadArg;
    if (NULL == params[paramNo-1])
    {
        printError(ErrSysFatal, "param not set. Should never happen");
        return ErrSysFatal;
    }

    ConditionValue *cValue;
    UpdateFieldValue *uValue;
    if (paramNo <= totalAssignParams) {
        uValue = (UpdateFieldValue*) params[paramNo-1];
        memcpy(uValue->value, value, 2 * uValue->length);
    } else {
        cValue = (ConditionValue*) params[paramNo-1];
        AllDataType::convertToBinary(cValue->value,value,typeString,cValue->length);
    }
    return OK;
}

DbRetVal UpdStatement::resolve()
{
    if (dbMgr == NULL) return ErrNoConnection;
    //check whether the table exists
    table = dbMgr->openTable(parsedData->getTableName());
    if (table == NULL) 
    {
        printError(ErrNotExists, "Unable to open the table:Table not exists");
        return ErrNotExists;
    }

    DbRetVal rv = OK;
    
    if (usrMgr->isAuthorized(PRIV_UPDATE, ((TableImpl*)table)->getId()))
    {
        Predicate *pred = NULL;
        if (OK != (rv = (DbRetVal)usrMgr->getTableRestriction(((TableImpl*)table)->getId(), pred, parsedData->getConditionValueList())))
        {
            goto cleanupAndExit;
        }
        
        // do additional restrictions apply? if so, add them to the existing condition
        if (NULL != pred)
        {
            if (NULL != parsedData->getCondition() && NULL != parsedData->getCondition()->getPredicate())
            {
                Predicate *finalPred = new PredicateImpl();
                finalPred->setTerm(parsedData->getCondition()->getPredicate(), OpAnd, pred);
                parsedData->setCondition(finalPred);
            }
            else
            {
                parsedData->setCondition(pred);
            }
        }
    }
    else
    {
        rv = ErrNoPrivilege;
        printError(rv, "User not authorized to update this table.");
        goto cleanupAndExit;
    }
        
    table->setCondition(parsedData->getCondition());
    
    rv = resolveForAssignment();
    
    cleanupAndExit:
        if (rv != OK) 
        {
            //TODO::free memory allocated for params
            table->setCondition(NULL);
            dbMgr->closeTable(table);
            table = NULL;
        }
        return rv;
}

DbRetVal UpdStatement::resolveForAssignment()
{
    //get the fieldname list and validate field names
    ListIterator iter = parsedData->getUpdateFieldValueList().getIterator();

    UpdateFieldValue *value;
    FieldInfo *fInfo = new FieldInfo();
    int paramPos =1;
    DbRetVal rv = OK;
    while (iter.hasElement())
    {
        value = (UpdateFieldValue*) iter.nextElement();
        if (NULL == value) 
        {
            delete fInfo;
            printError(ErrSysFatal, "Should never happen.");
            return ErrSysFatal;
        }
        rv = table->getFieldInfo(value->fldName, fInfo);
        if (ErrNotFound == rv)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        value->fldName);
            return ErrSyntaxError;
        }
        if (fInfo->isUnique) {
            delete fInfo;
            printError(ErrUnique, "Unique field %s cannot be updated", value->fldName);
            return ErrUnique;
        }
        if (fInfo->isAutoIncrement){
            delete fInfo;
            printError(ErrAutoIncUpdate, "Auto_increment key field '%s' cannot be updated \n", value->fldName);
            return ErrAutoIncUpdate;

        } 
        value->type = fInfo->type;
        value->length = fInfo->length;
        value->isNullable = fInfo->isNull;
        // for binary datatype input buffer size should be 2 times the length 
        if (value->type == typeBinary)
		    value->value = AllDataType::alloc(fInfo->type, 2 * fInfo->length);
        else value->value = AllDataType::alloc(fInfo->type, fInfo->length);
        table->bindFld(value->fldName, value->value);
        if( NULL != value->expre )
        {
            (value->expre)->convertStrToVal(value->type);
            continue;
        }
        if (value->parsedString == NULL) 
        {    
            if (fInfo->isNull) { 
                delete fInfo; 
                printError(ErrNullViolation, "Null Violation Error.");
                return ErrNullViolation; 
            }
            table->markFldNull(value->fldName); 
            memset(value->value, 0, value->length);
            continue; 
        }
        if (value->parsedString[0] == '?')
        {
            value->paramNo = paramPos++;
        }
        if (!value->paramNo) {
            // checking for Integer value
	     if((value->type == typeInt) || (value->type==typeShort) || (value->type==typeByteInt) || (value->type==typeLongLong) || (value->type==typeLong)){
	           int len=strlen(value->parsedString);
	           for(int n=0;n<len;n++){
	               int p=value->parsedString[n];
	               if(!(p>=48 && p<=57 || p==45)) {
                          delete fInfo;
	                  return ErrBadArg;
                       }
	           }
	     }
	    // for binary datatype buffer is just strcpy'd. It will be converted into binary datatype in copyValuesToBindBuffer in DBAPI
            if (value->type == typeBinary)
                strncpy((char *)value->value, value->parsedString, 2 * fInfo->length);
            else {
                rv = AllDataType::strToValue(value->value, value->parsedString, fInfo->type, value->length);
                if (OK != rv)
                {
                    delete fInfo;
                    return ErrBadArg;
                }
            }
            /* Check for char data type 8kb(8000) */
            if(value->type==typeString){
                 int len=strlen(value->parsedString);
                 if(len > 8000){
                     printError(ErrBadRange, "Char DataType length should be less than 8kb(8000).");
                     delete fInfo;
                     return ErrBadRange;
                 }
             }

       }	
    }
    totalAssignParams = paramPos -1;
    //get the fieldname list and validate field names
    ListIterator cIter = parsedData->getConditionValueList().getIterator();
    ConditionValue *cValue = NULL;
    while (cIter.hasElement())
    {
        cValue = (ConditionValue*) cIter.nextElement();
        if (NULL == cValue) 
        {
            delete fInfo;
            printError(ErrSysFatal, "Should never happen.");
            return ErrSysFatal;
        }
        char tName[IDENTIFIER_LENGTH];
        Table::getTableNameAlone(cValue->fName,tName);
        if( strcmp(tName,"")!=0 && strcmp(parsedData->getTableName(),tName)!=0 )
        {
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table %s", cValue->fName,parsedData->getTableName());
            return ErrSyntaxError;
        }

        rv = table->getFieldInfo(cValue->fName, fInfo);
        if (ErrNotFound == rv)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Field %s does not exist in table", 
                                        cValue->fName);
            return ErrSyntaxError;
        }
        cValue->type = fInfo->type;
        cValue->length = fInfo->length;
        cValue->isNullable = fInfo->isNull;
        // for binary datatype input buffer size should be 2 times the length 
        if (cValue->type == typeBinary) 
        {
            if(cValue->parsedString[0] == '?')
                cValue->value = AllDataType::alloc(fInfo->type, fInfo->length);
            else 
                cValue->value = AllDataType::alloc(fInfo->type, 2 * fInfo->length);
        }
        else cValue->value = AllDataType::alloc(fInfo->type, fInfo->length);
        if(cValue->paramNo == 1){continue;}
        if (cValue->parsedString == NULL)
        {
            delete fInfo;
            printError(ErrSyntaxError, "Condition value should not be NULL");
            return ErrSyntaxError;
        }

        if (cValue->parsedString[0] == '?')
        {
  	    //if(! cValue->opLike) // checks if 'LIKE' operator is used
            cValue->paramNo = paramPos++;
        }
        if (!cValue->paramNo) {
           //Checking for integer value
	   if((cValue->type == typeInt) || (cValue->type==typeShort) || (cValue->type==typeByteInt) || (cValue->type==typeLongLong) || (cValue->type==typeLong)){
	        int len = strlen(cValue->parsedString);
	        for(int n=0;n<len;n++){
	             int p=cValue->parsedString[n];
	             if(!(p>=48 && p<=57 || p==45)) {
                        delete fInfo;
	                return ErrBadArg;
                     }
	        }
	   }
           // Here for binary dataType it is not strcpy'd bcos internally memcmp is done for predicates like f2 = 'abcd' where f2 is binary
           rv = AllDataType::strToValue(cValue->value, cValue->parsedString, fInfo->type, fInfo->length);
           if (OK != rv) {
               delete fInfo;
               return ErrBadArg;
           }
       }
    }
    delete fInfo;
    totalParams = paramPos -1;
    if (0 == totalParams) return OK;
    params = (void**) malloc ( totalParams * sizeof(FieldValue*));
    paramValues = (char**) malloc( totalParams * sizeof(char*));

    memset(params, 0, totalParams * sizeof(FieldValue*));
    memset(paramValues, 0, totalParams * sizeof(char*));

    iter.reset();
    while(iter.hasElement())
    {
        value = (UpdateFieldValue*) iter.nextElement();
        if (value == NULL) 
        {
            free(params); params = NULL;
            free(paramValues); paramValues = NULL;
            printError(ErrSysFatal, "Should never happen. value NULL after iteration");
            return ErrSysFatal;
        }
        if (0 == value->paramNo) continue;
        params[value->paramNo -1 ] = value;
    }

    cIter.reset();
    while(cIter.hasElement())
    {
        cValue = (ConditionValue*) cIter.nextElement();
        if (cValue == NULL) 
        {
            free(params); params = NULL;
            free(paramValues); paramValues = NULL;
            printError(ErrSysFatal, "Should never happen. value NULL after iteration");
            return ErrSysFatal;
        }
        if (0 == cValue->paramNo) continue;
        params[cValue->paramNo -1 ] = cValue;
    }
    return OK;
}
int  UpdStatement::getFldPos(char *name)
{
    return table->getFldPos(name);
}

