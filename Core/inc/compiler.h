#ifndef _JCCOMPILER_H_
#define _JCCOMPILER_H_
/**************************************************
* File: compiler.h.
* Desc: Contains the definition of a Java single-thread of compilation management.
* Module: AkraLog : JavaComp.
* Rev: 3 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"


class PreCompSymbols;
class SourceFile;
class JCPackageName;
class JCImportedPackage;
class JCPackage;
class JCType;
class JCIdentifier;
class JCReferencedType;
class JCNameSpace;
class JCUnresolved;
class CountList;
class JCLabelStack;
class JCCodeBuffer;
class JCOutAttribute;
class AttributesList;
class JCImportManager;
class JCImportedType;
class JCCompOptions;
class PathList;


class JCCompilationContext;	// Forward definition.


class JCCompiler : public AkObject {
  public:
    enum PathType {
	compiledClasses, sourceClasses
    };

  private:		// Class variables.
    static JCCompiler *publicCompiler;

  public:		// Class methods.
    static JCCompiler *getCurrentCompiler(void);

  private:		// Instance variables.
    PreCompSymbols *precomp;	// Pre-compilation symbols.
    SourceFile *imports;			// Manages the recursive import operations.
    JCPackage *currentCompPackage;	// Package that is currently being defined (target of compilation).
    JCReferencedType *starClass;
    // Comment gere les name spaces ?
    JCNameSpace *nameSpace;
    CountList *linesTrace;
    JCCompilationContext *codeContext;
    unsigned int errors, warnings;
    JCImportManager *classManager;	// Manages the general loading of imported classes.
    JCCompOptions *options;			// Options that modify the compilation.

  public:		// Instance methods.
    JCCompiler(void);
    virtual bool importImplicitPackage(void);
    virtual bool boot(int argc, char **argv);
    virtual int compileFile(char *aFile);
    virtual bool phaseOne();
    virtual bool phaseTwo();
    virtual bool spitBinary();
    virtual bool pushFileContext();	// Save the current source file context, and create a new context.
    virtual bool popFileContext();	// Bring back the last source file context.

    virtual bool importPackage(JCPackageName *packName, unsigned int mode);
    virtual bool defineCurrentPackage(JCPackageName *aName);
    virtual JCPackage *currentPackage();

    virtual JCUnresolved *findUnresolved(JCIdentifier *anIdent);

    JCReferencedType *getStarClass(void);

    static int locateJavaPath(JCPackageName *aPackage);  // Return 0, 1 according to dir/file.
    static int locateLocalPath(JCPackageName *aPackage);  // Return 2, 3 according to dir/file.

// Work in progress.
    virtual void makeClassFileName(char *aNameBuffer, JCType *aType);
    virtual void addError(char *aString);
    virtual JCImportedPackage *attachSynonymName(JCPackageName *aName);
    virtual JCImportedPackage *attachOnDemandPackage(JCPackageName *aName);
    virtual void pushLineNumber(void);
    virtual unsigned int popLineNumber(void);
    virtual unsigned int currentLineNumber(void);
    virtual JCImportedType *loadTypeFile(char *aFullName);
    virtual bool findRealType(JCReferencedType *aRefType);
    virtual PathList *getPathFor(PathType aType);
    virtual JCImportManager *getClassManager(void);
 };


#endif	/* _JCCOMPILER_H_ */
