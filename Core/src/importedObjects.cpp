/**************************************************
* File: importedObjects.cc.
* Desc: Implementation of the JCImportedType.
* Module: AkraLog : JavaComp.
* Rev: 28 mai 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <string.h>
#include "constants.h"
#include "classSource.h"
#include "nameSpace.h"
#include "typing.h"
#include "importClass.h"
#include "package.h"
#include "identifiers.h"
#include "outConstant.h"
#include "lists.h"
#include "expressions.h"
#include "containment.h"
#include "importedObjects.h"


/**************************************************
* Implementation: JCImportedGhost.
**************************************************/

JCImportedGhost::JCImportedGhost(void)
{
    dataSource= NULL;
    users= NULL;
    dependants= NULL;
    realType= NULL;
}


JCImportedGhost::JCImportedGhost(JCFileSource *aSource, JCIdentifier *aName)
{
    dataSource= aSource;
    users= NULL;
    dependants= NULL;
    className= aName;
    realType= NULL;
}


void JCImportedGhost::attachMissing(JCUnresolved *anUnresolved)
{

    if (anUnresolved->getCategory() == JCName::noClue) {
// RENDU ICI-971021.

	// The name semantic fonction was unknown, must do an update of the situation to treat
	// it as a type.
	JCUnresolved *tmpSubName;
	JCHolder *lastUser, *nextUser, *tmpUser= anUnresolved->flushUsers();
	JCNamedExpr *tmpExpr;
	JCContainer *tmpOwner;

	tmpSubName= anUnresolved->getSubNames();

	while (tmpSubName != NULL) {
	    if (tmpSubName->getCategory() == JCName::noClue) {
		tmpSubName->updateNoClue(JCName::fieldVariable);
	    }
	    tmpSubName->setRoot(NULL);
	    tmpSubName= (JCUnresolved *)tmpSubName->getNext();
	}

	while (tmpUser != NULL) {
	    nextUser= tmpUser->getNext();
	    switch(tmpUser->getCategory()) {
		case JCHolder::hExpression:
		    tmpExpr= (JCNamedExpr *)((JCExprHolder *)tmpUser)->content();
		    if ((tmpOwner= tmpExpr->getOwner()) != NULL) {
			if (tmpOwner->getContainerType() == (unsigned int)JCContainer::expression) {
			    // TMPTMP-971021:
			    ((JCNamedExpr *)tmpOwner)->setSubExpression(tmpExpr->getSubExpression());
			}
		    }
		    delete tmpExpr;
		    delete tmpUser;
		    break;
		case JCHolder::hType:
		    if (users == NULL) {
			users= (JCTypeHolder *)tmpUser;
		    }
		    else {
			lastUser->setNext(tmpUser);
		    }
		    lastUser= tmpUser;
		    lastUser->setNext(NULL);
		    break;
		default:
		    cout << "ERRMSG: JCImportedGhost::attachMissing got a tmpUser of unknown type.\n";
		    break;
	    }
	    tmpUser= nextUser;
	}

	if (dependants != NULL) {
	    JCUnresolved *tmpUnres, *lastUnres;
    
	    tmpUnres= anUnresolved->getSubNames();
	    lastUnres= (JCUnresolved *)tmpUnres->getNext();
	    while (lastUnres != NULL) {
		tmpUnres= lastUnres;
		lastUnres= (JCUnresolved *)tmpUnres->getNext();
	    }
	    tmpUnres->link(dependants);
	}
	dependants= anUnresolved->getSubNames();
	anUnresolved->nameType= JCName::uType;
    }
    else {
	if (users != NULL) {
	    JCTypeHolder *firstUser, *tmpUsers, *lastUsers;
    
	    firstUser= tmpUsers= (JCTypeHolder *)anUnresolved->flushUsers();
	    lastUsers= (JCTypeHolder *)tmpUsers->getNext();
	    while (lastUsers != NULL) {
		tmpUsers= lastUsers;
		lastUsers= (JCTypeHolder *)tmpUsers->getNext();
	    }
	    tmpUsers->setNext(users);
	    users= firstUser;
	}
	else {
	    users= (JCTypeHolder *)anUnresolved->flushUsers();
	}
    

	JCUnresolved *tmpUnres, *lastUnres;

	lastUnres= tmpUnres= anUnresolved->getSubNames();
	while (tmpUnres != NULL) {
	    tmpUnres->setRoot(NULL);
	    lastUnres= tmpUnres;
	    tmpUnres= (JCUnresolved *)tmpUnres->getNext();
	}

	if (dependants != NULL) {
    	    if (lastUnres != NULL) lastUnres->link(dependants);
	}
	dependants= anUnresolved->getSubNames();
    }
}


