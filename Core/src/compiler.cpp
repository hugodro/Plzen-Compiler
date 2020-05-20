/**************************************************
* File: compiler.cc.
* Desc: Contains the implementation of a Java single-thread of compilation management.
* Module: AkraLog : JavaComp.
* Rev: 10 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <sys/stat.h>
#include <string.h>
};

#include <iostream.h>
//using std::cout;

#include "package.h"
#include "identifiers.h"
#include "lists.h"
#include "sourceFile.h"
#include "constants.h"
#include "typing.h"
#include "nameSpace.h"
#include "outClassFile.h"
#include "outConstant.h"
#include "labelStack.h"
#include "codeBuffer.h"
#include "compContext.h"
#include "importClass.h"
#include "importManager.h"
#include "compOptions.h"
#include "compiler.h"


extern bool isUpperCase(char *);
extern bool isJava(char *);

void ShowCompilerMessage(int, char *, char *);


/* Variables used in this module defined in external modules. */

extern int yylineno;
extern FILE *yyin;
extern int yyparse(void);


extern JCPackage *thePackage;


/**************************************************
* Implementation: JCCompiler.
**************************************************/

JCCompiler *JCCompiler::publicCompiler= NULL;


JCCompiler *JCCompiler::getCurrentCompiler(void)
{
    return publicCompiler;
}


JCCompiler::JCCompiler(void)
{
    JCPackageName *tmpPackage;
    currentCompPackage= new JCPackage;
    thePackage= currentCompPackage;
    currentCompPackage->setOwner(this);

    nameSpace= new JCNameSpace;
    linesTrace= new CountList();
    codeContext= new JCCompilationContext(this);
    errors= warnings= 0;

    publicCompiler= this;		// ATTN: Must manage in a better way !

    classManager= new JCImportManager(this);
    options= new JCCompOptions();
    options->setDefaultOptions();
}


bool JCCompiler::importImplicitPackage(void)
{
    JCPackageName *implicitName;
    JCImportedPackage *implicitPackage;
    JCClass *fakeRootClass;
    JCImportedType *rootClass;
    JCResolved *tmpResolver;
    JCIdentifier *tmpIdent;
    JCCteUtf8 *aCteName;

    tmpIdent= new JCIdentifier[3];
    aCteName= JCCteUtf8::addUniqueInstance((unsigned short *)"java");
    tmpIdent[0].setValue(aCteName);
    aCteName= JCCteUtf8::addUniqueInstance((unsigned short *)"lang");
    tmpIdent[1].setValue(aCteName);

    implicitName= new JCPackageName(&tmpIdent[0]);
    implicitName->addName(&tmpIdent[1]);
    implicitPackage= attachOnDemandPackage(implicitName);

	// Fake the object class for now.
    aCteName= JCCteUtf8::addUniqueInstance((unsigned short *)"Object");
    tmpIdent[2].setValue(aCteName);

#if defined(USE_FAKE_ROOT)

    // Il faudrait ajouter les methodes de Object ici.
    fakeRootClass= new JCClass(&tmpIdent[2], implicitPackage);
    fakeRootClass->debugDefineRootClass();
    starClass= implicitPackage->findType(&tmpIdent[2]);
#endif
    rootClass= (JCImportedType *)implicitPackage->findReferedType(&tmpIdent[2]);
    if (rootClass != NULL) {
	starClass= rootClass->getRefEquivalent();

	// Transfer the implicit names into the default current package.
	currentCompPackage->loadNames(implicitPackage);
	return true;
    }
    else {
	// Could not find the root class, abort.
	cout << "ERRMSG: JCCompiler::importImplicitPackage: can't find root class.\n";
	return false;
    }
}


bool JCCompiler::boot(int argc, char **argv)
{
    JCIdentifier *tmpIdent;
    JCCteUtf8 *aCteName;

	// Deal with options.
    if (options->scanCommands(argv, argc) != 1001) {

	    // Do a class initialization.
	JCCteUtf8::initCteUtf8Class();
    
	// Do an import of java.lang.
	return importImplicitPackage();
    }
    return false;
}


