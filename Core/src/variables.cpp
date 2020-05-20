/**************************************************
* File: variables.cc.
* Desc: Implementation of the variable declaration classes.
* Module: AkraLog : JavaComp.
* Rev: 5 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "typing.h"
#include "identifiers.h"
#include "expressions.h"
#include "lists.h"
#include "outConstant.h"
#include "variables.h"


JCVariableDeclaration::JCVariableDeclaration()
{
    next= NULL;
    name= NULL;
    type= NULL;
    initializer= NULL;
    shadow= NULL;
}


void JCVariableDeclaration::link(JCVariableDeclaration *nextDecl)
{
    if (next == NULL) next= nextDecl;
    else {
	JCVariableDeclaration *tmpNext= next;
	while (tmpNext->next != NULL) tmpNext= tmpNext->next;
	tmpNext->next= nextDecl;
     }
    return;
}


JCVariableDeclaration *JCVariableDeclaration::getNext(void)
{
    return next;
}


bool JCVariableDeclaration::setName(JCDimIdentifier *anIdent)
{
    name= anIdent;
    return false;
}


JCIdentifier *JCVariableDeclaration::getUndimIdentifier(void)
{
    return name->getName();
}


bool JCVariableDeclaration::setInitializator(JCExpression *anExpression)
{
    // Warning: could be in fact the head of a linked list of expressions.
    initializer= anExpression;
    return false;
}


bool JCVariableDeclaration::setTyping(JCReferencedType *aType)
{
    type= aType;
    return false;
}


JCReferencedType *JCVariableDeclaration::typing(void)
{
    return type;
}


bool JCVariableDeclaration::hasComplexType(void)
{
    return (!(type->isPrimitive()));
}


JCIdentifier *JCVariableDeclaration::getTypeName(void)
{
    return type->getTypeName();
}


unsigned int JCVariableDeclaration::getNbrDimensions(void)
{
    if (name != NULL) {
	if (type != NULL) {
	    return name->getNbrDimensions() + type->getNbrDimensions();
	}
	else return name->getNbrDimensions();
    }
    else return 0;
}


JCDimIdentifier *JCVariableDeclaration:: getName()
{
    return name;
}


JCExpression *JCVariableDeclaration::getInitializer()
{
    return initializer;
}


void JCVariableDeclaration::mapToPool(ConstantsList *aPool)
{
  // TODO: Envoit la var seulement si elle contient une initialisation (sinon, on l'envoit lorsqu'on la trouve utilisee).

    // if option -g is there, we add the name and signature of the variable.
    if (/* includeVarDebug */ 1) {
	JCCteUtf8 *tmpSignature;
	unsigned int tmpLength;
	static char tmpBuffer[512];
    
	if ((tmpLength= name->getNbrDimensions()) > 0) {
	    for (unsigned int i= 0; i < tmpLength; i++) tmpBuffer[i]= '[';
	}

	tmpLength+= type->composeSignature(&tmpBuffer[tmpLength]);
	tmpBuffer[tmpLength]= '\0';
	tmpSignature= JCCteUtf8::addUniqueInstance((unsigned short *)tmpBuffer);
	shadow= new JCCteNameAndType(name->getName()->getValue(), tmpSignature);
	aPool->addIndexedObject(tmpSignature);
	aPool->addIndexedObject(shadow);
    }

	// ATTN: The name should be included only if the VarDecl is inside a JCField.
    aPool->addIndexedObject(name->getName()->getValue());

    if (!type->isPrimitive()) {
	if (initializer != NULL) {
		// ATTN: Do we add the base type, or the signature ???
	    JCCteClass *aCteClass= type->getTypeShadow();
	    if (aCteClass) aPool->addIndexedObject(aCteClass);
	}
    }
    if (initializer != NULL) {
	JCExpression *tmpExpr= initializer;

	do {
	    tmpExpr->mapToPool(aPool);
	    tmpExpr= tmpExpr->getNext();
	} while (tmpExpr != NULL);
    }
}


bool JCVariableDeclaration::isResolved(void)
{
    return (type->isResolved());
}


void JCVariableDeclaration::setIndex(unsigned int anIndex)
{
    index= anIndex;
}


bool JCVariableDeclaration::incAccess(void)
{
    accessCount++;
    return (assignCount != 0);
}

void JCVariableDeclaration::incAssign(void)
{
    assignCount++;
}


JCCteNameAndType *JCVariableDeclaration::getShadow(void)
{
    return shadow;
}


unsigned int JCVariableDeclaration::getIndex(void)
{
    return index;
}


bool JCVariableDeclaration::hasWideType(void)
{
    if (type->isPrimitive()) {
	if (type->is64Bits()) return true;
	else return false;
    }
    else return false;
}
