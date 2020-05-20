/**************************************************
* File: nameSpace.cc.
* Desc: Contains the implementation of the name space handling classes.
* Module: AkraLog : JavaComp.
* Rev: 12 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <string.h>
}

#include <iostream.h>

#include "identifiers.h"
#include "expressions.h"
#include "typing.h"
#include "compileObjects.h"
#include "variables.h"
#include "importedObjects.h"
#include "importManager.h"
#include "lists.h"
#include "nameSpace.h"



/**************************************************
* Implementation: JCHolder.
**************************************************/

JCHolder *JCHolder::getNext(void)
{
    return next;
}


void JCHolder::setNext(JCHolder *another)
{
    next= another;
}


/**************************************************
* Implementation: JCExprHolder.
**************************************************/

JCExprHolder::JCExprHolder(JCExpression *anExpression, JCHolder *aHolder)
{
    next= aHolder;
    myContent= anExpression;
}


void JCExprHolder::setContent(JCExpression *anExpression)
{
    myContent= anExpression;
}


JCExpression *JCExprHolder::content(void)
{
    return (JCExpression *)myContent;
}


void JCExprHolder::setContentResolver(JCName *aName)
{
    if (((JCExpression *)myContent)->getCategory() == JCExpression::eVariable)
	((JCVarAccess *)myContent)->setResolution(aName);
    else
	((JCNamedExpr *)myContent)->setResolution(aName);
}


JCHolder::HolderType JCExprHolder::getCategory(void)
{
    return hExpression;
}


/**************************************************
* Implementation: JCTypeHolder.
**************************************************/

JCTypeHolder::JCTypeHolder(JCReferencedType *aType, JCHolder *aHolder)
{
    next= aHolder;
    myContent= aType;
}


void JCTypeHolder::setContent(JCReferencedType *aType)
{
    myContent= aType;
}


JCReferencedType *JCTypeHolder::content(void)
{
    return (JCReferencedType *)myContent;
}


void JCTypeHolder::setContentResolver(JCName *aName)
{
	// ATTN: How to deal with this JCResolver thing correctly.
    ((JCReferencedType *)myContent)->setResolution((JCResolved *)aName);
}


JCHolder::HolderType JCTypeHolder::getCategory(void)
{
    return hType;
}


/**************************************************
* Implementation: JCName.
**************************************************/

const char *JCName::getCategoryNameFor(UnitType aType)
{
    switch(aType) {
	case  localVariable:
	    return "local variable";
	case  fieldVariable:
	    return "instance variable";
	case  unknownVariable:
	    return "variable";
	case  uClass:
	    return "class";
	case  uInterface:
	    return "interface";
	case  noClue:
	    return "yet undecidable unit type";
	case  uType:
	    return "class or interface";
	case  uMethod:
	    return "method";
	case  uState:
	    return "state";
	default:
	    return "corrupted symbol";
    }
}


JCName::JCName(void)
{
    prev= next= NULL;
    ident= NULL;
    nameType= noClue;		// Defines unknown type.
}


JCName::JCName(JCIdentifier *anIdent)
{
    prev= next= NULL;
    ident= anIdent;
    nameType= noClue;		// Defines unknown type.
}


JCName *JCName::getNext(void)
{
    return next;
}


void JCName::link(JCName *another)
{
    next= another;
    another->prev= this;
}



JCName::UnitType JCName::getCategory(void)
{
    return nameType;
}


void JCName::setIdent(JCIdentifier *anIdent)
{
    ident= anIdent;
}


JCIdentifier *JCName::getIdent(void)
{
    return ident;
}


bool JCName::isMatching(JCIdentifier *anIdent)
{
/*
    char *name1, *name2;
    bool result= false;
*/

    return ident->isMatching(anIdent);

/* MOD-960614 [HD]:
    name1= ident->getNarrowValue();
    name2= anIdent->getNarrowValue();
    if (strcmp(name1, name2) == 0) {
	result= true;
     }

    return result;
*/
}


bool JCName::isCompatible(UnitType aKind)
{
	// Kind of type.
    if ((aKind == uClass) || (aKind == uType) || (aKind == uInterface) || (aKind == uEvent)) {
	if ((nameType == uClass) || (nameType == uType) || (nameType == uInterface) || (nameType == uEvent)) {
	    return true;
	}
	return false;
    }

	// Kind of variable.
    if ((aKind == unknownVariable) || (aKind == localVariable) || (aKind == fieldVariable)) {
	if ((nameType == unknownVariable) || (nameType == localVariable) || (nameType == fieldVariable)) {
	    return true;
	}
	return false;
    }

    if ((aKind == package) || (aKind == importation)) {
	if ((nameType == package) || (nameType == importation)) {
	    return true;
	}
	return false;
    }

    return true;		// In case of doubt, make it compatible.
}


// TMP Debug:
void JCName::dumpInfo(void)
{
    cout << "DBG: Identifier: ";
    ident->dumpInfo();
}


/**************************************************
* Implementation: JCUnresolved.
**************************************************/

JCUnresolved::JCUnresolved(void) : JCName()
{
    subNames= NULL;
    users= NULL;
    root= NULL;
}


JCUnresolved::JCUnresolved(JCReferencedType *aRefType) : JCName()
{
    nameType= uType;
    users= new JCTypeHolder(aRefType, NULL);
    if ((ident= aRefType->getTypeName())->isComposed()) {
/*
* Est-ce qu'il faut traiter le nom s'il est compose ? On essaye de l'attacher
* a un package.
*/
    }
    else {
	subNames= NULL;
    }
    root= NULL;
// ATTN: Should we attach an unresolved name as the tmp resolution for a JCReferencedType ?
//    aRefType->setResolution(this);
}


JCUnresolved::JCUnresolved(JCExpression *anExpression) : JCName()
{
    JCExpression::ExprCategory aCategory;

	// Temporarly, clean all members.
    root= NULL;
    subNames= NULL;

    switch((aCategory= anExpression->getCategory())) {
	case JCExpression::eVariable:
		// Si l'expression est un Var, alors on ajoute le nom simplement.
	    nameType= unknownVariable;		// Can be local or field.
	    ident= ((JCVarAccess *)anExpression)->getVarName();
	    users= new JCExprHolder(anExpression, NULL);
	    ((JCVarAccess *)anExpression)->setResolution(this);
	    break;
	case JCExpression::eField:
	case JCExpression::eInvoke:
	    JCExpression *tmpExpr;
/*
    Si l'expression est Field ou Invoke:
	Si elle contient une sous-expression, alors le nom doit etre simple: a tester.
	si le nom est avec sous-composantes, alors on cree une chaine de unresolved et
	une autre chaine de JCFieldExpr ou JCInvokeExpr selon le cas.
*/
	    if (aCategory == JCExpression::eField)
		nameType= fieldVariable;
	    else
		nameType= uMethod;
	    ident= ((JCNamedExpr *)anExpression)->getName();
	    users= new JCExprHolder(anExpression, NULL);
	    ((JCNamedExpr *)anExpression)->setResolution(this);
	    break;
	case JCExpression::eArray:
/*
    Si l'expression est un Array, alors il faut verifier qu'il y a bien un nom.  Si non, il faut qu'il
	y ait une sous-expression, et c'est celle-la qui contient la nomenclature.
*/
	    if ((tmpExpr= ((JCNamedExpr *)anExpression)->getSubExpression()) != NULL) {
		switch(tmpExpr->getCategory()) {
		    case JCExpression::eVariable:
		    case JCExpression::eField:
			ident= ((JCNamedExpr *)anExpression)->getName();
			nameType= fieldVariable;
			((JCNamedExpr *)anExpression)->setResolution(this);
			break;
		    default:
			cout << "TODO: new JCUnresolved got an ArrayAccess with a subExpression.\n";
			break;
		}
	    }
	    else {
		ident= ((JCNamedExpr *)anExpression)->getName();
		nameType= unknownVariable;
		((JCNamedExpr *)anExpression)->setResolution(this);
	    }
	    users= new JCExprHolder(anExpression, NULL);
	    break;
	case JCExpression::eUnknownName:
		// Si l'expression est un Var, alors on ajoute le nom simplement.
	    nameType= noClue;		// Can be field, var, type or package name.
	    ident= ((JCNamedExpr *)anExpression)->getName();
	    users= new JCExprHolder(anExpression, NULL);
	    ((JCNamedExpr *)anExpression)->setResolution(this);
	    break;
	default:
	    cout << "ERRMSG: JCUnresolved::JCUnresolved got an expression of category " << (int)anExpression->getCategory() << " to add to name space !\n";
	    break;
    }
}


JCUnresolved::~JCUnresolved(void)
{
    return;

/* ATTN: Deleting the holders cause a probleme somewhere else...
* Must find where the 'flushUsers' must be used and is not.
    if (users != NULL) {
	JCHolder *tmpHolder;
	do {
	    tmpHolder= users->next;
	    delete users;
	    users= tmpHolder;
	} while (users != NULL);
    }
*/
}


void JCUnresolved::setIdent(JCIdentifier *anIdent)
{
    ident= anIdent;

    if ((anIdent= anIdent->getComponent()) != NULL) {
	subNames= new JCUnresolved;
	subNames->setIdent(anIdent);
	subNames->root= this;
     }
}


JCName::Situation JCUnresolved::getSituation(void)
{
    return unresolved;
}


bool JCUnresolved::isMatching(JCResolved *aResolver)
{

// ATTENTION: Must do the real multi-level matching !  This would only work for simple name.

    return isMatching(aResolver->getIdent());
}


bool JCUnresolved::isMatching(JCIdentifier *anIdent)
{

    return JCName::isMatching(anIdent);
}


void JCUnresolved::linkExpression(JCExpression *anExpression)
{
	// This automatically creates a LIFO list.
    // Must correct the users if the new expression brings more information about expected
    // role of the name.
    users= new JCExprHolder(anExpression, users);
}


void JCUnresolved::linkType(JCReferencedType *aType)
{
	// This automatically creates a LIFO list.
    // Must test that the link of a type makes sense to this Unresolved (it is not a var).
    users= new JCTypeHolder(aType, users);
}



bool JCUnresolved::solveExpressions(JCResolved *resolver)
{
    JCExprHolder *tmpExprHolder;
    JCExpression *expression;

    tmpExprHolder= (JCExprHolder *)users;
    while (tmpExprHolder != NULL) {
	expression= tmpExprHolder->content();
	if (expression->getCategory() == JCExpression::eVariable) {
	    ((JCVarAccess *)expression)->setResolution(resolver);
	}
	else {
	    ((JCNamedExpr *)expression)->setResolution(resolver);
	    expression->typeUpdateOwner();
	}
	tmpExprHolder= (JCExprHolder *)tmpExprHolder->next;
     }

    return false;
}


