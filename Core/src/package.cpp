/**************************************************
* File: package.cc.
* Desc: Implementation of the packages class.
* Module: AkraLog : JavaComp.
* Rev: 5 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
#if defined(NeXT)   /* MOD-MSC: libc.h n'existe pas chez VC++. */
#include <libc.h>
#endif
#if defined(_WIN32)
#include <stdlib.h>
#include <direct.h>
#endif
#if defined(__linux__)
#include <unistd.h>
#endif
};

#include <iostream.h>
#include <string.h>	/* MOD-MSC: ajoute pour strcpy. */
#include "compileObjects.h"
#include "compiler.h"
#include "lists.h"
#include "identifiers.h"
#include "expressions.h"
#include "nameSpace.h"
#include "typing.h"
#include "outConstant.h"
#include "constants.h"
#include "classSource.h"
#include "importClass.h"
#include "importedObjects.h"
#include "inConstant.h"
#include "importManager.h"
#include "package.h"


/**************************************************
* Implementation: JCPackageDeclaration.
**************************************************/

JCType *JCPackageDeclaration::findName(JCIdentifier *aName)
{
    return NULL;
}


/**************************************************
* Implementation: JCPackageName.
**************************************************/

JCPackageName::JCPackageName(void)
{
    name= new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)"current"));
    path= new char[1024];
#if defined(NeXT)
    strcpy(path, getwd(path));
#else
    strcpy(path, getcwd(path, 1024));
#endif
    isUnnamed= true;
}


JCPackageName::JCPackageName(JCIdentifier *aName)
{
    path= NULL;
    name= aName;
    isUnnamed= false;
}


void JCPackageName::addName(JCIdentifier *aName)
{
    if (name != NULL) {
	name->addComponent(aName);
     }
    else {
	name= aName;	// ATTN: Must review this path assignation.
     }
    isUnnamed= false;
    return;
}


JCIdentifier *JCPackageName::getName(void)
{
    return name;
}


void JCPackageName::setDirectAccess(char *aPath)
{
    path= aPath;	
}


char *JCPackageName::getPath(void)
{
    if (path == NULL) {
	JCIdentifier *cursor;
	unsigned int pathLength, componentNbr;

	componentNbr= pathLength= 0;

	cursor= name;
	do {
	    pathLength+= cursor->nameLength();
	    componentNbr++;
	    cursor= cursor->getComponent();
	} while (cursor != NULL);

	path= new char[pathLength + componentNbr + 1];
	strcpy(path, name->getAsciiValue());
	cursor= name->getComponent();
	while (cursor != NULL) {
	    strcat(path, "/");
	    strcat(path, cursor->getAsciiValue());
	    cursor= cursor->getComponent();
	}
    }
    return path;
}


unsigned int JCPackageName::getDotNotation(char *buffer)
{
    JCIdentifier *tmpName;
    unsigned int totalLength= 0;

    if (isUnnamed) return 0;
    tmpName= name;
    while (tmpName != NULL) {
	strcpy(&buffer[totalLength], tmpName->getAsciiValue());
	totalLength+= tmpName->getValue()->asciiLength();
	tmpName= tmpName->getComponent();
	if (tmpName != NULL) buffer[totalLength++]= '/';
    }
    return totalLength;
}


bool JCPackageName::matchName(JCIdentifier *aName, unsigned int nbrSuffixes)
{
    if (!isUnnamed) {
	JCIdentifier *cursor= name;

	do {
	    if (!cursor->isMatching(aName)) {
		break;
	    }
	    cursor= cursor->getComponent();
	    aName= aName->getComponent();
	} while ((cursor != NULL) && (aName != NULL));

// MOD-980508 [HD]: If the package name is not yet finished, it is too long.
	if (cursor != NULL) return false;

	if (nbrSuffixes == 0) {
	    if ((cursor == NULL) && (aName == NULL)) {
		return true;
	    }
	}
	else {
	    if (aName != NULL) {
		while (aName != NULL) {
		    nbrSuffixes--;
		    aName= aName->getComponent();
		}
		if (nbrSuffixes == 0) return true;
	    }
	}
    }
    return false;
}


