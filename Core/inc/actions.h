#ifndef _ACTIONS_H_
#define _ACTIONS_H_
/**************************************************
* File: actions.h.
* Desc: Contains the definitions of the classes used to contain actions
*	related syntaxic components.
*	JCActionBlock, JCAction.
* Module: AkraLog : JavaComp.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "containment.h"
#include "jvtypes.h"


// Type of actions.
// Plzen level 1 => Java.
#define EMPTY_STAT			1
#define LABELED_STAT		2
#define EXPRESSION_STAT	3
#define SELECTION_STAT		4
#define ITERATION_STAT		5
#define JUMP_STAT			6
#define GUARDING_STAT		7
#define BLOCK_STAT			8
#define VARDECL_STAT		9
#define IMPLIEDINIT_STAT		10


// Labeled subtypes.
#define IDENT_LABELED		(1<<8)
#define CASE_LABELED		(2<<8)
#define DEFAULT_LABELED	(3<<8)


// Expression subtypes.
#define ASSIGN_EXPRESSION		(1<<8)
#define PREINCR_EXPRESSION		(2<<8)
#define PREDECR_EXPRESSION	(3<<8)
#define POSTINCR_EXPRESSION	(4<<8)
#define POSTDECR_EXPRESSION	(5<<8)
#define INVOKE_EXPRESSION		(6<<8)
#define ALLOC_EXPRESSION		(7<<8)


// Selection subtypes.
#define IF_SELECTION				(1<<8)
#define IFELSE_SELECTION		(2<<8)
#define SWITCH_SELECTION		(3<<8)


// Iteration subtypes.
#define WHILE_ITERATION			(1<<8)
#define DO_ITERATION			(2<<8)
#define FOR_ITERATION			(3<<8)


// Jump subtypes.
#define BREAK_JUMP				(1<<8)
#define CONTINUE_JUMP			(2<<8)
#define RETURN_JUMP			(3<<8)
#define THROW_JUMP				(4<<8)


// Guarding subtypes.
#define SYNCH_GUARD			(1<<8)
#define TRYFINAL_GUARD			(2<<8)
#define TRYCATCH_GUARD		(3<<8)
#define TRYFULL_GUARD			(4<<8)


#if defined(PLZEN_LEVEL_2)

// Plzen level 2.
#define FSM_STAT			11


// Plzen level 2: MEF.
// FSM subtypes:
#define FIRE_PLZEN				(1 << 8)
#define WAIT_PLZEN				(2 << 8)

// Guarding subtypes.
#define CRITICAL_GUARD			(5 << 8)

#endif

#if defined(PLZEN_LEVEL_3)
// Plzen level 3: SQL-3.
#define SQL_STAT			12

#endif


class JCReferencedType;
class JCAction;
class JCExpression;
class JCVariableDeclaration;
class JCNameSpace;
class JCIdentifier;
class ConstantsList;
class JCMethod;
class JCCompilationContext;
class JCType;
class TransitionList;
class JCSqlStatement;
class JCExecSqlInvoke;
class JCPackage;


class JCActionBlock : public AkObject {
  protected:
    unsigned int totalNbrVars;
    unsigned int nbrLocalVars;
    JCAction *actions;
    JCNameSpace *nameSpace;
    bool isResolved;
    unsigned int startLine, endLine;

  public:
    JCActionBlock();
    virtual bool setContent(JCAction *aListHead);
    virtual JCAction *getContent(void);
    virtual bool setNameSpace(JCNameSpace *aNameSpace);
    virtual unsigned int getVarCount(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual unsigned int getLocalVarCount(void);
    virtual bool resolve(JCMethod *aMethod);
    virtual void setLineRange(unsigned int firstLine, unsigned int lastLine);
    virtual unsigned int getStartLine(void);
    virtual unsigned int getEndLine(void);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual bool resolutionStatus(void);
 };


// This class purpose is simply to store temporarely transitions while the
// grammar uploads them to the JCState context.

#if defined(PLZEN_LEVEL_2)

class JCStateActionBlock : public JCActionBlock {

  protected:	// Instance variables.
    TransitionList *transitions;

  public:
    virtual void setTransitions(TransitionList *aList);
    virtual TransitionList *getTransitions(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
};

#endif

class JCHandlingBlock : public JCActionBlock {
  protected:
    JCHandlingBlock *next;
    JCActionBlock *actionBlock;
    JCVariableDeclaration *trap;

  public:
    JCHandlingBlock();
    virtual void link(JCHandlingBlock *aBlock);
    virtual bool setTrap(JCVariableDeclaration *aDeclaration);
    virtual bool setHandler(JCActionBlock *aBlock);
    virtual unsigned int getVarCount(void);
    virtual JCHandlingBlock *getNext(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual JCVariableDeclaration *getTrap(void);
 };


class JCAction : public JCContainer {
    friend class JCActionBlock;
  public:	/* MOD-MSC: Change la protection a 'public' pour que LabelStat y ait acces (??). */
    JCAction *next;
    unsigned int actionType;
    bool isResolved;
    unsigned int nbrVariables;
    unsigned int startLine, endLine;
    JCAction *lastNext;		// MOD-971127 [HD]: Added to speed things up.

  public:
    JCAction();

    virtual unsigned int getContainerType(void);

    virtual void link(JCAction *anAction);
    virtual unsigned int getActionType(void);
    virtual JCAction *getNext(void);
    virtual unsigned int getVarCount(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual bool resolve(JCMethod *aMethod, JCActionBlock *aBlock);
    virtual void setLineRange(unsigned int firstLine, unsigned int lastLine);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual unsigned int getStartLine(void);
    virtual unsigned int getEndLine(void);
 };