bool JCUnresolved::solveTypes(JCResolved *resolver)
{
    JCTypeHolder *tmpTypeHolder;
    JCReferencedType *aType;

    tmpTypeHolder= (JCTypeHolder *)users;
    while (tmpTypeHolder != NULL) {
	aType= tmpTypeHolder->content();
	aType->setResolution(resolver);
	tmpTypeHolder= (JCTypeHolder *)tmpTypeHolder->next;
     }

    return false;
}


JCHolder *JCUnresolved::flushUsers(void)
{
    JCHolder *tmpUsers= users;
    users= NULL;
    return tmpUsers;
}


JCUnresolved *JCUnresolved::getSubNames(void)
{
    return subNames;
}


// TMP Debug:
void JCUnresolved::dumpInfo(void)
{
    JCUnresolved *tmpUnres;
    JCExprHolder *tmpHolder;
    JCTypeHolder *tmpTypeHolder;
    unsigned int nbrHolders= 0;

    JCName::dumpInfo();
    switch(nameType) {
	case unknownVariable:
	case uMethod:
	case uState:
	case localVariable:
	case fieldVariable:
	    tmpHolder= (JCExprHolder *)users;
	    while (tmpHolder) {
		nbrHolders++;
		tmpHolder= (JCExprHolder *)tmpHolder->next;
	    }
	    cout << ", referenced by " << nbrHolders << " expressions.\n";
	    break;
	case JCName::uType:
	case JCName::uClass:
	case JCName::uInterface:
	case importation:
	    tmpTypeHolder= (JCTypeHolder *)users;
	    while (tmpTypeHolder) {
		nbrHolders++;
		tmpTypeHolder= (JCTypeHolder *)tmpTypeHolder->next;
	    }
	    cout << ", referenced by " << nbrHolders << " type refs.\n";
	    break;
	default:
	    cout << ", referenced by yet undecidable unit type: " << (int)nameType << ".\n";
	    break;
    }
/*
    if ((tmpUnres= subNames) != NULL) {
	cout << "DBG: ---- Dumping Dependance NameSpace ----\n";
	while (tmpUnres != NULL) {
	    tmpUnres->dumpInfo();
	    tmpUnres= (JCUnresolved *)tmpUnres->next;
	}
	cout << "DBG: ---- --------------------------- ----\n";
    }
*/
}

void JCUnresolved::setRoot(JCName *aName)
{
    root= aName;

    if (aName == NULL) return;	// Warning: quick exit.

    if (aName->getSituation() == unresolved) {
	next= ((JCUnresolved *)aName)->subNames;
	if (((JCUnresolved *)aName)->subNames != NULL) {
	    ((JCUnresolved *)aName)->subNames->prev= this;
	}
	((JCUnresolved *)aName)->subNames= this;
    }
}


void JCUnresolved::updateNoClue(JCResolved *aSolution)
{
    if ((aSolution->nameType == uType) 
	    || (aSolution->nameType == uClass)
	    || (aSolution->nameType == uInterface)) {
	// The named expr. have to be deleted.
	// The immediate subnames have to be updated to 'fieldVariable', and their
	// users have to be updated to FieldAccess.
	// TODO.

	JCExpression *newExpr;
	JCExprHolder *tmpHolder= (JCExprHolder *)users;

	while (tmpHolder != NULL) {
		// ATTN: The insertion of new holder can bring information about the expected
		// role of the variable, and this should be taken care in the 'link' to the unresolved.
	    if (tmpHolder->content()->getCategory() == JCExpression::eUnknownName) {
		if ((newExpr= ((JCNamedExpr *)tmpHolder->content())->muteTo(JCExpression::eField, aSolution)) != NULL) {
		    tmpHolder->setContent(newExpr);
		}
		else {
		    cout << "ERRMSG: JCUnresolved::updateNoClue can't mute a new expression for symbol ";
		    cout << ident->getAsciiValue() << " !\n";
		}
	    }
	    tmpHolder= (JCExprHolder *)tmpHolder->next;
	}
	nameType= fieldVariable;
	cout << "JCUnresolved::updateNoClue: called for a type update.\n";
    }
    else {
	UnitType newType= aSolution->nameType;
	JCExpression::ExprCategory newCategory;
	switch(newType) {
	    case localVariable:
		newCategory= JCExpression::eVariable;
		break;
	    case fieldVariable:
		newCategory= JCExpression::eField;
		break;
	    default:
		newCategory= JCExpression::eUnknownName;
		break;
	}
	if (newCategory != JCExpression::eUnknownName) {
	    JCExpression *newExpr;
	    JCExprHolder *tmpHolder= (JCExprHolder *)users;

	    while (tmpHolder != NULL) {
		    // ATTN: The insertion of new holder can bring information about the expected
		    // role of the variable, and this should be taken care in the 'link' to the unresolved.
		switch(tmpHolder->content()->getCategory()) {
		    case JCExpression::eUnknownName:
			if ((newExpr= ((JCNamedExpr *)tmpHolder->content())->muteTo(newCategory, aSolution)) != NULL) {
			    tmpHolder->setContent(newExpr);
			}
			else {
			    cout << "ERRMSG: JCUnresolved::updateNoClue can't mute a new expression for symbol ";
			    cout << ident->getAsciiValue() << " !\n";
			}
			break;
		    case JCExpression::eVariable:
			((JCVarAccess *)tmpHolder->content())->setResolution(aSolution);
			break;
		    default:
			cout << "ERRMSG: JCUnresolved::updateNoClue got for ident ";
			cout << ident->getAsciiValue() << "an unexpected JCExpression::Category !\n";
			break;
		}
		tmpHolder= (JCExprHolder *)tmpHolder->next;
	    }
	}
	else {
	    cout << "ERRMSG: JCUnresolved::updateNoClue can't update named expressions for symbol ";
	    cout << ident->getAsciiValue() << " !\n";
	}
    }
}


void JCUnresolved::updateNoClue(JCUnresolved *aClue)
{

    // TODO.
    cout << "ERRMSG: JCUnresolved::updateNoClue(JCUnresolved *): being used while not implemented.\n";
}


void JCUnresolved::updateNoClue(JCName::UnitType newType)
{
    JCHolder *lastUser, *nextUser, *tmpUser= users;
    JCNamedExpr *tmpExpr;
    JCExpression *newExpr;

    switch(newType) {
	case JCName::fieldVariable:
	    nameType= newType;
	    while (tmpUser != NULL) {
		nextUser= tmpUser->getNext();
		switch(tmpUser->getCategory()) {
		    case JCHolder::hExpression:
			tmpExpr= (JCNamedExpr *)((JCExprHolder *)tmpUser)->content();
			newExpr= tmpExpr->muteTo(JCExpression::eField, this);
			((JCExprHolder *)tmpUser)->setContent(newExpr);
			break;
		    case JCHolder::hType:
			if (users == NULL) {
			    users= (JCTypeHolder *)tmpUser;
			}
			else {
			    lastUser->setNext(tmpUser);
			}
			lastUser= tmpUser;
			break;
		    default:
			cout << "ERRMSG: JCImportedGhost::attachMissing got a tmpUser of unknown type.\n";
			break;
		}
		tmpUser= nextUser;
	    }
	    break;
	case JCName::unknownVariable:
	    nameType= newType;
	    while (tmpUser != NULL) {
		nextUser= tmpUser->getNext();
		switch(tmpUser->getCategory()) {
		    case JCHolder::hExpression:
			if ((((JCExprHolder *)tmpUser)->content())->getCategory() == JCExpression::eUnknownName) {
			    tmpExpr= (JCNamedExpr *)((JCExprHolder *)tmpUser)->content();
			    newExpr= tmpExpr->muteTo(JCExpression::eVariable, this);
			    ((JCExprHolder *)tmpUser)->setContent(newExpr);
			}
			break;
		    case JCHolder::hType:
			if (users == NULL) {
			    users= (JCTypeHolder *)tmpUser;
			}
			else {
			    lastUser->setNext(tmpUser);
			}
			lastUser= tmpUser;
			break;
		    default:
			cout << "ERRMSG: JCImportedGhost::attachMissing got a tmpUser of unknown type.\n";
			break;
		}
		tmpUser= nextUser;
	    }
	case JCName::uType:
	    // TODO: check what has to be modified in such a type of unresolved.
	    break;
	default:
	    cout << "ERRMSG: JCUnresolved::updateNoClue(JCName::UnitType): being used for new type " << (unsigned int)newType << ".\n";
	    break;
    }

}


bool JCUnresolved::isRootless(void)
{
    return (root == NULL);
}


/**************************************************
* Implementation: JCResolved.
**************************************************/

JCResolved::JCResolved(void)
{
    nameType= noClue;
    dereference= NULL;
}


JCResolved::JCResolved(JCResolved *aResolved)
{
	// JCName section.
    prev= next= NULL;		// Construction doesn't copy the 'prev/next'.
    if (aResolved != NULL) {
	ident= aResolved->ident;
	nameType= aResolved->nameType;
    
	    // JCResolved section.
	dereference= aResolved->dereference;
    }
    else {
	nameType= noClue;
	dereference= NULL;
    }
}


JCResolved::JCResolved(JCIdentifier *anIdent, void *aTangible, UnitType aType) : JCName(anIdent)
{
    nameType= aType;
    dereference= aTangible;
}


JCName::Situation JCResolved::getSituation(void)
{
    return resolved;
}


void JCResolved::setDefinition(void *aTangible)
{
    dereference= aTangible;
}


void JCResolved::setDefType(UnitType aType)
{
    nameType= aType;
}


// ATTN: Must be replaced by JCName::getCategory.
JCName::UnitType JCResolved::getDefType(void)
{
    return nameType;
}


void *JCResolved::getDefinition(void)
{
    return dereference;
}

// TMP Debug:
void JCResolved::dumpInfo(void)
{
    JCName::dumpInfo();
    cout << ", resolved as a " << JCName::getCategoryNameFor(nameType) << " with ID " << dereference << ".\n";
}


/**************************************************
* Implementation: JCNameSpace.
**************************************************/

JCNameSpace::JCNameSpace(void)
{
    prev= next= NULL;
    subLevel= superLevel= NULL;
    unresolved= lastUnresolved= NULL;
    resolved= lastResolved= NULL;
    methodHolders= lastMethodHolder= NULL;
}


