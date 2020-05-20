#ifndef _IMPORTMANAGER_H_
#define _IMPORTMANAGER_H_
/**************************************************
* File: importManager.h.
* Desc: Definition of the JCClassManager.
* Module: AkraLog : JavaKit.
* Rev: 29 mai 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "importedObjects.h"

class JCCompiler;
class PackagesList;
class JCLoaded;
class Path;
class JCImportedGhost;


/********************************************************
* Class: JCImportManager.
* Desc: Manages the loading of imported classes (those mentioned in the source
*	code, and those that are required as derivatives.
* Class variables:
* Instance variables:
* Super-Class: AkObject (should become an abstract ClassManager, shared by the run-time).
* Module: JavaKit : Compiler.
********************************************************/

class JCImportManager : public AkObject {
  protected:
    JCCompiler *owner;
    unsigned int nbrLoaded;
    PackagesList *synonymPackages;
    PackagesList *onDemandPackages;
    PackagesList *explicitClassPackages;
    JCLoaded *typesLoaded;
    JCPackageDef *javaPackage;		// The special java.lang package.

  public:
    JCImportManager(void);
    JCImportManager(JCCompiler *aCompiler);
    virtual bool addPackage(JCImportedPackage *aPackage);
    virtual bool fetchMissingSymbols(JCNameSpace *aSpace);
    virtual bool loadImportedTypes(void);
    virtual bool resolveImportedTypes(void);
    virtual JCImportedType *getTypeFrom(char *aFullName);
    virtual void * findLoadedType(void *aName);	// Retrouve un type deja charge.
    virtual JCImportedGhost::Kind checkTypePresenceAt(void *name, Path *path);    // Essaie de trouve un type a un endroit donne.
    virtual void *loadTypeAtLocation(void *name, void *path);    // Charge un fichier qui a ete detecte.
    virtual JCImportedGhost::Kind isImportAType(JCImportedPackage *aPackage);    // Verifie si un import est un type ou un package.
    virtual JCImportedGhost *getGhostType(JCImportedPackage *aPackage, JCIdentifier *anIdent);	// Fait la recherche du fichier qui contient le type recherche (package: prefixe, anIdent: nom).
    virtual JCType *findReferedType(JCReferencedType *aReference);
    virtual JCImportedPackage *findPackage(JCIdentifier *aName);
    virtual bool isJavaLang(JCImportedPackage *aPackage);
};

#endif		/* _IMPORTMANAGER_H_ */
