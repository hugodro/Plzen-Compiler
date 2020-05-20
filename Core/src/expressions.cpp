/**************************************************
* File: expressions.cc.
* Desc: .
* Module: AkraLog : JavaComp.
* Rev: 5 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

/* MOD-MSC: Mis des casts pour quel le compilo accepte les changements de types.
*/

extern "C" {
#include <stdio.h>
#include <string.h>
};

#include <iostream.h>
#include "identifiers.h"
#include "variables.h"
#include "constants.h"
#include "package.h"
#include "nameSpace.h"
#include "lists.h"
#include "outConstant.h"
#include "compContext.h"
#include "instructions.h"
#include "compiler.h"
#include "expressions.h"


// ATTENTION: We must find a better way to deal with reaching the current package.
// extern JCPackage *thePackage: giving it instead as a parameter in 'bindInCurrentNameSpace'.


/**************************************************
* Implementation: JCExpression.
**************************************************/
JCExpression::JCExpression()
{
    category= eEmpty;
    next= NULL;
    owner= NULL;
    return;
}


JCExpression::JCExpression(ExprCategory aKind)
{
    category= aKind;
    next= NULL;
    owner= NULL;
    return;
}


unsigned int JCExpression::getContainerType(void)
{
    return (unsigned int)JCContainer::expression;
}


void JCExpression::linkExpression(JCExpression *nextMember)
{
    if (next == NULL) next= nextMember;
    else {
	JCExpression *tmpNext= next;
	while (tmpNext->next != NULL) tmpNext= tmpNext->next;
	tmpNext->next= nextMember;
     }

    return;
}


JCExpression::ExprCategory JCExpression::getCategory(void)
{
    return category;
}


#if defined(USE_OUTDATED_CODE)
bool JCExpression::setExprName(JCIdentifier *aName)
{
    JCUnresolved *unknown;

    name= aName;
    if (!aName->isReserved()) {
	if (!thePackage->bind(aName, this)) {
	    // The package didn't find any reference to the name, we will add it.
	    unknown= thePackage->addUnknown(this);
	 }
     }
    return false;
}
#endif


JCExpression *JCExpression::getNext(void)
{
    return next;
}


void JCExpression::mapToPool(ConstantsList *aPool)
{
    // ATTN: Maybe a warning message should be sent.
}


bool JCExpression::isResolved(void)
{
    return true;
}


void JCExpression::handleMute(JCExpression *before, JCExpression *after)
{
    // By default, do nothing.
}


JCReferencedType *JCExpression::getFinalType(void)
{
    return JCReferencedType::getPopularType(JCReferencedType::popVoid);
}


void JCExpression::typeUpdateChild(JCExpression *anExpression)
{
    // TODO: calcule le nouveau type de l'expression, a partir de l'information donnee par une
    // de ses sous-expressions (passee en argument), qui vient d'etre 'decidee'.
//    cout << "ERRMSG: Warning, using JCExpression::typeUpdateChild, still in construction.\n";
}


void JCExpression::typeUpdateOwner(void)
{
    // TODO: calcule le nouveau type du owner, a partir de l'information donnee par 
    // la sous-expression courante.
//    cout << "ERRMSG: Warning, using JCExpression::typeUpdateOwner, still in construction.\n";
	// TMP-970821 [HD]: Solution temporaire:
    if (owner != NULL) {
	if (owner->getContainerType() == (unsigned int)JCContainer::expression) {
	    ((JCExpression *)owner)->typeUpdateChild(this);
	}
    }
}


void JCExpression::setOwner(JCContainer *anOwner)
{
    owner= anOwner;
}


JCContainer *JCExpression::getOwner(void)
{
    return owner;
}


unsigned int JCExpression::getStartLine(void)
{
    if (owner != NULL) {
	return owner->getStartLine();
    }
    else return 0x0FFFFFFFF;
}


unsigned int JCExpression::getEndLine(void)
{
    if (owner != NULL) {
	return owner->getEndLine();
    }
    else return 0x0FFFFFFFF;
}


/**************************************************
* Implementation: JCBlockExpr.
**************************************************/

JCBlockExpr::JCBlockExpr() : JCExpression(eBlock)
{
    subExpressions= NULL;
}


void JCBlockExpr::setInternal(JCExpression *anExpression)
{
    subExpressions= anExpression;
    do {
	anExpression->owner= this;
	anExpression= anExpression->next;
    } while (anExpression != NULL);
    return;
}


void JCBlockExpr::mapToPool(ConstantsList *aPool)
{
    if (subExpressions) {
	JCExpression *tmpExpr= subExpressions;

	do {
	    tmpExpr->mapToPool(aPool);
	    tmpExpr= tmpExpr->next;
	} while (tmpExpr != NULL);
    }
}


void JCBlockExpr::handleMute(JCExpression *before, JCExpression *after)
{
    JCExpression *tmpExpr= subExpressions, *lastExpr;

	// A sub-expr call this, so there must be something in subExprssions;
    lastExpr= NULL;
    while (tmpExpr != NULL) {
	if (tmpExpr == before) {
	    if (lastExpr != NULL) lastExpr->next= after;
	    else subExpressions= after;
	    break;
	}
	lastExpr= tmpExpr;
	tmpExpr= tmpExpr->next;
    } 
}


JCReferencedType *JCBlockExpr::getFinalType(void)
{
    if (subExpressions) {
	return subExpressions->getFinalType();
    }
    else return JCExpression::getFinalType(); 
}


/**************************************************
* Implementation: JCCteExpr.
**************************************************/

JCCteExpr::JCCteExpr() : JCExpression(eConstant)
{
    typing= JCReferencedType::popVoid;
}


JCCteExpr::JCCteExpr(JCReferencedType::PopularType aBType)
{
    typing= aBType;
    category= eConstant;
    return;
}


void JCCteExpr::setBoolValue(bool aValue)
{
    shadow= (JCOutCFConstant *)aValue;
    typing= JCReferencedType::popBoolean;
}


void JCCteExpr::setCharValue(wchar *aValue)
{
   shadow= (JCOutCFConstant *)aValue;
    typing= JCReferencedType::popChar;
}


void JCCteExpr::setIntValue(int aValue)
{
    shadow= JCWord::addUnique(aValue);
    typing= JCReferencedType::popInteger;
}


void JCCteExpr::setIntZero(void)
{
    shadow= JCWord::getSpecialCte(JCWord::scIntZero);
}


void JCCteExpr::setIntOne(void)
{
    shadow= JCWord::getSpecialCte(JCWord::scIntOne);
}


void JCCteExpr::setIntMinusOne(void)
{
    shadow= JCWord::getSpecialCte(JCWord::scIntMinusOne);
}


void JCCteExpr::setFloatValue(float aValue)
{
    shadow= JCWord::addUnique(aValue);
    typing= JCReferencedType::popFloat;
}


void JCCteExpr::setFloatZero(void)
{
    shadow= JCWord::getSpecialCte(JCWord::scFloatZero);
}


void JCCteExpr::setFloatOne(void)
{
    shadow= JCWord::getSpecialCte(JCWord::scFloatOne);
}


void JCCteExpr::setFloatMinusOne(void)
{
    shadow= JCWord::getSpecialCte(JCWord::scFloatMinusOne);
}

 
void JCCteExpr::setLongValue(unsigned int *aValue)
{
    shadow= JCDoubleWord::addUnique(aValue);
    typing= JCReferencedType::popLong;
}