JCNameSpace::Kind JCNameSpace::getKind(void)
{
    return kBlock;
}


void JCNameSpace::link(JCNameSpace *aNameSpace)
{
    JCNameSpace *tmpNS;

    if ((tmpNS= next) == NULL) {
	next= aNameSpace;
	aNameSpace->prev= this;
     }
    else {
	while (tmpNS->next != NULL) tmpNS= tmpNS->next;
	tmpNS->next= aNameSpace;
	aNameSpace->prev= tmpNS;
     }
}


void JCNameSpace::linkAsSuper(JCNameSpace *aNameSpace)
{
    JCNameSpace *tmpNS;

    if (superLevel == NULL) {
	this->link(aNameSpace);
     }
    else {
	tmpNS= superLevel;
	while (tmpNS->superLevel != NULL) tmpNS= tmpNS->superLevel;
	tmpNS->link(aNameSpace);
     }
    aNameSpace->superLevel= this;
}


JCNameSpace * JCNameSpace::getNext(void)
{
    return next;
}


JCUnresolved * JCNameSpace::addUnresolved(JCReferencedType *aRefType)
{
    JCUnresolved *result;
    result= new JCUnresolved(aRefType);
    if (lastUnresolved != NULL) {
	lastUnresolved->next= result;
	result->prev= lastUnresolved;
     }
    else {
	unresolved= result;
     }
    lastUnresolved= result;
    return result;
}


JCUnresolved * JCNameSpace::addUnresolved(JCExpression *anExpr)
{
    JCUnresolved *result;

    result= new JCUnresolved(anExpr);
    if (lastUnresolved != NULL) {
	lastUnresolved->next= result;
	result->prev= lastUnresolved;
     }
    else {
	unresolved= result;
     }
    lastUnresolved= result;
    return result;
}


JCUnresolved * JCNameSpace::addUnresolved(JCIdentifier *anIdent)
{
    JCUnresolved *result;

    result= new JCUnresolved;
    if (lastUnresolved != NULL) {
	lastUnresolved->next= result;
	result->prev= lastUnresolved;
     }
    else {
	unresolved= result;
     }
    lastUnresolved= result;

    result->setIdent(anIdent);
    return result;
}


JCUnresolved *JCNameSpace::findUnresolved(JCIdentifier *anIdent)
{
    JCUnresolved *result;

    result= unresolved;
    while (result != NULL) {
	if (result->isMatching(anIdent)) break;
	result= (JCUnresolved *)result->next;
     }

    return result;
}


JCUnresolved *JCNameSpace::findUnresolved(JCIdentifier *anIdent, JCName *aRootName)
{
    JCUnresolved *result;

    if (aRootName != NULL) {	// MOD-971118 [HD]: Scope the search in the root if it is non-null.
	if (aRootName->getSituation() == JCName::unresolved) {
	    result= ((JCUnresolved *)aRootName)->subNames;
	    while (result != NULL) {
		if (result->isMatching(anIdent)) break;
		result= (JCUnresolved *)result->next;
	    }
	    return result;	// Warning: quick exit.
	}
    }

    result= unresolved;
    while (result != NULL) {
	if (result->root == aRootName) {
	    if (result->isMatching(anIdent)) break;
	}
	result= (JCUnresolved *)result->next;
     }

    return result;
}


JCResolved *JCNameSpace::findResolved(JCIdentifier *anIdent)
{
    JCResolved *result;

    result= resolved;
    while (result != NULL) {
	if (result->isMatching(anIdent)) break;
	result= (JCResolved *)result->next;
     }

    return result;
}


JCResolved *JCNameSpace::findResolved(JCIdentifier *anIdent, JCName::UnitType aKind)
{
    JCResolved *result;

    result= resolved;
    while (result != NULL) {
	if (result->isCompatible(aKind)) {
	    if (result->isMatching(anIdent)) break;
	}
	result= (JCResolved *)result->next;
     }

    return result;
}


JCResolved *JCNameSpace::findResolved(JCIdentifier *anIdent, JCResolved *srcResolver)
{
    JCResolved *result= NULL;

    if (srcResolver == NULL) {
	result= findResolved(anIdent);
    }
    else {
	JCReferencedType *targetType;
	JCMember *aMember;
	JCVariableDeclaration *varDecl;
	JCType *aType= NULL;	    /* MOD-MSC: Bouge la definition ici parce que VC++ la voit comme global dans le switch. */

	switch(srcResolver->getCategory()) {
	    case JCName::uType:
	    case JCName::uClass:
	    case JCName::uInterface:
		aType= (JCType *)srcResolver->getDefinition();
		// ATTN: doit construire un nouveau resolved pour cette definition.
		result= aType->findSymbol(anIdent);
		break;
	    case JCName::importation:
		break;
	    case JCName::unknownVariable:
		break;
	    case JCName::localVariable:
		varDecl= (JCVariableDeclaration *)srcResolver->dereference;

		if ((targetType= varDecl->typing()) != NULL) {
		    if (targetType->isArray()) {
			if (strcmp(anIdent->getAsciiValue(), "length") == 0) {
			    // ATTN-970827: Can it be used with a non-array (by specifying all its dimension indices ?).
			    result= JCSpecialField::getField(JCSpecialField::ksLength);
			}
			else {
			    cout << "ERRMSG: JCNameSpace::findResolved is looking for a member in an array type.\n";
			}
		    }
		    else if (targetType->isPrimitive()) {
			cout << "ERRMSG: JCNameSpace::findResolved is looking for a member in a primitive type.\n";
		    }
		    else {
			JCType *realLocation;
			if ((realLocation= targetType->getRealType()) != NULL) {
			    result= realLocation->findSymbol(anIdent);
			}
			else {
    /* MOD-970207 [HD]: Don't give an error, this is (normally) a forward reference situation.
			    cout << "ERRMSG: JCNameSpace::findResolved has no real type for referenced type " << targetType->getTypeName()->getAsciiValue();
			    cout << " !\n";
    */
			}
		    }
		}
		else {
		    cout << "ERRMSG: JCNameSpace::findResolved has no type bounded to local variable ";
		    cout << srcResolver->ident->getAsciiValue() << " !\n";
		}
		break;
	    case JCName::fieldVariable:
	    case JCName::uMethod:
		// RENDU ICI: Il faut etre certain qu'on a la bonne methode !!!
		// TODO. Replicate in 'localVariable' section.
		aMember= (JCMember *)srcResolver->dereference;

		if ((targetType= aMember->getReturnedType()) != NULL) {
		    JCType *realLocation;

		    if (targetType->isArray()) {
			if (strcmp(anIdent->getAsciiValue(), "length") == 0) {
			    // ATTN-970827: Can it be used with a non-array (by specifying all its dimension indices ?).
			    result= JCSpecialField::getField(JCSpecialField::ksLength);
			}
			else {
			    cout << "ERRMSG: JCNameSpace::findResolved is looking for a member in an array type.\n";
			}
		    }
		    else if (targetType->isPrimitive()) {
			cout << "ERRMSG: JCNameSpace::findResolved is looking for a member in a primitive type.\n";
		    }
		    else {
			if ((realLocation= targetType->getRealType()) != NULL) {
			    result= realLocation->findSymbol(anIdent);
			}
			else {
/* MOD-970207 [HD]: Don't give an error, this is (normally) a forward reference situation.
			    cout << "ERRMSG: JCNameSpace::findResolved has no real type for referenced type " << targetType->getTypeName()->getAsciiValue();
			    cout << " !\n";
*/
			}
		    }
		}
		else {
		    if (srcResolver->getCategory() == JCName::fieldVariable) {
			cout << "ERRMSG: JCNameSpace::findResolved has no type bounded to field ";
		    }
		    else {
			cout << "ERRMSG: JCNameSpace::findResolved has no type bounded to method ";
		    }
		    cout << srcResolver->ident->getAsciiValue() << " !\n";
		}
		break;
	    case JCName::uState:
		break;
	    default:
		break;
	}
    }
    return result;    /* MOD-MSC: Bouge le 'return' du bloc precedent a ici. */
}


JCResolved *JCNameSpace::quickAddResolved(JCIdentifier *anIdent, void *aTangible, JCName::UnitType aType)
{
    JCResolved *result;
    result= new JCResolved(anIdent, aTangible, aType);

    if (lastResolved != NULL) {
	lastResolved->next= result;
	result->prev= lastResolved;
     }
    else {
	resolved= result;
     }
    lastResolved= result;
    return result;
}


JCResolved *JCNameSpace::addResolution(JCIdentifier *anIdent, void *aTangible, JCName::UnitType aType)
{
    JCResolved *result;

    result= resolved;
    while (result != NULL) {
	if (result->isMatching(anIdent)) break;
	result= (JCResolved *)result->next;
     }
    if (result == NULL) {
	result= new JCResolved(anIdent, aTangible, aType);
	if (lastResolved != NULL) {
	    lastResolved->next= result;
	    result->prev= lastResolved;
	 }
	else {
	    resolved= result;
	 }
	lastResolved= result;
     }
    else {
	result= NULL;		// Indicates that we found an Ident of the same name.
     }

    return result;
}


bool JCNameSpace::applyResolution(JCResolved *aResolved)
{
    JCUnresolved *tmpUnres= unresolved, *tmpSubName, *tmpLastSubName, *nextUnres;
    bool foundOne= false, result= true;

    while (tmpUnres != NULL) {
	nextUnres= (JCUnresolved *)tmpUnres->next;
	if (tmpUnres->isMatching(aResolved)) {
	    if (foundOne) {
		cout << "ERRMSG: JCNameSpace::applyResolution: found more than one unresolved for a resolver.\n";
		result= false;		// We should not find more than one unresolved of a given name.
	     }
	    else {
		foundOne= true;
		applyResolution(aResolved, tmpUnres);
		delete tmpUnres;
	     }
	 }
	tmpUnres= nextUnres;
     }
    return result;
}