JCImportedType *JCImportedGhost::load(JCCompiler *compiler)
{
    JCImportClassFile *classFile;
    JCImportedClass *result= NULL;

    if (realType != NULL) return realType;	// Warning: quick exit.

    if ((fileKind == kClass) || (fileKind == kGlass)) {
	if ((classFile= dataSource->load(compiler)) != NULL) {
	    JCTypeHolder *tmpTypeHolder;
	    JCReferencedType *aType;
	    JCResolved *resolver;
	    JCUnresolved *tmpDependant, *nextDep;
    
	    cout << "DBG: JCImportedGhost::load: imported compiled type " << className->getAsciiValue() << ".\n";

	    realType= result= new JCImportedClass(classFile, className);
	    result->setPackage(package);
	    resolver= result->getResolver();
    
	    tmpTypeHolder= users;
	    while (tmpTypeHolder != NULL) {
		users= (JCTypeHolder *)tmpTypeHolder->getNext();
		if (((JCHolder *)tmpTypeHolder)->getCategory() == JCHolder::hType) {
		    aType= tmpTypeHolder->content();
		    aType->setResolution(resolver);
		    delete tmpTypeHolder;
		    tmpTypeHolder= users;
		}
		else {
		    JCHolder *fakeTypeHolder= tmpTypeHolder;
		    // ATTN-970611 [HD]: The JCNamedExpr in the holder is most likely
		    // a memory leak.
		    delete fakeTypeHolder;
		}
		tmpTypeHolder= users;
	    }
    
	    tmpDependant= dependants;
	    while (tmpDependant != NULL) {
		nextDep= (JCUnresolved *)tmpDependant->getNext();
		if (tmpDependant->getCategory() == JCName::noClue) {
		    tmpDependant->updateNoClue(resolver);
		}
		tmpDependant= nextDep;
	    }
    
	    result->importUnknown(dependants);
	}
    }
    else {
	cout << "ERRMSG: Warning, import of a source file.\n";
    }
    return result;
}


bool JCImportedGhost::isNamed(JCIdentifier *aName)
{
    return className->isMatching(aName);
}


void JCImportedGhost::setKind(Kind aKind)
{
    fileKind= aKind;
}


JCImportedGhost::Kind JCImportedGhost::getKind(void)
{
    return fileKind;
}


void JCImportedGhost::setPackage(JCImportedPackage *aPackage)
{
    package= aPackage;
}


JCImportedPackage *JCImportedGhost::getPackage(void)
{
    return package;
}


/**************************************************
* Implementation: JCImportedType.
**************************************************/

JCImportedType::JCImportedType(void)
{
    nsResolver= NULL;
}


JCImportedType::JCImportedType(JCIdentifier *aName, JCName::UnitType preciseType) : JCType()
{
    shortName= aName;
    nameSpace= new JCImportSpace(this);
    nsResolver= nameSpace->quickAddResolved(aName, this, preciseType);
}


JCResolved *JCImportedType::getResolver(void)
{
    return nsResolver;
}


bool JCImportedType::resolveClassSymbols(JCImportManager *aManager)
{
    return ((JCImportSpace *)nameSpace)->resolveAll(aManager);
}


/*************************************************
* Implementation: JCImportedClass.
**************************************************/

JCImportedClass::JCImportedClass(void)
{
    theClass= NULL;
}


