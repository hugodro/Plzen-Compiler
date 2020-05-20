/**************************************************
* File: actions.cc.
* Desc: .
* Module: AkraLog : JavaComp.
* Rev: 5 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include "typing.h"
#include "variables.h"
#include "expressions.h"
#include "package.h"
#include "nameSpace.h"
#include "lists.h"
#include "identifiers.h"
#include "compiler.h"
#include "compContext.h"
#include "instructions.h"
#include "labelStack.h"
#include "outConstant.h"
#include "sqlActions.h"
#include "actions.h"


// ATTENTION: We must find a better way to deal with reaching the current package.
extern JCPackage *thePackage;


/**************************************************
* Implementation: JCActionBlock.
**************************************************/

JCActionBlock::JCActionBlock()
{
    totalNbrVars= nbrLocalVars= 0;
    actions= NULL;
}


bool JCActionBlock::setContent(JCAction *aListHead)
{
    unsigned int maxVar= 0;
    actions= aListHead;

	// Count usage of variables.
    while (aListHead != NULL) {
	if (aListHead->getActionType() == VARDECL_STAT) {
	    nbrLocalVars+= aListHead->getVarCount();
	}
	else {
	    if (aListHead->getVarCount() > maxVar) maxVar= aListHead->getVarCount();
	}
	aListHead= aListHead->getNext();
    }
    totalNbrVars+= maxVar + nbrLocalVars;

    return false;
}


JCAction *JCActionBlock::getContent(void)
{
    return actions;
}


bool JCActionBlock::setNameSpace(JCNameSpace *aNameSpace)
{
    nameSpace= aNameSpace;
    return false;
}


unsigned int JCActionBlock::getVarCount(void)
{
    return totalNbrVars;
}

unsigned int JCActionBlock:: getLocalVarCount(void)
{
    return nbrLocalVars;
}


void JCActionBlock::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCAction *tmpAction= actions;
    unsigned int localVarIndex= 0;

    while (tmpAction != NULL) {
	if (tmpAction->getActionType() == VARDECL_STAT) {    // Local Variable Declaration.
	    JCVariableDeclaration *tmpVarDecl;

	    tmpVarDecl= ((JCVarStat *)tmpAction)->getMembers();
	    do {
		tmpVarDecl->setIndex(varIndexOffset + localVarIndex++);
		if (tmpVarDecl->hasWideType()) localVarIndex++;
		tmpVarDecl= tmpVarDecl->getNext();
	    } while (tmpVarDecl != NULL);
	}
	tmpAction->mapToPool(aPool, nbrLocalVars + varIndexOffset);
	tmpAction= tmpAction->next;
    }
}


// ATTN: This it not called presently, all resolution is done from name space.
bool JCActionBlock::resolve(JCMethod *aMethod)
{
    JCAction *tmpAction= actions;
    unsigned int varIndex= aMethod->getNbrArguments();

    if (isResolved) return true;		// Warning: quick exit.

    while (tmpAction != NULL) {
	if (tmpAction->getActionType() == VARDECL_STAT) {    // Local Variable Declaration.
	    JCVariableDeclaration *tmpVarDecl;
	    tmpVarDecl= ((JCVarStat *)tmpAction)->getMembers();
	    do {
		if (!tmpVarDecl->isResolved()) {
		    cout << "ERRMSG: local variable " << tmpVarDecl->getUndimIdentifier()->getAsciiValue();
		    cout << " has unknown type " << tmpVarDecl->getTypeName()->getAsciiValue() << ".\n";
		    isResolved= false;
		}
		tmpVarDecl->setIndex(varIndex++);
		if (tmpVarDecl->hasWideType()) varIndex++;
		tmpVarDecl= tmpVarDecl->getNext();
	    } while (tmpVarDecl != NULL);
	}
	else {
	    if (!tmpAction->resolve(aMethod, this)) isResolved= false;
	}
	tmpAction= tmpAction->next;
    }
    return isResolved;
}


void JCActionBlock::setLineRange(unsigned int firstLine, unsigned int lastLine)
{
    startLine= firstLine;
    endLine= lastLine;
}


unsigned int JCActionBlock::getStartLine(void)
{
    return startLine;
}


unsigned int JCActionBlock::getEndLine(void)
{
    return endLine;
}


void JCActionBlock::spitTo(JCCompilationContext *codeContext)
{
    JCAction *tmpAction;
    if ((tmpAction= actions) != NULL) {
	do {
	    tmpAction->spitTo(codeContext);
	    tmpAction= tmpAction->next;
	} while (tmpAction != NULL);
    }
}


bool JCActionBlock::resolutionStatus(void)
{
    return isResolved;
}


/**************************************************
* Implementation: JCStateActionBlock.
**************************************************/

void JCStateActionBlock::setTransitions(TransitionList *aList)
{
    transitions= aList;
}


TransitionList *JCStateActionBlock::getTransitions(void)
{
    return transitions;
}

void JCStateActionBlock::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCActionBlock::mapToPool(aPool, varIndexOffset);

    for (unsigned int i= 0; i < transitions->count(); i++) {
	transitions->objectAt(i)->mapToPool(aPool);
    }
}


/**************************************************
* Implementation: JCHandlingBlock.
**************************************************/