void JCNameSpace::applyResolution(JCResolved *resolver, JCUnresolved *anUnknown)
{
	// Unlink the symbol from the list.
    if (unresolved == anUnknown) {
	unresolved= (JCUnresolved *)anUnknown->next;
    }
    if (anUnknown->next != NULL) {
	anUnknown->next->prev= anUnknown->prev;
    }
    if (lastUnresolved == anUnknown) {
	lastUnresolved= (JCUnresolved *)anUnknown->prev;
    }
    if (anUnknown->prev != NULL) {
	anUnknown->prev->next= anUnknown->next;
    }

    switch(anUnknown->getCategory()) {
	case JCName::uType:
	case JCName::uClass:
	case JCName::uInterface:
	case JCName::importation:
	    anUnknown->solveTypes(resolver);
	    break;
	case JCName::unknownVariable:
	case JCName::localVariable:
	case JCName::fieldVariable:
	    anUnknown->solveExpressions(resolver);
	    break;
	case JCName::uMethod:
	case JCName::uState:
	    anUnknown->solveExpressions(resolver);
	    addMethodUsers((JCExprHolder *)anUnknown->users);
	    break;
	case JCName::noClue:	// Found a NamedExpr we knew nothing about.
	    anUnknown->updateNoClue(resolver);
	    break;
	default:
	    cout << "ERRMSG: JCNameSpace::applyResolution: having to solve an unknown ";
	    cout << "which is not supposed to exist.\n";
	    break;
    }

	// We unlink the sub-names to the resolved field.
    if (anUnknown->subNames != NULL) {
	JCUnresolved *tmpSubName, *tmpLastSubName= NULL;

	tmpSubName= anUnknown->subNames;
	switch(resolver->getCategory()) {
	    case JCName::uType:
	    case JCName::uClass:
	    case JCName::uInterface:
	    case JCName::importation:
		while (tmpSubName != NULL) {
		    tmpSubName->root= NULL;
		    tmpSubName= (JCUnresolved *)tmpSubName->next;
		}
		((JCType *)resolver->getDefinition())->importUnknown(anUnknown->subNames);
		break;
	    case JCName::localVariable:
		while (tmpSubName != NULL) {
		    tmpSubName->root= NULL;
		    tmpSubName= (JCUnresolved *)tmpSubName->next;
		}
		if (((JCVariableDeclaration *)resolver->getDefinition())->typing() != NULL) {
		    ((JCVariableDeclaration *)resolver->getDefinition())->typing()->importUnknown(anUnknown->subNames);
		}
		else {
		    cout << "ERRMSG: JCNameSpace::applyResolution: want to transfer unknown to ";
		    cout << "a variable declaration that has no typing.\n";
		}
		break;
	    case JCName::fieldVariable:
	    case JCName::uMethod:
	    case JCName::uState:
		while (tmpSubName != NULL) {
		    tmpSubName->root= NULL;
		    tmpSubName= (JCUnresolved *)tmpSubName->next;
		}
		if (((JCMember *)resolver->getDefinition())->getReturnedType() != NULL) {
		    ((JCMember *)resolver->getDefinition())->getReturnedType()->importUnknown(anUnknown->subNames);
		}
		else {
		    cout << "ERRMSG: JCNameSpace::applyResolution: want to transfer unknown to ";
		    cout << "a member that has no returned type.\n";
		}
		break;
	    case JCName::unknownVariable:
	    case JCName::noClue:
	    default:
		while (tmpSubName != NULL) {
		    tmpSubName->root= resolver;
		    tmpSubName= (JCUnresolved *)tmpSubName->next;
		}
		cout << "ERRMSG: JCNameSpace::applyResolution: want to transfer unknown to ";
		cout << "impossible receiver.\n";
		break;
	}
    }
}


JCNameSpace *JCNameSpace::getUpperLevel(void)
{
    return superLevel;
}


JCNameSpace *JCNameSpace::getLastLevel(void)
{
    JCNameSpace *result;
    if ((result= subLevel) != NULL) {
	while (result->subLevel != NULL) result= result->subLevel;
     }
    else result= this;
    return result;
}


bool JCNameSpace::addALevel(JCNameSpace *newLevel)
{
    JCNameSpace *tmpNS;

    if (subLevel == NULL) {
	subLevel= newLevel;
	newLevel->superLevel= this;
     }
    else {
	tmpNS= subLevel;
	while (tmpNS->subLevel != NULL) tmpNS= tmpNS->subLevel;
	tmpNS->subLevel= newLevel;
	newLevel->superLevel= tmpNS;
     }

	// We add the new name space to the top level, so that we can
	// find all name spaces quickly.
    if (superLevel == NULL) {
	this->link(newLevel);
     }
    else {
	tmpNS= superLevel;
	while (tmpNS->superLevel != NULL) tmpNS= tmpNS->superLevel;
	tmpNS->link(newLevel);
     }
    return false;
}


bool JCNameSpace::removeLastLevel(void)
{
    JCNameSpace *tmpNS;

    if ((tmpNS= subLevel) != NULL) {
	while (tmpNS->subLevel != NULL) tmpNS= tmpNS->subLevel;
	if (tmpNS->superLevel != NULL) tmpNS->superLevel->subLevel= NULL;
     }

    return false;
}


bool JCNameSpace::flushUnresolved(void)
{
    if (unresolved != NULL) {
	JCUnresolved *tmpUnres= unresolved, *nextUnres, *tmpList= NULL, *lastTmpList;

	while (tmpUnres != NULL) {
	    nextUnres= (JCUnresolved *)tmpUnres->next;
		// Keep in this space the names that are not prefixed.
	    if (tmpUnres->root != NULL) {
		tmpUnres= nextUnres;
		continue;
	    }

		// Unlink the node from the current name space list.
	    if (tmpUnres->prev) tmpUnres->prev->next= tmpUnres->next;
	    if (tmpUnres->next) tmpUnres->next->prev= tmpUnres->prev;
	    if (unresolved == tmpUnres) {
		unresolved= nextUnres;
	    }
	    if (lastUnresolved == tmpUnres) {
		if (tmpUnres->prev != NULL)
		    lastUnresolved= (JCUnresolved *)tmpUnres->prev;
		else
		    lastUnresolved= unresolved;
	    }

	    if (!mergeToSuperSpace(tmpUnres)) {
		if (tmpList == NULL) {
		    tmpList= tmpUnres;
		    tmpUnres->prev= NULL;
		}
		else {
		    tmpUnres->prev= lastTmpList;
		    lastTmpList->next= tmpUnres;
		}
		tmpUnres->next= NULL;
		lastTmpList= tmpUnres;
	    }

		// Add the node to the temp. list.
	    tmpUnres= nextUnres;
	}

	    // Link the temporary list (extracted nodes) to the super level.
	if (tmpList != NULL) {
	    if (superLevel->lastUnresolved != NULL) {
		superLevel->lastUnresolved->next= tmpList;
		tmpList->prev= superLevel->lastUnresolved;
	    }
	    else {
		superLevel->unresolved= tmpList;
	    }
	    superLevel->lastUnresolved= lastTmpList;
	}
     }
    return false;
}


// TMP Debug:

void JCNameSpace::dumpContent(void)
{
    JCUnresolved *tmpUnres;
    JCResolved *tmpRes;


    if (unresolved != NULL) {
	cout << "DBG: ---- Dumping Unresolved NameSpace ----\n";
	tmpUnres= unresolved;
	while (tmpUnres != NULL) {
	    tmpUnres->dumpInfo();
	    tmpUnres= (JCUnresolved *)tmpUnres->next;
	 }
     }
#if defined(DEBUG_UNRESOLVED_LV2)
    else {
	cout << "** No unresolved identifiers:\n";
     }
#endif

#if defined(DEBUG_RESOLVED)
    if (resolved != NULL) {
	cout << "-- Resolved identifiers --\n";
	tmpRes= resolved;
	while (tmpRes != NULL) {
	    tmpRes->dumpInfo();
	    tmpRes= (JCResolved *)tmpRes->next;
	 }
     }
#if defined(DEBUG_RESOLVED_LV2)
    else {
	cout << "DBG:  ** No resolved identifiers:\n";
     }
#endif
#endif

}


bool JCNameSpace::hasUnresolved(void)
{
    return (unresolved != NULL);
}


void JCNameSpace::seekUnresolvedFrom(JCNameSpace *aSpace)
{
    JCUnresolved *tmpUnresolved, *nextUnresolved;
    JCResolved *aResolution;

    tmpUnresolved= aSpace->unresolved;
    while (tmpUnresolved != NULL) {
	nextUnresolved= (JCUnresolved *)tmpUnresolved->next;

	if ((aResolution= findResolved(tmpUnresolved->ident)) != NULL) {
	    aSpace->applyResolution(aResolution);
	    aSpace->removeUnresolved(tmpUnresolved);
	    delete tmpUnresolved;
	}
	tmpUnresolved= nextUnresolved;
    }
}


void JCNameSpace::includeResolutions(JCResolved *resolvers)
{
    if (resolved == NULL) {		// Take care of kick-start.
	resolved= lastResolved= new JCResolved(resolvers);
	resolvers= (JCResolved *)resolvers->next;
    }
    while (resolvers != NULL) {
	lastResolved->next= new JCResolved(resolvers);
	lastResolved= (JCResolved *)lastResolved->next;
	resolvers= (JCResolved *)resolvers->next;
    }
}


JCResolved *JCNameSpace::getResolvers(void)
{
    return resolved;
}


bool JCNameSpace::relateSimpleVar(JCVarAccess *aSimpleVar)
{
    JCIdentifier *tmpIdent;

    tmpIdent= aSimpleVar->getVarName();
    if (!tmpIdent->isComposed()) {
	JCResolved *tmpResolved= resolved;

	    // First, try to match a resolved name.
	while (tmpResolved != NULL) {
	    if (tmpResolved->isMatching(tmpIdent)) break;
	    tmpResolved= (JCResolved *)tmpResolved->next;
	}
	if (tmpResolved != NULL) {
	    aSimpleVar->setResolution(tmpResolved);
	}
	else {
	    JCUnresolved *tmpUnresolved= unresolved;

		// Second, try to match an existing unresolved name.
	    while (tmpUnresolved != NULL) {
		if (tmpUnresolved->root == NULL) {	// Look for names which are without prefix.
		    if (tmpUnresolved->isMatching(tmpIdent)) break;
		}
		tmpUnresolved= (JCUnresolved *)tmpUnresolved->next;
	    }
	    if (tmpUnresolved != NULL) {
		aSimpleVar->setResolution(tmpUnresolved);
		tmpUnresolved->linkExpression(aSimpleVar);
	    }
	    else {
		    // Third, add the name as an unresolved.
		aSimpleVar->setResolution(addUnresolved(aSimpleVar));
	    }
	}
	return true;
    }
    return false;
}