void JCPackageName::refreshPath(void)
{
    if (path != NULL) {
	delete[] path;
	path= NULL;
    }
}


/**************************************************
* Implementation: JCPackageDef.
**************************************************/

JCPackageDef::JCPackageDef(JCCompiler *aCompiler, JCPackageName *aName)
{
    owner= aCompiler;
    classes= new RealTypesList;
    interfaces= new RealTypesList;
    locName= aName;
    nameSpace= new JCNameSpace();
}


JCPackageDef::JCPackageDef(JCCompiler *aCompiler)
{
    owner= aCompiler;
    classes= new RealTypesList;
    interfaces= new RealTypesList;
    locName= new JCPackageName();
    nameSpace= new JCNameSpace();
}


JCPackageDef::~JCPackageDef(void)
{
    delete nameSpace;
    delete interfaces;
    delete classes;
    if (locName != NULL) delete locName;
}


void JCPackageDef::setOwner(JCCompiler *aCompUnit)
{
    owner= aCompUnit;
}


void JCPackageDef::setName(JCPackageName *aName)
{
    if (locName != NULL) delete locName;
    locName= aName;
}


JCPackageName *JCPackageDef::getName(void)
{
    return locName;
}


char * JCPackageDef::getPath(void)
{
    if (locName != NULL) return locName->getPath();
    else return ".";
}


JCCompiler *JCPackageDef::getCompiler(void)
{
    return owner;
}


RealTypesList * JCPackageDef::getClasses(void)
{
    return classes;
}


JCReferencedType * JCPackageDef::getStarClass(void)
{
    return owner->getStarClass();
}


unsigned int JCPackageDef::composeClassName(char *buffer, JCType *aType)
{
    unsigned int nameLength;

    buffer[0]= '\0';
    if ((nameLength= locName->getDotNotation(buffer)) != 0) {
	buffer[nameLength++]= '/';
	buffer[nameLength]= '\0';
    }
    strcpy(&buffer[nameLength], aType->getAsciiName());
    return (nameLength + aType->getName()->nameLength());
}


JCUnresolved *JCPackageDef::findUnresolved(JCIdentifier *aName)
{
    JCUnresolved *result;

    if ((result= nameSpace->findUnresolved(aName)) == NULL) {
	result= owner->findUnresolved(aName);
     }

    return result;
}


JCUnresolved *JCPackageDef::addUnknown(JCReferencedType *aRefType)
{
    return nameSpace->getLastLevel()->addUnresolved(aRefType);
}


JCUnresolved *JCPackageDef::addUnknown(JCExpression *anExpr)
{
    return nameSpace->getLastLevel()->addUnresolved(anExpr);
}


JCUnresolved *JCPackageDef::addUnknown(JCIdentifier *aName)
{
    return nameSpace->getLastLevel()->addUnresolved(aName);
}


bool JCPackageDef::defineType(JCIdentifier *anIdent, JCType *aType, JCName::UnitType subType)
{
   JCNameSpace *bottomNS;
    JCResolved *resolved;
    bool result= true;

    bottomNS= nameSpace->getLastLevel();
    if ((resolved= bottomNS->addResolution(anIdent, aType, subType)) != NULL) {
	bottomNS->applyResolution(resolved);
     }
    else result= false;
    return result;
}


bool JCPackageDef::defineField(JCIdentifier *anIdent, JCField *aNewField)
{
    JCNameSpace *bottomNS;
    JCResolved *resolved;
    bool result= false;

    bottomNS= nameSpace->getLastLevel();
    if ((resolved= bottomNS->addResolution(anIdent, aNewField, JCName::fieldVariable)) != NULL) {
	bottomNS->applyResolution(resolved);
	result= true;
     }
    return result;
}