JCImportedClass::JCImportedClass(JCImportClassFile *aClass, JCIdentifier *aName) : JCImportedType(aName, JCName::uClass)
{
    theClass= aClass;
    aClass->setDual(this);
    refEquivalent= new JCReferencedType(TYPE_CLASS, aName, nsResolver);
    shadow= new JCCteClass(JCCteUtf8::addUniqueInstance((unsigned short *)theClass->getAsciiName()));
}


char *JCImportedClass::getAsciiName(void)
{
    return theClass->getAsciiName();
}


unsigned int JCImportedClass::storeFullName(char *buffer)
{
    strcpy(buffer, theClass->getAsciiName());
    return strlen(buffer);
}


bool JCImportedClass::isInterface(void)
{
    return false;
}


JCType *JCImportedClass::getSuper(void)
{
    if (extended == NULL) {
	JCCFUtf8 *superClass;

	if ((superClass= theClass->getSuper()) != NULL) {
	    if ((extended= ((JCImportedPackage *)package)->loadReferedType(superClass)) != NULL) {
		JCType *superSuper;

		superSuper= extended;
		do {
		    if (package->isTypeStarClass(superSuper)) {
		    	break;
		    }

			// Expand the process higher.
			// ATTN: Should check that superSuper is always a 'class'.
		    superSuper= ((JCImportedClass *)superSuper)->getSuper();
		} while (superSuper != NULL);
	    }
	}

/* MOD-971117 [HD]: If no super-class is found, we don't supply the star class.
	if (extended == NULL) {		// If the extended is still null here, we get the root class.
	    extended= package->getStarClass()->getRealType();
	}
*/
    }
    return extended;
}


JCReferencedType *JCImportedClass::getSuperType(void)
{
    if (extended == NULL) {
	getSuper();
    }
    return extended->getRefEquivalent();
}


JCResolved *JCImportedClass::findSymbol(JCUnresolved *anUnknown)
{
    JCType *tmpExtended;
    JCFieldInfo *fieldInfo;
    JCMethodInfo *methodInfo;
    JCResolved *result= NULL;

	// First, look in the current space, for previously known symbols.
	if ((result= nameSpace->findResolved(anUnknown->getIdent())) != NULL) {
	    return result;		// Warning: quick exit.
	}

	// Second, look in the members.
    switch(anUnknown->getCategory()) {
	case JCName::unknownVariable:
	case JCName::localVariable:
	case JCName::fieldVariable:
	    if ((fieldInfo= theClass->getField(anUnknown->getIdent())) != NULL) {
		JCField *aField;

		if ((aField= fieldInfo->resolve(package->getCompiler())) != NULL) {
		    fields->addObject(aField);
		    result= nameSpace->quickAddResolved(anUnknown->getIdent(), aField, JCName::fieldVariable);
		    return result;		// Warning: quick exit.
		}
		else {
		    cout << "ERRMSG: JCImportedClass::findSymbol can't dereference field " << anUnknown->getIdent()->getAsciiValue() << " of class " << theClass->getAsciiName() << ".\n";
		}
	    }
	    break;
	case JCName::uMethod:
	case JCName::uState:
	    if ((methodInfo= theClass->getBaseMethod(anUnknown->getIdent())) != NULL) {
		if (methodInfo->isState()) {
		    JCState *aState;

		    do { 
			if ((aState= (JCState *)methodInfo->resolve(package->getCompiler())) != NULL) {
			    states->addObject(aState);
			    result= nameSpace->quickAddResolved(anUnknown->getIdent(), aState, JCName::uState);
			}
			else {
			    cout << "ERRMSG: can't dereference state.\n";
			}
			methodInfo= theClass->getNextMethod(methodInfo);
		    } while (methodInfo != NULL);
		    return result;		// Warning: quick exit.
		}
		else {
		    JCMethod *aMethod;

		    do {
			if ((aMethod= methodInfo->resolve(package->getCompiler())) != NULL) {
			    methods->addObject(aMethod);
			    result= nameSpace->quickAddResolved(anUnknown->getIdent(), aMethod, JCName::uMethod);
			}
			else {
			    cout << "ERRMSG: can't dereference method.\n";
			}
			methodInfo= theClass->getNextMethod(methodInfo);
		    } while (methodInfo != NULL);
		    return result;		// Warning: quick exit.
		}
	    }
	    break;
    }

    if (extended == NULL) {
	getSuper();		// Fetch super-class if not yet present.
    }

	// Third, look in the super-class space.
    if (extended != NULL) {
	result= extended->findSymbol(anUnknown->getIdent());
    }
    return result;
}