bool JCNameSpace::relateNamedExpr(JCNamedExpr *aNamedExpr)
{
    JCIdentifier *tmpName;
    bool canLookupSuffix= false, resolvedTopExpr= false;

    tmpName= aNamedExpr->getName();
    if (tmpName->isComposed()) {		// Compose name, no sub-expression.
	JCResolved *aResolver= NULL;
	JCUnresolved *aKnown= NULL;
	JCName *lastSeen;
	JCNamedExpr *currentExpr= aNamedExpr;
	JCExpression *subExpr;
	JCIdentifier *nextName;

	aNamedExpr->setName(tmpName->removeSuffix());
	if (aNamedExpr->getSubExpression()) {
	    cout << "ERRMSG: JCNameSpace::relateNamedExpr a un nom compose et une sous-expression !\n";
	    return false;
	}
	    // First, create the sub-expressions that are 'known'.
	while (tmpName != NULL) {
	    if ((aResolver= findResolved(tmpName, aResolver)) != NULL) {
		subExpr= NULL;
		switch(aResolver->nameType) {
		    case JCName::localVariable:
			nextName= tmpName->removePrefix();
			subExpr= new JCVarAccess(tmpName, aResolver);
			tmpName= nextName;
			break;
		    case JCName::fieldVariable:
			subExpr= new JCFieldAccess(tmpName, aResolver);
			break;
		    case JCName::uType:
		    case JCName::uClass:
		    case JCName::uInterface:
			break;
		    default:
			cout << "ERRMSG: JCNameSpace::relateNamedExpr has found an illegal resolver (" <<  (int)aResolver->nameType << ") in a composed name.\n";
			nextName= tmpName->removePrefix();
			break;
		}
		if (subExpr != NULL) {
		    if (currentExpr->getCategory() == JCExpression::eVariable) {
			// ATTN: Temporarly, we check to make sure that NameSpace can't screw up.
			// This situation should never occur.
			cout << "ERRMSG: JCNameSpace::relateNamedExpr has found a local variable not at the start of a composed name.";
		    }
		    else {
			currentExpr->setSubExpression(subExpr);
			currentExpr= (JCNamedExpr *)subExpr;
		    }
		}

	    }
	    else break;	// When we can't find resolver, we go for unresolved in the next loop.
	}

	    // Second, create sub-expressions for the unknown names.
	lastSeen= aResolver;
	while (tmpName != NULL) {
	    nextName= tmpName->removePrefix();
	    if ((aKnown= findUnresolved(tmpName, lastSeen)) != NULL) {
		switch(aKnown->nameType) {
		    case JCName::uType:
		    case JCName::uClass:
		    case JCName::uInterface:
			// All suffix left must be field access, and the initial expression
			// must be field, array or invoke access.
			// All names used before must be package component.
			// Take care of resolving anything before, and everything after.
			tmpName= nextName;	// ATTN: TMP.
			break;
		    case JCName::localVariable:
			subExpr= new JCVarAccess(tmpName, aKnown);
			currentExpr->setSubExpression(subExpr);
			currentExpr= (JCNamedExpr *)subExpr;
			aKnown->linkExpression(subExpr);
			// A prefix can be a local variable.
			tmpName= nextName;
			break;
		    case JCName::fieldVariable:
		    case JCName::unknownVariable:
/* MOD-970531 [HD]: Put a test on 'lastSeen', to detect if we are dealing with a root name.
*	If so, a VarAccess is created, because it could be a local field or local variable.
*/
			if (lastSeen != NULL) {
			    subExpr= new JCFieldAccess(tmpName, aKnown);
			}
			else {
			    subExpr= new JCVarAccess(tmpName, aKnown);
			}
			currentExpr->setSubExpression(subExpr);
			currentExpr= (JCNamedExpr *)subExpr;
			aKnown->linkExpression(subExpr);
			// All suffix left must be field access, and the initial expression
			// must be field, array or invoke access.
			tmpName= nextName;
			break;
		    case JCName::uMethod:
			// Make no sense.
			cout << "ERRMSG: method name " << tmpName->getAsciiValue() << " used as an intermediary name.\n";
			return false;
			break;
		    case JCName::importation:
			// Not too much info on following names.  Previous names should have been
			// resolved as importation also !
			tmpName= nextName;	// ATTN: TMP.
			break;
		    case JCName::package:
			// Not too much info on following names.  Previous names should have been
			// resolved as packages also !
			tmpName= nextName;	// ATTN: TMP.
			break;
		    case JCName::noClue:
			    // Some name of unknown function.  Just link and continue.
			subExpr= new JCNamedExpr(JCExpression::eUnknownName, tmpName, aKnown);
			currentExpr->setSubExpression(subExpr);
			currentExpr= (JCNamedExpr *)subExpr;
			aKnown->linkExpression(subExpr);
			tmpName= nextName;
			break;
		    default:
			cout << "ERRMSG: unresolved " << aKnown->ident->getAsciiValue() << " is of incompatible type (" << (int)aKnown->nameType <<") in relateNamedExpr.\n";
			return false;
			break;
		}
		lastSeen= aKnown;
	    }
	    else break;
	}
	    // Third, fill in the expression with the new unknown terms, creating Unresolved.
	canLookupSuffix= (tmpName == NULL);
	while (tmpName != NULL) {
	    subExpr= new JCNamedExpr(tmpName);
	    currentExpr->setSubExpression(subExpr);
	    currentExpr= (JCNamedExpr *)subExpr;
	    if (lastSeen == NULL) {
		aKnown= addUnresolved(subExpr);
	    }
	    else {
		aKnown= new JCUnresolved(subExpr);
		aKnown->setRoot(lastSeen);
		((JCNamedExpr *)subExpr)->setResolution(aKnown);
	    }
	    lastSeen= aKnown;
	    tmpName= nextName;
	    if (nextName != NULL) {
		nextName= tmpName->removePrefix();
	    }
	}
	if (canLookupSuffix) {
		// lastSeen is not empty.
		// First try to find it as a resolved.
	    tmpName= aNamedExpr->getName();	// Fetch the final suffix.
	    if (lastSeen->getSituation() == JCName::resolved) {
		if ((aResolver= findResolved(tmpName, (JCResolved *)lastSeen)) != NULL) {
		    aNamedExpr->setResolution(aResolver);
		    resolvedTopExpr= true;
		}
	    }
		// If not found, then try to find it as an unresolved.
	    if (!resolvedTopExpr) {
		if ((aKnown= findUnresolved(tmpName, lastSeen)) != NULL) {
		    aNamedExpr->setResolution(aKnown);
		    aKnown->linkExpression(aNamedExpr);
		    resolvedTopExpr= true;
		}
	    }
	}
	    // If top expression is not known at this point, a new unresolved is going to take care of it.
	if (!resolvedTopExpr) {
	    if (lastSeen == NULL) {
		aKnown= addUnresolved(aNamedExpr);
	    }
	    else {
		aKnown= new JCUnresolved(aNamedExpr);
		aKnown->setRoot(lastSeen);
		if (lastSeen->getSituation() == JCName::resolved) {
			// Add the new unresolved to the list.
		    if (unresolved == NULL) {
			unresolved= (JCUnresolved *)aKnown;
		    }
		    else {
			lastUnresolved->next= aKnown;
			aKnown->prev= lastUnresolved;
		    }
		    lastUnresolved= (JCUnresolved *)aKnown;
		}
	    }
	    aNamedExpr->setResolution(aKnown);
	}
    }
    else {		// Simple name expression.
	JCExpression *tmpExpr;
	JCName *aKnown, *lastSeen;
        JCReferencedType *aTypeRef= NULL;
	JCResolved *typeResolver;
	bool resolvedTopExpr= false;

	if ((tmpExpr= aNamedExpr->getSubExpression()) != NULL) {
	    JCExpression::ExprCategory tmpCategory= tmpExpr->getCategory();
	    switch(tmpCategory) {
		case JCExpression::eVariable:
		    if ((aKnown= ((JCVarAccess *)tmpExpr)->resolution()) != NULL) {
			lastSeen= aKnown;
			if (aKnown->getSituation() == JCName::resolved) {
			    if ((aKnown= findResolved(tmpName, (JCResolved *)lastSeen)) != NULL) {
				aNamedExpr->setResolution(aKnown);
				resolvedTopExpr= true;
			    }
			}
			if (!resolvedTopExpr) {
			    if ((aKnown= findUnresolved(tmpName, lastSeen)) != NULL) {
				aNamedExpr->setResolution(aKnown);
				((JCUnresolved *)aKnown)->linkExpression(aNamedExpr);
				resolvedTopExpr= true;
			    }
			}
			if (!resolvedTopExpr) {
			    aKnown= new JCUnresolved(aNamedExpr);
			    ((JCUnresolved *)aKnown)->setRoot(lastSeen);

			    if (lastSeen->getSituation() == JCName::resolved) {
				    // Add the new unresolved to the list.
				if (unresolved == NULL) {
				    unresolved= (JCUnresolved *)aKnown;
				}
				else {
				    lastUnresolved->next= aKnown;
				    aKnown->prev= lastUnresolved;
				}
				lastUnresolved= (JCUnresolved *)aKnown;
			    }
			}
		    }
		    else {
			// No [un]resolver for the sub-expression.  It is most likely an incorrect syntaxic construct.
			cout << "ERRMSG: relateNamedExpr: no resolver available for a JCVariableDeclaration sub-expression !!\n";
			return false;
		    }
		    break;
		case JCExpression::eField:
		case JCExpression::eArray:
		case JCExpression::eInvoke:
		case JCExpression::eUnknownName:
		    if ((aKnown= ((JCNamedExpr *)tmpExpr)->resolution()) != NULL) {
			lastSeen= aKnown;
			if (aKnown->getSituation() == JCName::resolved) {
			    if ((aKnown= findResolved(tmpName, (JCResolved *)lastSeen)) != NULL) {
				aNamedExpr->setResolution(aKnown);
				resolvedTopExpr= true;
			    }
			}
			if (!resolvedTopExpr) {
			    if ((aKnown= findUnresolved(tmpName, lastSeen)) != NULL) {
				aNamedExpr->setResolution(aKnown);
				((JCUnresolved *)aKnown)->linkExpression(aNamedExpr);
				resolvedTopExpr= true;
			    }
			}
			if (!resolvedTopExpr) {
			    aKnown= new JCUnresolved(aNamedExpr);
			    ((JCUnresolved *)aKnown)->setRoot(lastSeen);

			    if (lastSeen->getSituation() == JCName::resolved) {
				    // Add the new unresolved to the list.
				if (unresolved == NULL) {
				    unresolved= (JCUnresolved *)aKnown;
				}
				else {
				    lastUnresolved->next= aKnown;
				    aKnown->prev= lastUnresolved;
				}
				lastUnresolved= (JCUnresolved *)aKnown;
			    }

			}
		    }
		    else {
			// No [un]resolver for the sub-expression.  It is most likely an incorrect syntaxic construct.
			cout << "ERRMSG: relateNamedExpr: no resolver available for a JCNamedExpr sub-expression !!\n";
			return false;
		    }
		    break;
		case JCExpression::eCast:
		    // Facon tmp lente de le faire, en attendant de pouvoir aller chercher le Unresolved
		    // qui represente le type rapidement:
		    aTypeRef= ((JCCastExpr *)tmpExpr)->getFinalType();

		    if ((typeResolver= aTypeRef->resolution()) != NULL) {
			if ((aKnown= findResolved(tmpName, (JCResolved *)typeResolver)) != NULL) {
			    aNamedExpr->setResolution(aKnown);
			}
			else if ((aKnown= findUnresolved(tmpName, typeResolver)) != NULL) {
			    aNamedExpr->setResolution(aKnown);
			    ((JCUnresolved *)aKnown)->linkExpression(aNamedExpr);
			}
			else {
			    aKnown= new JCUnresolved(aNamedExpr);
			    ((JCUnresolved *)aKnown)->setRoot(typeResolver);

				// Add the new unresolved to the list.
			    if (unresolved == NULL) {
				unresolved= (JCUnresolved *)aKnown;
			    }
			    else {
				lastUnresolved->next= aKnown;
				aKnown->prev= lastUnresolved;
			    }
			    lastUnresolved= (JCUnresolved *)aKnown;

			}
		    }
		    else {
			JCUnresolved *extraUnresolved= new JCUnresolved(aTypeRef);
			aKnown= new JCUnresolved(aNamedExpr);
			((JCUnresolved *)aKnown)->setRoot(extraUnresolved);
/*
			    // Add the new unresolved to the list.
			if (unresolved == NULL) {
			    unresolved= (JCUnresolved *)aKnown;
			}
			else {
			    lastUnresolved->next= aKnown;
			    aKnown->prev= lastUnresolved;
			}
			lastUnresolved= (JCUnresolved *)aKnown;
*/
		    }
		    break;
		case JCExpression::eBlock:
		    cout << "ERRMSG: relateNamedExpr: simple name with block sup-expression !!\n";
		    return false;
		case JCExpression::eConstant:
		    // Can be valid if the constant is a String.
		    cout << "ERRMSG: relateNamedExpr: simple name with constant sup-expression !!\n";
		    return false;
		case JCExpression::eOperation:
		    // Can be valid if the result of the operation is a String.
		    cout << "ERRMSG: relateNamedExpr: simple name with operation sup-expression !!\n";
		    return false;
		case JCExpression::eAssign:
		    // The assignment must return a non-primitive type.
		    break;
		case JCExpression::eAlloc:
		    // The assignment must return a non-primitive scalar type.
		    // ATTN: Copy of the eCast code !
		    aTypeRef= ((JCAllocExpr *)tmpExpr)->getReferencedType();

		    if ((typeResolver= aTypeRef->resolution()) != NULL) {
			if ((aKnown= findResolved(tmpName, (JCResolved *)typeResolver)) != NULL) {
			    aNamedExpr->setResolution(aKnown);
			}
			else if ((aKnown= findUnresolved(tmpName, typeResolver)) != NULL) {
			    aNamedExpr->setResolution(aKnown);
			    ((JCUnresolved *)aKnown)->linkExpression(aNamedExpr);
			}
			else {
			    aKnown= new JCUnresolved(aNamedExpr);
			    ((JCUnresolved *)aKnown)->setRoot(typeResolver);

				// Add the new unresolved to the list.
			    if (unresolved == NULL) {
				unresolved= (JCUnresolved *)aKnown;
			    }
			    else {
				lastUnresolved->next= aKnown;
				aKnown->prev= lastUnresolved;
			    }
			    lastUnresolved= (JCUnresolved *)aKnown;

			}
		    }
		    else {
			JCUnresolved *extraUnresolved= new JCUnresolved(aTypeRef);

			aKnown= new JCUnresolved(aNamedExpr);
			((JCUnresolved *)aKnown)->setRoot(extraUnresolved);
		    }
		    break;
		case JCExpression::eConditional:
		    // The assignment must return a non-primitive type.
		    break;
		case JCExpression::eEmpty:
		    cout << "ERRMSG: relateNamedExpr: simple name with empty sup-expression !!\n";
		    return false;
		case JCExpression::eSpecial:
		    break;
		default:
		    cout << "ERRMSG: relateNamedExpr is lost in trying to seek sub-expresion of simple name !!\n";
		    break;
	    }
	}
	else {
	    if ((aNamedExpr->getCategory() == JCExpression::eArray) 
		    || (aNamedExpr->getCategory() == JCExpression::eInvoke)) {
		JCResolved *tmpResolved= resolved;
	
		    // First, try to match a resolved name.
		while (tmpResolved != NULL) {
		    if (tmpResolved->isMatching(tmpName)) break;
		    tmpResolved= (JCResolved *)tmpResolved->next;
		}
		if (tmpResolved != NULL) {
		    aNamedExpr->setResolution(tmpResolved);
		}
		else {
		    JCUnresolved *tmpUnresolved= unresolved;

			// Second, try to match an existing unresolved name.
		    while (tmpUnresolved != NULL) {
			if (tmpUnresolved->root == NULL) {	// Look for names which are without prefix.
			    if (tmpUnresolved->isMatching(tmpName)) break;
			}
			tmpUnresolved= (JCUnresolved *)tmpUnresolved->next;
		    }
		    if (tmpUnresolved != NULL) {
			aNamedExpr->setResolution(tmpUnresolved);
			tmpUnresolved->linkExpression(aNamedExpr);
		    }
		    else {
			    // Third, add the name as an unresolved.
			addUnresolved(aNamedExpr);
		    }
		}
	    }
	    else {
		cout << "ERRMSG: relateNamedExpr has simple name, no sub-expression !!\n";
	    }
	}
    }

    return true;
}