bool JCPackageDef::defineMethod(JCIdentifier *anIdent, JCMethod *aMethod)
{
   JCNameSpace *bottomNS;
    JCResolved *resolved;
    bool result= true;

    bottomNS= nameSpace->getLastLevel();
    if ((resolved= bottomNS->findResolved(anIdent)) == NULL) {
    	if ((resolved= bottomNS->quickAddResolved(anIdent, aMethod, JCName::uMethod)) != NULL) {
	    bottomNS->applyResolution(resolved);
	 }
     }
    else {
	if (resolved->getDefType() != JCName::uMethod) {
	    // ERRMSG: Definition of a method name that is used by something else.
	    cout << "Method name ";
	    anIdent->dumpInfo();
	    cout << " is clashing with a previously defined resolver ";
	    resolved->dumpInfo();
	    result= false;
	 }
     }
    return result;
}


bool JCPackageDef::defineState(JCIdentifier *anIdent, JCState *aState)
{
   JCNameSpace *bottomNS;
    JCResolved *resolved;
    bool result= true;

    bottomNS= nameSpace->getLastLevel();
    if ((resolved= bottomNS->findResolved(anIdent)) == NULL) {
    	if ((resolved= bottomNS->quickAddResolved(anIdent, aState, JCName::uState)) != NULL) {
	    bottomNS->applyResolution(resolved);
	 }
     }
    else {
	if (resolved->getDefType() != JCName::uState) {
	    // ERRMSG: Definition of a method name that is used by something else.
	    cout << "State name ";
	    anIdent->dumpInfo();
	    cout << " is clashing with a previously defined resolver ";
	    resolved->dumpInfo();
	    result= false;
	 }
     }
    return result;
}


JCName *JCPackageDef::bind(JCIdentifier *aName, JCExpression *aUser)
{
    JCNameSpace *tmpNS;
    JCResolved *resolution;
    JCUnresolved *unresolution;
    JCName * result= NULL;

    tmpNS= nameSpace->getLastLevel();
    while (tmpNS != NULL) {
	if ((resolution= tmpNS->findResolved(aName)) != NULL) {
	    if (aUser->getCategory() == JCExpression::eVariable) {
		((JCVarAccess *)aUser)->setResolution(resolution);
	    }
	    else {
		((JCNamedExpr *)aUser)->setResolution(resolution);
	    }
	    result= resolution;
	    break;
	 }
	else if ((unresolution= tmpNS->findUnresolved(aName)) != NULL) {
	    unresolution->linkExpression(aUser);
	    result= unresolution;
	    break;
	 }
	tmpNS= tmpNS->getUpperLevel();
     }

    return result;
}


// This tries to get a Type name.
JCName *JCPackageDef::bind(JCIdentifier *aName, JCReferencedType *aUser)
{
    JCNameSpace *tmpNS;
    JCResolved *resolution;
    JCUnresolved *unresolution;
    JCName * result= NULL;

    tmpNS= nameSpace->getLastLevel();
    while (tmpNS != NULL) {
	if ((resolution= tmpNS->findResolved(aName, JCName::uType)) != NULL) {
	    aUser->setResolution(resolution);
	    result= resolution;
	    break;
	 }
	else if ((unresolution= tmpNS->findUnresolved(aName)) != NULL) {
	    unresolution->linkType(aUser);
	    result= unresolution;
	    break;
	 }
	tmpNS= tmpNS->getUpperLevel();
     }

    return result;
}


void JCPackageDef::pushNameSpace(void)
{
    JCNameSpace *tmpNameSpace;

    tmpNameSpace= new JCNameSpace;
    nameSpace->addALevel(tmpNameSpace);
}


void JCPackageDef::pushNameSpace(JCNameSpace *aSpace)
{
    nameSpace->addALevel(aSpace);
}


void JCPackageDef::includeNameSpace(JCNameSpace *aSpace)
{
    nameSpace->linkAsSuper(aSpace);
}


JCNameSpace *JCPackageDef::popNameSpace(void)
{
    JCNameSpace *result;

    result= nameSpace->getLastLevel();
	// ATTN: Must transfer all unresolved access to the upper-level name space.
    if (result != nameSpace) {
	result->flushUnresolved();
	nameSpace->removeLastLevel();
     }
    else result= NULL;
    return result;
}


// TMP Debug:

void JCPackageDef::dumpNameSpace(void)
{
    JCNameSpace *tmpNS;
    tmpNS= nameSpace;

    while (tmpNS) {
	tmpNS->dumpContent();
	tmpNS= tmpNS->getNext();
     }
}


