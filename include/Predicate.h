/***************************************************************************
 *   Copyright (C) 2007 by www.databasecache.com                           *
 *   Contact:  *   Contact: praba_tuty@databasecache.com                                 *
                                     *
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
#ifndef PREDICATE_H
#define PREDICATE_H
#include<Expression.h>
#include<DataType.h>
#include <ParserDataTypes.h>

class PredicateImpl;
class Predicate;



/**
* @class Condition
*
* @brief Represents the condition part of SQL Query.
* Used in SELECT, UPDATE and DELETE statement to retrieve only tuples which satisfy<br/>
* the condition. This represents the root of the logical expression. This logical <br/>
* expression may contain multiple terms(predicates).<br/>
* For example to set this condition f1 == f2 && f1 == 100. <br/>
*    Condition c1;<br/>
*    int val1 = 100;<br/>
*    c1.setTerm("f1", OpEquals, &val1);<br/>
*    Predicate *p1 = c1.getPredicate();<br/>
*    Condition c2;<br/>
*    c2.setTerm("f1", opEquals, "f2");<br/>
*    Predicate *p2 = c2.getPredicate();<br/>
*    Condtion rootCondition;<br/>
*    rootCondition.setTerm(p1, OpAnd, p2);<br/>
*    table->setCondition(rootCondition);<br/>
* 
*/
class DllExport Condition
{
    Predicate *pred;
    public:
    Condition();
    ~Condition();
    void reset();

    /** gets the current predicate. This is used to create logical expressions with terms or predicates.
    *   @return Predicate* predicate
    */ 
    Predicate* getPredicate() { return pred; }

    /** sets the current predicate. This is set after creating the logical expression and used in the table interface for setting the condition.
    *   @param Predicate* predicate
    */ 
    void setPredicate(Predicate * predicate) {  pred = predicate; }


    /** sets the predicate term of form f1 = f2.
    *   @param fName1* field name
    *   @param op comparision operator
    *   @param fName2* field name
    */ 
    void setTerm(const char* fName1, ComparisionOp op, const char *fName2);

    /** sets the predicate term of form f1 = 10
    *   @param fName1* field name
    *   @param op comparision operator(=,!=, >,<,>=,<=)
    *   @param opnd* pointer to the  value
    */ 
    void setTerm(const char* fName1, ComparisionOp op, void *opnd);

    /** sets the predicate term of form f1 =10, using pointer semantics
    *   @param fName1* field name
    *   @param op comparision operator(=,!=, >,<,>=,<=)
    *   @param opnd** pointer to pointer to the  value
    */ 
    void setTerm(const char* fName1, ComparisionOp op, void **opnd );
    void setTerm(const char* fName1, ComparisionOp op, void **opnd, AggType aggType);


    /** sets the predicate term of form f1 = f2 && f1 = 100.
    *   @param p1* predicate
    *   @param op logical operator (&&, ||, !)
    *   @param p2* predicate
    */ 
    void setTerm(Predicate *p1, LogicalOp op, Predicate *p2 = NULL);

};

/**
 * @class Predicate
 * @brief Represents a single term in the condition.
 * Predicate instance(s) represent all terms in the condition. Predicates can be
 * nested to form a tree structure.
 */
class DllExport Predicate
{
    public:
    virtual void setTerm(const char* fName1, ComparisionOp op, const char *fName2)=0;

    //Operand should be of the same type of the field. This is must
    virtual void setTerm(const char* fName1, ComparisionOp op, void *opnd)=0;

    //Operand should be of the same type of the field. This is must
    virtual void setTerm(const char* fName1, ComparisionOp op, void **opnd)=0;

    virtual void setTerm(Predicate *p1, LogicalOp op, Predicate *p2 = NULL)=0;
    virtual void setTerm(const char* fName1, ComparisionOp op,bool nullFlag)=0;
    virtual void setTerm(Expression *exp, ComparisionOp op, void **opnd) = 0;
    virtual void setTerm(Expression *exp, ComparisionOp op, const char *fName2) = 0;
    virtual void setTerm(Expression *exp1, ComparisionOp op, Expression *exp2) = 0;
    virtual void print(int space)=0;

    virtual ~Predicate(){}
};


#endif