JCHandlingBlock::JCHandlingBlock()
{
    next= NULL;
    actionBlock= NULL;
    trap= NULL;
}

void JCHandlingBlock::link(JCHandlingBlock *aBlock)
{
    if (next == NULL) next= aBlock;
    else {
	JCHandlingBlock *tmpNext= next;
	while (tmpNext->next != NULL) tmpNext= tmpNext->next;
	tmpNext->next= aBlock;
     }
}


bool JCHandlingBlock::setTrap(JCVariableDeclaration *aDeclaration)
{
    trap= aDeclaration;
    return false;
}


bool JCHandlingBlock::setHandler(JCActionBlock *aBlock)
{
    actionBlock= aBlock;
    return false;
}


unsigned int JCHandlingBlock::getVarCount(void)
{
    return 1 + actionBlock->getVarCount();
}


JCHandlingBlock *JCHandlingBlock::getNext(void)
{
    return next;
}


void JCHandlingBlock::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    trap->mapToPool(aPool);		// This variable is assigned when there is an exception.
    actionBlock->mapToPool(aPool, 1 + varIndexOffset);
}


void JCHandlingBlock::spitTo(JCCompilationContext *codeContext)
{
    // TODO.
}


JCVariableDeclaration *JCHandlingBlock::getTrap(void)
{
    return trap;
}


/**************************************************
* Implementation: JCAction.
**************************************************/

JCAction::JCAction()
{
    next= NULL;
    actionType= 0;
    isResolved= true;	// If nothing else happens, the action is resolved.
    nbrVariables= 0;
    lastNext= NULL;
}


unsigned int JCAction::getContainerType(void)
{
    return (unsigned int)JCContainer::action;
}


void JCAction::link(JCAction *anAction)
{
    if (next == NULL) lastNext= next= anAction;
    else {
/*
	JCAction *tmpNext= next;
	while (tmpNext->next != NULL) tmpNext= tmpNext->next;
	tmpNext->next= anAction;
*/
	lastNext->next= anAction;
	lastNext= anAction;
     }
}


unsigned int JCAction::getActionType(void)
{
    return actionType;
}


JCAction *JCAction::getNext(void)
{
    return next;
}


unsigned int JCAction::getVarCount(void)
{
    return nbrVariables;
}


// ATTN: This it not called presently, all resolution is done from name space.
bool JCAction::resolve(JCMethod *aMethod, JCActionBlock *aBlock)
{
    // TODO.
    return true;    /* MOD-MSC. */
}

void JCAction::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    // Must be implemented by subclasses.
    cout << "ERRMSG: generic JCAction::mapToPool called.\n";
}


void JCAction::setLineRange(unsigned int firstLine, unsigned int lastLine)
{
    startLine= firstLine;
    endLine= lastLine;
}


void JCAction::spitTo(JCCompilationContext *codeContext)
{
    // TODO. ATTN-970513 [HD]: Anything to do here ?
}


unsigned int JCAction::getStartLine(void)
{
    return startLine;
}


unsigned int JCAction::getEndLine(void)
{
    return endLine;
}


/**************************************************
* Implementation: JCVarStat.
**************************************************/

JCVarStat::JCVarStat()
{
    baseType= NULL;
    variables= NULL;
    actionType= VARDECL_STAT;
    hasInitializers= false;
    nbrVariables= 0;
}


bool JCVarStat::setTyping(JCReferencedType *aType)
{
    baseType= aType;
    return false;
}


bool JCVarStat::setMembers(JCVariableDeclaration *varDeclarations)
{
    JCVariableDeclaration *tmpVarDecl;
    JCUnresolved *unknown;

    variables= varDeclarations;

	// Declare the variables in the current name space.
    tmpVarDecl= varDeclarations;
    while (tmpVarDecl != NULL) {
	if (!thePackage->defineLocalVariable(tmpVarDecl->getUndimIdentifier(), tmpVarDecl)) {
	    cout << "ERRMSG: Already defined variable name: " << tmpVarDecl->getUndimIdentifier()->getAsciiValue();
	    cout << ".\n";
	 }
	else {
	    JCExpression *anInit;
	    nbrVariables++;
	    if ((anInit= tmpVarDecl->getInitializer()) != NULL) {
		hasInitializers= true;
		anInit->setOwner(this);
	    }
	    if (tmpVarDecl->hasComplexType()) {
		if (!thePackage->bind(tmpVarDecl->getTypeName(), tmpVarDecl->typing())) {
		    unknown=  thePackage->addUnknown(tmpVarDecl->typing());
		}
	    }
	}
	tmpVarDecl= tmpVarDecl->getNext();
     }

    return false;
}


JCVariableDeclaration *JCVarStat::getMembers(void)
{
    return variables;
}


void JCVarStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCVariableDeclaration *tmpVarDecl;
    JCExpression *tmpExpr;

	// If the option -g is on, we map the var, else we map it only if there is some initializers.
    if (/* includeVarDebug */ 0) if (!hasInitializers) return;	// Warning: quick exit.

    tmpVarDecl= variables;
    while (tmpVarDecl != NULL) {
	tmpVarDecl->mapToPool(aPool);
	if ((tmpExpr= tmpVarDecl->getInitializer()) != NULL) {
	    do {
		tmpExpr->mapToPool(aPool);
		tmpExpr= tmpExpr->getNext();
	    } while (tmpExpr);
	}
	tmpVarDecl= tmpVarDecl->getNext();
    }

}