void JCCteExpr::setLongValue(unsigned int highBytes, unsigned int lowBytes)
{
    unsigned int tmpInt[2]= { lowBytes, highBytes };    
    shadow= JCDoubleWord::addUnique(tmpInt);
    typing= JCReferencedType::popLong;
}


void JCCteExpr::setLongZero(void)
{
    shadow= JCDoubleWord::getSpecialCte(JCDoubleWord::scLongZero);
}


void JCCteExpr::setLongOne(void)
{
    shadow= JCDoubleWord::getSpecialCte(JCDoubleWord::scLongOne);
}


void JCCteExpr::setLongMinusOne(void)
{
    shadow= JCDoubleWord::getSpecialCte(JCDoubleWord::scLongMinusOne);
}

 
void JCCteExpr::setDoubleValue(double aValue)
{
    shadow= JCDoubleWord::addUnique(aValue);
    typing= JCReferencedType::popDouble;
}


void JCCteExpr::setDoubleZero(void)
{
    shadow= JCDoubleWord::getSpecialCte(JCDoubleWord::scDoubleZero);
}


void JCCteExpr::setDoubleOne(void)
{
    shadow= JCDoubleWord::getSpecialCte(JCDoubleWord::scDoubleOne);
}


void JCCteExpr::setDoubleMinusOne(void)
{
    shadow= JCDoubleWord::getSpecialCte(JCDoubleWord::scDoubleMinusOne);
}

 
bool JCCteExpr::setStringValue(wchar *aValue)
{
    shadow= JCCteString::addUnique(JCCteUtf8::addUniqueInstance(aValue));
    typing= JCReferencedType::popString;
    return false;
}


int JCCteExpr::getIntValue(void)
{
    return ((JCCteInteger *)shadow)->intValue();
}


float JCCteExpr::getFloatValue(void)
{
    return ((JCCteFloat *)shadow)->floatValue();
}


unsigned int *JCCteExpr::getLongValue(void)
{
    static unsigned int tmpValue[2];		// ATTN: Not thread safe.

    ((JCCteLong *)shadow)->longValue((unsigned int *)tmpValue);
    return &tmpValue[0];
}


double JCCteExpr::getDoubleValue(void)
{
    return ((JCCteDouble *)shadow)->doubleValue();
}


void JCCteExpr::mapToPool(ConstantsList *aPool)
{
    if ((typing != JCReferencedType::popBoolean) && (typing != JCReferencedType::popChar) && (typing != JCReferencedType::popNullObject)) {
/* MOD-970821 [HD]: Changed the pattern to use the 'addToPool'.
	aPool->addIndexedObject(shadow);
*/
	if (typing != JCReferencedType::popInteger) {
	    shadow->addToPool(aPool);
	    JCCteUtf8::getWellKnownName(JCCteUtf8::constantValue)->addToPool(aPool);
	}
	else {
	    if ((getIntValue() < -32768) || (getIntValue() > 32767)) {
		shadow->addToPool(aPool);
		JCCteUtf8::getWellKnownName(JCCteUtf8::constantValue)->addToPool(aPool);
	    }
	}
    }
}


JCReferencedType *JCCteExpr::getFinalType(void)
{
    return JCReferencedType::getPopularType(typing);
}


void JCCteExpr::negate(void)
{
    // ATTN: Work only on numerical constant.
    if (typing == JCReferencedType::popInteger) {
	if (JCWord::isSpecialCte((JCWord *)shadow)) {
	    shadow= ((JCWord *)shadow)->arithmeticNegation();
	}
	else {
	    setIntValue(-1 * getIntValue());
	}
    }
    else if (typing == JCReferencedType::popFloat) {
	if (JCWord::isSpecialCte((JCWord *)shadow)) {
	    shadow= ((JCWord *)shadow)->arithmeticNegation();
	}
	else {
	    setFloatValue(-1.0 * getFloatValue());
	}
    }
    else if (typing == JCReferencedType::popLong) {
	if (JCDoubleWord::isSpecialCte((JCDoubleWord *)shadow)) {
	    shadow= ((JCDoubleWord *)shadow)->arithmeticNegation();
	}
	else {
	    unsigned int *oldValue= getLongValue();
	    // TODO: Must do a multiply by -1 on a Java long.
	    setLongValue(oldValue);
	}
    }
    else if (typing == JCReferencedType::popDouble) {
	if (JCDoubleWord::isSpecialCte((JCDoubleWord *)shadow)) {
	    shadow= ((JCDoubleWord *)shadow)->arithmeticNegation();
	}
	else {
	    setDoubleValue(getDoubleValue() * (double)-1.0);
	}
    }
}


bool JCCteExpr::isNullCte(void)
{
    if (typing == JCReferencedType::popNullObject) return true;
    else return false;
}


/**************************************************
* Implementation: JCNamedExpr.
**************************************************/

JCNamedExpr::JCNamedExpr(ExprCategory aCategory) : JCExpression(aCategory)
{
    name= NULL;
    subExpression= NULL;
}


JCNamedExpr::JCNamedExpr(ExprCategory aCategory, JCIdentifier *aName, JCName *aResolution) : JCExpression(aCategory)
{
    resolver= aResolution;
    name= aName;
    subExpression= NULL;
}


JCNamedExpr::JCNamedExpr(JCIdentifier *aName) : JCExpression(eUnknownName)
{
    name= aName;
    subExpression= NULL;
}


void JCNamedExpr::setName(JCIdentifier *aName)
{
    name= aName;
    // Is there any treatment to do at this point on the name ?
}


void JCNamedExpr::setSubExpression(JCExpression *anExpression)
{
    subExpression= anExpression;
    if (anExpression != NULL) anExpression->owner= this;
}


JCIdentifier *JCNamedExpr::getName(void)
{
    return name;
}


JCExpression *JCNamedExpr::getSubExpression(void)
{
    return subExpression;
}


void JCNamedExpr::setResolution(JCName *aResolver)
{
    resolver= aResolver;
}


JCName * JCNamedExpr::resolution(void)
{
    return resolver;
}


