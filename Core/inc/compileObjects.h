#ifndef _COMPILEOBJECTS_H_
#define _COMPILEOBJECTS_H_
/**************************************************
* File: compileObjects.h.
* Desc: Contains the definitions of some classes used to contain major syntaxic units:
*	CompilerObject, JCType, JCClass, JCInterface, JCField, JCMethod.
* Module: AkraLog : JavaComp.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"


// sub-types of JCMembers:
#define ABSTRACT_MEMBER	1	// Base type, should not be used.
#define FIELD_MEMBER		2	// JCField member.
#define METHOD_MEMBER	3	// JCMethod member.
#define STATINIT_MEMBER	4	// JCStaticInitializer member.
#define STATE_MEMBER		5	// JCState member.


class JCInterface;
class FieldsList;
class MethodsList;
class StatesList;
class ExpressionsList;
class TypesList;
class InitializersList;
class ConstantsList;
class AttributesList;
class ExceptionsList;
class JCActionBlock;
class JCReferencedType;
class JCIdentifier;
class JCDimIdentifier;
class JCMember;
class JCVariableDeclaration;
class JCNameSpace;
class JCField;
class JCMethod;
class JCState;
class JCStaticInitializer;
class JCOutClassFile;
class JCCteClass;
class JCReference;
class JCCteUtf8;
class JCPackageDef;
class RealTypesList;
class JCResolved;
class JCExpression;
class JCMethodSpace;
class JCNamedExpr;
class JCUnresolved;
class JCName;
class JCStateInvokeExpr;
class JCInvokeExpr;
class JCOverloadDictionary;
class JCSynonymTable;
class JCCompiler;


class CompilerObject : public AkObject {
  protected:
    unsigned int modifiers;	// Access modifiers.
    unsigned int subType;	// Subtype of the object.
    char resolutionLevel;		// Indicates if it still needs resolution of components.

  public:
    CompilerObject(void);
    virtual bool setModifiers(unsigned int flags);	// All flags must fit within 32 bits.
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual bool isStatic(void);
    virtual bool testFlags(unsigned int testFlags);
 };


/********************************************************
* Class: JCType.
* Desc: Descriptor for a type defined in Java (classes, interfaces).
* Super-Class: CompilerObject.
* Module: AkraLog : JavaKit.
********************************************************/

class JCType : public CompilerObject {		// Va etre la super-classe de Class et Interface.
  protected:
    enum ResolutionLevel {
	hierarchy= (1 << 0), members= (1 << 1), allCode= (1 << 2)
    };
  protected:
    JCType *next;				// Next Type in an implied list of types.
    JCType *extended;			// Type that this type extends.
    RealTypesList *interfaces;		// Interfaces implemented (or extended) by the type.
    FieldsList *fields;			// Fields that are defined in this type.
    MethodsList *methods;		// Methods that are defined in this type.
    StatesList *states;			// States that are defined in this type.
    JCNameSpace *nameSpace;	// Name space for the class.

    JCIdentifier *shortName;		// Name of the type.
    JCReferencedType *rawSuper;
    JCReferencedType *rawInterfaces;
    JCMember *rawMembers;

    JCCteClass *shadow;	// Representation for the constant pool.
    JCPackageDef *package;	// Package in which this type is defined.
    unsigned int startLine, endLine;
    JCResolved *thisResolver;	// Resolution of 'this' variable wherever it is valid.
    JCResolved *superResolver;	// Resolution of 'super' variable wherever it is valid.
    JCReferencedType *refEquivalent;	// ATTN: Must bind this to all users, instead of having a waste of 'JCReferencedType' going on.
    							// ATTN: Must find a good place to create it.
    JCOverloadDictionary *overloadDict;