bool JCPackageDef::hasUnresolved(void)
{
    return nameSpace->hasUnresolved();
}


JCNameSpace *JCPackageDef::getNameSpace(void)
{
    return nameSpace;
}


void JCPackageDef::loadNames(JCPackageDef *aPackage)
{  
    nameSpace->includeResolutions(aPackage->nameSpace->getResolvers());
}


bool  JCPackageDef::isPackageOfReferedType(JCReferencedType *aRefType)
{
    return (locName->matchName(aRefType->getTypeName(), 1));
}


bool JCPackageDef::isNamed(JCIdentifier *aName)
{
    return (locName->matchName(aName, 0));
}


bool JCPackageDef::isTypeStarClass(JCType *aType)
{
    JCResolved *aResolved;

    if ((aResolved= owner->getStarClass()->resolution()) != NULL) {
	return (aResolved->getDefinition() == aType);
    }
    else {
	char tmpBuffer[1024];

	aType->storeFullName(tmpBuffer);
	return (strcmp("java/lang/Object", tmpBuffer) == 0);
    }

    return false;		// Should never get here !
}


/**************************************************
* Implementation: JCPackage.
**************************************************/

JCPackage::JCPackage(void) : JCPackageDef(NULL)
{
    location= NULL;
    caseCounts= new CountList();
    loopCount= 0;
}


JCPackage::JCPackage(JCCompiler *aCompUnit) : JCPackageDef(aCompUnit)
{
    location= NULL;
    caseCounts= new CountList();
    loopCount= 0;
}


JCPackage::~JCPackage(void)
{
    delete caseCounts;
    if (location != NULL) delete location;
}


bool JCPackage::isImported(void)
{
    return false;
}


bool JCPackage::startClass(JCIdentifier *aName)
{
    JCClassSpace *tmpNameSpace;

    currentType= new JCClass;
    currentType->setTypeName(aName);	// Enter the class name in the top name space.
    currentType->setPackage(this);
    currentType->setModifiers(currentModifiers);
	// MOD-970207 [HD]: Create the nameSpace before the defineType, for enable
	// import of symbols in JCRefType encoutered previously.
    tmpNameSpace= new JCClassSpace((JCClass *)currentType);
    currentType->setNameSpace(tmpNameSpace);

    if (!defineType(aName, currentType, JCName::uClass)) {
	// ERRMSG: Redefining an already existing type.
	aName->dumpInfo();
	cout  << " is redefining an already existing type.\n";
     }

    nameSpace->addALevel(tmpNameSpace);
    return false;
}


bool JCPackage::endCurrentClass(void)
{
    JCNameSpace *tmpNS;
    JCCteClass *tmpCteClass;
    char tmpTypeName[1024];
    bool result= true;

    tmpNS= nameSpace->getLastLevel();
    if (tmpNS != nameSpace) {
	// ATTN: All unresolved named at this level should be types.
	// For now, we flush without looking.
	tmpNS->flushUnresolved();
	nameSpace->removeLastLevel();

	    // Add a constant pool rep for the class.
	composeClassName(tmpTypeName, currentType);
	tmpCteClass= new JCCteClass(JCCteUtf8::addUniqueInstance((unsigned short *)tmpTypeName));
	currentType->setShadow(tmpCteClass);
     }
    else result= false;

    classes->addObject(currentType);
    return result;
}


bool JCPackage::startInterface(JCIdentifier *aName)
{
    JCNameSpace *tmpNameSpace;

    currentType= new JCInterface;
    currentType->setTypeName(aName);	// Enter the class name in the top name space.

    if (!defineType(aName, currentType, JCName::uInterface)) {
	// ERRMSG: Redefining an already existing type.
	aName->dumpInfo();
	cout  << " is redefining an already existing type.\n";
     }

    tmpNameSpace= new JCNameSpace;
    currentType->setNameSpace(tmpNameSpace);
    nameSpace->addALevel(tmpNameSpace);
    return false;
}