void JCNamedExpr::mapToPool(ConstantsList *aPool) {
    if (resolver != NULL) {
	if (resolver->getSituation() == JCName::resolved) {
	    JCType *aType;
	    JCMember *aMember;
	    JCVariableDeclaration *aDecl;

	    switch(resolver->getCategory()) {
		case JCName::uClass:
		case JCName::uInterface:
		    aType= (JCType *)((JCResolved *)resolver)->getDefinition();
		    aPool->addIndexedObject(aType->getShadow());
		    break;
		case JCName::localVariable:
		    aDecl= (JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition();
		    if (!aDecl->typing()->isPrimitive()) {
			if (aDecl->typing()->getTypeShadow() != NULL) {
			    aPool->addIndexedObject(aDecl->typing()->getTypeShadow());
			}
			else {
			    cout << "ERRMSG:  JCNamedExpr:mapToPool can't have the shadow of a local var type !\n";
			}
		    }
		    break;
		case JCName::fieldVariable:
		case JCName::uMethod:
		case JCName::uState:
		    aMember= (JCMember *)((JCResolved *)resolver)->getDefinition();
		    aMember->getShadow()->addToPool(aPool);
/* MOD-970529 [HD]: Replaced the addIndexedObject, because the signatures of unmentioned
*		super class was not included.
		    aMember= (JCMember *)((JCResolved *)resolver)->getDefinition();
		    aPool->addIndexedObject(aMember->getShadow());
*/
		    break;
		default:
		    cout << "ERRMSG:  JCNamedExpr:mapToPool dealing with unknown resolver ";
		    cout << "of type " << (int)resolver->getCategory() << " !\n";
		    break;
	    }
	}
	else {
	    cout << "ERRMSG:  JCNamedExpr:mapToPool has still an unresolved !\n";
	}
    }
    else {
	cout << "ERRMSG:  JCNamedExpr:mapToPool has no resolver to add !.\n";
    }
}


bool JCNamedExpr::isResolved(void)
{
    if (resolver != NULL) {
	return (resolver->getSituation() == JCName::resolved);
    }
    else {
	return false;
    }
}


void JCNamedExpr::bindInLocalSpace(JCNameSpace *aSpace)
{
    if (name->isReserved()) {
	cout << "ERRMSG: Reserved name appearing in a Named Expression.\n";
    }
    else {
	if (!aSpace->relateNamedExpr(this)) {
	    cout << "ERRMSG: JCNamedAccess " << name->getAsciiValue();
	    cout << " can't be related in any way !\n";
	}
     }
}


void JCNamedExpr::addBottomSubExpression(JCExpression *anExpression)
{
    if (subExpression == NULL) {
	subExpression= anExpression;
	anExpression->owner= this;
    }
    else {
	    // ATTN: Is this valid ??
	JCNamedExpr *tmpExpr= (JCNamedExpr *)subExpression;
	while (tmpExpr->subExpression != NULL) {
	    if ((tmpExpr->subExpression->category == eField)
		    || (tmpExpr->subExpression->category == eArray)
		    || (tmpExpr->subExpression->category == eInvoke)) {
		tmpExpr= (JCNamedExpr *)tmpExpr->subExpression;
	    }
	    else {
		cout << "ERRMSG: Can't add a subExpression.\n";
		break;
	    }
	}
	tmpExpr->subExpression= anExpression;
	anExpression->owner= tmpExpr->subExpression;
    }
}


JCExpression *JCNamedExpr::muteTo(ExprCategory aClearForm, JCName *someName)
{
    JCExpression *result= NULL;

    if (aClearForm == eVariable) {
	JCVarAccess *tmpResult= new JCVarAccess(name, someName);
	result= tmpResult;
    }
    else if (aClearForm == eField) {
	JCFieldAccess *tmpResult= new JCFieldAccess(name, someName);
	tmpResult->subExpression= subExpression;
// MOD-970611 [HD]: Added the backward link.
	if (subExpression != NULL) subExpression->owner= tmpResult;
	result= tmpResult;
    }
    else {
	 cout << "ERRMSG: JCNamedExpr::mute to " << (unsigned int)aClearForm << " not implemented.\n";
    }
    // ATTN: Can we mute to Invoke or ArrayAccess ???

    if (result != NULL) {
	result->next= next;

	if ((someName->getCategory() != JCName::uType) && (someName->getCategory() != JCName::uClass)
		&& (someName->getCategory() != JCName::uClass)) {
	    result->owner= owner;
	}
	else {
	    if (owner != NULL) {
		if (owner->getContainerType() == (unsigned int)JCContainer::expression) {
		    result->owner= ((JCExpression *)owner)->owner;
		}
	    }
	}
	if (result->owner != NULL) {
	    if (owner->getContainerType() == (unsigned int)JCContainer::expression) {
		((JCExpression *)owner)->handleMute(this, result);
	    }
	}
	// ATTN: Is this always OK ? Or can we get into a list ?
	delete this;
    }
    return result;
}


void JCNamedExpr::handleMute(JCExpression *before, JCExpression *after)
{
    subExpression= after;
}


JCReferencedType *JCNamedExpr::getFinalType(void)
{
    if (resolver->getSituation() == JCName::resolved) {
	switch(resolver->getCategory()) {
	    case JCName::uClass:
	    case JCName::uInterface:
		return ((JCType *)((JCResolved *)resolver)->getDefinition())->getRefEquivalent();
		break;
	    case JCName::localVariable:
		return ((JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition())->typing();
		break;
	    case JCName::fieldVariable:
	    case JCName::uMethod:
	    case JCName::uState:
		return ((JCMember *)((JCResolved *)resolver)->getDefinition())->getReturnedType();
		break;
	    default:
		cout << "ERRMSG:  JCNamedExpr:getFinalType dealing with unknown resolver ";
		cout << "of type " << (int)resolver->getCategory() << " !\n";
		break;
	}
    }
    else {
	cout << "ERRMSG: JCNamedExpr:getFinalType dealing with unresolved JCNameExpr.\n";
    }
    return JCReferencedType::getPopularType(JCReferencedType::popVoid);
}


/**************************************************
* Implementation: JCVarAccess.
**************************************************/

JCVarAccess::JCVarAccess(void) : JCExpression(eVariable)
{
    name= NULL;
}


JCVarAccess::JCVarAccess(JCIdentifier *aName, JCName *aResolution) : JCExpression(eVariable)
{
    name= aName;
    resolver= aResolution;
}


bool JCVarAccess::setVarName(JCIdentifier *aName)
{
    name= aName;
    return true;
}


JCIdentifier *JCVarAccess::getVarName(void)
{
    return name;
}


void JCVarAccess::setResolution(JCName *aResolver)
{
    resolver= aResolver;
    if (owner != NULL && (resolver->getSituation() == JCName::resolved)) {
	if (owner->getContainerType() == (unsigned int)JCContainer::expression) {
	    ((JCExpression *)owner)->typeUpdateChild(this);
	}
    }
}


JCName * JCVarAccess::resolution(void)
{
    return resolver;
}


void JCVarAccess::mapToPool(ConstantsList *aPool)
{
    if (resolver != NULL) {
	if (resolver->getSituation() == JCName::resolved) {
	    JCMember *aMember;
	    JCVariableDeclaration *aDecl;

	    switch(resolver->getCategory()) {
		case JCName::localVariable:
		    aDecl= (JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition();
		    if (!aDecl->typing()->isPrimitive()) {
			if (aDecl->typing()->getTypeShadow() != NULL) {
			    aPool->addIndexedObject(aDecl->typing()->getTypeShadow());
			}
			else {
			    cout << "ERRMSG:  JCVarAccess::mapToPool can't have the shadow of a local var type !\n";
			}
		    }
		    break;
		case JCName::fieldVariable:
		    aMember= (JCMember *)((JCResolved *)resolver)->getDefinition();
		    aMember->getShadow()->addToPool(aPool);
/* MOD-970529 [HD]: Replaced the addIndexedObject, because the signatures of unmentioned
*		super class was not included.
		    aPool->addIndexedObject(aMember->getShadow());
*/
		    break;
		default:
		    cout << "ERRMSG:  JCVarAccess::mapToPool dealing with unknown resolver ";
		    cout << "of type " << (int)resolver->getCategory() << " !\n";
		    break;
	    }
	}
	else {
	    cout << "ERRMSG:  JCVarAccess::mapToPool has still an unresolved !\n";
	}
    }
    else {
	cout << "ERRMSG:  JCVarAccess::mapToPool has no resolver to add !.\n";
    }
}


bool JCVarAccess::isResolved(void)
{
    if (resolver != NULL) {
	return (resolver->getSituation() == JCName::resolved);
    }
    else {
	return false;
    }
}


void JCVarAccess::bindInLocalSpace(JCNameSpace *aSpace)
{
    if (name->isReserved()) {
	switch(name->getSpecialName()) {
	    case JCIdentifier::snSuper:
		resolver= aSpace->getSuperVariable();
		break;
	    case JCIdentifier::snThis:
		resolver= aSpace->getThisVariable();
		break;
	    case JCIdentifier::snNull:
	    	// Should check that the 'null' name is only used in reference,
		// never in field/array/invoke access or as the receiver of an assignment.
		// ATTN: Must decide how to treat the 'null' identifier.
		break;
	    default:
		cout << "ERRMSG: unknown special name in JCNamedExpr::bindInLocalSpace.\n";
		return;
		break;
	}
    }
    else {
	if (!aSpace->relateSimpleVar(this)) {
	    cout << "ERRMSG: JCVarAccess " << name->getAsciiValue();
	    cout << " has composed name !\n";
	}
    }
}


JCReferencedType *JCVarAccess::getFinalType(void)
{
    if (resolver->getSituation() == JCName::resolved) {
	switch(resolver->getCategory()) {
	    case JCName::localVariable:
		return  ((JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition())->typing();
		break;
	    case JCName::fieldVariable:
		return ((JCField *)((JCResolved *)resolver)->getDefinition())->getReturnedType();
		break;
	    default:
		cout << "ERRMSG:  JCVarAccess::getFinalType dealing with unknown resolver ";
		cout << "of type " << (int)resolver->getCategory() << " !\n";
		break;
	}
    }
    else {
	cout << "ERRMSG: JCVarAccess:getFinalType dealing with unresolved JCNameExpr.\n";
    }
    return JCReferencedType::getPopularType(JCReferencedType::popVoid);
}


/**************************************************
* Implementation: JCFieldAccess.
**************************************************/

JCFieldAccess::JCFieldAccess(void) : JCNamedExpr(eField)
{
}


JCFieldAccess::JCFieldAccess(JCIdentifier *aName, JCName *aResolution) : JCNamedExpr(eField, aName, aResolution)
{
}

void JCFieldAccess::mapToPool(ConstantsList *aPool)
{
    if (subExpression != NULL) {	// This field is not a local one, must map its source.
	JCMember * aMember= (JCMember *)((JCResolved *)resolver)->getDefinition();
	aMember->mapToPool(aPool);
    }
    JCNamedExpr::mapToPool(aPool);
    if (subExpression != NULL) {
	subExpression->mapToPool(aPool);
    }
}


/**************************************************
* Implementation: JCArrayAccess.
**************************************************/

JCArrayAccess::JCArrayAccess() : JCNamedExpr(eArray)
{
    valueOffset= NULL;
    nbrOffsets= 0;
    accessType= NULL;
}


bool JCArrayAccess::addDimensionOffset(JCExpression *offset)
{
    offset->owner= this;
	// Link the offsets.
    nbrOffsets++;
    if (valueOffset != NULL) {
	JCExpression *tmpExpr= valueOffset;
	    // ATTN: rather unefficient way of link offsets.
	while (tmpExpr->next != NULL) tmpExpr= tmpExpr->next;
	tmpExpr->next= offset;
    }
    else {
	valueOffset= offset;
    }
    return false;
}


void JCArrayAccess::mapToPool(ConstantsList *aPool)
{
    JCExpression *tmpExpr;

    JCNamedExpr::mapToPool(aPool);
    if (subExpression) subExpression->mapToPool(aPool);
    tmpExpr= valueOffset;
    while (tmpExpr != NULL) {
	tmpExpr->mapToPool(aPool);
	tmpExpr= tmpExpr->next;
    }
}


void JCArrayAccess::bindInLocalSpace(JCNameSpace *aSpace)
{
    if (subExpression) {
	// ATTN: Nothing is to be done with subExpression, right ??
    }
    else {
	if (name->isReserved()) {
	    switch(name->getSpecialName()) {
		case JCIdentifier::snSuper:
		    resolver= aSpace->getSuperVariable();
		    break;
		case JCIdentifier::snThis:
		    resolver= aSpace->getThisVariable();
		    break;
		case JCIdentifier::snNull:
		    // Should check that the 'null' name is only used in reference,
		    // never in field/array/invoke access or as the receiver of an assignment.
		    // ATTN: Must decide how to treat the 'null' identifier.
		    cout << "ERRMSG: can not use the null identifier in an array access.\n";
		    break;
		default:
		    cout << "ERRMSG: unknown special name in JCNamedExpr::bindInLocalSpace.\n";
		    return;
		    break;
	    }
	}
	else {
	    aSpace->relateNamedExpr(this);
	}
    }
}


JCReferencedType *JCArrayAccess::getFinalType(void)
{
    if (accessType == NULL) {
	JCReferencedType *tmpType;
	unsigned int realNbrDims;

	switch(resolver->getCategory()) {
	    case JCName::localVariable:
		tmpType=  ((JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition())->typing();
		realNbrDims= ((JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition())->getNbrDimensions();
		break;
	    case JCName::fieldVariable:
		tmpType= ((JCField *)((JCResolved *)resolver)->getDefinition())->getReturnedType();
		realNbrDims= ((JCField *)((JCResolved *)resolver)->getDefinition())->getNbrDimensions();
		break;
	    default:
		cout << "ERRMSG:  JCArrayAccess::setResolution dealing with unknown resolver ";
		cout << "of type " << (int)resolver->getCategory() << " !\n";
		return NULL;
		break;
	}
	if (realNbrDims == nbrOffsets) {
	    if (tmpType->isPrimitive()) {
		accessType= new JCReferencedType();
		accessType->setKind(TYPE_BASIC);
		accessType->setOfPrimitiveType(tmpType->getPrimitiveType());
	    }
	    else {
		if (tmpType->isArray()) {
		    accessType= tmpType->getArrayBaseType();
		}
		else {	// The type itself is scalar, the declaration has dimensions.
		    accessType= tmpType;
		}
	    }
	}
	else {
	    accessType= new JCReferencedType();
	    if (tmpType->isPrimitive()) {
		accessType->setOfPrimitiveType(tmpType->getPrimitiveType());
	    }
	    else {
		accessType->setOfReferencedType(tmpType);
	    }
	    accessType->setKind(TYPE_ARRAY);
	    accessType->setNbrDimensions(realNbrDims - nbrOffsets);
	}
    }
    return accessType;
}


/**************************************************
* Implementation: JCOperExpr.
**************************************************/

JCOperExpr::JCOperExpr() : JCExpression(eOperation)
{
    builtinOp= 0;
    left= right= NULL;
    resolved= true;
    resultType= NULL;
}


JCOperExpr::JCOperExpr(ExprCategory aCategory) : JCExpression(aCategory)
{
    builtinOp= 0;
    left= right= NULL;
    resolved= true;
    resultType= NULL;
}



bool JCOperExpr::setOperator(unsigned int operation)
{
    builtinOp= operation;
    return false;
}


bool JCOperExpr::setLeftOperand(JCExpression *anExpr)
{
    left= anExpr;
    anExpr->owner= this;
    resolved&= anExpr->isResolved();
    return false;
}


bool JCOperExpr::setRightOperand(JCExpression *anExpr)
{
    bool result;

	// NOTE: The right oper must be added as the last member, because it causes
	//	a type computation of the expression.
    right= anExpr;
    anExpr->owner= this;
    resolved&= anExpr->isResolved();

    if (resolved) {
	result= computeOperType();
    }
    else result= false;

    return result;
}


void JCOperExpr::mapToPool(ConstantsList *aPool)
{
    if (left) left->mapToPool(aPool);
    if (right) right->mapToPool(aPool);
}


bool JCOperExpr::isResolved(void)
{
    return resolved;
}


void JCOperExpr::handleMute(JCExpression *before, JCExpression *after)
{
    if (before == right) right= after;
    else left= after;
}


bool JCOperExpr::computeOperType(void)
{
    JCReferencedType *leftType, *rightType, *promotedType;

    if (left == NULL) {
	if (right == NULL) {
	    cout << "ERRMSG: JCOperExpr::computeOperType has no operands to work on.\n";
	    resultType= JCReferencedType::getPopularType(JCReferencedType::popVoid);
	    return false;
	}
    }

	// There is always something in the right side.
    rightType= right->getFinalType();

    switch(builtinOp) {
	case NE_OPER:
	case EQ_OPER:
		// Rules: Arith x Arith => bool; bool x bool => bool; Class x Class => bool.
		// On Arith, perform binary promotion.
		// On Class, test Class compatibility.
	    leftType= left->getFinalType();
	    if (leftType->isArithmetic() && rightType->isArithmetic()) {
		doBinaryPromote(leftType, rightType);
	    }
	    else if (leftType->isBoolean() && rightType->isBoolean()) {
		// Nothing else to do than the check.
	    }
	    else if (leftType->isInstance() && rightType->isInstance()) {
		if (JCReferencedType::typeCompatibility(leftType, rightType) == 0) {
		    JCCompiler::getCurrentCompiler()->addError("Expression must be type-similar for an egality test");
		    return false;		// Warning: quick exit.
		}
	    }
	    else if (!(leftType->isArray() || rightType->isArray())
		    && !(leftType->isBoolean() || rightType->isBoolean())
		    && (leftType->isPrimitive() && rightType->isPrimitive())) {
		    // ATTN: Special situation involving 'char' type.  It is used by Sun, but it is not
		    // legal according to their definition.
		cout << "WARN: equality test using char type.\n";
		doBinaryPromote(leftType, rightType);
	    }
	    else {
		JCCompiler::getCurrentCompiler()->addError("Mismatching expressions types for an egality test");
		return false;	// Warning: quick exit.
	    }
	    resultType= JCReferencedType::getPopularType(JCReferencedType::popBoolean);
	    break;
	case LE_OPER:
	case GE_OPER:
	case GT_OPER:
	case LT_OPER:
		// Rules: Arith x Arith => bool.
		// On Arith, perform binary promotion.
	    leftType= left->getFinalType();
	    if (leftType->isArithmetic() && rightType->isArithmetic()) {
		doBinaryPromote(leftType, rightType);
	    }
	    else {
		JCCompiler::getCurrentCompiler()->addError("Mismatching expressions types for an bitwise operation");
		return false;	// Warning: quick exit.
	    }
	    resultType= JCReferencedType::getPopularType(JCReferencedType::popBoolean);
	    break;
	case ISA_OPER:
    // TODO: Move the type of reference from 'resultType' in JCCastExpr.
	    resultType= JCReferencedType::getPopularType(JCReferencedType::popBoolean);
	    break;

	case OROR_OPER:
	case ANDAND_OPER:
		// Rules: bool x bool => bool.
	    leftType= left->getFinalType();
	    if (!(leftType->isBoolean() && rightType->isBoolean())) {
		JCCompiler::getCurrentCompiler()->addError("Expressions in a logical combinator are not both boolean");
		return false;
	    }
	    resultType= JCReferencedType::getPopularType(JCReferencedType::popBoolean);
	    break;

	case OR_OPER:
	case AND_OPER:
	case XOR_OPER:
		// Rules: Arith x Arith => Arith; bool x bool => bool.
		// On Arith, perform binary promotion.
	    leftType= left->getFinalType();
	    if (leftType->isArithmetic() && rightType->isArithmetic()) {
		resultType= doBinaryPromote(leftType, rightType);
	    }
	    else if (leftType->isBoolean() && rightType->isBoolean()) {
		resultType= JCReferencedType::getPopularType(JCReferencedType::popBoolean);
	    }
	    else {
		JCCompiler::getCurrentCompiler()->addError("Mismatching expressions types for an bitwise operation");
		return false;	// Warning: quick exit.
	    }
	    break;

	case URS_OPER:
	case RS_OPER:
	case LS_OPER:
		// Rules: Arith x Arith => Arith; bool x bool => bool.
		// On Arith, perform binary promotion.
	    leftType= left->getFinalType();
	    if (leftType->isIntegral() && rightType->isIntegral()) {
		resultType= doUnaryPromote(leftType);
		doUnaryPromote(rightType);
	    }
	    else {
		JCCompiler::getCurrentCompiler()->addError("Expressions types for a bit shift are not integral");
		return false;	// Warning: quick exit.
	    }
	    break;

	case SUBST_OPER:
	case MULTIPLY_OPER:
	case DIVIDE_OPER:
	case MODULO_OPER:
		// Rules: Arith x Arith => Arith.
	    leftType= left->getFinalType();
	    if (leftType->isArithmetic() && rightType->isArithmetic()) {
		resultType= doBinaryPromote(leftType, rightType);
	    }
	    else if ((builtinOp == SUBST_OPER)
		    && !(leftType->isArray() || rightType->isArray())
		    && !(leftType->isBoolean() || rightType->isBoolean())
		    && (leftType->isPrimitive() && rightType->isPrimitive())) {
		    // ATTN: Special situation involving 'char' type.  It is used by Sun, but it is not
		    // legal according to their definition.
		cout << "WARN: mathematical operation using char type.\n";
		doBinaryPromote(leftType, rightType);
	    }
	    else {
		JCCompiler::getCurrentCompiler()->addError("Expressions types for a mathematical operation");
		return false;	// Warning: quick exit.
	    }
	    break;

	case ADD_OPER:
		// Rules: Arith x Arith => Arith; String x Type => String; Type x String => String.
	    leftType= left->getFinalType();
	    if (leftType->isString()) {
		if (!rightType->isString()) {
		    if (rightType->isPrimitive()) {
			// TODO: Instanciate a string, using the right expression as the init parameter.
		    }
		    else {
			// TODO: send the 'toString()' message to the right expression.
		    }
		}
		resultType= leftType;
	    }
	    else if (rightType->isString()) {
		if (!leftType->isString()) {
		    if (leftType->isPrimitive()) {
			// TODO: Instanciate a string, using the right expression as the init parameter.
		    }
		    else {
			// TODO: send the 'toString()' message to the right expression.
		    }
		}
		resultType= rightType;
	    }
	    else if (leftType->isArithmetic() && rightType->isArithmetic()) {
		resultType= doBinaryPromote(leftType, rightType);
	    }
	    else {
		JCCompiler::getCurrentCompiler()->addError("Expressions types for a mathematical operation");
		return false;	// Warning: quick exit.
	    }
	    break;

	case BITFLIP_OPER:
		// Rules: Integral x Integral => Integral.
	    if (rightType->isIntegral()) {
		resultType= doUnaryPromote(rightType);
	    }
	    else {
		JCCompiler::getCurrentCompiler()->addError("Non integral expression type for a bitwise complement");
		return false;	// Warning: quick exit.
	    }
	    break;

	case NOT_OPER:
		// Rules: bool x bool => bool.
	    if (!rightType->isBoolean()) {
		JCCompiler::getCurrentCompiler()->addError("Expression type is not boolean for a boolean negation");
		return false;	// Warning: quick exit.
	    }
	    resultType= JCReferencedType::getPopularType(JCReferencedType::popBoolean);
	    break;

	case NEGATE_OPER:
	case POSATE_OPER:
		// Rules: Integral x Integral => Integral.
	    if (!rightType->isArithmetic()) {
		JCCompiler::getCurrentCompiler()->addError("Expression type is not arithmetic for a unary mathematic operation");
		return false;	// Warning: quick exit.
	    }
	    resultType= doUnaryPromote(rightType);
	    break;

	case PREINCR_OPER:
	case PREDECR_OPER:
	case POSTINCR_OPER:
	case POSTDECR_OPER:
		// Rules: Integral x Integral => Integral.
	    if (!rightType->isArithmetic()) {
		JCCompiler::getCurrentCompiler()->addError("Expression type is not arithmetic for a pre/post incr/decr");
		return false;	// Warning: quick exit.
	    }
	    resultType= rightType;
	    break;


	    // TODO: TMPTMP solution en attendant.
	case SIMPLEASS_OPER:
	    leftType= left->getFinalType();
	    if (leftType->isArithmetic() && rightType->isArithmetic()) {
		if (leftType != rightType) {
		    // TODO: mute if it is a constant.
		    JCCastExpr *caster= new JCCastExpr();
	    
		    caster->setTypeMember(leftType);
		    caster->setRightOperand(this->right);	
		    this->right= caster;
		}
	    }
	    else {
		// TODO-971117 [HD]: Take care of the various other type mismatch situations.
	    }
	    resultType= leftType;
	    break;

	    // TODO: TMPTMP solution en attendant.
	case CAST_OPER:
	case PLUSASS_OPER:
	case MINUSASS_OPER:
	case TIMEASS_OPER:
	case DIVIDEASS_OPER:
	case ANDASS_OPER:
	case ORASS_OPER:
	case NOTASS_OPER:
	case MODASS_OPER:
	case LSASS_OPER:
	case RSASS_OPER:
	case URSASS_OPER:
	    // TODO: TMPTMP solution en attendant.
	    leftType= left->getFinalType();
	    resultType= leftType;
	    break;
    }

    return true;
}


JCReferencedType *JCOperExpr::doBinaryPromote(JCReferencedType *leftType, JCReferencedType *rightType)
{
    JCReferencedType *promotedType;

    promotedType= JCReferencedType::binaryPromotion(leftType, rightType);
    if (promotedType != leftType) {
	// TODO: mute if it is a constant.
	JCCastExpr *caster= new JCCastExpr();

	caster->setTypeMember(promotedType);
	caster->setRightOperand(this->left);	
	this->left= caster;
    }
    if (promotedType != rightType) {
	// TODO: mute if it is a constant.
	JCCastExpr *caster= new JCCastExpr();

	caster->setTypeMember(promotedType);
	caster->setRightOperand(this->right);	
	this->right= caster;
    }
    return promotedType;
}


JCReferencedType *JCOperExpr::doUnaryPromote(JCReferencedType *aType)
{
    JCReferencedType *promotedType;

    promotedType= JCReferencedType::unaryPromotion(aType);
    if (promotedType != aType) {
	// TODO: insert a cast or mute if it is a constant.
    }
    return promotedType;
}


JCReferencedType *JCOperExpr::getFinalType(void)
{
    return resultType;
}


void JCOperExpr::typeUpdateChild(JCExpression *anExpression)
{
    bool leftReso, rightReso;

    leftReso= rightReso= 1;
    if (left != NULL) {
	leftReso= left->isResolved();
    }
    if (right != NULL) {
	rightReso= right->isResolved();
    }

    resolved= leftReso & rightReso;
    if (resolved) {
	if (computeOperType()) {
	    if (owner != NULL) {
		if (owner->getContainerType() == (unsigned int)JCContainer::expression) {
		    ((JCExpression *)owner)->typeUpdateChild(this);
		}
	    }
	}
    }
}


void JCOperExpr::typeUpdateOwner(void)
{
    if (owner != NULL) {
	if (owner->getContainerType() == (unsigned int)JCContainer::expression) {
	    ((JCExpression *)owner)->typeUpdateChild(this);
	}
    }
}


/**************************************************
* Implementation: JCCastExpr.
**************************************************/

JCCastExpr::JCCastExpr() : JCOperExpr(eCast)
{
}


void JCCastExpr::setTypeMember(JCReferencedType *aType)
{
    resolved&= aType->isResolved();
    resultType= aType;
}


void JCCastExpr::mapToPool(ConstantsList *aPool)
{
    if (!resultType->isPrimitive()) {
	if (resultType->getTypeShadow() != NULL) {
	    aPool->addIndexedObject(resultType->getTypeShadow());
	}
	else {
	    cout << "ERRMSG: JCCastExpr::mapToPool has no shadow for its cast !\n";
	}
    }
    JCOperExpr::mapToPool(aPool);
}


void JCCastExpr::typeUpdateChild(JCExpression *anExpression)
{
    if (anExpression == right) {
	    // We suppose that the type will be resolved later if it is unknown yet.
	if (resultType->isResolved()) {
	    cout << "DBG: JCCastExpr::typeUpdateChild on right, type is resolved.\n";
	}
    }
    else {
	cout << "ERRMSG: JCCastExpr::typeUpdateChild dealing with unknown subExpression.\n";
    }
}


/**************************************************
* Implementation: JCAssignExpr.
**************************************************/

JCAssignExpr::JCAssignExpr() : JCOperExpr(eAssign)
{
}


bool JCAssignExpr::setLeftOperand(JCExpression *anExpr)
{
    left= anExpr;
    anExpr->owner= this;
    resolved&= anExpr->isResolved();
    return false;
}


bool JCAssignExpr::setOperator(unsigned int operation)
{
    builtinOp= operation;
    return false;
}


/**************************************************
* Implementation: JCInvokeExpr.
**************************************************/

JCInvokeExpr::JCInvokeExpr() : JCNamedExpr(eInvoke)
{
    arguments= NULL;
    cantBeVirtual= false;
}


bool JCInvokeExpr::setArguments(JCExpression *argList)
{
    if ((arguments= argList) != NULL) {
	do {
	    argList->setOwner(this);
	    argList= argList->next;
	} while (argList != NULL);
    }
    return false;
}


void JCInvokeExpr::mapToPool(ConstantsList *aPool)
{
    JCExpression *tmpExpr;

    if (resolver->getSituation() != JCName::resolved) {
//	JCCompiler::getCurrentCompiler()->addError("method call not resolved");
// Tmp:
	cout << "ERRMSG: JCInvokeExpr::mapToPool: unresolved method call for ";
	cout << name->getAsciiValue() << " (line " << getStartLine() << ").\n";
	return;
    }

    if (subExpression != NULL) {	// This field is not a local one, must map its source.
	JCMember * aMember= (JCMember *)((JCResolved *)resolver)->getDefinition();
	ExprCategory category;

	aMember->JCMember::mapToPool(aPool);
	category= subExpression->getCategory();
/* MOD-971118 [HD]: Took out the restriction, so that foreign fields get mapped also.
	if ((category != eVariable) && (category != eField) && (category != eArray)) {
*/
		// The sub-expression might contain other stuff, map it also.
	    subExpression->mapToPool(aPool);
/* MOD-971118 [HD]
	}
*/
    }

	// ATTN: To merge correctly with JCNamedExpr.
    JCNamedExpr::mapToPool(aPool);

	// Map arguments.
    if ((tmpExpr= arguments) != NULL) {
	do {
	    tmpExpr->mapToPool(aPool);
	    tmpExpr= tmpExpr->next;
	} while (tmpExpr != NULL);
    }
}


void JCInvokeExpr::handleMute(JCExpression *before, JCExpression *after)
{
    if (subExpression == before) {
	subExpression= after;
    }
    else {
	JCExpression *tmpExpr= arguments, *lastExpr;

	lastExpr= NULL;
	while (tmpExpr != NULL) {
	    if (tmpExpr == before) {
		if (lastExpr != NULL) lastExpr->next= after;
		else arguments= after;
		return;			// Warning: quick exit.
	    }
	    lastExpr= tmpExpr;
	    tmpExpr= tmpExpr->next;
	}
    }
}


void JCInvokeExpr::bindInLocalSpace(JCNameSpace *aSpace)
{
    if (name->isReserved()) {
	resolver= NULL;	// Make sure that the resolver is null !
	switch(name->getSpecialName()) {
	    case JCIdentifier::snSuper:
		resolver= aSpace->getSuperVariable();
		break;
	    case JCIdentifier::snThis:
		resolver= aSpace->getThisVariable();
		break;
	    case JCIdentifier::snNull:
		// Should check that the 'null' name is only used in reference,
		// never in field/array/invoke access or as the receiver of an assignment.
		// ATTN: Must decide how to treat the 'null' identifier.
		cout << "ERRMSG: can not use the null identifier in an method invocation.\n";
		break;
	    default:
		cout << "ERRMSG: unknown special name in JCNamedExpr::bindInLocalSpace.\n";
		return;
		break;
	}
	if (resolver != NULL) {
	    subExpression= new JCVarAccess(name, resolver);
	    subExpression->owner= this;
	    resolver= NULL;
	    name= new JCIdentifier(JCCteUtf8::getWellKnownName(JCCteUtf8::initIdent));
	    cantBeVirtual= true;
	    JCNamedExpr::bindInLocalSpace(aSpace);
	}
    }
    else {
	JCNamedExpr::bindInLocalSpace(aSpace);
     }
}


void JCInvokeExpr::typeUpdateChild(JCExpression *anExpression)
{
    // TODO: calcule le nouveau type de l'expression, a partir de l'information donnee par une
    // de ses sous-expressions (passee en argument), qui vient d'etre 'decidee'.
//   cout << "DBG: Warning, using JCInvokeExpr::typeUpdateChild (line " << getStartLine() << ").\n";
   if (anExpression == subExpression) {
	JCReferencedType *context;

	if ((context= subExpression->getFinalType()) != NULL) {
	    // Il faut trouver la methode dans le contexte de la sous-expression !
	}
   }
   else {
	// TODO: Take care of argument type update.
   }
}


void JCInvokeExpr::typeUpdateOwner(void)
{
    // TODO: calcule le nouveau type du owner, a partir de l'information donnee par 
    // la sous-expression courante.
//    cout << "DBG: Warning, using JCInvokeExpr::typeUpdateOwner (line " << getStartLine() << ").\n";

    if (owner != NULL) {
	if (owner->getContainerType() == (unsigned int)JCContainer::expression) {
	    ((JCExpression *)owner)->typeUpdateChild(this);
	}
    }
}


unsigned int JCInvokeExpr::getNbrArguments(void)
{
    JCExpression *tmpExpr= arguments;
    unsigned int nbrArgs= 0;

    while (tmpExpr) {
	nbrArgs++;
	tmpExpr= tmpExpr->next;
    }

    return nbrArgs;
}


void JCInvokeExpr::spitArgumentTypes(JCReferencedType **argTyping)
{
    JCExpression *tmpExpr= arguments;
    unsigned int nbrArgs= 0;

    while (tmpExpr) {
	argTyping[nbrArgs++]= tmpExpr->getFinalType();
	tmpExpr= tmpExpr->next;
    }
}


/**************************************************
* Implementation: JCAllocExpr.
**************************************************/

JCAllocExpr::JCAllocExpr() : JCExpression(eAlloc)
{
    type= NULL;
    dimensionSizes= NULL;
    shadow= NULL;
    nbrSizes= nbrEmptyDims= 0;
    resolved= true;
    initializer= NULL;	    /* MOD-MSC: Ajoute l'initialisation correcte de cette var. */
}


bool JCAllocExpr::setType(JCReferencedType *aType)
{
    type= aType;
    resolved&= aType->isResolved();
    if (!aType->isPrimitive() && !aType->isArray()) {
	initializer= new JCInitInvoke(aType);
	resolved&= initializer->isResolved();
    }
    return false;
}


void JCAllocExpr::setArrayType(JCReferencedType *aType, JCExpression *dimList, unsigned int emptyDims)
{

    dimensionSizes= dimList;
    nbrEmptyDims= emptyDims;
    while (dimList != NULL) {
	resolved&= dimList->isResolved();
	nbrSizes++;
	dimList= dimList->next;
    }

    if (nbrSizes > 0) {
	if (nbrSizes > 1) {	// Second case: multi-dimensional vector of values.
	    type= new JCReferencedType();
	    type->setKind(TYPE_ARRAY);
	    type->setOfReferencedType(aType);
	    type->setNbrDimensions(nbrSizes + nbrEmptyDims);
	}
	else {	// In this sitjation, there is only one dimension of values.
	    if (nbrEmptyDims > 0) {	// Third case: must create array instances.
		type= new JCReferencedType();
		type->setKind(TYPE_ARRAY);
		type->setOfReferencedType(aType);
		type->setNbrDimensions(nbrEmptyDims);
	    }
	    else {		// Fourth case: must create values of a non-array type.
		type= aType;
	    }
	}
    }
    else {			// Illegal situation: trying to alloc an empty array holder.
	    // NOTE: Should never occur, since dimension expressions are a syntaxic constraint.
	cout << "ERRMSG: Illegal create an array without any elements.";
	return;			// Warning: quick exit.
    }

    resolved&= aType->isResolved();

}


bool JCAllocExpr::setArguments(JCExpression *argList)
{
    if (initializer != NULL) {
	initializer->setArguments(argList);
	while (argList != NULL) {
	    resolved&= argList->isResolved();
	    argList= argList->next;
	}
    }
    return false;
}


void JCAllocExpr::mapToPool(ConstantsList *aPool)
{
    JCExpression *tmpExpr;

    if (!type->isPrimitive()) {
	if ((nbrSizes + nbrEmptyDims) > 1) {	// Must build an extra shadow for the type specified in the alloc.
	    unsigned int tmpLength;
	    char tmpBuffer[512];

	    if (nbrSizes == 1) {
		for (tmpLength= 0; tmpLength < nbrEmptyDims-1; tmpLength++) tmpBuffer[tmpLength]= '[';
	    }
	    else tmpLength= 0;

	    tmpLength+= type->composeSignature(&tmpBuffer[tmpLength]);
	    tmpBuffer[tmpLength]= '\0';
	    shadow= new JCCteClass(JCCteUtf8::addUniqueInstance((unsigned short *)tmpBuffer));
/* MOD-970211 [HD]: Replaced by a addToPool.
	aPool->addIndexedObject(shadow);
*/
	    shadow->addToPool(aPool);
	}
	else {
	    if (type->getTypeShadow() != NULL) {
/* MOD-970211 [HD]: Replaced by a addToPool.
		aPool->addIndexedObject(type->getTypeShadow());
*/
		type->getTypeShadow()->addToPool(aPool);
	    }
	    else {
		cout << "ERRMSG: JCAllocExpr::mapToPool has no shadow for its type !\n";
	    }
	}
    }
    else if (type->isArray()) {		// Vectorial primitive type: may not exist in the pool !
	unsigned int tmpLength;
 	char tmpBuffer[80];

	if (nbrSizes == 1) {
	    for (tmpLength= 0; tmpLength < nbrEmptyDims-1; tmpLength++) tmpBuffer[tmpLength]= '[';
	}
	else tmpLength= 0;

	tmpLength+= type->composeSignature(&tmpBuffer[tmpLength]);
	tmpBuffer[tmpLength]= '\0';
	shadow= new JCCteClass(JCCteUtf8::addUniqueInstance((unsigned short *)tmpBuffer));
/* MOD-970211 [HD]: Replaced by a addToPool.
	aPool->addIndexedObject(shadow);
*/
	shadow->addToPool(aPool);
    }

	// ATTN: Must review the what the initializer is made of.
    if ((tmpExpr= initializer) != NULL) {
	do {
	    tmpExpr->mapToPool(aPool);
	    tmpExpr= tmpExpr->next;
	} while (tmpExpr != NULL);
    }
    else {
	tmpExpr= dimensionSizes;
	while (tmpExpr != NULL) {
	    tmpExpr->mapToPool(aPool);
	    tmpExpr= tmpExpr->next;
	}
    }
}


bool JCAllocExpr::isResolved(void)
{
    return resolved;
}


void JCAllocExpr::handleMute(JCExpression *before, JCExpression *after)
{
	// ATTN: Must review the what the initializer is made of.
    JCExpression *tmpExpr= initializer, *lastExpr;

    for (unsigned int i= 0; i < 2; i++) {
	lastExpr= NULL;
	while (tmpExpr != NULL) {
	    if (tmpExpr == before) {
		if (lastExpr != NULL) lastExpr->next= after;
		else {
		    if (i == 0) initializer= (JCInitInvoke *)after;
		    else dimensionSizes= after;
		}
		return;			// Warning: quick exit.
	    }
	    lastExpr= tmpExpr;
	    tmpExpr= tmpExpr->next;
	}
    }
    tmpExpr= dimensionSizes;		// If not found in arguments, scan sizes.
}


JCReferencedType *JCAllocExpr::getReferencedType()
{
    return type;
}


/**************************************************
* Implementation: JCCondExpr.
**************************************************/

JCCondExpr::JCCondExpr() : JCExpression(eConditional)
{
    test= trueExpr= falseExpr= NULL;
    resolved= true;
}


bool JCCondExpr::setCondition(JCExpression *anExpr)
{
    test= anExpr;
    anExpr->owner= this;
    resolved&= anExpr->isResolved();
    return false;
}


bool JCCondExpr::setExprOnTrue(JCExpression *anExpr)
{
    trueExpr= anExpr;
    anExpr->owner= this;
    resolved&= anExpr->isResolved();
    return false;
}


bool JCCondExpr::setExprOnFalse(JCExpression *anExpr)
{
    falseExpr= anExpr;
    anExpr->owner= this;
    resolved&= anExpr->isResolved();
    return false;
}


bool JCCondExpr::isResolved(void)
{
    return resolved;
}


void JCCondExpr::handleMute(JCExpression *before, JCExpression *after)
{
    if (test == before) {
	test= after;
    }
    else if (trueExpr == before) {
	trueExpr= after;
    }
    else {
	falseExpr= after;
    }
}


/**************************************************
* Implementation: JCInitInvoke.
**************************************************/

JCInitInvoke::JCInitInvoke(JCReferencedType *aType)
{
    name= new JCIdentifier(JCCteUtf8::getWellKnownName(JCCteUtf8::initIdent));
    cantBeVirtual= true;
    aType->addUser(this);
}


void JCInitInvoke::mapToPool(ConstantsList *aPool)
{
    JCMember * aMember;
    JCExpression *tmpExpr;

    if (resolver->getSituation() != JCName::resolved) {
	JCCompiler::getCurrentCompiler()->addError("method call not resolved");
	return;
    }

    aMember= (JCMember *)((JCResolved *)resolver)->getDefinition();
    aMember->JCMember::mapToPool(aPool);

	// ATTN: To merge correctly with JCNamedExpr.
    JCNamedExpr::mapToPool(aPool);

	// Map arguments.
    if ((tmpExpr= arguments) != NULL) {
	do {
	    tmpExpr->mapToPool(aPool);
	    tmpExpr= tmpExpr->next;
	} while (tmpExpr != NULL);
    }
}


#if defined(PLZEN_LEVEL_2)

JCStateInvokeExpr::JCStateInvokeExpr(void)
{
    startLabel= 0;
    endLabel= 0;
}


void JCStateInvokeExpr::setName(JCIdentifier *aName)
{
    char *tmpName;
    unsigned int nameLength;
    
	// Add state name 'differentiator'.
    tmpName= new char[(nameLength= aName->nameLength()) + 2];
    strcpy(tmpName, aName->getAsciiValue());
    tmpName[nameLength]= '+';
    tmpName[nameLength+1]= '\0';
    aName->setValue(JCCteUtf8::addUniqueInstance((unsigned short *)tmpName));
    delete tmpName;

    name= aName;
}


void  JCStateInvokeExpr::setLabels(unsigned int start, unsigned int end)
{
    startLabel= start;
    endLabel= end;
}


void  JCStateInvokeExpr::getLabels(unsigned int &start, unsigned int &end)
{
    start= startLabel;
    end= endLabel;
}


#endif



#if defined(PLZEN_LEVEL_3)

/**************************************************
* Implementation: JCExecSqlInvoke.
**************************************************/

JCExecSqlInvoke::JCExecSqlInvoke(JCReferencedType *aType)
{
    name= new JCIdentifier(JCCteUtf8::getWellKnownName(JCCteUtf8::execSql));
    cantBeVirtual= true;
    aType->addUser(this);
    initialArgs[0].setStringValue((wchar *)"fakeSqlTokens");
    initialArgs[1].setIntZero();
    initialArgs[2].setIntZero();
    initialArgs[1].linkExpression(&initialArgs[2]);
    initialArgs[0].linkExpression(&initialArgs[1]);
    arguments= initialArgs;
}


void JCExecSqlInvoke::useArguments(JCCteExpr *newArgs)
{
    arguments= newArgs;
}


#endif