void JCVarStat::spitTo(JCCompilationContext *codeContext)
{
    JCVariableDeclaration *tmpVarDecl;

    if (/* includeVarDebug */ 1 ) {
	codeContext->addVarInfo(variables);
    }

    if (hasInitializers) {
	JCExpression *tmpExpr, *tmpOwner= new JCExpression();

	tmpVarDecl= variables;
	while (tmpVarDecl != NULL) {
	    if ((tmpExpr= tmpVarDecl->getInitializer()) != NULL) {
		if (tmpVarDecl->typing()->isArray()) {
		    unsigned int i= 0;

		    do {
			tmpExpr->setOwner(tmpOwner);
			tmpExpr->spitTo(codeContext);
			tmpExpr->setOwner(NULL);
			JCAssignExpr::spitAssignmentFor(codeContext, tmpVarDecl, i);
			tmpExpr= tmpExpr->getNext();
			i++;
		    } while (tmpExpr);
		}
		else {
		    tmpExpr->setOwner(tmpOwner);
		    tmpExpr->spitTo(codeContext);
		    tmpExpr->setOwner(NULL);
		    JCAssignExpr::spitAssignmentFor(codeContext, tmpVarDecl);
		}
	    }
	    tmpVarDecl= tmpVarDecl->getNext();
	}
	delete tmpOwner;
   }
    else {
	// ATTN: Is it necessary to reset the local var. content ?
    }

}


/**************************************************
* Implementation: JCStatement.
**************************************************/

JCStatement::JCStatement()
{
    subCategory= 0;
    subStatement= NULL;
    expressions= NULL;
    actionType= EMPTY_STAT;
    nbrVariables= 0;
}


JCStatement::JCStatement(unsigned int aCategory)
{
    subCategory= 0;
    subStatement= NULL;
    expressions= NULL;
    actionType= aCategory;
    nbrVariables= 0;
}


bool JCStatement::setSubCategory(unsigned int aCategory)
{
    subCategory= aCategory;
    return false;
}


bool JCStatement::setSubStatement(JCStatement *aStatement)
{
    subStatement= aStatement;

    if (subStatement) {
	JCStatement *tmpStatement= subStatement;
	    // Chaining should occur only in EXPR_STAT sub-category.
	while (tmpStatement != NULL) {
	    tmpStatement->owner= this;
	    isResolved &= tmpStatement->isResolved;
	    nbrVariables+= tmpStatement->getVarCount();

	    tmpStatement= (JCStatement *)tmpStatement->next;
	}
    }
    return false;
}


bool JCStatement::setSubExpression(JCExpression *aSubExpression)
{

// ATTN: Must the expressions know the statement which owns them ?
// ATTN: Must scan the expressions to find out if we are 'resolved'.

    expressions= aSubExpression;
    aSubExpression->setOwner(this);
/* ATTN: Must make sure that an expression can not define variables.
    if (aSubExpression != NULL) {
	unsigned int maxVars= 0;
	do {
	    if (aSubExpression->getVarCount() > maxVars) maxVars= aSubExpression->getVarCount();
	    aSubExpression= aSubExpression->getNext();
	} while (aSubExpression != NULL);
	nbrVariables+= maxVars;
    }
*/
    return false;
}


unsigned int JCStatement::getVarCount(void)
{
    return nbrVariables;
}


// ATTN: This it not called presently, all resolution is done from name space.
bool JCStatement::resolve(JCMethod *aMethod, JCActionBlock *aBlock)
{
    // ATTN: TMP-970108: this code is just to pass down a 'resolve' method.
    // Must decide on what is the correct meaning of 'resolved'.

    if (actionType != EMPTY_STAT) {
	if (subStatement != NULL) {
	    JCStatement *tmpStatement= subStatement;
	    bool tmpReso= true;

	    while (tmpStatement != NULL) {
		tmpReso&= tmpStatement->resolve(aMethod, aBlock);
		tmpStatement= (JCStatement *)tmpStatement->next;
	    }
	    isResolved&= tmpReso;
	}
    }
    return isResolved;
}


void JCStatement::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    if (actionType != EMPTY_STAT) {
	if (subStatement != NULL) {
		// Chaining should occur only on EXPR_STAT subCategory.
	    JCStatement *tmpStatement= subStatement;
	    while (tmpStatement != NULL) {
		tmpStatement->mapToPool(aPool, varIndexOffset);
		tmpStatement= (JCStatement *)tmpStatement->next;
	    }
	}
	JCExpression *tmpExpr= expressions;
	while (tmpExpr != NULL) {
	    tmpExpr->mapToPool(aPool);
	    tmpExpr= tmpExpr->getNext();
	}
    }
}


void JCStatement::spitTo(JCCompilationContext *codeContext)
{
    // TODO.	ATTN-970513 [HD]: Anything to do here.
}


unsigned int JCStatement::getSubCategory(void)
{
    return subCategory;
}


/**************************************************
* Implementation: JCLabelStat.
**************************************************/

JCLabelStat::JCLabelStat() : JCStatement(LABELED_STAT)
{
    label= NULL;
    varDeclaration= NULL;
}


bool JCLabelStat::setIdentifier(JCIdentifier *anIdent)
{
    label= anIdent;
    return false;
}


