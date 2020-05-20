#ifndef _SQLEXPRESSIONS_H_
#define _SQLEXPRESSIONS_H_
/**************************************************
* File: sqlExpressions.h.
* Desc: Definition of the JCSqlExpression hierarchy.
* Module: AkraLog : JavaKit.
* Rev: 2 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>
#include "sqlConstants.h"
#include "jvtypes.h"


class JCExpression;
class JCSqlIdentifier;
class JCIdentifier;
class JCSqlSelectList;
class JCSqlClause;
class JCSqlTableClause;
class SqlCompileContext;
class ConstantsList;
class JCCompilationContext;


class JCSqlExpression : public AkObject {
  public:
    enum Kind {
	kConstant, kEmbeddedVar, kSelect, kColumn, kOperation,
	kSynonym, kContainer, kList, kFunction, kFetchOrientation
	, kUnknown
    };

  protected:
    Kind kind;

  public:
    JCSqlExpression(void);
    JCSqlExpression(Kind aKind);
    virtual Kind getKind(void); 
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlSelect : public JCSqlExpression {
  protected:
    JCSqlConstants::SetQuantifier resultQuantifier;
    JCSqlSelectList *selectList;
    JCSqlTableClause *tableDef;

  public:		// Instance methods.
    JCSqlSelect(JCSqlSelectList *aList, JCSqlTableClause *tables);
    virtual void quantifySelection(JCSqlConstants::SetQuantifier aQuantification);
    virtual JCSqlSelectList *getSelectList(void);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlSynonym  : public JCSqlExpression {
  protected:
    JCSqlExpression *expression;
    JCSqlIdentifier *synonym;

  public:		// Instance methods.
    JCSqlSynonym(JCSqlExpression *anExpression, JCSqlIdentifier *anIdentifier);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlColumnExpr : public JCSqlExpression {
  protected:
    JCSqlIdentifier *column;

  public:
    JCSqlColumnExpr(JCSqlIdentifier *anIdent);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlEmbedded : public JCSqlExpression {
  protected:
     JCSqlEmbedded *next;
    JCExpression *javaExpr;
    JCExpression *javaIndicator;

  public:		// Instance methods.
    JCSqlEmbedded(JCExpression *anExpression);
    JCSqlEmbedded(JCExpression *anExpression, JCExpression *anIndicator);	// Defines an additional indicator.
    virtual void link(JCSqlEmbedded *anEmbedded);
    virtual JCSqlEmbedded *getNext(void);
    virtual void mapToPool(ConstantsList *aPool);
    virtual bool spitTo(SqlCompileContext *aContext);
    virtual void spitBCodeTo(JCCompilationContext *aContext);
    virtual void spitIntoReceiver(JCCompilationContext *aContext, JCExpression *aReceiver);
    virtual JCExpression *getExpression(void);
    virtual JCExpression *getIndicator(void);
};


class JCSqlContainerExpr : public JCSqlExpression {
  public:
    enum Operators {
	values, table
    };

 protected:	// Instance variables.
    void *containee;
    Operators operation;

  public:		// Instance methods.
    JCSqlContainerExpr(void *aValue, Operators anOperator);
    virtual bool spitTo(SqlCompileContext *aContext);
    virtual Operators getOperation(void);
    virtual void *getValue();
};


class JCSqlOperExpr : public JCSqlExpression {
  public:
    enum Operators {
	orOp, andOp, notOp,
	is, isnot,
	parenthesis,
	equal, notEqual,
	lt, gt, le, ge,
	between, notBetween,
	in, notIn,
	like, notLike,
	escape,
	eqAll, eqSome, eqAny,
	neAll, neSome, neAny,
	ltAll, ltSome, ltAny,
	gtAll, gtSome, gtAny,
	leAll, leSome, leAny,
	geAll, geSome, geAny,
	exists, unique, overlaps,
	match, matchUnique,
	matchPartial, matchFull, matchUniPartial, matchUniFull,
	add, substract, multiply, divide, posate, negate
	, userDefined
    };

  public:		// Class methods.
    static Operators mergeSetOperators(Operators anOp, JCSqlConstants::SetQuantifier quantifier);

  protected:	// Instance variables.
    JCSqlExpression *left, *right;
    Operators operation;

  public:		// Instance methods.
    JCSqlOperExpr(JCSqlExpression *leftOperand, JCSqlExpression *rightOperand, Operators anOperator);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlFunction : public JCSqlExpression {
  public:
    enum BuiltinFcts {
	countStar, avg, max, min, sum, count
	, nbrBuiltIn
	, customFunction		// Indicate that the function is not buit-in.
    };


  private:
    static JCSqlFunction *builtinFcts[nbrBuiltIn];

  private:		// Class methods.
    static void initBuiltinFunctions(void);
  public:
    static JCSqlFunction *getBuiltin(BuiltinFcts aFct);

  protected:	// Instance variables.
    BuiltinFcts function;
    JCSqlConstants::SetQuantifier operQuantifier;
    JCSqlExpression *operand;
    
  public:		// Instance methods.
    JCSqlFunction(void);
    virtual void setQuantifier(JCSqlConstants::SetQuantifier aQuantifier);
// ATTN: anOperand must be able to become a list of operands.
    virtual void setOperands(JCSqlExpression *anOperand);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlConstantExpr : public JCSqlExpression {
  public:
    enum Populars {
	popNullCte= 0, popDefaultCte,
	popUser, popCurrent, popSession, popSystem, popValue
	, nbrPopulars
    };
    enum Type {
	tSpecial, tEnumerated, tString, tChar, tReal, tInteger, tBoolean
    };

  protected:	// Class variables.
    static JCSqlConstantExpr *popularValues[nbrPopulars];

  public:		// Class methods.
    static JCSqlConstantExpr *getPopularConstant(Populars aPopular);

  protected:
    Type type;
    void *value;

  public:		// Instance methods.
    JCSqlConstantExpr(void);
    JCSqlConstantExpr(Type aType);
    virtual void setSpecial(Populars aPop);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlNumericCte : public JCSqlConstantExpr {
  public:
    JCSqlNumericCte(unsigned int anInt);
    JCSqlNumericCte(float aFloat);
    virtual void posate(void);
    virtual void negate(void);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlBoolCte : public JCSqlConstantExpr {
  public:
    JCSqlBoolCte(JCSqlConstants::TruthValues aValue);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlCharCte : public JCSqlConstantExpr {
  public:
    JCSqlCharCte(wchar *aCharArray);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlListExpr : public JCSqlExpression {
  protected:
    JCSqlClause *clause;

  public:
    JCSqlListExpr(JCSqlClause *aClause);
    virtual bool spitTo(SqlCompileContext *aContext);
};


class JCSqlFetchOrientation : public JCSqlExpression {
  public:
    enum Information {
	nbrSimpleOrientations= 5
    };

  private:		// Class variables.
    static JCSqlFetchOrientation *simpleOrientation[nbrSimpleOrientations];

  public:		// Class methods
    static JCSqlFetchOrientation *getSimpleOrientation(JCSqlConstants::FetchOrder anOrder);

  protected:		// Instance variables.
    JCSqlConstants::FetchOrder orientation;
    JCSqlExpression *baseValue;

  public:		// Instance methods.
    JCSqlFetchOrientation(void);
    JCSqlFetchOrientation(JCSqlConstants::FetchOrder anOrder, JCSqlExpression *anExpr);
    virtual bool spitTo(SqlCompileContext *aContext);
};


#endif		/* _SQLEXPRESSIONS_H_ */
