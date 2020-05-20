#ifndef _PACKAGE_H_
#define _PACKAGE_H_
/**************************************************
* File: package.h.
* Desc: Contains the definition of the JCPackage class, used to contain compilation
*	of the Java Compiler.
* Module: AkraLog : JavaComp.
* Rev: 3 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"
#include "nameSpace.h"
#include "compileObjects.h"


class JCCompiler;
class JCType;
class JCClass;
class JCInterface;
class JCIdentifier;
class AkList;
class RealTypesList;
class JCNameSpace;
class JCUnresolved;
class JCName;
class JCExpression;
class JCReferencedType;
class CountList;
class ImportTypeList;
class JCImportedGhost;
class JCCFUtf8;
class JCImportedType;
class JCImportManager;


class JCPackageDeclaration : public AkObject {
  private:
    unsigned int type;	// Short-hand, single type or on demand.
  public:
    virtual JCType *findName(JCIdentifier *aName);
 };


class JCPackageName : public CompilerObject {
  protected:
    JCIdentifier *name;
    char *path;
    bool isUnnamed;

  public:
    JCPackageName(void);
    JCPackageName(JCIdentifier *aName);
    virtual void addName(JCIdentifier *aName);
    virtual JCIdentifier *getName(void);
    virtual void setDirectAccess(char *aPath);

// Work in progress.
    virtual char *getPath(void);
    virtual unsigned int getDotNotation(char *buffer);
    virtual bool matchName(JCIdentifier *aName, unsigned int nbrSuffixes);
    virtual void refreshPath(void);
 };


class JCPackageDef : public CompilerObject {
  protected:
    JCCompiler *owner;		// Compilation unit that owns the package.
    JCPackageName *locName;	// Name in package 'xyz'.
    RealTypesList *classes;		// List of classes defined in the package.
    RealTypesList *interfaces;	// List of interfaces defined in the package.
    JCNameSpace *nameSpace;	// Top-level name space of the package.

  public:
    JCPackageDef(JCCompiler *aCompiler);
    JCPackageDef(JCCompiler *aCompiler, JCPackageName *aName);
    virtual ~JCPackageDef(void);

    virtual void setOwner(JCCompiler *aCompUnit);
    virtual void setName(JCPackageName *aName);
    virtual char *getPath(void);
    virtual JCPackageName *getName(void);
    virtual JCCompiler *getCompiler(void);

    JCReferencedType *getStarClass(void);
    virtual unsigned int composeClassName(char *buffer, JCType *aType);

    virtual JCUnresolved *findUnresolved(JCIdentifier *aName);
    virtual JCUnresolved *addUnknown(JCReferencedType *aRefType);
    virtual JCUnresolved *addUnknown(JCExpression *anExpr);
    virtual JCUnresolved *addUnknown(JCIdentifier *aName);
    virtual bool defineType(JCIdentifier *anIdent, JCType *aType, JCName::UnitType subType);
    virtual bool defineMethod(JCIdentifier *anIdent, JCMethod *aMethod);
    virtual bool defineField(JCIdentifier *anIdent, JCField *aNewField);
    virtual bool defineState(JCIdentifier *anIdent, JCState *aMethod);

    virtual JCName *bind(JCIdentifier *aName, JCExpression *aUser);
    virtual JCName *bind(JCIdentifier *aName, JCReferencedType *aUser);
    virtual void pushNameSpace(void);
    virtual void pushNameSpace(JCNameSpace *aSpace);
    virtual void includeNameSpace(JCNameSpace *aSpace);
    virtual JCNameSpace *popNameSpace(void);

    virtual RealTypesList *getClasses(void);

    virtual bool isImported(void)= 0;

// TMP DEBUG:
    virtual void dumpNameSpace(void);

// Work in progress.
    virtual bool hasUnresolved(void);
    virtual JCNameSpace *getNameSpace(void);
    virtual void loadNames(JCPackageDef *aPackage);
    virtual bool isPackageOfReferedType(JCReferencedType *aRefType);
    virtual bool isNamed(JCIdentifier *aName);
    virtual bool isTypeStarClass(JCType *aType);
};


class JCPackage : public JCPackageDef {
  protected:
    char *location;			// Location to save the elements of the package.
	// Compilation context.
    JCType *currentType;	// Type which is currently being defined.
    bool isCurrentAClass;	// Define if the current type is a class (else it is an interface).
    unsigned int loopCount;	// The number of embedded loops in a method being compiled.
    CountList *caseCounts;	// Number of case statements in the switch statements.
    unsigned int currentModifiers;

  public:
	// Construction/destruction.
    JCPackage(void);
    JCPackage(JCCompiler *aCompUnit);
    virtual ~JCPackage(void);
    virtual bool isImported(void);
    
    virtual bool startClass(JCIdentifier *aName);
    virtual bool endCurrentClass(void);
    virtual bool startInterface(JCIdentifier *aName);
    virtual bool endCurrentInterface(void);
    virtual JCType *getCurrentType(void);

    virtual bool defineLocalVariable(JCIdentifier *anIdent, JCVariableDeclaration *aVarDecl);

    virtual bool addMemberInType(JCMember *aMember);
    virtual bool resolveTyping(void);

    virtual void startCaseContext(void);
    virtual bool incCaseCount(bool isCase);
    virtual unsigned int endCaseContext(void);
    virtual void resetCaseContext(void);
    virtual bool isInsideSwitch(void);
    virtual void incLoopLevel(void);
    virtual void decLoopLevel(void);
    virtual unsigned int getLoopLevel(void);
    virtual void resetLoopLevels(void);

    virtual JCNameSpace *getBottomNameSpace(void);
    virtual void setCurrentModifiers(unsigned int modifierSet);
    virtual unsigned int getCurrentModifiers(void);
};


class JCImportedPackage : public JCPackageDef {
  protected:
    bool onDemand;
    JCReferencedType *references;
    ImportTypeList *typesToLoad;

  public:
    JCImportedPackage(JCCompiler *aCompiler, JCPackageName *aName);
    virtual bool isImported(void);
    virtual void setOnDemand(bool aFlag);
    virtual bool isOnDemand(void);

    virtual bool defineType(JCIdentifier *anIdent, JCType *aType, JCName::UnitType subType);

// ATTN: This method is not to be used anymore, it is going away !
    virtual void seekUnresolved(JCNameSpace *aSpace);    // Try to resolve unknowns from a given name space.
    virtual JCReferencedType *findType(JCIdentifier *aName);
// ATTN: This method is not to be used anymore, it is going away !
    virtual JCImportedGhost *getUnloadedType(JCIdentifier *aName);    // Try to locate a type in the package.
    virtual bool loadTypes(void);    // Load the set of imported types known so far.

    virtual bool resolveTyping(void);

    virtual JCImportedType *loadReferedType(JCCFUtf8 *aType);
    virtual bool isClashingWith(JCPackageDef *aPackage);
    virtual bool solveUnknownType(JCUnresolved *anUnres);    // Locate the name given as a known type.
    virtual bool addExternType(JCIdentifier *typeName);
    virtual JCImportedGhost *findGhostNamed(JCIdentifier *aName);    // Look for a type in the known ghosts.
    virtual void refreshPath(void);
    virtual JCType *findReferedType(JCIdentifier *aName);
    virtual bool resolveTyping(JCImportManager *aManager);
};


#endif	/* _PACKAGE_H_ */