JCResolved *JCImportedClass::findSymbol(JCIdentifier *aName)
{
    JCType *tmpExtended;
    JCFieldInfo *fieldInfo;
    JCMethodInfo *methodInfo;
    JCResolved *result= NULL;

	// First, look in the current space, for previously known symbols
    if ((result= nameSpace->findResolved(aName)) != NULL) {
	return result;		// Warning: quick exit.
    }

    if ((fieldInfo= theClass->getField(aName)) != NULL) {
	JCField *aField;

	if ((aField= fieldInfo->resolve(package->getCompiler())) != NULL) {
	    fields->addObject(aField);
	    result= nameSpace->quickAddResolved(aName, aField, JCName::fieldVariable);
	    return result;		// Warning: quick exit.
	}
	else {
	    cout << "ERRMSG: JCImportedClass::findSymbol<ident> can't dereference field " << aName->getAsciiValue() << " of class " << theClass->getAsciiName() << ".\n";
	}
    }

    if ((methodInfo= theClass->getBaseMethod(aName)) != NULL) {
	if (methodInfo->isState()) {
	    JCState *aState;
	    do { 
		if ((aState= (JCState *)methodInfo->resolve(package->getCompiler())) != NULL) {
		    states->addObject(aState);
		    result= nameSpace->quickAddResolved(aName, aState, JCName::uState);
		}
		else {
		    cout << "ERRMSG: can't dereference state.\n";
		}
		methodInfo= theClass->getNextMethod(methodInfo);
	    } while (methodInfo != NULL);
	    return result;		// Warning: quick exit.
	}
	else {
	    JCMethod *aMethod;
	    do {
		if ((aMethod= methodInfo->resolve(package->getCompiler())) != NULL) {
		    methods->addObject(aMethod);
		    result= nameSpace->quickAddResolved(aName, aMethod, JCName::uMethod);
		}
		else {
		    cout << "ERRMSG: can't dereference method.\n";
		}
		methodInfo= theClass->getNextMethod(methodInfo);
	    } while (methodInfo != NULL);
	    return result;		// Warning: quick exit.
	}
    }

    if (extended == NULL) {
	getSuper();		// Fetch super-class if not yet present.
    }

	// Third, look in the super-class space.
    if ((extended != NULL) && (extended != this)) {
	result= extended->findSymbol(aName);
    }
    return result;
}


JCResolved *JCImportedClass::findMemberSymbol(JCIdentifier *aName)
{
    JCType *tmpExtended;
    JCFieldInfo *fieldInfo;
    JCMethodInfo *methodInfo;
    JCResolved *result= NULL;

    if ((fieldInfo= theClass->getField(aName)) != NULL) {
	JCField *aField;

	if ((aField= fieldInfo->resolve(package->getCompiler())) != NULL) {
	    fields->addObject(aField);
	    result= nameSpace->quickAddResolved(aName, aField, JCName::fieldVariable);
	    return result;		// Warning: quick exit.
	}
	else {
	    cout << "ERRMSG: JCImportedClass::findMemberSymbol can't dereference field " << aName->getAsciiValue() << " of class " << theClass->getAsciiName() << ".\n";
	}
    }

    if ((methodInfo= theClass->getBaseMethod(aName)) != NULL) {
	if (methodInfo->isState()) {
	    JCState *aState;

	    do {
		if ((aState= (JCState *)methodInfo->resolve(package->getCompiler())) != NULL) {
		    states->addObject(aState);
		    result= nameSpace->quickAddResolved(aName, aState, JCName::uState);
		}
		else {
		    cout << "ERRMSG: can't dereference state.\n";
		}
		methodInfo= theClass->getNextMethod(methodInfo);
	    } while (methodInfo != NULL);
	    return result;		// Warning: quick exit.
	}
	else {
	    JCMethod *aMethod;

	    do {
		if ((aMethod= methodInfo->resolve(package->getCompiler())) != NULL) {
		    methods->addObject(aMethod);
		    result= nameSpace->quickAddResolved(aName, aMethod, JCName::uMethod);
		}
		else {
		    cout << "ERRMSG: can't dereference method.\n";
		}
		methodInfo= theClass->getNextMethod(methodInfo);
	    } while (methodInfo != NULL);
	    return result;		// Warning: quick exit.
	}
    }

    if (extended == NULL) {
	getSuper();		// Fetch super-class if not yet present.
    }

	// Third, look in the super-class space.
    if ((extended != NULL) && (extended != this)) {
	result= extended->findSymbol(aName);
    }
    return result;
}