bool JCPackage::endCurrentInterface(void)
{
    bool result= true;
    JCNameSpace *tmpNS;

    tmpNS= nameSpace->getLastLevel();
    if (tmpNS != nameSpace) {
	// ATTN: All unresolved named at this level should be types.
	// For now, we flush without looking.
	tmpNS->flushUnresolved();
	nameSpace->removeLastLevel();
     }
    else result= false;

    interfaces->addObject(currentType);
    return result;
}


JCType *JCPackage::getCurrentType(void)
{
    return currentType;
}


bool JCPackage::defineLocalVariable(JCIdentifier *anIdent, JCVariableDeclaration *aVarDecl)
{
    JCNameSpace *bottomNS;
    JCResolved *resolved;
    bool result= false;

    bottomNS= nameSpace->getLastLevel();
    if ((resolved= bottomNS->addResolution(anIdent, (void *)aVarDecl, JCName::localVariable)) != NULL) {
	bottomNS->applyResolution(resolved);
	result= true;
     }
    return result;
}


bool JCPackage::addMemberInType(JCMember *aMember)
{
    switch (aMember->memberType()) {
	case FIELD_MEMBER:
	    if (currentType->addField((JCField *)aMember)) {
		aMember->bindToType(currentType);
	     }
	    else {
		// ERRMSG: Method could not be defined inside current type.
		cout  << "The field can't be added to the type.\n";
	     }
	    break;
	case METHOD_MEMBER:
	case STATE_MEMBER:
	    if (currentType->addMethod((JCMethod *)aMember)) {
		aMember->bindToType(currentType);
	     }
	    else {
		// ERRMSG: Method could not be defined inside current type.
		cout  << "ERRMSG: The ";
		cout << (aMember->memberType() == METHOD_MEMBER) ? "method" : "state";
		cout << " can't be added to the type.\n";
	     }
	    break;
	case STATINIT_MEMBER:
	    if (currentType->addClassInitializer((JCStaticInitializer *)aMember)) {
		aMember->bindToType(currentType);
	     }
	    else {
		// ERRMSG: Static initializer defined inside interface.
		cout  << "Can't define a static initiliazer inside an interface.\n";
	     }
	    break;
	default:		// ERRMSG: Internal error: invalid member definition.
	    cout  << "Internal error: Unknown member field.\n";
	    break;
     }
    return false;
}


bool JCPackage::resolveTyping(void)
{
    JCClass *tmpClass;
    JCInterface *tmpInterface;
    unsigned int nbrElements, i;
    bool result= true;

	// First, get the class tree well connected.
    nbrElements= classes->count();
    for (i= 0; i < nbrElements; i++) {
	tmpClass= (JCClass *)classes->objectAt(i);
	if (tmpClass != NULL) {
	    if (!tmpClass->resolveHierarchy()) result= false;
	 }
     }

    nbrElements= interfaces->count();
    for (i= 0; i < nbrElements; i++) {
	tmpInterface= (JCInterface *)interfaces->objectAt(i);
	if (tmpInterface != NULL) {
	    if (!tmpInterface->resolveHierarchy()) result= false;
	 }
     }


	// Second, complete the connection of types' members.
    nbrElements= classes->count();
    for (i= 0; i < nbrElements; i++) {
	tmpClass= (JCClass *)classes->objectAt(i);
	if (tmpClass != NULL) {
	    if (!tmpClass->resolveMemberTyping()) result= false;
	 }
     }
    nbrElements= interfaces->count();
    for (i= 0; i < nbrElements; i++) {
	tmpInterface= (JCInterface *)interfaces->objectAt(i);
	if (tmpInterface != NULL) {
	    if (!tmpInterface->resolveMemberTyping()) result= false;
	 }
     }

	// Third, resolve all the undecided situations that made their way in the class spaces.
    nbrElements= classes->count();
    for (i= 0; i < nbrElements; i++) {
	tmpClass= (JCClass *)classes->objectAt(i);
	if (tmpClass != NULL) {
	    if (!tmpClass->resolveClassSymbols()) result= false;
	 }
     }
    nbrElements= interfaces->count();
    for (i= 0; i < nbrElements; i++) {
	tmpInterface= (JCInterface *)interfaces->objectAt(i);
	if (tmpInterface != NULL) {
	    if (!tmpInterface->resolveClassSymbols()) result= false;
	 }
     }

	// Fourth, resolve all the undecided situations in the code.
    nbrElements= classes->count();
    for (i= 0; i < nbrElements; i++) {
	tmpClass= (JCClass *)classes->objectAt(i);
	if (tmpClass != NULL) {
	    if (!tmpClass->resolveStatements()) result= false;
	 }
     }

    JCNameSpace *tmpSpace= nameSpace;
    do {
	if (!tmpSpace->resolveMethodUsers()) result= false;
	tmpSpace= tmpSpace->getNext();
    } while (tmpSpace != NULL);
    return result;
}