int JCCompiler::compileFile(char *aFile)
{
    SourceFile *mainSource;
    int result;

    mainSource= new SourceFile(aFile);
    if (mainSource->getFIO() != NULL) {
	yyin= mainSource->getFIO();
	result= yyparse();
#if defined(DEBUG_NS_1)
	if (result == 0) currentCompPackage->dumpNameSpace();
#endif
	if (result == 0) {
	    if (phaseOne()) {
		if (phaseTwo() && (errors == 0)) {
		    if (spitBinary()) {
			result= 0;
		    }
		    else {
			cout << "ERRMSG: Phase 3 was problematic.\n";
		    }
		}
		else {
		    cout << "ERRMSG: Skipping phase 3, syntaxic/semantic errors detected.\n";
		}
	    }
	    else {
		cout << "ERRMSG: Can't start phase 2.\n";
		if (currentCompPackage->hasUnresolved()) {
		    cout << "ERRMSG: Could not resolve the following symbols:\n";
		    JCUnresolved *tmpUnresolved;

		    tmpUnresolved= currentCompPackage->getNameSpace()->getFirstUnresolved();
		    do {
			cout << "symbol: " << tmpUnresolved->getIdent()->getAsciiValue() << ", category " << (int)tmpUnresolved->getCategory() << ".\n";
			tmpUnresolved= (JCUnresolved *)tmpUnresolved->getNext();
		    } while (tmpUnresolved != NULL);
		    
		}
	    }
	}
     }
    else {
	result= -1;
     }
    return result;
}


bool JCCompiler::phaseOne()
{
    bool result;

cout << "DBG: Starting phase 1: import of missing types.\n";

    if (currentCompPackage->hasUnresolved()) {
	JCNameSpace *tmpSpace;
	result= classManager->fetchMissingSymbols((tmpSpace= currentCompPackage->getNameSpace()));
	if (!result) {
	    JCUnresolved *tmpUnres, *nextUnres;
	    bool onlyPotentialFields= true;

	    tmpUnres= tmpSpace->getFirstUnresolved();
	    while (tmpUnres != NULL) {
		nextUnres= (JCUnresolved *)tmpUnres->getNext();
		if (tmpUnres->getCategory() == JCName::fieldVariable) {
		    tmpSpace->removeUnresolved(tmpUnres);
		}
		else onlyPotentialFields= false;
		tmpUnres= nextUnres;
	    }
	    result= onlyPotentialFields;
	}
    }
    else result= true;

cout << "DBG: Phase 1 finished.\n";
    return result;
}


bool JCCompiler::phaseTwo()
{
    unsigned int i;
    bool tmpResult= true;

cout << "DBG: Starting phase 2: resolution of all unknown situations.\n";

	// Seek missing classes in import sections.
//TMPTMP:    tmpResult= ;
    classManager->loadImportedTypes();

	// Then resolve all other necessary symbols that the imported types mention.
    tmpResult&= classManager->resolveImportedTypes();

	// Finally resolve all unknown symbols and typing situations in the compiled code.
    tmpResult&= (currentCompPackage->resolveTyping() == true);

cout << "DBG: Phase 2 finished.\n";
    return tmpResult;
}


bool JCCompiler::spitBinary()
{
    RealTypesList  *classes;
    JCClass *tmpClass;
    JCOutClassFile *outputFile;
    unsigned int nbrElements, i;
    bool result= true;
    char nameBuffer[1024];

cout << "DBG: Starting phase 3: j-code spitting.\n";

    classes= currentCompPackage->getClasses();
    nbrElements= classes->count();
    for (i= 0; i < nbrElements; i++) {
	tmpClass= (JCClass *)classes->objectAt(i);
	makeClassFileName(nameBuffer, tmpClass);
	outputFile= new JCOutClassFile(codeContext, nameBuffer, tmpClass);
	if (outputFile->opened()) {
	    outputFile->save();
	    delete outputFile;
	}
	else {
	    // ATTN: Signal the error: Can't create class file.
	}
     }

cout << "DBG: Phase 3 finished.\n";
    return result;
}