  public:
    JCType(void);
    virtual void setNext(JCType *nextElement);
    virtual void link(JCType *nextElement);
    virtual JCType *getNext(void);
    virtual bool setTypeName(JCIdentifier *aName);
    virtual bool setInterfaces(JCReferencedType *someInterfaces);
    virtual bool setBody(JCMember *someMembers);
    virtual void setNameSpace(JCNameSpace *aNameSpace);
    virtual bool addField(JCField *aField);
    virtual bool addMethod(JCMethod *aMethod);
    virtual bool addClassInitializer(JCStaticInitializer *aMethod);
    virtual bool isInterface(void);

// Work in progress (for output).
    virtual RealTypesList *getInterfaces(void);
    virtual FieldsList *getFields(void);
    virtual MethodsList *getMethods(void);
    virtual StatesList *getStates(void);
    virtual unsigned int getAccessFlags(void);
    virtual char *getAsciiName(void);
    virtual JCIdentifier *getName(void);
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual void setShadow(JCCteClass *aClassCte);
    virtual JCCteClass *getShadow(void);
    virtual void setPackage(JCPackageDef *aPackage);
    virtual unsigned int storeFullName(char *buffer);
    virtual JCMember *checkFieldForClash(JCField *aField);
    virtual JCMember *checkMethodForClash(JCMethod *aField);
    virtual JCMember *checkStateForClash(JCState *aField);
    virtual bool resolveHierarchy(void);
    virtual bool resolveMemberTyping(void);
    virtual bool resolveClassSymbols(void);
    virtual void setLineRange(unsigned int firstLine, unsigned int lastLine);
    virtual JCResolved *getThisDeclarator(void);
    virtual JCResolved *getSuperDeclarator(void);
    virtual JCResolved *findSymbol(JCIdentifier *anIdent);
    virtual JCResolved *findCorrectMethod(JCIdentifier *anIdent, JCExpression *typing);
    virtual bool containsJCode(void);
    virtual JCReferencedType *getRefEquivalent(void);
    virtual void addUser(JCNamedExpr *anExpression);
    virtual void importUnknown(JCNameSpace *aSpace);
    virtual void importUnknown(JCUnresolved *unresList);
    virtual JCResolved *findSymbol(JCUnresolved *anUnknown);
    virtual JCOverloadDictionary *getOverloadDictionary(void);
    virtual JCCompiler *getCompiler(void);
    virtual void setReference(JCReferencedType *aRef);
 };


class JCClass : public JCType {
  protected:
    // ConstantPool *ctePool;
    InitializersList *classInitializers;

  public:
    JCClass(void);
    JCClass(JCIdentifier *aName, JCPackageDef *aPackage);
    virtual bool setSuperClass(JCReferencedType *aRefType);
    virtual bool addField(JCField *aField);
    virtual bool addClassInitializer(JCStaticInitializer *aMethod);
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual bool isInterface(void);
    virtual JCType *getSuper(void);
    virtual JCReferencedType *getSuperType(void);
    virtual bool resolveStatements(void);
    virtual void debugDefineRootClass(void);
 };


class JCInterface : public JCType {
  protected:

  public:
    JCInterface(void);
    virtual bool addClassInitializer(JCStaticInitializer *aMethod);
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual bool isInterface(void);
 };


class JCMember : public CompilerObject {
  protected:
    enum ResolutionLevel {
	returnType= (1 << 0), parameters= (1 << 1), actionBlock= (1 << 2)
    };
  public:	/* MOD-MSC: mis la protection a public pour que JCField y ait acces. */
    JCType *owner;
    JCMember *next;

    JCReferencedType *rawType;
    unsigned int nbrDimensions;		// Nbr of dimensions of the r-type.
    JCCteUtf8 *identName;			// Name of identifier for the member.
    JCReference *shadow;		// Constant pool representation.
    AttributesList *attributes;
    unsigned int startLine, endLine;

  public:
    JCMember(void);
    virtual void setNext(JCMember *nextElement);
    virtual void link(JCMember *nextElement);
    virtual JCMember *getNext(void);
    virtual bool setReturnedType(JCReferencedType *aType);
    virtual bool bindToType(JCType *aType);
    virtual unsigned int memberType(void);
    virtual bool resolveTyping(void);
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual void mapToPool(ConstantsList *aPool);
    virtual JCCteUtf8 *buildCteSignature(void);
    virtual void setShadow(JCReference *aClassCte);
    virtual JCReference *getShadow(void);
    virtual char *getAsciiValue(void);
    virtual void setLineRange(unsigned int firstLine, unsigned int lastLine);
    virtual void getLineRange(unsigned int& firstLine, unsigned int& lastLine);
    virtual JCReferencedType *getReturnedType(void);
    virtual JCType *getOwner(void);
    virtual unsigned int getNbrDimensions(void);
    virtual JCCteUtf8 *getName();
 };


class JCField : public JCMember {
  protected:
    ExpressionsList *initializers;
    JCVariableDeclaration *rawDeclaration;

  public:
    JCField(void);
    virtual bool setDeclarator(JCVariableDeclaration *varDeclarator);
    virtual bool setReturnedType(JCReferencedType *aType);
    virtual bool bindToType(JCType *aType);
    virtual unsigned int memberType(void);
    virtual bool isClashing(JCMember *aMember);
    virtual JCCteUtf8 *buildCteSignature(void);
    virtual bool resolveTyping(void);
    virtual ExpressionsList *getInitializer(void);
    virtual bool hasInitializer(void);
 };