void JCPackage::startCaseContext(void)
{
    caseCounts->addValue(0);
}

	
bool JCPackage::incCaseCount(bool isCase)
{
    if (caseCounts->count() > 0) {
	caseCounts->incLastValue();
	return true;
    }
    else return false;
}


unsigned int JCPackage::endCaseContext(void)
{
    unsigned int tmpCount;

    if (caseCounts->count() > 0) {
	tmpCount= caseCounts->getLastValue();
	caseCounts->removeLastValue();
    }
    else tmpCount= 0;
    return tmpCount;
}


bool JCPackage::isInsideSwitch(void)
{
    return (caseCounts->count() > 0);
}


void JCPackage::resetCaseContext(void)
{
    caseCounts->removeAll();
}


void JCPackage::incLoopLevel(void)
{
    loopCount++;
}


void JCPackage::decLoopLevel(void)
{
    loopCount--;
}


unsigned int JCPackage::getLoopLevel(void)
{
    return loopCount;
}


void JCPackage::resetLoopLevels(void)
{
    loopCount= 0;
}


JCNameSpace *JCPackage::getBottomNameSpace(void)
{
    return nameSpace->getLastLevel();
}


void JCPackage::setCurrentModifiers(unsigned int modifierSet)
{
    currentModifiers= modifierSet;
}


unsigned int JCPackage::getCurrentModifiers(void)
{
    return currentModifiers;
}


/**************************************************
* Implementation: JCImportedPackage.
**************************************************/

JCImportedPackage::JCImportedPackage(JCCompiler *aCompiler, JCPackageName *aName) : JCPackageDef(aCompiler, aName)
{
    onDemand= false;
    references= NULL;
    typesToLoad= new ImportTypeList();
}


void JCImportedPackage::setOnDemand(bool aFlag)
{
    onDemand= aFlag;
}


bool JCImportedPackage::isOnDemand(void)
{
    return onDemand;
}


bool JCImportedPackage::isImported(void)
{
    return true;
}


// ATTN: Make sure that this is not used anymore, and delete.
void JCImportedPackage::seekUnresolved(JCNameSpace *aSpace)
{
	// First, use own nameSpace to resolve types that were already loaded from the
	// package.
    nameSpace->seekUnresolvedFrom(aSpace);

    if (aSpace->hasUnresolved() && onDemand) {
	JCUnresolved *tmpUnresolved, *nextCandidate;
	JCImportedGhost *importedType;

	// If there are still unknown, must lookup the package to find the unknown symbols.
	// To do this, must loop through the unresolved, and do a seek of the name
	// in the lists of known type.
	tmpUnresolved= aSpace->getFirstUnresolved();
	do {
	    nextCandidate= (JCUnresolved *)tmpUnresolved->getNext();
	    switch(tmpUnresolved->getCategory()) {
		case JCName::uType:
		    if ((importedType= getUnloadedType(tmpUnresolved->getIdent())) != NULL) {
			    // Resolve the unknown to the imported type and transfer its dependency.
			typesToLoad->addObject(importedType);
			importedType->attachMissing(tmpUnresolved);
			aSpace->removeUnresolved(tmpUnresolved);
			delete tmpUnresolved;
		    }
		    break;
		case JCName::noClue:
		    // TODO: Try to match the ident as a package name component, and then
		    // as a type.
		    // Must do a update on what is found, if anything.
		    break;
	    }
	    tmpUnresolved= nextCandidate;
	} while (tmpUnresolved != NULL);
    }
}