class JCVarStat : public JCAction {
  protected:
    JCReferencedType  *baseType;
    JCVariableDeclaration *variables;
    bool hasInitializers;

  public:
    JCVarStat();
    virtual bool setTyping(JCReferencedType *aType);
    virtual bool setMembers(JCVariableDeclaration *varDeclarations);
    virtual JCVariableDeclaration *getMembers(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
 };


class JCStatement : public JCAction {
  protected:
    unsigned int subCategory;
    JCStatement *owner;
    JCStatement *subStatement;
    JCExpression *expressions;

  public:
    JCStatement();
    JCStatement(unsigned int aCategory);
    virtual bool setSubCategory(unsigned int aCategory);
    virtual bool setSubStatement(JCStatement *aStatement);
    virtual bool setSubExpression(JCExpression *aSubExpression);
    virtual unsigned int getVarCount(void);
    virtual bool resolve(JCMethod *aMethod, JCActionBlock *aBlock);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual unsigned int getSubCategory(void);
 };


class JCLabelStat : public JCStatement {
  protected:
    JCIdentifier *label;
    JCVarStat *varDeclaration;	// Variables declared in a CASE or DEFAULT statement.

  public:
    JCLabelStat();
    virtual bool setIdentifier(JCIdentifier *anIdent);
    virtual void setSubStatement(JCAction *anAction);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
 };


// Lists of JCExprStat are created by the init and incr part of the for iterator.
class JCExprStat : public JCStatement {
  protected:
  public:
    JCExprStat();
    virtual void spitTo(JCCompilationContext *codeContext);
 };


class JCSelectStat : public JCStatement {
  protected:
    JCStatement *falseStatement;

  public:
    JCSelectStat();
    virtual bool setFalseStatement(JCStatement *aStatement);
    virtual unsigned int getVarCount(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
 };


class JCSwitchStat : public JCSelectStat {
  protected:
    JCActionBlock *switchBlock;
    unsigned int nbrCases;

  public:
    JCSwitchStat();
    virtual bool setSwitchTable(JCActionBlock *aBlock, unsigned int aCount);
    virtual unsigned int getVarCount(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
};


class JCIterStat : public JCStatement {
  protected:
    JCAction *initActions;	// These are local var declarations or EXPRESSION_STAT.
    JCAction *loopActions;	// These are EXPRESSION_STAT.
    JCNameSpace *nameSpace;	// Local name space, for FOR iterator.

  public:
    JCIterStat();
    virtual bool setForInit(JCAction *actionList);
    virtual bool setLoopExpression(JCAction *actionList);
    virtual bool setNameSpace(JCNameSpace *aNameSpace);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
 };


class JCJumpStat : public JCStatement {
  protected:
    JCIdentifier *label;

  public:
    JCJumpStat();
    virtual bool setIdentifier(JCIdentifier *anIdent);
    virtual void spitTo(JCCompilationContext *codeContext);
 };


class JCGuardStat : public JCStatement {
  protected:
    JCActionBlock *guardedSection;		// The try section.
    JCActionBlock *mandatorySection;		// The finally section.
    JCHandlingBlock *handlers;			// list of catch sections.

  public:
    JCGuardStat();
    virtual bool setGuardedBlock(JCActionBlock *aBlock);
    virtual bool setMandatoryBlock(JCActionBlock *aBlock);
    virtual void setHandlingBlocks(JCHandlingBlock *someBlock);
    virtual unsigned int getVarCount(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
 };


class JCBlockStat : public JCStatement {
  protected:
    JCActionBlock *subBlock;

  public:
    JCBlockStat();
    virtual bool setSubBlock(JCActionBlock *aBlock);
    virtual JCActionBlock *getSubBlock(void);
    virtual unsigned int getVarCount(void);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
 };


// TODO.  Le travail de cette action est de faire l'initialisation de toutes
// les variables d'instances qui contiennent un 'initializer', juste apres l'appel
// au super-constructeur d'un nouvel objet.
class JCImpliedInitialization : public JCStatement {
  protected:
    JCType *container;

  public:
    JCImpliedInitialization(JCType *aType);
};


#if defined(PLZEN_LEVEL_2)
class JCFireStat : public JCStatement {
  protected:	// Instance variables.
    JCExpression *receiver;		// ATTN: Should become a list.

  public:		// Instance methods.
    JCFireStat(void);
    virtual void setEvent(JCExpression *anEvent);
    virtual void setDestination(JCExpression *aDestination);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
};
#endif	/* PLZEN_LEVEL_2 */

#if defined(PLZEN_LEVEL_3)


class JCMetaSqlStatement : public JCStatement {
  protected:
    static JCExecSqlInvoke *execInvoker;
    static JCReferencedType *pipeType;

  protected:
    static void initMetaSql(void);

  protected:	// Instance variables.
    bool activeFlag;
    JCAction *sqlAction;
    JCExpression *pipeContext;

  public:		// Instance methods.
    JCMetaSqlStatement(void);
    JCMetaSqlStatement(JCAction *anAction);
    virtual void makeDeclarative(void);
    virtual void setPipeContext(JCExpression *aCtxt);
    virtual void mapToPool(ConstantsList *aPool, unsigned int varIndexOffset);
    virtual void spitTo(JCCompilationContext *codeContext);
    virtual void bindToPackage(JCPackage *aPackage); 
};

#endif	/* PLZEN_LEVEL_3 */

#endif	/* _ACTIONS_H_ */