void JCLabelStat::setSubStatement(JCAction *anAction)
{
    if (anAction->getActionType() == VARDECL_STAT) {
	varDeclaration= (JCVarStat *)anAction;
     }
    else {
	subStatement= (JCStatement *)anAction;
     }
    nbrVariables+= anAction->getVarCount();
    isResolved &= anAction->isResolved;
}


void JCLabelStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    if (varDeclaration != NULL) {
	varDeclaration->mapToPool(aPool, varIndexOffset);
    }
   JCStatement::mapToPool(aPool, varIndexOffset);
}


void JCLabelStat::spitTo(JCCompilationContext *codeContext)
{
    // TODO.
    switch(subCategory) {
	case IDENT_LABELED:		// Defines a named label.
	    codeContext->defineNamedLabel(label);
	    break;
	case CASE_LABELED:		// Defines a constant expression address label.
	    codeContext->defineCaseLabel(expressions);
	    break;
	case DEFAULT_LABELED:	// Defines address label n.
	    codeContext->defineDefaultLabel();
	    break;
	default:		// Internal error.
	    break;
    }

}


/**************************************************
* Implementation: JCExprStat.
**************************************************/

JCExprStat::JCExprStat() : JCStatement(EXPRESSION_STAT)
{
}


void JCExprStat::spitTo(JCCompilationContext *codeContext)
{
   expressions->spitTo(codeContext);
}


/**************************************************
* Implementation: JCSelectStat.
**************************************************/

JCSelectStat::JCSelectStat() : JCStatement(SELECTION_STAT)
{
    falseStatement= NULL;
}


bool JCSelectStat::setFalseStatement(JCStatement *aStatement)
{
    falseStatement= aStatement;
    isResolved &= aStatement->isResolved;
    return false;
}


unsigned int JCSelectStat::getVarCount(void)
{
    if (subCategory == IFELSE_SELECTION) {
	unsigned int maxVars= 0;
	if (subStatement != NULL) maxVars= subStatement->getVarCount();
	if (falseStatement != NULL) {
	    if (falseStatement->getVarCount() > maxVars) {
		maxVars= falseStatement->getVarCount();
	    }
	}
	return maxVars;
    }
   else return JCStatement::getVarCount();
}


void JCSelectStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    if (falseStatement != NULL) {
	falseStatement->mapToPool(aPool, varIndexOffset);
    }
   JCStatement::mapToPool(aPool, varIndexOffset);
}


void JCSelectStat::spitTo(JCCompilationContext *codeContext)
{
    unsigned int labelID;

    labelID= codeContext->getLabelBlock(3, JCAddressLabel::ifType);
    expressions->spitToAsFalseTest(codeContext, labelID+1, labelID+2, false);
    codeContext->defineLabel(labelID+1);
    subStatement->spitTo(codeContext);

    if (subCategory == IFELSE_SELECTION) {
	codeContext->addInstruction(JCInstrSet::goto_n, labelID);
	codeContext->defineLabel(labelID+2);
	falseStatement->spitTo(codeContext);
    }
    else {
	codeContext->defineLabel(labelID+2);
    }
    codeContext->defineLabel(labelID);
    codeContext->deleteLabelBlock(3);
}


/**************************************************
* Implementation: JCSwitchStat.
**************************************************/

JCSwitchStat::JCSwitchStat() : JCSelectStat()
{
    switchBlock= NULL;
    nbrCases= 0;
    subCategory= SWITCH_SELECTION;
}


bool JCSwitchStat::setSwitchTable(JCActionBlock *aBlock, unsigned int aCount)
{
	// ATTN: Must scan the action block to find out if we are 'resolved'.
    switchBlock= NULL;
    nbrCases= aCount;
    return false;
}


unsigned int JCSwitchStat::getVarCount(void)
{
    if (switchBlock != NULL) return switchBlock->getVarCount();
    else return 0;
}


void JCSwitchStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    if (switchBlock != NULL) {
	switchBlock->mapToPool(aPool, varIndexOffset);
    }
    JCSelectStat::mapToPool(aPool, varIndexOffset);
}


void JCSwitchStat::spitTo(JCCompilationContext *codeContext)
{
    //TODO.
}


/**************************************************
* Implementation: JCIterStat.
**************************************************/

JCIterStat::JCIterStat() : JCStatement(ITERATION_STAT)
{
    initActions= loopActions= NULL;
}


bool JCIterStat::setForInit(JCAction *actionList)
{
    initActions= actionList;

    while (actionList) {
	if (actionList->getActionType() == VARDECL_STAT) {
	    nbrVariables+= actionList->getVarCount();
	}
	actionList= actionList->getNext();
    }

    // ATTN: Must scan the action block to find out if we are 'resolved'.
    return false;
}


bool JCIterStat::setLoopExpression(JCAction *actionList)
{
    loopActions= actionList;
    // ATTN: Must scan the action block to find out if we are 'resolved'.
    return false;
}


bool JCIterStat::setNameSpace(JCNameSpace *aNameSpace)
{
    nameSpace= aNameSpace;
    return false;
}


void JCIterStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCAction *tmpAction;
    unsigned int nbrLocalDecl= 0;

    tmpAction= initActions;
    while (tmpAction != NULL) {
	if (tmpAction->getActionType() == VARDECL_STAT) {    // Local Variable Declaration.
	    JCVariableDeclaration *tmpVarDecl;

	    tmpVarDecl= ((JCVarStat *)tmpAction)->getMembers();
	    do {
		tmpVarDecl->setIndex(varIndexOffset + nbrLocalDecl++);
		if (tmpVarDecl->hasWideType()) nbrLocalDecl++;
		tmpVarDecl= tmpVarDecl->getNext();
	    } while (tmpVarDecl != NULL);
	}
	tmpAction->mapToPool(aPool, varIndexOffset);
	tmpAction= tmpAction->next;
    }

    tmpAction= loopActions;
    while (tmpAction != NULL) {
	tmpAction->mapToPool(aPool, varIndexOffset+nbrLocalDecl);
	tmpAction= tmpAction->next;
    }

   JCStatement::mapToPool(aPool, varIndexOffset+nbrLocalDecl);
}


void JCIterStat::spitTo(JCCompilationContext *codeContext)
{
    unsigned int labelID;
   
    if (subCategory == FOR_ITERATION) {
	JCAction *tmpAction;

	labelID= codeContext->getLabelBlock(5, JCAddressLabel::forType);
	codeContext->defineLabel(labelID+4);		// Code start of the whole thing, for var life info.

	if ((tmpAction= initActions) != NULL) {
	    do {
		if (tmpAction->actionType == VARDECL_STAT) {
		    ((JCVarStat *)tmpAction)->spitTo(codeContext);
		}
		else {
		    tmpAction->spitTo(codeContext);
		}

		tmpAction= tmpAction->next;
	    } while (tmpAction != NULL);
	}

	// for initExpr, [1] loopBlock, [2] loopIter, [3] loopTest [0];
	// 	break: va a 0; continue: va a 2; loopTest(true) va a 1.
	codeContext->addInstruction(JCInstrSet::goto_n, labelID+3);
	codeContext->defineLabel(labelID+1);
	subStatement->spitTo(codeContext);
	codeContext->defineLabel(labelID+2);

	if ((tmpAction= loopActions) != NULL) {
	    do {
		tmpAction->spitTo(codeContext);
		tmpAction= tmpAction->next;
	    } while (tmpAction != NULL);
	}
	codeContext->defineLabel(labelID+3);
	expressions->spitToAsTrueTest(codeContext, labelID+1, labelID, false);
    }
    else {
	if (subCategory == WHILE_ITERATION) {
	    labelID= codeContext->getLabelBlock(3, JCAddressLabel::whileType);
		// while [2] loopTest [1] loopBlock goto 2  [0].
		// 	break: va a 0; continue: va a 2; loopTest(false) va a 0.
	    codeContext->defineLabel(labelID+2);
	    expressions->spitToAsFalseTest(codeContext, labelID+1, labelID, false);
	    codeContext->defineLabel(labelID+1);		// Useless.
	    subStatement->spitTo(codeContext);
	    codeContext->addInstruction(JCInstrSet::goto_n, labelID+2);
	}
	else if (subCategory == DO_ITERATION) {
	    labelID= codeContext->getLabelBlock(3, JCAddressLabel::doType);
		// do [1] loopBlock while [2] loopTest if true goto 1 [0].
		// 	break: va a 0; continue: va a 2; loopTest(true) va a 1.
	    codeContext->defineLabel(labelID+1);
	    subStatement->spitTo(codeContext);
	    codeContext->defineLabel(labelID+2);
	    expressions->spitToAsTrueTest(codeContext, labelID+1, labelID, false);
	}
    }
    codeContext->defineLabel(labelID);
    codeContext->deleteLabelBlock((subCategory == FOR_ITERATION) ? 5 : 3);
}


/**************************************************
* Implementation: JCJumpStat.
**************************************************/

JCJumpStat::JCJumpStat() : JCStatement(JUMP_STAT)
{
    label= NULL;
}


bool JCJumpStat::setIdentifier(JCIdentifier *anIdent)
{
    label= anIdent;
    return false;
}


void JCJumpStat::spitTo(JCCompilationContext *codeContext)
{
    JCReferencedType *resultType;

    switch(subCategory) {
	case BREAK_JUMP:
	    if (label != NULL) {
		codeContext->handleNamedBreak(label);
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::goto_n, codeContext->getLabel(JCAddressLabel::breakScan));
	    }
	    break;
	case CONTINUE_JUMP:
	    if (label != NULL) {
		codeContext->handleNamedContinue(label);
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::goto_n, codeContext->getLabel(JCAddressLabel::continueScan));
	    }
	    break;
	case RETURN_JUMP:
	    if (expressions != NULL) {
		expressions->spitTo(codeContext);
		resultType= expressions->getFinalType();
	    }
	    else resultType= NULL;
	    codeContext->addInstruction(JCInstrSet::vreturn, resultType);
	    break;
	case THROW_JUMP:
	    if (expressions == NULL) {
		cout << "ERRMSG: throw with empty expression detected.\n";
	    }
	    else {
		expressions->spitTo(codeContext);
		codeContext->addInstruction(JCInstrSet::athrow);
	    }
	    // ATTN: Who has the responsability to build the 'finally' jumps.
	    break;
	default:		// Internal error.
	    cout << "ERRMSG: Internal error: unknown jump statement.\n";
	    break;
    }
}