bool JCImportedPackage::defineType(JCIdentifier *anIdent, JCType *aType, JCName::UnitType subType)
{
    JCResolved *tmpResolver;
    JCReferencedType *newReference;

// ATTN: Must do a checking to see if the type is already existing in the package.

    if ((tmpResolver= nameSpace->addResolution(anIdent, aType, subType)) == NULL) {
	cout << "ERRMSG: JCImportedPackage::defineType: could not add a new type definition to the package.\n";
	return false;
     }

    aType->setPackage(this);
    if (subType == JCName::uInterface) {
	interfaces->addObject(aType);
    }
    else {
	classes->addObject(aType);
    }

	// Make a reference for the type.
    if (owner->getClassManager()->isJavaLang(this)) {
	if (strcmp(aType->getAsciiName(), "java/lang/String") == 0) {
	    newReference= JCReferencedType::getPopularType(JCReferencedType::popString);
	    aType->setReference(newReference);
	}
	else {
	    newReference= aType->getRefEquivalent();
	}
    }
    else {
	newReference= aType->getRefEquivalent();
    }
    newReference->setNext(references);
    references= newReference;

    return ((tmpResolver != NULL) && (newReference != NULL));
}


JCReferencedType *JCImportedPackage::findType(JCIdentifier *aName)
{
    JCReferencedType *tmpRef= references;

    while (tmpRef != NULL) {
	if (aName->isMatching(tmpRef->getTypeName())) {
	    break;
	}
	tmpRef= tmpRef->getNext();
    }

    return tmpRef;
}


// ATTN: Make sure that this is not used anymore, and delete.
JCImportedGhost *JCImportedPackage::getUnloadedType(JCIdentifier *aName)
{
    JCImportedGhost *result= NULL;
    struct stat tmpStatInfo;
    unsigned int pathLength;
    char fullFilePath[1024]= "/usr/local/packages/";

    // ATTN: Must use a more clever class loader, that can do searches in various
    // locations, and in various format (compiled (file and archived), source, db).
    // The class paths are in CLASSPATH.  The class loader will also make sure that 
    // we don't reload the same file twice, and provide sub-resolution on demand.

    pathLength= strlen(locName->getPath())+20;
    strcpy(fullFilePath+20, locName->getPath());
    fullFilePath[pathLength]= '/';
    pathLength++;
    strcpy(&fullFilePath[pathLength], aName->getAsciiValue());
    pathLength+= strlen(aName->getAsciiValue());
    strcpy(&fullFilePath[pathLength], ".class");

    if (stat(fullFilePath, &tmpStatInfo) == 0) {
	JCFileSource *aSource;

	// ATTN-970528 [HD]: At this point, it is still impossible to know if it is a
	// class or an interface that was found.  All we can know is that it is either
	// compiled (.class) or not (.java/.plzn).

	    // Add the file as a type to load.
	aSource= new JCFileSource(fullFilePath);
	result= new JCImportedGhost(aSource, aName);
	result->setPackage(this);
    }

    if (result != NULL) {
	cout << "DBG: Using file "<< fullFilePath << " as compiled version of type " << aName->getAsciiValue() << ".\n";
    }
    return result;
}


bool JCImportedPackage::loadTypes(void)
{
    JCImportedType *loadedClass;
    unsigned int i;
    bool result= true;

    for (i= 0; i < typesToLoad->count(); i++) {
	if ((loadedClass= typesToLoad->objectAt(i)->load(owner)) != NULL) {
	    cout << "DBG: JCImportedPackage::loadTypes: imported compiled type " << loadedClass->getAsciiName() << ".\n";
	    defineType(loadedClass->getName(), loadedClass, loadedClass->isInterface() ? JCName::uInterface : JCName::uClass);
	}
	else {
	    result= false;
	}
    }
    return result;
}


bool JCImportedPackage::resolveTyping(void)
{
    bool result= true;
    for (unsigned int i= 0; i < classes->count(); i++) {
	result&= classes->objectAt(i)->resolveClassSymbols();
    }

    return result;
}