JCReferencedType *JCNameSpace::getSuperClassType(void)
{
    JCNameSpace *tmpLevel= superLevel;

    while (tmpLevel != NULL) {
	if (tmpLevel->getKind() == kClass) {
	    return tmpLevel->getSuperClassType();
	}
	tmpLevel= tmpLevel->superLevel;
    }

    return NULL;
}


JCResolved *JCNameSpace::getThisVariable(void)
{
    JCNameSpace *tmpLevel= superLevel;

    while (tmpLevel != NULL) {
	if (tmpLevel->getKind() == kMethod) {
	    return tmpLevel->getThisVariable();
	}
	tmpLevel= tmpLevel->superLevel;
    }

    return NULL;
}


JCResolved *JCNameSpace::getSuperVariable(void)
{
    JCNameSpace *tmpLevel= superLevel;

    while (tmpLevel != NULL) {
	if (tmpLevel->getKind() == kMethod) {
	    return tmpLevel->getSuperVariable();
	}
	tmpLevel= tmpLevel->superLevel;
    }

    return NULL;
}


bool JCNameSpace::mergeToSuperSpace(JCUnresolved *aSymbol)
{
    JCResolved *tmpResolved;
    bool hasMatch= false;

    // ATTN: For now, we only deal with unresolved that are 'rootless'.
    if (aSymbol->root != NULL) return true;

    if (superLevel == NULL) return false;    // Warning: quick exit.

/* Note: aSymbol peut trouver dans le super-space:
    1- le symbole qui est son 'root': le root provient soit du ns courant, soit d'un ns de classe,
     Un unresolved qui a une racine ne doit pas monter, puisqu'il est inutile au niveau
    sup. a moins qu'on puisse faire une relation entre son root et un autre defini dans le ns sup.
    Donc il faudrait chercher un resolved qui a le meme 'dereference' que son root.
    2- le symbole qui le represente (son root est nul ? non).
    3- le unresolved qui match son 'root'.
    4- le unresolved qui le match.
    5- rien.
*/

    tmpResolved= superLevel->resolved;

    while (tmpResolved != NULL) {
	if (aSymbol->isMatching(tmpResolved)) {
	    switch(aSymbol->getCategory()) {
		case JCName::uType:
		case JCName::uClass:
		case JCName::uInterface:
		case JCName::importation:
		    aSymbol->solveTypes(tmpResolved);
		    break;
		case JCName::unknownVariable:
		case JCName::localVariable:
		case JCName::fieldVariable:
		    aSymbol->solveExpressions(tmpResolved);
		    break;
		case JCName::uMethod:
		case JCName::uState:
		    aSymbol->solveExpressions(tmpResolved);
		    addMethodUsers((JCExprHolder *)aSymbol->users);
		    break;
		case JCName::noClue:	// Found a NamedExpr we knew nothing about.
		    aSymbol->updateNoClue(tmpResolved);
		    break;
		default:
		    cout << "ERRMSG: JCNameSpace::mergeToSuperSpace: having to solve an unknown ";
		    cout << "which is not supposed to exist.\n";
		    break;
	    }
	    // We relink the sub-names to the resolved field.
	    if (aSymbol->subNames != NULL) {
		JCUnresolved *tmpSubName, *tmpLastSubName= NULL;

		tmpSubName= aSymbol->subNames;
		while (tmpSubName != NULL) {
		    tmpSubName->root= tmpResolved;
		    tmpLastSubName= tmpSubName;
		    tmpSubName= (JCUnresolved *)tmpSubName->next;
		}
		tmpSubName= aSymbol->subNames;
		if (unresolved == NULL) {
		    unresolved= tmpSubName;
		}
		else {
		    lastUnresolved->next= tmpSubName;
		    tmpSubName->prev= lastUnresolved;
		}
		lastUnresolved= tmpLastSubName;
	    }
	    hasMatch= true;
	    break;
	}
	tmpResolved= (JCResolved *)tmpResolved->next; 
    }

    if (!hasMatch) {
	JCUnresolved *duplicata;
	if ((duplicata= superLevel->findUnresolved(aSymbol->ident, aSymbol->root)) != NULL) {
	    JCHolder *tmpHolder;

	    if (aSymbol->subNames != NULL) {
		// Add the subNames to the duplicata.
		JCUnresolved *tmpUnresolved, *tmpSubName;

		if ((tmpSubName= duplicata->subNames) != NULL) {
			// ATTN-971021 [HD]: Adding subNames must be by testing first
			//	if the subNames are not present in the duplicata, so that it doesn't
			//	get useless subNames.
		    while (tmpSubName->next != NULL) tmpSubName= (JCUnresolved *)tmpSubName->next;
		    tmpSubName->next= aSymbol->subNames;
		    aSymbol->subNames->prev= tmpSubName;
		}
		else {
		    duplicata->subNames= aSymbol->subNames;
		}
		tmpUnresolved= aSymbol->subNames;
		do {
		    tmpUnresolved->root= duplicata;
		    tmpUnresolved= (JCUnresolved *)tmpUnresolved->next;
		} while (tmpUnresolved != NULL);
	    }

		// Add the holders to the duplicata list.
	    if ((tmpHolder= duplicata->users) != NULL) {
		while (tmpHolder->next != NULL) tmpHolder= tmpHolder->next;
		tmpHolder->next= aSymbol->users;
	    }
	    else {
		duplicata->users= aSymbol->users;
	    }
	    switch(aSymbol->getCategory()) {
		case JCName::uType:
		case JCName::uClass:
		case JCName::uInterface:
		case JCName::importation:
		    // ATTN: Should there be a link done from the JCReferencedType to the unknown ?
		    break;
		case JCName::noClue:	// noClue symbols are NamedExpr, until they are resolved.
		    if (duplicata->getCategory() == JCName::uType) {
			JCUnresolved *tmpUnresolved;

			// ATTN: TODO: The unknown NamedExpr is to be deleted (with its users).
			aSymbol->subNames= NULL;
		    }
		    else if (duplicata->getCategory() != JCName::noClue) {
			aSymbol->updateNoClue(duplicata->getCategory());
			tmpHolder= aSymbol->users;
			do {
			    ((JCExprHolder *)tmpHolder)->setContentResolver(duplicata);
			    tmpHolder= tmpHolder->next;
			} while (tmpHolder != NULL);
		    }
		    break;
		case JCName::unknownVariable:
		case JCName::localVariable:
		case JCName::fieldVariable:
		case JCName::uMethod:
		case JCName::uState:
		    tmpHolder= aSymbol->users;
		    do {
			((JCExprHolder *)tmpHolder)->setContentResolver(duplicata);
			tmpHolder= tmpHolder->next;
		    } while (tmpHolder != NULL);
		    break;
	    }
	    
	    hasMatch= true;
	}
    }

    if (hasMatch) {
	delete aSymbol;
    }

    return hasMatch;
}


