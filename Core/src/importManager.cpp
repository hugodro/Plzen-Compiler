/**************************************************
* File: importManager.cc.
* Desc: Implementation of the JCClassManager.
* Module: AkraLog : JavaKit.
* Rev: 29 mai 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
}

#include <iostream.h>
#include <classfile/filePath.h>
#include "lists.h"
#include "compiler.h"
#include "package.h"
#include "identifiers.h"
#include "classSource.h"
#include "typing.h"
#include "runtimeDefs.h"
#include "outConstant.h"
#include "importManager.h"


JCImportManager::JCImportManager(void)
{
// ATTN: Should not be called !!
}


JCImportManager::JCImportManager(JCCompiler *aCompiler)
{
    owner= aCompiler;
    nbrLoaded= 0;
    typesLoaded= NULL;
    synonymPackages= new PackagesList();
    onDemandPackages= new PackagesList();
    explicitClassPackages= new PackagesList();
}


bool JCImportManager::addPackage(JCImportedPackage *aPackage)
{
    bool noConflict= true;

    if (aPackage->isOnDemand()) {
	for (unsigned int i= 0; i < onDemandPackages->count(); i++) {
	    if (onDemandPackages->objectAt(i)->isClashingWith(aPackage)) {
		noConflict= false;
		break;
	    }
	}
	if (noConflict) {
	    onDemandPackages->addObject(aPackage);
	    if (strcmp(aPackage->getPath(), "java/lang") == 0) {    // This is the special Java package.
		javaPackage= aPackage;
	    }
	}
    }
    else {
	if (isImportAType(aPackage) != JCImportedGhost::kUnknown) {
	    JCImportedPackage *tmpPackage;
	    JCIdentifier *packName, *typeName;

	    // Must find if the package exists already.
	    packName= aPackage->getName()->getName();
	    typeName= packName->removeSuffix();

// MODNT:  Bug: si typeName == NULL, alors le package n'a qu'une compo, ce qui veut dire que
// c'est un type, et qu'il fait partie du package courant.  Actuellement, on va planter sur la sequence 
// suivante:

	    if (typeName == NULL) {
		typeName= packName;
		// RENDU ICI: Doit extraire l'equivalent du package courant en tant qu'importOnDemand,
		// et s'en servir pour faire la suite.
	    }
	    else {
		if ((tmpPackage= findPackage(packName)) == NULL) {
		    explicitClassPackages->addObject(aPackage);
		    tmpPackage= aPackage;
		    tmpPackage->refreshPath();
		}
		else {
		    delete aPackage;
		}
    
		// Must attach the type to the package.
		tmpPackage->addExternType(typeName);
	    }
	}
	else {
	    for (unsigned int i= 0; i < synonymPackages->count(); i++) {
		if (synonymPackages->objectAt(i)->isClashingWith(aPackage)) {
		    noConflict= false;
		    break;
		}
	    }
	    if (noConflict) {
		synonymPackages->addObject(aPackage);
	    }
	}
    }

    return noConflict;
}


bool JCImportManager::fetchMissingSymbols(JCNameSpace *aSpace)
{
    bool result= true;

    if (aSpace->hasUnresolved()) {
	JCUnresolved *tmpUnresolved, *nextCandidate;
	JCResolved *aResolved;
	unsigned int i;

	tmpUnresolved= aSpace->getFirstUnresolved();
	do {
	    nextCandidate= (JCUnresolved *)tmpUnresolved->getNext();

	    switch(tmpUnresolved->getCategory()) {
		case JCName::package:
// TODO: locate the package name in the different packages.
		    cout << "ERRMSG: JCImportManager::fetchMissingSymbol: trying to resolve a package name.\n";
		    break;
		case JCName::uType:
		    for (i= 0; i < explicitClassPackages->count(); i++) {
			if (explicitClassPackages->objectAt(i)->solveUnknownType(tmpUnresolved)) break;
		    }
		    if (i == explicitClassPackages->count()) {
			for (i= 0; i < onDemandPackages->count(); i++) {
			   if (onDemandPackages->objectAt(i)->solveUnknownType(tmpUnresolved)) break;
			}
			if (i == onDemandPackages->count()) {
			    result= false;
			}
		    }
		    if (result) {
			aSpace->removeUnresolved(tmpUnresolved);
			delete tmpUnresolved;
		    }
		    break;
		case JCName::noClue:
		    // TODO: Try to match the ident as a package name component, and then
		    // as a type.
		    // Must do a update on what is found, if anything.

		    for (i= 0; i < explicitClassPackages->count(); i++) {
			if (explicitClassPackages->objectAt(i)->solveUnknownType(tmpUnresolved)) break;
		    }
		    if (i == explicitClassPackages->count()) {
			for (i= 0; i < onDemandPackages->count(); i++) {
			   if (onDemandPackages->objectAt(i)->solveUnknownType(tmpUnresolved)) break;
			}
			if (i == onDemandPackages->count()) {
			    result= false;
			}
		    }
		    if (result) {
			aSpace->removeUnresolved(tmpUnresolved);
// MOD-980523 [HD]: The deletion cause a corruption in the noClueList of JCClassSpaces.
//			delete tmpUnresolved;
// Instead, we update it to a typeName, and let the JCClassSpaces deal with its presence their.
			tmpUnresolved->updateNoClue(JCName::uType);
		    }
		    else {
			// The symbol is not a known class.  So it is either a field variable from super-class,
			// or an unknown type.  We change it to a field variable, and try to resolve it later.
			tmpUnresolved->updateNoClue(JCName::fieldVariable);
		    }
		    break;
		default:
		    cout << "ERRMSG: JCImportManager::fetchMissingSymbol: trying to resolve an unknown";
		    cout << "kind of unresolved, category is " << (int)tmpUnresolved->getCategory() << ".\n";
		    break;
	    }

	    tmpUnresolved= nextCandidate;
	} while (tmpUnresolved != NULL);

    }

    return result;
}


bool JCImportManager::loadImportedTypes(void)
{
    unsigned int i;
    bool result= true;

    for (i= 0; i < explicitClassPackages->count(); i++) {
	if (!explicitClassPackages->objectAt(i)->loadTypes()) {
	    // Got some error while trying to load an external type.
	    cout << "ERRMSG: Could not load all types from package (id = " << i << ").\n";
	    result= false;
	}
    }

    for (i= 0; i < onDemandPackages->count(); i++) {
	if (!onDemandPackages->objectAt(i)->loadTypes()) {
	    // Got some error while trying to load an external type.
	    cout << "ERRMSG: Could not load all types from package (id = " << i << ").\n";
	    result= false;
	}
    }

    return result;
}


bool JCImportManager::resolveImportedTypes(void)
{
    unsigned int i;
    bool result= true;

    for (i= 0; i < explicitClassPackages->count(); i++) {
	if (!explicitClassPackages->objectAt(i)->resolveTyping()) {
	    cout << "ERRMSG: Could not load all types could be resolved in package (id = " << i << ").\n";
	    result= false;
	}
    }

    for (i= 0; i < onDemandPackages->count(); i++) {
	if (!onDemandPackages->objectAt(i)->resolveTyping(this)) {
	    cout << "ERRMSG: Could not load all types could be resolved in package (id = " << i << ").\n";
	    result= false;
	}
    }
    return result;
}


JCImportedType *JCImportManager::getTypeFrom(char *aFullName)
{
    JCImportedPackage *sourcePack;
    JCImportedGhost *ghostType= NULL;
    JCImportedType *result= NULL;
    JCIdentifier *packageName, *currentIdent, *lastIdent, *className;
    char *slashFinder, *currentStart;

    if ((slashFinder= aFullName) == NULL) {
	return NULL;		// Warning: quick exit.
    }

    currentStart= aFullName;
    packageName= lastIdent= NULL;

    while (*slashFinder != '\0') {
	if (*slashFinder == '/') {
	    *slashFinder= '\0';
	    currentIdent= new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)currentStart));
	    if (lastIdent != NULL) {
		lastIdent->addComponent(currentIdent);	// MODNT.
	    }
	    else {
		packageName= currentIdent;
	    }
	    lastIdent= currentIdent;
	    *slashFinder= '/';
	    currentStart= slashFinder +1;
	}
	slashFinder++;
    }
    className= new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)currentStart));

    if (packageName != NULL) {

	if ((sourcePack= findPackage(packageName)) == NULL) {
	    JCPackageName *locName;
	    JCImportedPackage *newPackage;

	    locName= new JCPackageName(packageName);
	    sourcePack= newPackage= new JCImportedPackage(owner, locName);
	    newPackage->setOnDemand(true);
	    onDemandPackages->addObject(newPackage);
	}
	else {
	    JCReferencedType *refType;

	    delete packageName;
	    if ((refType= sourcePack->findType(className)) == NULL) {
		ghostType= sourcePack->findGhostNamed(className);
	    }
	    else {
		// ATTN-971112 [HD]: Must check that a refType in an imported package is always
		// defered to a JCImportedType.
		return (JCImportedType *)refType->getRealType();
	    }
	}
    }
    else {
	// Must be in the 'current' package.
	// TODO: get current package.
	sourcePack= NULL;
    }

    if (ghostType == NULL) {
	if ((ghostType= getGhostType(sourcePack, className)) == NULL) {
	    return NULL;	// Warning: quick exit.
	}
    }

    if ((result= ghostType->load(owner)) != NULL) {
	sourcePack->defineType(result->getName(), result, result->isInterface() ? JCName::uInterface : JCName::uClass);
    }

    return result;
}


void *JCImportManager::findLoadedType(void *aName)
{
    PathList *pathList;
    Path *path;
    void *result;

	// ATTN-970601 [HD]: This is a mistake:
    if ((result= findLoadedType(aName)) == NULL) {    // Not in-core, try to load it.
	pathList= owner->getPathFor(JCCompiler::compiledClasses);
	if (pathList != NULL) {
	    path= pathList->getFirst();
	    while (path && (result == NULL)) {
		if (path->getTypeIndex() == 0) {		// If it is a local path.
		    if (checkTypePresenceAt(aName, path) != JCImportedGhost::kUnknown) {
			result= loadTypeAtLocation(aName, path);
		     }
		 }
		path= pathList->getNext();
	     }
	 }
     }

    return result;
}


JCImportedGhost::Kind JCImportManager::checkTypePresenceAt(void *name, Path *path)
{
    struct stat tmpStatInfo;
    JCImportedGhost::Kind fileKind[4]= {
	JCImportedGhost::kClass, JCImportedGhost::kGlass,
	JCImportedGhost::kJava, JCImportedGhost::kPlzen
    };
    char classPath[512];
    char *fileExtensions[4]= {
	CLASS_EXTENSION, GLASS_EXTENSION,
    	JAVA_EXTENSION, PLZEN_EXTENSION
    };
    JCImportedGhost::Kind result= JCImportedGhost::kUnknown;

    if (path->getTypeIndex() == 0) {
	path->getFilePath(classPath);
	if (classPath[0] != '\0') {
	    unsigned int pathLength= strlen(classPath);
	    unsigned int nameLength= strlen((char *)name);
	    unsigned int i;

	    classPath[pathLength++]= FILE_SEPARATOR;
	    memcpy(&classPath[pathLength], name, nameLength);
	    pathLength+= nameLength;
	    for (i= 0; i < 4; i++) {
		strcpy(&classPath[pathLength], fileExtensions[i]);
		if (stat(classPath, &tmpStatInfo) == 0) {
		    result= fileKind[i];
		    break;
		}
	    }
	}
     }
    return result;
}


void *JCImportManager::loadTypeAtLocation(void *name, void *path)
{
// TODO.
    return NULL;
}


JCImportedGhost::Kind JCImportManager::isImportAType(JCImportedPackage *aPackage)
{
    PathList *pathList;
    Path *path;
    JCImportedGhost::Kind result= JCImportedGhost::kUnknown;

    pathList= owner->getPathFor(JCCompiler::compiledClasses);
    if (pathList != NULL) {
	char *packageName= aPackage->getPath();
	path= pathList->getFirst();
	while (path != NULL) {
	    if ((result= checkTypePresenceAt(packageName, path)) != JCImportedGhost::kUnknown) {
		break;
	    }
	    path= pathList->getNext();
	}
    }


    return result;
}


JCImportedGhost *JCImportManager::getGhostType(JCImportedPackage *aPackage, JCIdentifier *anIdent)
{
    PathList *pathList;
    Path *path;
    struct stat tmpStatInfo;
    JCImportedGhost::Kind fileKind[4]= {
	JCImportedGhost::kClass, JCImportedGhost::kGlass,
	JCImportedGhost::kJava, JCImportedGhost::kPlzen
    };
    char *fileExtensions[4]= {
	CLASS_EXTENSION, GLASS_EXTENSION,
    	JAVA_EXTENSION, PLZEN_EXTENSION
    };
    char classPath[512];

    pathList= owner->getPathFor(JCCompiler::compiledClasses);
    if (pathList != NULL) {
	path= pathList->getFirst();
	while (path != NULL) {
	    if (path->getTypeIndex() == 0) {		// If it is a local path.
		path->getFilePath(classPath);
		if (classPath[0] != '\0') {
		    unsigned int pathLength, packLength, nameLength, i;
		    char *packPath, *name;

		    packPath= aPackage->getPath();
			// ATTN: Is this giving the full name, or just the ident name (ex: gaga.gougou -> gaga/gougou) ??
		    name= anIdent->getAsciiValue();
		    pathLength= strlen(classPath);
		    packLength= strlen(packPath);
		    nameLength= strlen(name);

		    classPath[pathLength++]= FILE_SEPARATOR;
		    memcpy(&classPath[pathLength], packPath, packLength);
		    pathLength+= packLength;
		    classPath[pathLength++]= FILE_SEPARATOR;
		    memcpy(&classPath[pathLength], name, nameLength);
		    pathLength+= nameLength;
		    for (i= 0; i < 4; i++) {
			strcpy(&classPath[pathLength], fileExtensions[i]);
			if (stat(classPath, &tmpStatInfo) == 0) {
			    JCFileSource *aSource;
			    JCImportedGhost *ghost;
    
			    aSource= new JCFileSource(classPath);
			    ghost= new JCImportedGhost(aSource, anIdent);
			    ghost->setPackage(aPackage);
			    ghost->setKind(fileKind[i]);
			    return ghost;
			}
		    }
		}
	    }
	    path= pathList->getNext();
	}
    }

    return NULL;
}


JCType *JCImportManager::findReferedType(JCReferencedType *aReference)
{
    JCIdentifier *typeName;
    JCType *result;

    typeName= aReference->getTypeName();

// TODO: Traiter le cas du package local, et verifier si la routine fonctionne comme il faut.
    if (typeName->isComposed()) {
	JCPackageDef *container;
	JCIdentifier *realTypeName;
	unsigned int i;
	bool gotPackage= false;

	for (i= 0; i < synonymPackages->count(); i++) {
	    if (synonymPackages->objectAt(i)->isPackageOfReferedType(aReference)) {
		container= synonymPackages->objectAt(i);
		gotPackage= true;
		break;
	    }
	}
	if (!gotPackage) {
	    for (i= 0; i < onDemandPackages->count(); i++) {
		if (onDemandPackages->objectAt(i)->isPackageOfReferedType(aReference)) {
		    container= onDemandPackages->objectAt(i);
		    gotPackage= true;
		    break;
		}
	    }
	}
	if (!gotPackage) {
	    for (i= 0; i < explicitClassPackages->count(); i++) {
		if (explicitClassPackages->objectAt(i)->isPackageOfReferedType(aReference)) {
		    container= explicitClassPackages->objectAt(i);
		    gotPackage= true;
		    break;
		}
	    }
	}

	realTypeName= typeName->removeSuffix();

	if (!gotPackage) {
	    JCImportedPackage *newPackage;

	    // This package is not yet known by the Import Manager.
	    // Must look it up, and create a ImportedPackage for it.

	    newPackage= new JCImportedPackage(owner, new JCPackageName(typeName));
	    addPackage(newPackage);
	    container= newPackage;
	    gotPackage= true;
	}

	    // Replace the last component name.
	typeName->addComponent(realTypeName);

	if (gotPackage) {
// TODO: Review this thoroughly.
	    result= ((JCImportedPackage *)container)->findReferedType(realTypeName);
	}

    }
    else {
	// Name is local to current package.
    }

    return result;
}


JCImportedPackage *JCImportManager::findPackage(JCIdentifier *aName)
{
    unsigned int i;

    for (i= 0; i < onDemandPackages->count(); i++) {
	if (onDemandPackages->objectAt(i)->isNamed(aName)) {
	    return onDemandPackages->objectAt(i);	    // Warning: quick exit.
	    break;
	}
    }
    for (i= 0; i < explicitClassPackages->count(); i++) {
	if (explicitClassPackages->objectAt(i)->isNamed(aName)) {
	    return explicitClassPackages->objectAt(i);	    // Warning: quick exit.
	    break;
	}
    }
    for (i= 0; i < synonymPackages->count(); i++) {
	if (synonymPackages->objectAt(i)->isNamed(aName)) {
	    return synonymPackages->objectAt(i);	    // Warning: quick exit.
	    break;
	}
    }

    return NULL;	// If we get there, nothing was found.
}


bool JCImportManager::isJavaLang(JCImportedPackage *aPackage)
{
    return (aPackage == javaPackage);
}