JCImportedType *JCImportedPackage::loadReferedType(JCCFUtf8 *aTypeName)
{
    unsigned char nameBuffer[1024];

    aTypeName->writeAsciiValue(nameBuffer);
    return owner->loadTypeFile((char *)nameBuffer);
}


bool JCImportedPackage::isClashingWith(JCPackageDef *aPackage)
{
// ATTN: Is this the right way to check for clash in package names ?
    if (strcmp(locName->getPath(), aPackage->getName()->getPath()) == 0) {
	if (onDemand) {
	    if (aPackage->isImported()) {
		if (((JCImportedPackage *)aPackage)->onDemand) {
		    return true;
		}
		return false;
	    }
	    else return false;
	}
	else {
	    if (aPackage->isImported()) {
		if (((JCImportedPackage *)aPackage)->onDemand) {
		    return false;
		}
		else return true;
	    }
	    else {
		return true;
	    }
	}
    }
    return false;
}


bool JCImportedPackage::solveUnknownType(JCUnresolved *anUnres)
{
    JCImportedGhost *importedType= NULL;

    if ((importedType= findGhostNamed(anUnres->getIdent())) == NULL) {
	    // Sinon, il faut utiliser le ImportManager pour trouver un ghost.
	if ((importedType= owner->getClassManager()->getGhostType(this, anUnres->getIdent())) != NULL) {
	    typesToLoad->addObject(importedType);
	}
    }

    if (importedType != NULL) {
	importedType->attachMissing(anUnres);
	return true;		// Warning: quick exit.
    }

    return false;
}


bool JCImportedPackage::addExternType(JCIdentifier *typeName)
{
    JCImportedGhost *importedType;

    if ((importedType= findGhostNamed(typeName)) == NULL) {
	if ((importedType= owner->getClassManager()->getGhostType(this, typeName)) != NULL) {
	    typesToLoad->addObject(importedType);
	}
	else {
	    return false;		// Could not prepare the type loading.
	}
    }

    return true;		// If we get here, then the process was sucessful.
}


JCImportedGhost *JCImportedPackage::findGhostNamed(JCIdentifier *aName)
{
    for (unsigned int i= 0; i < typesToLoad->count(); i++) {
	if (typesToLoad->objectAt(i)->isNamed(aName)) {
	    return typesToLoad->objectAt(i);
	}
    }

    return NULL;
}


void JCImportedPackage::refreshPath(void)
{
    locName->refreshPath();
}


JCType *JCImportedPackage::findReferedType(JCIdentifier *aName)
{
    JCImportedType *result= NULL;
    JCImportedGhost *importedType;
    unsigned int i;

	// Look in known classes.
    for (i= 0; i < classes->count(); i++) {
	if (((JCType *)classes->objectAt(i))->getName()->isMatching(aName)) {
	    return (JCType *)classes->objectAt(i);	// Warning: quick exit.
	}
    }

	// Look in known interfaces.
    for (i= 0; i < interfaces->count(); i++) {
	if (((JCType *)interfaces->objectAt(i))->getName()->isMatching(aName)) {
	    return (JCType *)interfaces->objectAt(i);	// Warning: quick exit.
	}
    }

	// Look for those not yet loaded.
    if ((importedType= findGhostNamed(aName)) == NULL) {
	    // Sinon, il faut utiliser le ImportManager pour trouver un ghost.
	importedType= owner->getClassManager()->getGhostType(this, aName);
    }

    if (importedType != NULL) {
	if ((result= importedType->load(owner)) != NULL) {
	    defineType(result->getName(), result, result->isInterface() ? JCName::uInterface : JCName::uClass);
	}
	else {
	    cout << "DBG: JCImportedPackage::findReferedType: could not import compiled type ghosted as " << aName->getAsciiValue() << ".\n";
	}
    }
    return result;
}


bool JCImportedPackage::resolveTyping(JCImportManager *aManager)
{
    bool result= true;
    for (unsigned int i= 0; i < classes->count(); i++) {
	result&= ((JCImportedType *)classes->objectAt(i))->resolveClassSymbols(aManager);
    }

    return result;
}