/**************************************************
* Implementation: JCGuardStat.
**************************************************/

JCGuardStat::JCGuardStat() : JCStatement(GUARDING_STAT)
{
    guardedSection= mandatorySection= NULL;
    handlers= NULL;
}


bool JCGuardStat::setGuardedBlock(JCActionBlock *aBlock)
{
    guardedSection= aBlock;
    // ATTN: Must scan the action block to find out if we are 'resolved'.
    return false;
}


bool JCGuardStat::setMandatoryBlock(JCActionBlock *aBlock)
{
    JCHandlingBlock *ghostHandler;
    JCVariableDeclaration *ghostExceptVar;
    JCDimIdentifier *varDimIdent;
    JCIdentifier *varIdent;

    // ATTN: Must scan the action block to find out if we are 'resolved'.
    mandatorySection= aBlock;

	// Build the catch-it-all block for doing the 'finally' no matter what.
    varIdent= new JCIdentifier();
    varIdent->resolveToFinalCatcher();
    varDimIdent= new JCDimIdentifier();
    varDimIdent->setName(varIdent);
    ghostExceptVar= new JCVariableDeclaration();
    ghostExceptVar->setName(varDimIdent);
    ghostExceptVar->setTyping(JCReferencedType::getPopularType(JCReferencedType::popThrowable));
    ghostHandler= new JCHandlingBlock();
    ghostHandler->setTrap(ghostExceptVar);

	// Add the handler to the end of the list.
    if (handlers != NULL) {
	handlers->link(ghostHandler);
    }
    else {
	handlers= ghostHandler;
    }
    return false;
}


void JCGuardStat::setHandlingBlocks(JCHandlingBlock *someBlock)
{
    if ((handlers= someBlock) != NULL) {
	JCHandlingBlock *tmpHandler= handlers;

	do {
	    isResolved&= tmpHandler->resolutionStatus();
	    tmpHandler= tmpHandler->getNext();
	} while (tmpHandler != NULL);
    }
}


unsigned int JCGuardStat::getVarCount(void)
{
    if (subCategory == SYNCH_GUARD) {
	return JCStatement::getVarCount();
    }
#if defined(PLZEN_LEVEL_2)
    else if (subCategory == CRITICAL_GUARD) {
	return JCStatement::getVarCount();
    }
#endif
    else {
	if (guardedSection->getVarCount() > nbrVariables) {
	    nbrVariables= guardedSection->getVarCount();
	}
	if ((subCategory == TRYFINAL_GUARD) || (subCategory == TRYFULL_GUARD)) {
	    if (mandatorySection->getVarCount() > nbrVariables) {
		nbrVariables= mandatorySection->getVarCount();
	    }
	}
	if ((subCategory == TRYCATCH_GUARD) || (subCategory == TRYFULL_GUARD)) {
	    JCHandlingBlock *tmpHandler= handlers;
	    do {
		if (tmpHandler->getVarCount() > nbrVariables) {
		    nbrVariables= tmpHandler->getVarCount();
		}
		tmpHandler= tmpHandler->getNext();
	    } while (tmpHandler != NULL);
	}
	return nbrVariables;
    }
}


void JCGuardStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    if (subCategory == SYNCH_GUARD) {
	JCStatement::mapToPool(aPool, varIndexOffset);
    }
#if defined(PLZEN_LEVEL_2)
    else if (subCategory == CRITICAL_GUARD) {
	JCStatement::mapToPool(aPool, varIndexOffset);
    }
#endif
    else {
	guardedSection->mapToPool(aPool, varIndexOffset);
	if (mandatorySection != NULL)
	    mandatorySection->mapToPool(aPool, varIndexOffset);
	
	JCHandlingBlock *tmpHandler = handlers;
	while (tmpHandler != NULL) {
	    tmpHandler->mapToPool(aPool, varIndexOffset);
	    tmpHandler= tmpHandler->getNext();
	}

    }
}