/*************************************************
* Implementation: JCImportedField.
**************************************************/

JCImportedField::JCImportedField(JCImportedType *containterType, char *aName, JCReferencedType *aType) : JCField()
{ 
	// JCMember variables.
    owner= containterType;
    rawType= aType;
    nbrDimensions= rawType->getNbrDimensions();
    identName= JCCteUtf8::addUniqueInstance((unsigned short *)aName);

	// TODO: Prepare an ExpressionList to incorporate the initializer, for final fields.
}


void JCImportedField::buildShadow(char *signature)
{
    JCCteNameAndType *tmpNameType;
    JCCteUtf8 *tmpSignature;

    tmpSignature= JCCteUtf8::addUniqueInstance((unsigned short *)signature);
    tmpNameType= new JCCteNameAndType(identName, tmpSignature);
    shadow= new JCCteFieldRef(owner->getShadow(), tmpNameType);
}


/*************************************************
* Implementation: JCImportedMethod.
**************************************************/

JCImportedMethod::JCImportedMethod(JCImportedType *containterType, char *aName, unsigned int nbrTypes, JCReferencedType **types) : JCMethod()
{ 
	// JCMember variables.
    owner= containterType;
    rawType= types[0];
    identName= JCCteUtf8::addUniqueInstance((unsigned short *)aName);

	// JCMethod variables.
    constructorFlag= (aName[0] == '<');
    nbrArguments= nbrTypes-1;
    if (nbrArguments > 0) {
	argTypes= new JCReferencedType*[nbrArguments];
	for (unsigned int i= 0; i < nbrArguments; i++) {
	    argTypes[i]= types[i+1];
	}
    }
    rawName= new JCDimIdentifier();
    rawName->setName(new JCIdentifier(identName));
}


void JCImportedMethod::buildShadow(char *signature)
{
    JCCteNameAndType *tmpNameType;
    JCCteUtf8 *tmpSignature;

    tmpSignature= JCCteUtf8::addUniqueInstance((unsigned short *)signature);
    tmpNameType= new JCCteNameAndType(identName, tmpSignature);
    shadow= new JCCteMethodRef(owner->getShadow(), tmpNameType);
}


/*************************************************
* Implementation: JCImportedState.
**************************************************/

JCImportedState::JCImportedState(JCImportedType *containterType, char *aName, unsigned int nbrTypes, JCReferencedType **types) : JCState()
{ 
	// JCMember variables.
    owner= containterType;
    rawType= types[0];
    identName= JCCteUtf8::addUniqueInstance((unsigned short *)aName);

	// JCMethod variables.
    constructorFlag= (aName[0] == '<');
    nbrArguments= nbrTypes-1;
    if (nbrArguments > 0) {
	argTypes= new JCReferencedType*[nbrArguments];
	for (unsigned int i= 0; i < nbrArguments; i++) {
	    argTypes[i]= types[i+1];
	}
    }
    rawName= new JCDimIdentifier();
    rawName->setName(new JCIdentifier(identName));

    // TODO: Take care of transition list, for integrity checking.
}