class JCSpecialField : public JCField {
  public:
    enum KnownSpecial {
	ksLength
	, nbrKnownSpecial
    };

  public:
    static JCResolved *getField(KnownSpecial aSpecial);
};


class JCMethod : public JCMember {
    friend class JCCodeAttr;
    friend class JCStateCodeAttr;

  protected:
    bool constructorFlag;			// Indicates if the method is an instance constructor.
    unsigned int nbrArguments;	// Is it redondant with argTypes ?
    JCReferencedType **argTypes;
    ConstantsList *argNames;
    ExceptionsList *exceptions;
    JCMethodSpace *nameSpace;
    JCActionBlock *mainBlock;

    JCDimIdentifier *rawName;
    JCVariableDeclaration *rawArguments;
    JCReferencedType *rawExceptions;

    JCSynonymTable *synonyms;

  public:
    JCMethod(void);
    virtual bool setName(JCDimIdentifier *aName);
    virtual bool setParameters(JCVariableDeclaration *someDeclarations);
    virtual void setNameSpace(JCMethodSpace *aNameSpace);
    virtual bool setExceptions(JCReferencedType *someTypes);
    virtual bool setBody(JCActionBlock *aBlock);
    virtual bool bindToType(JCType *aType);
    virtual unsigned int memberType(void);
    virtual bool isClashing(JCMethod *aMethod);
    virtual bool isClashing(JCField *aField);
    virtual void makeAttributes(JCOutClassFile *aClassFile);
    virtual void mapToPool(ConstantsList *aPool);
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual JCCteUtf8 *buildCteSignature(void);
    virtual void setConstructor(bool aValue);
    virtual bool isConstructor(void);
    virtual bool resolveTyping(void);
    virtual unsigned int getNbrArguments(void);
    virtual bool resolveCode(void);
    virtual bool hasSomeJCode(void);
    virtual void quickExport(void);
    virtual bool resolveOverloading(JCInvokeExpr *anInvocation);
    virtual JCReferencedType **getTypeList(void);
    virtual void setSynonyms(JCSynonymTable *someSyns);
    virtual JCSynonymTable *getSynonyms(void);
 };


class JCStaticInitializer : public JCMethod {
  protected:

  public:
    JCStaticInitializer(void);
    virtual bool setBlock(JCActionBlock *aBlock);
    virtual unsigned int memberType(void);
 };


#if defined(PLZEN_LEVEL_2)

class JCState : public JCMethod {
  protected:
  public:
    JCState(void);
    virtual bool bindToType(JCType *aType);
    virtual unsigned int memberType(void);
    virtual void makeAttributes(JCOutClassFile *aClassFile);
    virtual void mapToPool(ConstantsList *aPool);
    virtual bool setName(JCDimIdentifier *aName);
    virtual JCCteUtf8 *buildCteSignature(void);
    virtual bool resolveTyping(void);
};

class JCTransition : public CompilerObject {
  public:		// Constant values.
    enum TransitionModifiers {
	tmBlocking= 1, tmImmediate= 2, tmParallel= 4,
	tmImplicit= 8, tmDefaulter= 16
    };

    enum DestinationModifiers {
	dmPush= 32, dmPop= 64, dmPassby=128,
	dmConsume= 256, dmRollback= 512, dmBreak= 1024
    };

  protected:		// Instance variables.
    JCExpression *trigger;		// A JCVarAccess or JCFieldAccess.
    JCStateInvokeExpr *destination;
    unsigned int modifiers;
    unsigned int startLine, endLine;

  public:		// Instance methods.
    JCTransition(void);
    virtual ~JCTransition(void);
    virtual void setTriggers(JCExpression *someTriggers);
    virtual void setSpecialDestination(DestinationModifiers simpleDest);
    virtual void setDestination(JCStateInvokeExpr *aStateDest);
    virtual void setLineRange(unsigned int firstLine, unsigned int lastLine);
    virtual void mapToPool(ConstantsList *aPool);
    virtual unsigned int getModifiers(void);
    virtual JCExpression *getTriggers(void);
    virtual JCStateInvokeExpr *getDestination(void);
    virtual bool setModifiers(unsigned int flags);	// All flags must fit within 32 bits.
};
#endif	/* PLZEN_LEVEL_2 */

#endif	/* _COMPILEOBJECTS_H_ */
