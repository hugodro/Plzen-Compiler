#ifndef _SQLACTIONS_H_
#define _SQLACTIONS_H_
/**************************************************
* File: sqlActions.h.
* Desc: Definition of the JCSqlStatement hierarchy.
* Module: AkraLog : JavaKit.
* Rev: 1 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/


#include <akra/AkObject.h>
#include "actions.h"


class JCSqlSelect;
class JCSqlTargetList;
class JCIdentifier;
class JCSqlIdentList;
class JCSqlIdentifier;
class JCCteExpr;
class ConstantsList;
class JCExecSqlInvoke;
class JCSqlExpression;
class JCSqlFetchOrientation;


// ATTN: This will become JCActiveSqlStatement, and JCSqlStatement
//	will become its root class, and the root class of JCDeclareSqlStatement
//	(associated with declareSql).
class JCSqlStatement : public JCAction {
  public:
    enum Category {
	cUnknown,
	cOpen, cClose, cFetch
	, cDelete, cInsert, cUpdate, cSelect
	, cCommit, cRollback
    };

  protected:
    Category category;
    JCCteExpr *compiledValue;
    unsigned int nbrEmbedded;
    JCExpression **embeddeds;

  public:
    JCSqlStatement(void);
    JCSqlStatement(Category aCategory);
    virtual void link(JCSqlStatement *aStatement);
    virtual void spitHolesTo(JCCompilationContext *codeContext);
    virtual void spitTruePostscriptum(JCCompilationContext *codeContext, unsigned int falseLabel);
    virtual void spitFalsePostscriptum(JCCompilationContext *codeContext);
    virtual void consolidate(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void attachInvoker(JCExecSqlInvoke *anInvoker);
    virtual void generateTokens(void);
};


class JCSqlOpen : public JCSqlStatement {
  public:
    JCSqlOpen(JCIdentifier *aCursor);
};


class JCSqlFetch : public JCSqlStatement {
  protected:		// Instance variables.
    JCSqlFetchOrientation *orientation;
    JCSqlIdentifier *cursor;
    JCSqlTargetList *localVars;
    JCCteExpr *outCountArg;
    
  public:			// Instance methods.
    JCSqlFetch(JCSqlFetchOrientation *anOrder, JCSqlIdentifier *anIdent, JCSqlTargetList *varList);
    virtual void consolidate(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTruePostscriptum(JCCompilationContext *codeContext, unsigned int trueLabel);
    virtual void generateTokens(void);
};


class JCSqlClose : public JCSqlStatement {
  public:
    JCSqlClose(JCIdentifier *aCursor);
};


class JCSqlDelete : public JCSqlStatement {
  public:
    JCSqlDelete();
};


class JCSqlInsert : public JCSqlStatement {
  protected:
    JCSqlIdentifier *tableName;
    JCSqlIdentList *columnTargets;
    JCSqlExpression *values;
    JCCteExpr *outCountArg;

  public:
    JCSqlInsert();
    JCSqlInsert(JCSqlIdentifier *aName, JCSqlIdentList *someNames, JCSqlExpression *aSelect);
    virtual void setTableName(JCSqlIdentifier *aName);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void generateTokens(void);
};


class JCSqlUpdate : public JCSqlStatement {
  public:
    JCSqlUpdate();
};


class JCSqlSelectStat : public JCSqlStatement {
  protected:
    JCSqlSelect *select;
    JCSqlTargetList *localVars;
    JCCteExpr *outCountArg;

  public:
    JCSqlSelectStat(JCSqlSelect *selectExpr, JCSqlTargetList *intos);
    virtual void consolidate(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTruePostscriptum(JCCompilationContext *codeContext, unsigned int trueLabel);
    virtual void generateTokens(void);
};


#endif		/* _SQLACTIONS_H_ */