bool JCCompiler::pushFileContext()
{
    // TODO.
    return false;
}


bool JCCompiler::popFileContext()
{
    // TODO.
    return false;
}


bool JCCompiler::importPackage(JCPackageName *packName, unsigned int mode)
{
    JCPackageDeclaration *imported;
    JCIdentifier *ident;
    unsigned int result;
    char *tmpName, fullPath[1024];

    ident= packName->getName();
    if (ident) {
	tmpName= ident->getAsciiValue();
	if (isUpperCase(tmpName)) {
		// ATTN: Must import a 'site' package.
	 }
	else if (isJava(tmpName)) {
		// ATTN: Must import a 'java' package.
	    result= locateJavaPath(packName);
	 }
	else {
	    result= locateLocalPath(packName);
	 }
	if (result < 0) {		// Couldn't get to the path required.
	    // ATTN: Signal the error.
	 }
	else if ((result == 0)  | (result == 2)) {		// Found a directory.
	    switch (mode) {
		case 0:		// Do short-naming.
		    break;
		case 1:		// Do an import-on-demand.
		    break;
		default:		// Signal an internal error.
		    break;
	      }
	 }
	else if ((result == 1)  | (result == 3)) {		// Found a file.
	    switch (mode) {
		case 0:		// Do a type import.
		    break;
		case 1:		// Can't be done.
		    // ATTN: Signal the error.
		    break;
		default:		// ATTN: Signal an internal error.
		    break;
	     }
	 }
	else {
	    // ATTN: Signal an internal error.
	 }
     }
    return false;
}


bool JCCompiler::defineCurrentPackage(JCPackageName *aName)
{
    if (currentCompPackage != NULL) {
	// Old approach was: 1- spit current package, 2- delete current package, 3- create new one.
	currentCompPackage->setName(aName);
     }
    else {	
	currentCompPackage= new JCPackage;
	currentCompPackage->setOwner(this);
	currentCompPackage->setName(aName); 
	thePackage= currentCompPackage;
    }
    return false;
}


JCPackage *JCCompiler::currentPackage()
{
    return currentCompPackage;
}


JCUnresolved *JCCompiler::findUnresolved(JCIdentifier *anIdent)
{
    return nameSpace->findUnresolved(anIdent);
}


JCReferencedType *JCCompiler::getStarClass(void)
{
    return starClass;
}


int JCCompiler::locateJavaPath(JCPackageName *aName)
{
    JCIdentifier *tmpIdent;
    struct stat statInfo;
    int result;		// 0 if the name is a directory, 1 if it is a file (or is contained by file).
    unsigned int totalNameLength= 0;
    char *tmpPath;

    tmpIdent= aName->getName();
    while (tmpIdent) {
	totalNameLength+= tmpIdent->nameLength() + 1;
	tmpIdent= tmpIdent->getNext();
     }
    if (totalNameLength > 0) {
	tmpPath= new char[totalNameLength+1 + 20];    // Link to '/usr/local/packages/'
	strcpy(tmpPath, "/usr/local/packages");	// ATTN: Get correct implementation !
	tmpIdent= aName->getName();
	while (tmpIdent) {
	    strcat(tmpPath, tmpIdent->getAsciiValue());
	    tmpIdent= tmpIdent->getNext();
	    if (tmpIdent != NULL) {
		strcat(tmpPath, "/");
	     }
	 }
	if (stat(tmpPath, &statInfo) == 0) {		// Got somewhere.
	    if (statInfo.st_mode & S_IFDIR) result= 0;
	    else if (statInfo.st_mode & S_IFCHR) result= 1;
	    else result= -2;		// Unknown kind of file.
	 }
	else {
	    result= -1;
	 }
     }
    if (result > -1) {
	aName->setDirectAccess(tmpPath);
     }
    else {
	delete tmpPath;
     }
    return result;
}