void JCGuardStat::spitTo(JCCompilationContext *codeContext)
{
// TODO: 970127: check for correctness, and what else ?
    JCHandlingBlock *tmpHandler;
    unsigned int startPC, endPC;

    if (subCategory == SYNCH_GUARD) {
	expressions->spitTo(codeContext);
	codeContext->addInstruction(JCInstrSet::monitorenter);
	subStatement->spitTo(codeContext);
	codeContext->addInstruction(JCInstrSet::monitorexit);
    }
#if defined(PLZEN_LEVEL_2)
    else if (subCategory == CRITICAL_GUARD) {
	subStatement->spitTo(codeContext);
    }
#endif
    else {
	unsigned int labelID;

	labelID= codeContext->getLabelBlock(2, 
			(subCategory == TRYFINAL_GUARD) ? JCAddressLabel::tryFinalType
			: ((subCategory == TRYCATCH_GUARD) ? JCAddressLabel::tryCatchType
			: JCAddressLabel::tryFullType));
	if (mandatorySection != NULL) {
	    	// Indicate that {return, break, continue} must do a jsr to finally.
	    codeContext->startTryBlock();
	}
	startPC= codeContext->getCurrentPC();
	guardedSection->spitTo(codeContext);
	endPC= codeContext->getCurrentPC();
	if (mandatorySection != NULL) {
	    // emit a jsr to the finally section.
	    codeContext->addInstruction(JCInstrSet::jsr, labelID+1);
	}
	codeContext->addInstruction(JCInstrSet::goto_n, labelID);

	// Build catch blocks if there is any.
	if ((tmpHandler= handlers) != NULL) {
		// for each, build an attribute which is {startPC, endPC, handler_pc, catch_type}.
	    do {
		if (tmpHandler->getTrap()->getName()->getName()->isReserved()) {
			// We got the catch-it-all handler.
		    codeContext->startHandler(startPC, endPC, 0);
		    codeContext->addInstruction(JCInstrSet::istore, tmpHandler->getTrap()->getIndex());
		    codeContext->addInstruction(JCInstrSet::jsr, labelID+1);
		    codeContext->addInstruction(JCInstrSet::iload, tmpHandler->getTrap()->getIndex());
		    codeContext->addInstruction(JCInstrSet::athrow);    // Must rethrow...
		}
		else {
		    codeContext->startHandler(startPC, endPC, tmpHandler->getTrap());
		    tmpHandler->spitTo(codeContext);
		    codeContext->endHandler();
		    if (mandatorySection != NULL) {
			    // emit a jsr to the finally section.
			codeContext->addInstruction(JCInstrSet::jsr, labelID+1);
		    }
		    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
		}
		tmpHandler= tmpHandler->getNext();
	    } while (tmpHandler != NULL);
	}
    
	// Register finally blocks.
	if (mandatorySection != NULL) {
		// Tell the context that we have finished the try/catch part.
	    codeContext->endTryBlock();

	    // build a sub-routine with the finally section.
	    // Load top stack value into a local var.
	    // spit statement block.
	    // emit ret.
	    codeContext->defineLabel(labelID+1);
	    mandatorySection->spitTo(codeContext);
	}
	codeContext->defineLabel(labelID);
	codeContext->deleteLabelBlock(2);
    }
}


/**************************************************
* Implementation: JCBlockStat.
**************************************************/

JCBlockStat::JCBlockStat() : JCStatement(BLOCK_STAT)
{
    subBlock= NULL;
}


bool JCBlockStat::setSubBlock(JCActionBlock *aBlock)
{
    subBlock= aBlock;
    setLineRange(aBlock->getStartLine(), aBlock->getEndLine());
    // ATTN: Must scan the action block to find out if we are 'resolved'.
    return false;
}


JCActionBlock *JCBlockStat::getSubBlock(void)
{
    return subBlock;
}


unsigned int JCBlockStat::getVarCount(void)
{
    return subBlock->getVarCount();
}


void JCBlockStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    subBlock->mapToPool(aPool, varIndexOffset);
}


void JCBlockStat::spitTo(JCCompilationContext *codeContext)
{
    subBlock->spitTo(codeContext);
}


/**************************************************
* Implementation: JCImpliedInitialization.
**************************************************/

JCImpliedInitialization::JCImpliedInitialization(JCType *aType)
    : JCStatement(IMPLIEDINIT_STAT)
{
    container= aType;
}


#if defined(PLZEN_LEVEL_2)
/**************************************************
* Implementation: JCFireStat.
**************************************************/


JCFireStat::JCFireStat(void)
    : JCStatement(FSM_STAT)
{
    subCategory= FIRE_PLZEN;
    receiver= NULL;
}


void JCFireStat::setEvent(JCExpression *anEvent)
{
    expressions= anEvent;
    if (anEvent != NULL) anEvent->setOwner(this);
}


void JCFireStat::setDestination(JCExpression *aDestination)
{
    receiver= aDestination;
    if (aDestination != NULL) aDestination->setOwner(this);
}


void JCFireStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCStatement::mapToPool(aPool, varIndexOffset);
    if (receiver != NULL) receiver->mapToPool(aPool);
}


void JCFireStat::spitTo(JCCompilationContext *codeContext)
{
    JCField *aField;
	// First, object to receive the event.
    if (receiver != NULL) {
	receiver->spitTo(codeContext);
    }
    else {
	codeContext->addInstruction(JCInstrSet::aload_0);
    }

	// Then, event and var used as reference.
    switch(expressions->getCategory()) {
	case JCExpression::eVariable:
	    if (((JCVarAccess *)expressions)->resolution()->getCategory() == JCName::fieldVariable) {
		JCField *aField;

		aField= (JCField *)((JCResolved *)((JCVarAccess *)expressions)->resolution())->getDefinition();
		if (aField->isStatic())
		    codeContext->addInstruction(JCInstrSet::firestatic, aField->getShadow()->getIndex());
		else {
		    codeContext->addInstruction(JCInstrSet::firefield, aField->getShadow()->getIndex());
		}
	    }
	    else {		// ATTN: Should test if it is indeed a var.
		JCVariableDeclaration *aDecl;

		aDecl= (JCVariableDeclaration *)((JCResolved *)((JCVarAccess *)expressions)->resolution())->getDefinition();
		codeContext->addInstruction(JCInstrSet::fire, aDecl->getIndex());
	    }
	    break;
	case JCExpression::eField:
	    aField= (JCField *)((JCResolved *)((JCFieldAccess *)expressions)->resolution())->getDefinition();
	    if (aField->isStatic())
		codeContext->addInstruction(JCInstrSet::firestatic, aField->getShadow()->getIndex());
	    else {
		codeContext->addInstruction(JCInstrSet::firefield, aField->getShadow()->getIndex());
	    }
	    break;
    default:	// TODO: Signal error.
	break;
    }
}