bool JCNameSpace::resolveAll(void)
{
    return true;
}


bool JCNameSpace::resolveAll(JCMethod *aContext)
{
    JCUnresolved *tmpUnres;
    JCResolved *aResolver;
    bool gotAllSymbols= true;

    if (unresolved == NULL) return true;		// Warning: quick exit.

    tmpUnres= unresolved;
    do {
	if (tmpUnres->root == NULL) {
	    // Not root.  What to do with this ?
	    if (getKind() == kBlock) {
		cout << "WARN: JCNameSpace::resolveAll: got name " << tmpUnres->ident->getAsciiValue();
		cout << " without a root, in method " << aContext->getAsciiValue() << ".\n";
		gotAllSymbols= false;
	    }
	    else {
		if ((aResolver= aContext->getOwner()->findSymbol(tmpUnres)) != NULL) {

		}
		else {
		    cout << "ERRMSG: JCNameSpace::resolveAll can't find a resolution for symbol " << tmpUnres->ident->getAsciiValue() << ", in method " << aContext->getAsciiValue() << ".\n";
		}
	    }
	}
	else if (tmpUnres->root->getSituation() == JCName::resolved) {
	    if ((aResolver= findResolved(tmpUnres->ident, (JCResolved *)tmpUnres->root)) == NULL) {
		cout << "ERRMSG: JCNameSpace::resolveAll can't find a resolution for symbol " << tmpUnres->ident->getAsciiValue() << " in method " << aContext->getAsciiValue() << ".\n";
		gotAllSymbols= false;
	    }
	    else {
		applyResolution(aResolver, tmpUnres);
	    }
	}
	else {
	    // Move this unresolved to the end of the list, since it depends on something unknown yet.
	    cout << "ERRMSG: JCNameSpace::resolveAll can't find a resolution for symbol " << tmpUnres->ident->getAsciiValue() << " in method " << aContext->getAsciiValue() << ".\n";
	}
	tmpUnres= (JCUnresolved *)tmpUnres->next;
    } while (tmpUnres != NULL);

    if (!gotAllSymbols && (superLevel != NULL)) {
	flushUnresolved();
	gotAllSymbols= true;
    }
    return gotAllSymbols;
}


void JCNameSpace::importUnresolved(JCUnresolved *aUnresList)
{
    JCUnresolved *tmpUnres, *nextUnres, *duplicata;
    JCHolder *tmpHolder;

    // NOTE-970207 [HD]: It is used when a JCReferencedType is resolved, to dump symbols
    // known to exist in the class name space.

    tmpUnres= aUnresList;
    while (tmpUnres != NULL) {
	nextUnres= (JCUnresolved *)tmpUnres->next;

	    // ATTN: Must check if the unknown is already known in the class, and resolve it
	    // instead of linking to unknowns.
	    // NOTE-970212 [HD]: Some of it is done below.  This could be eliminated by doing
	    // a replacement of  newly JCReferencedType by the first one found in a current
	    // nameSpace, thus always using the same temporary nameSpace.
	    // NOTE-970528 [HD]: More is done; if there is no root, then the symbol is searched in
	    // the resolution list.
	if (unresolved == NULL) {
	    JCResolved *aResolver;
		// First, check if the symbol is already resolved.
		// ATTN: 
	    if (tmpUnres->root == NULL) {
		if ((aResolver= findResolved(tmpUnres->ident)) != NULL) {
		    applyResolution(aResolver, tmpUnres);
		    tmpUnres= nextUnres;
		    continue;			// Warning: short loop.
		}
		else {
		    unresolved= tmpUnres;
		    tmpUnres->prev= NULL;
		}
	    }
	    else {
		    // TMP: Should continue the search...
		unresolved= tmpUnres;
		tmpUnres->prev= NULL;
	    }
	}
	else {
	    if ((duplicata= findUnresolved(tmpUnres->ident, tmpUnres->root)) != NULL) {
		// Link users.
		if ((tmpHolder= duplicata->users) != NULL) {
		    while (tmpHolder->next != NULL) tmpHolder= tmpHolder->next;
		    tmpHolder->next= tmpUnres->users;
		}
		else {
		    duplicata->users= tmpUnres->users;
		}
     		delete tmpUnres;
		tmpUnres= nextUnres;
		continue;
	    }
	    else {
	    }
	    lastUnresolved->next= tmpUnres;
	    tmpUnres->prev= lastUnresolved;
	}
	lastUnresolved= tmpUnres;
	lastUnresolved->next= NULL;

	tmpUnres= nextUnres;
    }
}


void JCNameSpace::importUnresolved(JCNameSpace *aSpace)
{

    importUnresolved(aSpace->unresolved);
    aSpace->lastUnresolved= aSpace->unresolved= NULL;
}


JCUnresolved * JCNameSpace::getFirstUnresolved(void)
{
    return unresolved;
}


void JCNameSpace::removeUnresolved(JCUnresolved *anUnres)
{
    if (unresolved == anUnres) {
	unresolved= (JCUnresolved *)anUnres->next;
	if (anUnres->next != NULL) anUnres->next->prev= NULL;
    }
    else {
	if (anUnres->prev != NULL) {
	    anUnres->prev->next= anUnres->next;
	}
    }
    if (lastUnresolved == anUnres) {
	lastUnresolved= (JCUnresolved *)anUnres->prev;
	if (anUnres->prev != NULL) anUnres->prev->next= NULL;
    }
    else {
	if (anUnres->next != NULL) {
	    anUnres->next->prev= anUnres->prev;
	}
    }
}


void JCNameSpace::addMethodUsers(JCExprHolder *someUsers)
{
    JCExprHolder *tmpHolder;

    if (someUsers == NULL) return;		// Warning: quick exit.

    tmpHolder= someUsers;
    while (tmpHolder->next != NULL) tmpHolder= (JCExprHolder *)tmpHolder->next;

    if (methodHolders == NULL) {
	methodHolders= someUsers;
	lastMethodHolder= tmpHolder;
    }
    else {
	lastMethodHolder->next= someUsers;
	lastMethodHolder= tmpHolder;
    }
}


bool JCNameSpace::resolveMethodUsers(void)
{
    JCExprHolder *tmpHolder;
    JCInvokeExpr *anInvoke;
    JCName *aResolver;
    bool result;

    if (methodHolders == NULL) return true;		// Warning: quick exit.

	// ATTN-971119 [HD]: All the assumptions in the following code should be checked for
	// validity.

    tmpHolder= methodHolders;
    result= true;
    do {
	if ((anInvoke= (JCInvokeExpr *)tmpHolder->content()) != NULL) {
	    if (anInvoke->getCategory() != JCExpression::eInvoke) {
		cout << "ERRMSG: Method ";
		switch(anInvoke->getCategory()) {
		    case JCExpression::eVariable:
			cout << ((JCVarAccess *)anInvoke)->getVarName()->getAsciiValue();
			break;
		    case JCExpression::eField:
			cout << ((JCNamedExpr *)anInvoke)->getName()->getAsciiValue();
			break;
		    default:
			cout << "<unknown>";
			break;
		}
		cout << " is used incorrectly (line " << anInvoke->getStartLine() << ").\n";
		result= false;
	    }
	    else if ((aResolver= anInvoke->resolution()) == NULL) {
		cout << "ERRMSG: No resolution for invoke ";
		cout << anInvoke->getName()->getAsciiValue() << " (line ";
		cout << anInvoke->getStartLine() << ").\n";
		result= false;
	    }
	    else if (aResolver->getSituation() == JCName::resolved) {
		JCMethod *aMethod;
    
		if ((aMethod= (JCMethod *)((JCResolved *)aResolver)->getDefinition()) != NULL) {
		    if (!aMethod->resolveOverloading(anInvoke)) {
			cout << "ERRMSG: No method match typing of ";
			cout << anInvoke->getName()->getAsciiValue() << " (line ";
			cout << anInvoke->getStartLine() << ").\n";
			result= false;
		    }
		}
		else result= false;
	    }
	    else result= false;
	}
	else {
	    cout << "ERRMSG: JCNameSpace::resolveMethodUsers: Internal error, a tmpHolder without content.\n";
	}
	tmpHolder= (JCExprHolder *)tmpHolder->next;
    } while (tmpHolder != NULL);

    return result;
}

/**************************************************
* Implementation: JCMethodSpace.
**************************************************/