int JCCompiler::locateLocalPath(JCPackageName *aName)
{
    int result;		// 0 if the name is a directory, 1 if it is a file (or is contained by file).
    unsigned int totalNameLength= 0;
    char *tmpPath;

    return result;
}


void JCCompiler::makeClassFileName(char *aNameBuffer, JCType *aType)
{
    char *packPath, *className;

    packPath= currentCompPackage->getPath();
    className= aType->getAsciiName();

// ATTN: very primitive name buildup !
    strcpy(aNameBuffer, packPath);
    strcat(aNameBuffer, "/");
    strcat(aNameBuffer, className);
    strcat(aNameBuffer, ".class");
}


void JCCompiler::addError(char *aString)
{
    errors++;
    // TODO: Get the real line number at which the error is detected, not the
    //		position at which the parser is in the source code.
    cout << "Error at line " << yylineno << ": " << aString << ".\n";
}


JCImportedPackage *JCCompiler::attachSynonymName(JCPackageName *packName)
{
    JCImportedPackage *tmpPackage;

    // ATTN: Il faut attacher la derniere composante du nom en tant que 'nom' resolu,
    // et faire pointer la resolution a la declaration.  A ce point-ci, on ne peut pas encore
    // decider si le JCPackageName se termine par un nom de type ou non.

    // Verifier que le nouveau nom synonyme n'est pas un clash sur les precedents.

    tmpPackage= new JCImportedPackage(this, packName);

    if (!classManager->addPackage(tmpPackage)) {
	cout << "Warning: package is already imported.\n";
	delete tmpPackage;
	tmpPackage= NULL;
    }
    return tmpPackage;
}


JCImportedPackage *JCCompiler::attachOnDemandPackage(JCPackageName *packName)
{
    JCImportedPackage *tmpPackage;
    tmpPackage= new JCImportedPackage(this, packName);
    tmpPackage->setOnDemand(true);

    if (!classManager->addPackage(tmpPackage)) {
	char dotName[256];
	packName->getDotNotation(dotName);
	cout << "Warning: package " << dotName << " is already imported.\n";
	delete tmpPackage;
	tmpPackage= NULL;
    }

    return tmpPackage;
}

void JCCompiler::pushLineNumber(void)
{
    linesTrace->addValue(yylineno);
}


unsigned int JCCompiler::popLineNumber(void)
{
    unsigned int tmpValue;

    tmpValue= linesTrace->getLastValue();
    linesTrace->removeLastValue();
    return tmpValue;
}


unsigned int JCCompiler::currentLineNumber(void)
{
    return yylineno;
}


JCImportedType *JCCompiler:: loadTypeFile(char *aFullName)
{
    return classManager->getTypeFrom(aFullName);
}


bool JCCompiler::findRealType(JCReferencedType *aRefType)
{
    JCType *aType;
    aType= classManager->findReferedType(aRefType);
    // TODO: Doit s'assurer que le type est charge et resolu.
    return (aType != NULL);
}


PathList *JCCompiler::getPathFor(PathType aType)
{
    switch(aType) {
	case compiledClasses: return options->getCompiledPath();
	case sourceClasses: return options->getSourcePath();
    }
    return NULL;		// Unknown type of paths.
}


JCImportManager *JCCompiler::getClassManager(void)
{
    return classManager;
}


/* ====================== Utility functions ====================== */


void ShowCompilerMessage(int lineNum, char *msg1, char *msg2)
{
    char msgBuffer[200];

    sprintf(msgBuffer, msg1, msg2);
    fprintf(stderr, "line %d: %s", yylineno, msgBuffer);
}


