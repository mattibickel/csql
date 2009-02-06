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
#include<os.h>
#include<DataType.h>
long AllDataType::size(DataType type, int length )
{
    if (type == typeInt) return sizeof(int);
    else if (type == typeString) return length;

    long size = 0;
    switch(type)
    {
        case typeInt:
            size = sizeof(int);
            break;
        case typeLong:
            size = sizeof(long);
            break;
        case typeLongLong:
            size = sizeof(long long);
            break;
        case typeShort:
            size = sizeof(short);
            break;
        case typeByteInt:
            size = sizeof(char);
            break;
        case typeDouble:
            size = sizeof(double);
            break;
        case typeFloat:
            size = sizeof(float);
            break;
        case typeDecimal:
            //TODO::for porting
            //fldDef.length_ = sizeof(long double);
            break;
        case typeDate:
            size = sizeof(Date);
            break;
        case typeTime:
            size = sizeof(Time);
            break;
        case typeTimeStamp:
            size = sizeof(TimeStamp);
            break;
        case typeString:
        case typeBinary:
        case typeComposite:
            size = length;
            break;
        default:
            size  = 0;
            break;
    }
    return size;
}
void AllDataType::copyVal(void* dest, void *src, DataType type, int length)
{
    //Performance optimization. putting likely case first
    if (typeInt == type ) 
    {
        *(int*)dest = *(int*)src;
        return;
    }else if (typeString == type)
    {
        //null is always put at the last byte by insert
        //so using strcpy is safe
        //strcpy((char*)dest, (char*)src);
        memcpy((char*)dest, (char*)src, length);
        //strncpy((char*)dest, (char*)src, length);
        //char *d =(char*)dest;
        //d[length-1] = '\0';
        return;
    }else if (typeShort == type) {
        *(short*)dest = *(short*)src;
    }else if (typeDouble == type) {
        *(double*)dest = *(double*)src;
    }else if (typeTimeStamp == type) {
        *(TimeStamp*)dest = *(TimeStamp*)src;
    }else if (typeDate == type) {
        *(Date*)dest = *(Date*)src;
    }else if (typeFloat == type) {
        *(float*)dest = *(float*)src;
    }else if (typeTime == type) {
        *(Time*)dest = *(Time*)src;
    }else if (typeLong == type) {
        *(long*)dest = *(long*)src;
    }else if (typeLongLong == type) {
        *(long long*)dest = *(long long*)src;
    }else if (typeByteInt == type) {
        *(char*)dest = *(char*)src;
    }else if (typeBinary == type) {
        os::memcpy(dest, src, length);
    }else if (typeComposite == type) {
        os::memcpy(dest, src, length);
    }
    return;
}
void AllDataType::addVal(void* dest, void *src, DataType type)
{
    if (type == typeInt)
    {
        *(int*)dest = *(int*)dest + *(int*)src;
        return;
    }
    switch(type)
    {
        case typeInt:
            *(int*)dest = *(int*)dest + *(int*)src;
            break;
        case typeLong:
            *(long*)dest = *(long*)dest + *(long*)src;
            break;
        case typeLongLong:
            *(long long*)dest = *(long long*)dest + *(long long*)src;
            break;
        case typeShort:
            *(short*)dest = *(short*)dest + *(short*)src;
            break;
        case typeByteInt:
            *(char*)dest = *(char*)dest + *(char*)src;
            break;
        case typeDouble:
            *(double*)dest = *(double*)dest + *(double*)src;
            break;
        case typeFloat:
            *(float*)dest = *(float*)dest + *(float*)src;
            break;
        case typeDecimal:
            //TODO::for porting
        case typeDate:
        case typeTime:
        case typeTimeStamp:
	case typeBinary:
        default:
             break;
     }
     return;
}

bool AllDataType::compareVal(void *val1, void *val2, ComparisionOp op,
                             DataType type, long length)
{
    //Performance optimization.
    //do not convert compareXXXVal to virtual functions. it takes more time
    if (typeInt == type) 
    {
        //as int is the heavily used type, hardcoding the compare here itself
        if (OpEquals == op) {
            if (*(int*)val1 == *(int*)val2) return true;
            else return false;
        }else if (OpLessThanEquals == op) {
            if (*(int*)val1 <= *(int*)val2) return true;
            else return false;
        }else if (OpGreaterThanEquals == op) {
            if (*(int*)val1 >= *(int*)val2) return true;
            else return false;
        }else if (OpGreaterThan == op) {
            if (*(int*)val1 > *(int*)val2) return true;
            else return false;
        }else if (OpLessThan == op) {
            if (*(int*)val1 < *(int*)val2) return true;
            else return false;
        }else if (OpNotEquals == op) {
            if (*(int*)val1 != *(int*)val2) return true;
            else return false;
        }
       
    }else if(typeString == type) {
        return AllDataType::compareStringVal(val1, val2, op);
    } else if (typeShort == type) {
        return AllDataType::compareShortVal(val1, val2, op);
    } else if (typeDouble == type) {
        return AllDataType::compareDoubleVal(val1, val2, op);
    } else if (typeFloat == type) {
        return AllDataType::compareFloatVal(val1, val2, op);
    } else if (typeLong == type) {
        return AllDataType::compareLongVal(val1, val2, op);
    } else if (typeLongLong == type) {
        return AllDataType::compareLongLongVal(val1, val2, op);
    } else if (typeByteInt == type) {
        return AllDataType::compareByteIntVal(val1, val2, op);
    } else if (typeTimeStamp == type) {
        return AllDataType::compareTimeStampVal(val1, val2, op);
    } else if (typeDate == type) {
        return AllDataType::compareDateVal(val1, val2, op);
    } else if (typeTime == type) {
        return AllDataType::compareTimeVal(val1, val2, op);
    } else if (typeBinary == type) {
        return AllDataType::compareBinaryVal(val1, val2, op, length);
    } else if (typeComposite == type) {
        return AllDataType::compareBinaryVal(val1, val2, op, length);
    }
}
ComparisionOp AllDataType::getComparisionOperator(char *str)
{
    ComparisionOp op;
    if (strcmp(str, "<=") == 0)
        op = OpLessThanEquals;
    else if (strcmp(str, ">=") == 0)
        op = OpGreaterThanEquals;
    else if (strcmp(str, "<") == 0)
        op = OpLessThan;
    else if (strcmp(str, ">") == 0)
        op = OpGreaterThan;
    else if (strcmp(str, "=") == 0)
        op = OpEquals;
    else if (strcmp(str, "!=") == 0 || strcmp(str, "<>") == 0 )
        op = OpNotEquals;
    else if (strcasecmp(str, "LIKE") == 0 )
        op = OpLike;
    else
        op = OpInvalidComparisionOp;
    return op;
}