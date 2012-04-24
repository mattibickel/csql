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
#ifndef PREDICATE_IMPL_H
#define PREDICATE_IMPL_H
#include<DataType.h>
#include<Predicate.h>
#include<ErrorType.h>
class TableImpl;
class Table;
class List;
class AggTableImpl;
class DllExport PredicateImpl:public Predicate
{
    //Members set during initialization of the term
    char fldName1[IDENTIFIER_LENGTH];
    char fldName2[IDENTIFIER_LENGTH];
    ComparisionOp compOp;
    void *operand; // != NULL if PredicateImpl is a leaf node (i.e. a value comparison) and PredicateImpl belongs to JoinTable
    void **operandPtr; // != NULL if PredicateImpl is a leaf node (i.e. a value comparison)
    LogicalOp logicalOp;
    PredicateImpl *lhs;
    PredicateImpl *rhs;
    PredicateImpl *parent;
    int offset1,offset2;
    DataType type;
    int length;
    bool isNullable;
    int fldPos;
    //Members set during execution
    void *tuple; //pointer to the tuple
    List *projList;
    bool isPushedDown;
    AggType aggType;
    //optimization:caching val1 and val2 for evaluation
    char *val1;
    char *val2;
    char *val3;
    bool isBindBufSet;
    bool isNoLeftRight;
    bool dontEvaluate;
    Expression *lExp;
    Expression *rExp;
    //opt for between queries
    ComparisionOp comp2Op;
    void *operand2;
    void **operand2Ptr;
    //This will be set before calling evaluate
    Table *table;
    bool isNull;
    
    public:
    PredicateImpl()
    {
        strcpy(fldName1, ""); strcpy(fldName2, ""); 
        lhs = rhs = NULL; 
        tuple = NULL; table = NULL; 
        projList = NULL;
        parent = NULL;
        offset1 = -1;  offset2 =-1;
        type = typeUnknown; length = 0;
        isPushedDown=false;
        isBindBufSet = false;
        val1= NULL; val2=NULL; val3=NULL;
        isNoLeftRight=false;
        dontEvaluate=false;
        aggType = AGG_UNKNOWN;
        operand2 = operand = NULL;
        operand2Ptr = operandPtr= NULL;
        compOp = comp2Op = OpInvalidComparisionOp;
        logicalOp = OpInvalidLogicalOp;
        isNull=false;
        lExp = NULL; rExp = NULL;
    }
    ~PredicateImpl();

    void setTerm(const char* fName1, ComparisionOp op, const char *fName2);

    //Operand should be of the same type of the field.This is must
    void setTerm(const char* fName1, ComparisionOp op, void *opnd);

    void setTerm(const char* fName1, ComparisionOp op, void **opnd);
    void setTerm(const char* fName1, ComparisionOp op, void **opnd, AggType aggType);
    void setTerm(const char* fName1, ComparisionOp op, void **opnd,
                                     ComparisionOp op2, void **opnd2 );


    void setTerm(Predicate *p1, LogicalOp op, Predicate *p2 = NULL);
    void setTerm(Expression *exp, ComparisionOp op, void **opnd);
    void setTerm(Expression *exp, ComparisionOp op, const char *fName2);
    void setTerm(Expression *exp1, ComparisionOp op, Expression *exp2);
    void setTerm(const char* fName1, ComparisionOp op,bool nullFlag);
    void* valPtrForIndexField(const char *name, bool isUnique);
    ComparisionOp opForIndexField(const char *name);
    void* opAndValPtrForIndexField(const char *name, bool isUnique,ComparisionOp &op);
    DbRetVal evaluate(bool &result);
    void evaluateForTable(bool &result, char*tuple);
    DbRetVal evaluateForHaving(bool &result, AggTableImpl *aImpl, void* elem);

    DbRetVal evaluateLogical(bool &result);
    DbRetVal evaluateLogicalForTable(bool &result, char *tuple);
    DbRetVal evaluateLogicalForHaving(bool &result, AggTableImpl *aImpl, void* elem);

    void setTable(Table *tbl);
    void setTuple(void *tpl);
    void setProjectionList(List *list); //used by JoinTableImpl
    void setOffsetAndType();
    bool isSingleTerm();
    bool isNotOrInvolved();
    bool isIsNullInvolved();
    //check predicate, whether it has field name and == operator
    //and does not have OR, NOT operator
    // TODO:: expression like !(f1 !=100) wont be optimized for now
    bool pointLookupInvolved(const char *fName);
    bool rangeQueryInvolved(const char *fName);
    bool isBetweenInvolved(const char *fname);
    PredicateImpl *getTablePredicate();
    PredicateImpl *getJoinPredicate();
    void removeIfNotNecessary();
    bool isDummyPredicate();
    PredicateImpl* getIfOneSidedPredicate();
    void setParent(PredicateImpl *pImpl);
    char* getFldName1(){ return fldName1; }
    char* getFldName2(){ return fldName2; }
    ComparisionOp getCompOp() {return compOp; }
    void print(int space);
    void setIfNoLeftRight();
    void setDontEvaluate(){dontEvaluate = true;}
    bool appendIfSameFld(char *fname, ComparisionOp op, void* buf);
    void* getValIfPointLookupOnInt(int &offset);
    void* getVal1IfBetweenOnInt(int &offset);
    void* getVal2IfBetweenOnInt(int &offset);
    void solveForProjList(Table *tab);
    
    /**
     * Copy term left and right hand side into a newly allocated Predicate, including operator.
     * This function is recursive.
     * 
     * @return NULL if not enough memory is available. A copy of this instance otherwise.
     */
    Predicate* deepCopy(const FieldConditionValMap &conditionValues) const;
};

#endif
