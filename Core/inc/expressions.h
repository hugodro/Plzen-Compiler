#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_
/**************************************************
* File: expressions.h.
* Desc: Contains the definitions of the expressions syntaxic components.
* Module: AkraLog : JavaComp.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"
#include "containment.h"
#include "typing.h"


class JCIdentifier;
class JCName;
class ConstantsList;
class JCOutCFConstant;
class JCPackage;
class JCNameSpace;
class JCCompilationContext;
class JCMethod;
class JCInitInvoke;
class JCVariableDeclaration;
class JCCteClass;


class JCExpression : public JCContainer {
  public:
    enum ExprCategory {
	eVariable,	// A variable reference, either local or from current object.
	eField,		// A field reference, using a composed or complex name.
	eArray,		// An array reference.
	eBlock,		// An expression in parenthesis.
	eConstant,	// A constant literal.
	eOperation,	// A unary or binary 'built-in' operation.
	eCast,		// A cast invocation.
	eAssign,		// Assignment of a value to a variable.
	eInvoke,		// A method invocation.
	eAlloc,		// An allocation of new instances.
	eConditional,	// A conditional expression ("<test> ? yes : no").
	eEmpty,
	eSpecial,		// Special expression (refering to 'null', 'this' or 'super').
	eUnknownName	// A JCNamedExpr that is unknown (and might be removed).
    };

  public:	// MOD-MSC: Change la protection de 'protected' a 'public'.
    JCExpression *next;		// Used to create a link list of expressions.
    ExprCategory category;	// Category of expression.
    JCContainer *owner;	// Container that owns us (most of the type, an Expression).

  public:
    JCExpression();
    JCExpression(ExprCategory aCategory);

    virtual unsigned int getContainerType(void);

    virtual void linkExpression(JCExpression *nextMember);
    virtual ExprCategory getCategory(void);
    virtual JCExpression *getNext(void);
    virtual void mapToPool(ConstantsList *aPool);
    virtual bool isResolved(void);
    virtual void handleMute(JCExpression *before, JCExpression *after);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
    virtual void spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
    virtual JCReferencedType *getFinalType(void);
    virtual void typeUpdateChild(JCExpression *anExpression);
    virtual void typeUpdateOwner(void);
    virtual void setOwner(JCContainer *anOwner);
    virtual JCContainer *getOwner(void);
    virtual unsigned int getStartLine(void);
    virtual unsigned int getEndLine(void);
 };


class JCBlockExpr : public JCExpression {
  protected:
    JCExpression *subExpressions;

  public:
    JCBlockExpr();
    virtual void setInternal(JCExpression *anExpression);
    virtual void mapToPool(ConstantsList *aPool);
    virtual void handleMute(JCExpression *before, JCExpression *after);
    virtual JCReferencedType *getFinalType(void);
 };

class JCCteExpr : public JCExpression {
  protected:
    JCReferencedType::PopularType typing;
	// Warning: we use the shadow also as a general 32 bits holder,
	// for bool, char values.
    JCOutCFConstant *shadow;	// Will be either JCWord or JCDblWord.

  public:
    JCCteExpr();
    JCCteExpr(JCReferencedType::PopularType aBType);
    virtual void setBoolValue(bool aValue);
    virtual void setCharValue(wchar *aValue);
    virtual void setIntValue(int aValue);
    virtual void setIntZero(void);
    virtual void setIntOne(void);
    virtual void setIntMinusOne(void);
    virtual void setFloatValue(float aValue);
    virtual void setFloatZero(void);
    virtual void setFloatOne(void);
    virtual void setFloatMinusOne(void);
    virtual void setLongValue(unsigned int *aValue);
    virtual void setLongValue(unsigned int highBytes, unsigned int lowBytes);
    virtual void setLongZero(void);
    virtual void setLongOne(void);
    virtual void setLongMinusOne(void);
    virtual void setDoubleValue(double aValue);
    virtual void setDoubleZero(void);
    virtual void setDoubleOne(void);
    virtual void setDoubleMinusOne(void);
    virtual int getIntValue(void);
    virtual float getFloatValue(void);
    virtual unsigned int *getLongValue(void);
    virtual double getDoubleValue(void);
    virtual bool setStringValue(wchar *aValue);
    virtual void mapToPool(ConstantsList *aPool);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual JCReferencedType *getFinalType(void);
    virtual void negate(void);
    virtual bool isNullCte(void);
};


class JCNamedExpr : public JCExpression {
  protected:
    JCIdentifier *name;
    JCExpression *subExpression;
    JCName *resolver;	// The way to find out what the expression refer to.

  public:
    JCNamedExpr(ExprCategory aCategory);
    JCNamedExpr(ExprCategory aCategory, JCIdentifier *aName, JCName *aResolution);
    JCNamedExpr(JCIdentifier *aName);

    virtual void setName(JCIdentifier *aName);
    virtual void setSubExpression(JCExpression *anArrayProducer);
    virtual JCIdentifier *getName(void);
    virtual JCExpression *getSubExpression(void);
    virtual void setResolution(JCName *aResolver);
    virtual JCName *resolution(void);
    virtual void mapToPool(ConstantsList *aPool);
    virtual bool isResolved(void);
    virtual void bindInLocalSpace(JCNameSpace *aSpace);
    virtual void addBottomSubExpression(JCExpression *anExpression);
    virtual JCExpression *muteTo(ExprCategory aClearForm, JCName *someName);
    virtual void handleMute(JCExpression *before, JCExpression *after);
    virtual JCReferencedType *getFinalType(void);
};



class JCVarAccess : public JCExpression {
  protected:
    JCIdentifier *name;	// This name doesn't have subComponents.
    JCName *resolver;	// The way to find out what the expression refer to.

  public:
    JCVarAccess(void);
    JCVarAccess(JCIdentifier *aName, JCName *aResolution);

    virtual bool setVarName(JCIdentifier *aName);
    virtual JCIdentifier *getVarName(void);
    virtual void setResolution(JCName *aResolver);
    virtual JCName *resolution(void);
    virtual void mapToPool(ConstantsList *aPool);
    virtual bool isResolved(void);
    virtual void bindInLocalSpace(JCNameSpace *aSpace);

    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
    virtual void spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
    virtual JCReferencedType *getFinalType(void);
};


class JCFieldAccess : public JCNamedExpr {
  protected:

  public:
    JCFieldAccess(void);
    JCFieldAccess(JCIdentifier *aName, JCName *aResolution);

    virtual void mapToPool(ConstantsList *aPool);

    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
    virtual void spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
 };


class JCArrayAccess : public JCNamedExpr {
  protected:
    // ATTN: 'name' and subExpression are mutually exclusive.
    JCExpression *valueOffset;
    unsigned int nbrOffsets;
    JCReferencedType *accessType;    // Type of the access, not of the original declaration.

  public:
    JCArrayAccess();
    virtual bool addDimensionOffset(JCExpression *offset);
    virtual void mapToPool(ConstantsList *aPool);
    virtual void bindInLocalSpace(JCNameSpace *aSpace);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void spitStorerTo(JCCompilationContext *codeContext);
    virtual JCReferencedType *getFinalType(void);
 };


class JCOperExpr : public JCExpression {
  protected:
    unsigned int builtinOp;
    JCExpression *left;
    JCExpression *right;		// Receive the operand of unary ops.
    JCReferencedType *resultType;	// TODO !
    bool resolved;

  public:
    JCOperExpr();
    JCOperExpr(ExprCategory aCategory);
    virtual bool setOperator(unsigned int operation);
    virtual bool setLeftOperand(JCExpression *anExpr);
    virtual bool setRightOperand(JCExpression *anExpr);
    virtual void mapToPool(ConstantsList *aPool);
    virtual bool isResolved(void);
    virtual void handleMute(JCExpression *before, JCExpression *after);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
    virtual void spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
    virtual bool computeOperType(void);
    JCReferencedType *doBinaryPromote(JCReferencedType *leftType, JCReferencedType *rightType);
    JCReferencedType *doUnaryPromote(JCReferencedType *aType);
    virtual JCReferencedType *getFinalType(void);
    virtual void typeUpdateChild(JCExpression *anExpression);
    virtual void typeUpdateOwner(void);
 };


class JCCastExpr : public JCOperExpr {
  protected:

  public:
    JCCastExpr();
    virtual void setTypeMember(JCReferencedType *aType);    // Type information for CAST and ISA.
    virtual void mapToPool(ConstantsList *aPool);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void typeUpdateChild(JCExpression *anExpression);
};


class JCAssignExpr : public JCOperExpr {
  protected:

  public:	// Class methods.
    static void spitAssignmentFor(JCCompilationContext *codeContext, JCVariableDeclaration *aDecl);
    static void spitAssignmentFor(JCCompilationContext *codeContext, JCVariableDeclaration *aDecl, unsigned int anIndex);

  public:
    JCAssignExpr();
    virtual bool setLeftOperand(JCExpression *anExpr);	// Must do a somewhat different checking.
    virtual bool setOperator(unsigned int operation);	// Idem.
    virtual void spitTo(JCCompilationContext *codeContext);
 };


class JCInvokeExpr : public JCNamedExpr {
  protected:
    JCExpression *arguments;
    bool cantBeVirtual;

  public:
    JCInvokeExpr();
    virtual bool setArguments(JCExpression *argList);
    virtual void mapToPool(ConstantsList *aPool);
    virtual void handleMute(JCExpression *before, JCExpression *after);
    virtual void bindInLocalSpace(JCNameSpace *aSpace);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void typeUpdateChild(JCExpression *anExpression);
    virtual void typeUpdateOwner(void);
    virtual unsigned int getNbrArguments(void);
    virtual void spitArgumentTypes(JCReferencedType **argTyping);
    virtual void mainSpitTo(JCCompilationContext *codeContext, bool mustPop);
    virtual void spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
    virtual void spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest);
 };


class JCAllocExpr : public JCExpression {
  protected:
    JCReferencedType *type;
    JCExpression *dimensionSizes;
    unsigned int nbrSizes, nbrEmptyDims;
    JCInitInvoke *initializer;
    bool resolved;
    JCCteClass *shadow;		// ATTN: Temporary solution for vectorial primary types.

  public:
    JCAllocExpr();
    virtual bool setType(JCReferencedType *aType);
    virtual void setArrayType(JCReferencedType *aType, JCExpression *dimList, unsigned int emptyDims);
//    virtual bool setPreciseDimensions(JCExpression *dimList);
//    virtual bool setAdditionalDimensions(unsigned int emptyDims);
    virtual bool setArguments(JCExpression *argList);
    virtual void mapToPool(ConstantsList *aPool);
    virtual bool isResolved(void);
    virtual void handleMute(JCExpression *before, JCExpression *after);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual JCReferencedType *getReferencedType();
 };


class JCCondExpr : public JCExpression {
  protected:
    JCExpression *test;
    JCExpression *trueExpr;
    JCExpression *falseExpr;
    bool resolved;

  public:
    JCCondExpr();
    virtual bool setCondition(JCExpression *anExpr);
    virtual bool setExprOnTrue(JCExpression *anExpr);
    virtual bool setExprOnFalse(JCExpression *anExpr);
    virtual bool isResolved(void);
    virtual void handleMute(JCExpression *before, JCExpression *after);
 };


class JCInitInvoke : public JCInvokeExpr {
  protected:
  public:
    JCInitInvoke(JCReferencedType *aType);
    virtual void mapToPool(ConstantsList *aPool);
    virtual void spitTo(JCCompilationContext *codeContext);
};


#if defined(PLZEN_LEVEL_2)

class JCStateInvokeExpr : public JCInvokeExpr {
  protected:
    unsigned int startLabel;
    unsigned int endLabel;

  public:		// Instance methods.
    JCStateInvokeExpr(void);

    virtual void setName(JCIdentifier *aName);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void setLabels(unsigned int start, unsigned int end);
    virtual void getLabels(unsigned int &start, unsigned int &end);
};

#endif

#if defined(PLZEN_LEVEL_3)

class JCExecSqlInvoke : public JCInvokeExpr {
  protected:
    JCCteExpr initialArgs[3];

  public:
    JCExecSqlInvoke(JCReferencedType *aType);
    virtual void useArguments(JCCteExpr *newArgs);
};

#endif
#endif	/* _EXPRESSIONS_H_ */