JCMethodSpace::JCMethodSpace(JCType *aType) : JCNameSpace()
{
    thisVar= aType->getThisDeclarator();
    superVar= aType->getSuperDeclarator();
}


JCNameSpace::Kind JCMethodSpace::getKind(void)
{
    return kMethod;
}


void JCMethodSpace::setThisResolver(JCResolved *aResolution)
{
    thisVar= aResolution;
}


JCResolved *JCMethodSpace::getThisVariable(void)
{
    return thisVar;
}


JCResolved *JCMethodSpace::getSuperVariable(void)
{
    return superVar;
}


bool JCMethodSpace::flushUnresolved(void)
{
    if (unresolved != NULL) {
	JCUnresolved *tmpUnres= unresolved, *nextUnres, *tmpList= NULL, *lastTmpList;

	while (tmpUnres != NULL) {
	    nextUnres= (JCUnresolved *)tmpUnres->next;
	    if (tmpUnres->nameType == JCName::localVariable) {
		cout << "ERRMSG: JCMethodSpace::flushUnresolved has local variable " << tmpUnres->ident->getAsciiValue() << " not solved in ";
	    }
	    else {
		if (tmpUnres->root != NULL) {
		    tmpUnres= nextUnres;
		    continue;
		}
    
		    // Unlink the node from the current name space list.
		if (tmpUnres->prev) tmpUnres->prev->next= tmpUnres->next;
		if (tmpUnres->next) tmpUnres->next->prev= tmpUnres->prev;
		if (unresolved == tmpUnres) {
		    unresolved= nextUnres;
		}
		if (lastUnresolved == tmpUnres) {
		    if (tmpUnres->prev != NULL)
			lastUnresolved= (JCUnresolved *)tmpUnres->prev;
		    else
			lastUnresolved= unresolved;
		}

		if (!mergeToSuperSpace(tmpUnres)) {
    		    if (tmpList == NULL) {
			tmpList= tmpUnres;
			tmpUnres->prev= NULL;
		    }
		    else {
			tmpUnres->prev= lastTmpList;
			lastTmpList->next= tmpUnres;
		    }
		    tmpUnres->next= NULL;
		    lastTmpList= tmpUnres;
		}
	    }
	    tmpUnres= nextUnres;
	}

	    // Link the temporary list (extracted nodes) to the super level.
	if (tmpList != NULL) {
	    if (superLevel->lastUnresolved != NULL) {
		superLevel->lastUnresolved->next= tmpList;
		tmpList->prev= superLevel->lastUnresolved;
	    }
	    else {
		superLevel->unresolved= tmpList;
	    }
	    superLevel->lastUnresolved= lastTmpList;
	}
     }
    return false;
}


/**************************************************
* Implementation: JCClassSpace.
**************************************************/

JCClassSpace::JCClassSpace(JCClass *aClass) : JCNameSpace()
{
    currentClass= aClass;
    noClueList= new UnresolvedList();
}


JCNameSpace::Kind JCClassSpace::getKind(void)
{
    return kClass;
}


JCClass *JCClassSpace::getCurrentClass(void)
{
    return currentClass;
}


JCReferencedType *JCClassSpace::getSuperClassType(void)
{
    if (currentClass != NULL) {
	return currentClass->getSuperType();
    }
    return NULL;
}


bool JCClassSpace::flushUnresolved(void)
{
    if (unresolved != NULL) {
	JCUnresolved *tmpUnres= unresolved, *nextUnres, *tmpList= NULL, *lastTmpList;

	while (tmpUnres != NULL) {
	    nextUnres= (JCUnresolved *)tmpUnres->next;
	    if ((tmpUnres->nameType == JCName::localVariable)
		    || (tmpUnres->nameType == JCName::fieldVariable)
		    || (tmpUnres->nameType == JCName::unknownVariable)
		    || (tmpUnres->nameType == JCName::uMethod)
		    || (tmpUnres->nameType == JCName::uState)) {
		// Must try to resolve from super-classes !  This is done later, in resolveAll.
	    }
	    else {
		    // Unlink the node from the current name space list.
		if (tmpUnres->prev) tmpUnres->prev->next= tmpUnres->next;
		if (tmpUnres->next) tmpUnres->next->prev= tmpUnres->prev;
		if (unresolved == tmpUnres) {
		    unresolved= nextUnres;
		}
		if (lastUnresolved == tmpUnres) {
		    if (tmpUnres->prev != NULL)
			lastUnresolved= (JCUnresolved *)tmpUnres->prev;
		    else
			lastUnresolved= unresolved;
		}

		    // Add the node to the temp. list.
		if (tmpList == NULL) {
		    tmpList= tmpUnres;
		    tmpUnres->prev= NULL;
		}
		else {
		    tmpUnres->prev= lastTmpList;
		    lastTmpList->next= tmpUnres;
		}
		tmpUnres->next= NULL;
		lastTmpList= tmpUnres;
	    }

		// If the unres is a mistery, we remember it in case it reveals itself to be a field variable
		// instead of a type or package component.
	    if (tmpUnres->nameType == JCName::noClue) {
		noClueList->addObject(tmpUnres);
	    }

	    tmpUnres= nextUnres;
	}

	    // Link the temporary list (extracted nodes) to the super level.
	if (tmpList != NULL) {
	    if (superLevel->lastUnresolved != NULL) {
		superLevel->lastUnresolved->next= tmpList;
		tmpList->prev= superLevel->lastUnresolved;
	    }
	    else {
		superLevel->unresolved= tmpList;
	    }
	    superLevel->lastUnresolved= lastTmpList;
	}
     }
    return false;
}


bool JCClassSpace::resolveAll(void)
{
    JCUnresolved *tmpUnres, *nextUnres;
    JCResolved *aResolver;
    unsigned int tmpLength;
    bool gotAllSymbols= true;

    // ATTN-980523 [HD]: This is a bug trap, since unresolved that were found in upper layers
    // of the name spaces are delete, but are still refered in the noClueList.  The resolution of a
    // noClue from higher name spaces (package) must be broadcasted to its classes name spaces,
    // so they take out the unresolved from their noClueList.
    if ((tmpLength= noClueList->count()) > 0) {
	for (unsigned int i= 0; i < tmpLength; i++) {
	    tmpUnres= noClueList->objectAt(i); 
	    if (tmpUnres->getCategory() == JCName::fieldVariable) {
		if (unresolved == NULL) {
		    unresolved= tmpUnres;
		}
		else {
		    lastUnresolved->link(tmpUnres);
		}
		lastUnresolved= tmpUnres;
	    }
	    else if (tmpUnres->getCategory() == JCName::uType) {
		delete tmpUnres;
	    }
	}
    }

    if (unresolved == NULL) return true;

    tmpUnres= unresolved;
    do {
	nextUnres= (JCUnresolved *)tmpUnres->next;

// MOD-971022 [HD]: Added a search first in current name space.
	if ((aResolver= findResolved(tmpUnres->getIdent())) != NULL) {
	    applyResolution(aResolver, tmpUnres);
	}
	else if ((aResolver= currentClass->findSymbol(tmpUnres)) != NULL) {
	    applyResolution(aResolver, tmpUnres);
	}
	else {
	    cout << "ERRMSG: JCClassSpace::resolveAll can not resolve symbol " << tmpUnres->getIdent()->getAsciiValue() << " used in class " << currentClass->getName()->getAsciiValue() << " !\n";
//	    gotAllSymbols= false;
	}
	tmpUnres= nextUnres;
	    // ATTN: Must take care of addition of symbols by applyResolution; the next line has to do it.
//	if ((tmpUnres == NULL) tmpUnres= unresolved;
    } while (tmpUnres != NULL);

    return gotAllSymbols;
}


/**************************************************
* Implementation: JCImportedClass.
**************************************************/

JCImportSpace::JCImportSpace(JCImportedType *aType)
    : JCNameSpace()
{
    ourType= aType;
}


bool JCImportSpace::resolveAll(void)
{
    if (unresolved != NULL) {
	cout << "ERRMSG: JCImportSpace::resolveAll is called without a ImportManager.\n";
	return false;
    }
    else return true;
}


bool JCImportSpace::resolveAll(JCImportManager *aManager)
{
    JCUnresolved *tmpUnres, *nextUnres, *tmpEnd;
    JCResolved *aResolver;
    bool gotAllSymbols= true;

    if (unresolved == NULL) return true;

    tmpUnres= unresolved;

    do {
	nextUnres= (JCUnresolved *)tmpUnres->next;

	if ((aResolver= ((JCImportedClass *)ourType)->findSymbol(tmpUnres)) != NULL) {
	    if (tmpUnres->getSubNames() != NULL) {
		JCReferencedType *returnType= NULL;
		switch(aResolver->getCategory()) {
		    case JCName::uType:
		    case JCName::uClass:
		    case JCName::uInterface:
		    case JCName::importation:
			    // Nothing to do.
			break;
		    case JCName::localVariable:
			returnType= ((JCVariableDeclaration *)aResolver->getDefinition())->typing();
			break;
		    case JCName::fieldVariable:
		    case JCName::uMethod:
		    case JCName::uState:
			returnType= ((JCMember *)aResolver->getDefinition())->getReturnedType();
			break;
		    case JCName::unknownVariable:
		    case JCName::noClue:
		    default:
			cout << "ERRMSG: JCImportSpace::resolveAll: want to find an impossible ";
			cout << "member category.\n";
			break;
		}
		if (returnType != NULL) {
		    JCType *realType;
		    if ((realType= aManager->findReferedType(returnType)) != NULL) {
			returnType->setResolution(realType->getRefEquivalent()->resolution());
		    }
		}
	    }
	    applyResolution(aResolver, tmpUnres);
	}
	else {
	    cout << "ERRMSG: JCClassSpace::resolveAll can not resolve symbol " << tmpUnres->getIdent()->getAsciiValue() << " used in class " << ourType->getName()->getAsciiValue() << " !\n";
//	    gotAllSymbols= false;
	}
	tmpUnres= nextUnres;
	    // ATTN: Must take care of addition of symbols by applyResolution; the next line has to do it.
//	if ((tmpUnres == NULL) tmpUnres= unresolved;
    } while (tmpUnres != NULL);

    return gotAllSymbols;
}


JCResolved *JCImportSpace::findResolved(JCIdentifier *anIdent)
{
    JCResolved *result;

    if ((result= JCNameSpace::findResolved(anIdent)) == NULL) {
	result= ourType->findMemberSymbol(anIdent);
    }
    
    return result;
}


