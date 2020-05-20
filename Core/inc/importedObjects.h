#ifndef _IMPORTEDOBJECTS_H_
#define _IMPORTEDOBJECTS_H_
/**************************************************
* File: importedObjects.h.
* Desc: Definition of the class JCImportedType.
* Module: AkraLog : JavaComp.
* Rev: 28 mai 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "nameSpace.h"
#include "compileObjects.h"


class JCFileSource;
class JCUnresolved;
class JCCompiler;
class JCHolder;
class JCImportClassFile;
class JCUnresolved;
class JCResolved;
class JCImportedType;
class JCFieldInfo;
class JCMethodInfo;
class JCImportedPackage;
class JCImportManager;
class JCImportedClass;


class JCImportedGhost : public AkObject {
  public:
    enum Kind {
	kClass, kGlass, kJava, kPlzen, kUnknown
    };

  protected:
    JCFileSource *dataSource;
    Kind fileKind;
    JCTypeHolder *users;
    JCUnresolved *dependants;
    JCIdentifier *className;
    JCImportedPackage *package;
    JCImportedClass *realType;

  public:
    JCImportedGhost(void);
    JCImportedGhost(JCFileSource *aSource, JCIdentifier *aName);
    virtual void attachMissing(JCUnresolved *anUnresolved);
    virtual JCImportedType *load(JCCompiler *compiler);
    virtual bool isNamed(JCIdentifier *aName);
    virtual void setKind(Kind aKind);
    virtual Kind getKind(void);
    virtual void setPackage(JCImportedPackage *aPackage);
    virtual JCImportedPackage *getPackage(void);
};


class JCImportedType : public JCType {
  protected:
    JCResolved *nsResolver;

  public:
    JCImportedType(void);
    JCImportedType(JCIdentifier *aName, JCName::UnitType preciseType);
    virtual JCResolved *getResolver(void);
    virtual bool resolveClassSymbols(JCImportManager *aManager);
    virtual JCResolved *findMemberSymbol(JCIdentifier *aName)= 0;
};


class JCImportedClass : public JCImportedType {
  protected:	// Instance variables.
    JCImportClassFile *theClass;

  public:		// Instance methods.
    JCImportedClass(void);
    JCImportedClass(JCImportClassFile *aClass, JCIdentifier *aName);
    virtual char *getAsciiName(void);
    unsigned int storeFullName(char *buffer);
    virtual bool isInterface(void);
    virtual JCType *getSuper(void);
    virtual JCReferencedType *getSuperType(void);
    virtual JCResolved *findSymbol(JCUnresolved *anUnknown);
    virtual JCResolved *findSymbol(JCIdentifier *aName);
    virtual JCResolved *findMemberSymbol(JCIdentifier *aName);
};


class JCImportedField : public JCField {
  public:	// Instance methods.
    JCImportedField(JCImportedType *containterType, char *aName, JCReferencedType *aType);
    virtual void buildShadow(char *signature);
};


class JCImportedMethod : public JCMethod {
  public:	// Instance methods.
    JCImportedMethod(JCImportedType *containterType, char *aName, unsigned int nbrTypes, JCReferencedType **types);
    virtual void buildShadow(char *signature);
};


class JCImportedState : public JCState {
  public:	// Instance methods.
    JCImportedState(JCImportedType *containterType, char *aName, unsigned int nbrTypes, JCReferencedType **types);
};



#endif		/* _IMPORTEDOBJECTS_H_ */