#endif	/* PLZEN_LEVEL_2 */


#if defined(PLZEN_LEVEL_3)
/**************************************************
* Implementation: JCMetaSqlStatement.
**************************************************/

JCExecSqlInvoke *JCMetaSqlStatement::execInvoker= NULL;
JCReferencedType *JCMetaSqlStatement::pipeType= NULL;


void JCMetaSqlStatement::initMetaSql(void)
{
    char tmpName[]= { "DataPipe" };
    pipeType= new JCReferencedType(tmpName, 8);
    execInvoker= new JCExecSqlInvoke(pipeType);
}


JCMetaSqlStatement::JCMetaSqlStatement(void)
    : JCStatement(SQL_STAT)
{
    activeFlag= true;
    sqlAction= NULL;
    pipeContext= NULL;
}


JCMetaSqlStatement::JCMetaSqlStatement(JCAction *anAction)
    : JCStatement(SQL_STAT)
{
    activeFlag= true;
    sqlAction= anAction;
    pipeContext= NULL;
}


void JCMetaSqlStatement::makeDeclarative(void)
{
    activeFlag= false;
}


void JCMetaSqlStatement::setPipeContext(JCExpression *aCtxt)
{
    pipeContext= aCtxt;
}


void JCMetaSqlStatement::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCSqlStatement *actions= NULL;

    if (sqlAction != NULL) {
	if (pipeContext != NULL) {
	    pipeContext->mapToPool(aPool);
	}
	else {
	    // Spit the default context.
	}

	if (sqlAction->getActionType() == BLOCK_STAT) {
	    ((JCBlockStat *)sqlAction)->getSubBlock()->mapToPool(aPool, varIndexOffset);
	}
	else	if ((sqlAction->getActionType() & 255)== SQL_STAT) {
	    ((JCSqlStatement *)sqlAction)->mapToPool(aPool, varIndexOffset);
	}
	else {
	    cout << "ERRMSG: non-sql sqlAction in JCMetaSqlStatement::mapToPool.\n";
	}
    }

    execInvoker->mapToPool(aPool);
}


void JCMetaSqlStatement::spitTo(JCCompilationContext *codeContext)
{
    if (sqlAction != NULL) {
	JCSqlStatement *tmpAction;
	JCExpression *dbContext= NULL;
	JCOperExpr fakeHolder;
	unsigned int labelID;

	// TODO: 
	//	1- if context is functional, create a local variable, put into it the db transaction context.
	if (pipeContext != NULL) {
	    // TMPTMP:
	    dbContext= pipeContext;
	}
	else {
	    // Spit the default context.
	}


	if (sqlAction->getActionType() == BLOCK_STAT) {
	    tmpAction= (JCSqlStatement *)((JCBlockStat *)sqlAction)->getSubBlock()->getContent();
	}
	else	if ((sqlAction->getActionType() & 255)== SQL_STAT) {
	    tmpAction= (JCSqlStatement *)sqlAction;
	}
	else {
	    cout << "ERRMSG: non-sql subStatement in JCMetaSqlStatement::mapToPool.\n";
	}

	fakeHolder.setLeftOperand(execInvoker);

	while (tmpAction != NULL) {
	    //	    2- spit each sqlAction in the form:
	    //		- the hole values.
	    tmpAction->spitHolesTo(codeContext);

	    // TODO:
	    //		- a 'new Baril' call.
	    //		- token string (event. serialized Baril), # holes, # returned values.
	    //		- a call to 'Baril::<init>(String, int, int)=>(void)'.
	    //		- a call to 'Pipe::execSql(Baril)=>(boolean)'.

	    //		- the context to execute the action.

/*
	    if (dbContext != NULL) {
		dbContext->spitTo(codeContext);
	    }
*/
	    JCContainer *tmpOwner= dbContext->getOwner();
	    execInvoker->setSubExpression(dbContext);
	    tmpAction->attachInvoker(execInvoker);
	    execInvoker->spitTo(codeContext);
	    dbContext->setOwner(tmpOwner);

	    labelID= codeContext->getLabelBlock(2, JCAddressLabel::ifType);

	    //		- emit 't' postscriptum.
	    //		- emit 'f' postscriptum.
	    tmpAction->spitTruePostscriptum(codeContext, labelID+1);
	    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
	    codeContext->defineLabel(labelID+1);
	    tmpAction->spitFalsePostscriptum(codeContext);
	    codeContext->defineLabel(labelID);
	    codeContext->deleteLabelBlock(2);

	    tmpAction= (JCSqlStatement *)tmpAction->next;
	}
    }

}


void JCMetaSqlStatement::bindToPackage(JCPackage *aPackage)
{
    JCUnresolved *unknown;

    if (execInvoker == NULL) {
	initMetaSql();
    }
//    execInvoker->bindInLocalSpace(aPackage->getBottomNameSpace());
    if (!aPackage->bind(pipeType->getTypeName(), pipeType)) {
	unknown=  thePackage->addUnknown(pipeType);
    }
}


#endif		/* PLZEN_LEVEL_3 */
