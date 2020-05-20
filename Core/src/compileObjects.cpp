/**************************************************
* File: compileObjects.cc.
* Desc: .
* Module: AkraLog : JavaComp.
* Rev: 6 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <stdio.h>
#include <string.h>
}

#include <iostream.h>
#include "typing.h"
#include "variables.h"
#include "identifiers.h"
#include "lists.h"
#include "actions.h"
#include "nameSpace.h"
#include "package.h"
#include "outClassFile.h"
#include "attributes.h"
#include "outConstant.h"
#include "constants.h"
#include "compiler.h"
#include "expressions.h"
#include "nameSpace.h"
#include "overloadDict.h"
#include "importManager.h"
#include "compileObjects.h"


// ATTENTION: We must find a better way to deal with reaching the current package.
extern JCPackage *thePackage;

/**************************************************
* Implementation: CompilerObject.
**************************************************/

CompilerObject::CompilerObject(void)
{
    modifiers= 0;
    subType= 0;
    resolutionLevel= 0;
}


bool CompilerObject::setModifiers(unsigned int flags)
{
    modifiers= flags;
    return true;
}


void CompilerObject::writeInto(JCOutClassFile *aClassFile)
{
    aClassFile->writeUShort(modifiers);
}


bool CompilerObject::isStatic(void)
{
    return modifiers & ACC_STATIC;
}


bool CompilerObject::testFlags(unsigned int testFlags)
{
    return (testFlags & modifiers);
}


/**************************************************
* Implementation: JCType.
**************************************************/

JCType::JCType(void)
{
    extended= NULL;
    interfaces= new RealTypesList;
    fields= new FieldsList;
    methods= new MethodsList;
    states= new StatesList;
    nameSpace= NULL;

    shortName= NULL;
    rawSuper= rawInterfaces= NULL;
    rawMembers= NULL;

    shadow= NULL;
    package= NULL;
    resolutionLevel= 0;
    thisResolver= NULL;
    superResolver= NULL;
    refEquivalent= NULL;
    overloadDict= NULL;
}


void JCType::setNext(JCType *nextElement)
{
    next= nextElement;
}


void JCType::link(JCType *nextElement)
{
    if (next == NULL) next= nextElement;
    else {
	JCType *tmpNext= next;
	while (tmpNext->next != NULL) tmpNext= tmpNext->next;
	tmpNext->next= nextElement;
     }

}


JCType *JCType::getNext(void)
{
    return next;
}


bool JCType::setTypeName(JCIdentifier *aName)
{
    shortName= aName;
    return false;
}


bool JCType::setInterfaces(JCReferencedType *someInterfaces)
{
    rawInterfaces= someInterfaces;
    return false;
}


bool JCType::setBody(JCMember *someMembers)
{
    rawMembers= someMembers;
    return false;
}


void JCType::setNameSpace(JCNameSpace *aNameSpace)
{
    nameSpace= aNameSpace;
}


bool JCType::addField(JCField *aField)
{
    unsigned int nbrElements;
    bool haveNoClash= true;

    if ((nbrElements= fields->count()) != 0) {
	JCField *tmpField;
	unsigned int i;

	for (i=0; i < nbrElements; i++) {
	    tmpField= fields->objectAt(i);
	    if (tmpField->isClashing(aField)) {
		haveNoClash= false;
		break;
	     }
	}
     }

    if ((nbrElements= methods->count()) != 0) {
	JCMethod *tmpMethod;
	unsigned int i;

	for (i=0; i < nbrElements; i++) {
	    tmpMethod= methods->objectAt(i);
	    if (tmpMethod->isClashing(aField)) {
		haveNoClash= false;
		break;
	     }
	}
     }

    if ((nbrElements= states->count()) != 0) {
	JCState *tmpState;
	unsigned int i;

	for (i=0; i < nbrElements; i++) {
	    tmpState= states->objectAt(i);
	    if (tmpState->isClashing(aField)) {
		haveNoClash= false;
		break;
	     }
	}
     }

    if (haveNoClash) fields->addObject(aField);

    return haveNoClash;
}


bool JCType::addMethod(JCMethod *aMethod)
{
    unsigned int nbrElements;
    bool haveNoClash= true;

    if ((nbrElements= fields->count()) != 0) {
	JCField *tmpField;
	unsigned int i;

	for (i=0; i < nbrElements; i++) {
	    tmpField= fields->objectAt(i);
	    if (tmpField->isClashing(aMethod)) {
		haveNoClash= false;
		break;
	     }
	}
     }
    if ((nbrElements= methods->count()) != 0) {
	JCMethod *tmpMethod;
	unsigned int i;

	for (i=0; i < nbrElements; i++) {
	    tmpMethod= methods->objectAt(i);
	    if (tmpMethod->isClashing(aMethod)) {
		haveNoClash= false;
		break;
	     }
	}
     }

    if ((nbrElements= states->count()) != 0) {
	JCState *tmpState;
	unsigned int i;

	for (i=0; i < nbrElements; i++) {
	    tmpState= states->objectAt(i);
	    if (tmpState->isClashing(aMethod)) {
		haveNoClash= false;
		break;
	     }
	}
     }
    if (haveNoClash) {
	if (aMethod->memberType() == METHOD_MEMBER) {
	    methods->addObject(aMethod);
	}
	else {
	    states->addObject((JCState *)aMethod);
	}
    }
    return haveNoClash;
}


bool JCType::addClassInitializer(JCStaticInitializer *anInit)
{
    return false;
}


bool JCType::isInterface(void)
{
	// Must be implemented by subclasses.
    return false;
}


RealTypesList *JCType::getInterfaces(void)
{
    return interfaces;
}


FieldsList *JCType::getFields(void)
{
    return fields;
}


MethodsList *JCType::getMethods(void)
{
    return methods;
}


StatesList *JCType::getStates(void)
{
    return states;
}


unsigned int JCType::getAccessFlags(void)
{
    return modifiers;
}


char *JCType::getAsciiName(void)
{
    return shortName->getAsciiValue();
}


JCIdentifier *JCType::getName(void)
{
    return shortName;
}


void JCType::writeInto(JCOutClassFile *aClassFile)
{
}


void JCType::setShadow(JCCteClass *aClassCte)
{
    shadow= aClassCte;
}


JCCteClass * JCType::getShadow(void)
{
    return shadow;
}


void JCType::setPackage(JCPackageDef *aPackage)
{
    package= aPackage;
}


unsigned int JCType::storeFullName(char *buffer)
{
    return package->composeClassName(buffer, this);
}


JCMember *JCType:: checkFieldForClash(JCField *aField)
{
//    TODO.
    return false;
}


JCMember *JCType:: checkMethodForClash(JCMethod *aField)
{
//    TODO.
    return false;
}



JCMember *JCType:: checkStateForClash(JCState *aField)
{
//    TODO.
    return false;
}


bool JCType::resolveHierarchy(void)
{
    if (!(resolutionLevel & hierarchy)) {
	bool result= true;
	if (rawSuper != NULL) {
	    if (extended == NULL) {
		if ((extended= rawSuper->getRealType()) == NULL) {
		    cout << "ERRMSG: class " << getAsciiName() << " extends unknown class ";
		    cout << rawSuper->getTypeName()->getAsciiValue() << ".\n";
		    result= false;
		}
	    }
	}
	if (rawInterfaces != NULL) {
	    JCReferencedType *tmpInterface= rawInterfaces;
	    do {
		if (tmpInterface->isResolved()) {
		    // ATTN: The presence of an interface in the list must be checked before adding.
		    interfaces->addObject(tmpInterface->getRealType());
		}
		else {
		    cout << "ERRMSG: class " << getAsciiName() << " implements unknown interface " << tmpInterface->getTypeName()->getAsciiValue() << ".\n";
			result= false;
		}
		tmpInterface= tmpInterface->getNext();
	    } while (tmpInterface != NULL);
	}
	resolutionLevel|= (result) ? hierarchy : 0;
    }
    return ((resolutionLevel & hierarchy) != 0);
}


bool JCType::resolveMemberTyping(void)
{
    if (!(resolutionLevel & members)) {
	JCField *tmpField;
	JCMethod *tmpMethod;
	JCState *tmpState;
	unsigned int nbrElements, i;
	char errMsg[512];
	bool result= true;

	// At this point, the super-classes and interfaces are all known (unless some can't
	// be found at all).  The super-class shadowed fields, the modifiers and the overloading
	// can be checked completely.
	// ATTN: Must also do a check on integrity of modifiers.
	// ATTN: Must make sure that no two methods have the same parameter typing in this
	// class.
	// ATTN: Must make sure that we don't sub-implement a final or static.

	    // Check typing for all fields.
	nbrElements= fields->count();
	for (i= 0; i < nbrElements; i++) {
	    tmpField= fields->objectAt(i);
	    if (!tmpField->resolveTyping()) {
		sprintf(errMsg, "In class %s, field %s is of undefined type %s", this->getAsciiName(), tmpField->getAsciiValue(), tmpField->getReturnedType()->getTypeName()->getAsciiValue());
		package->getCompiler()->addError(errMsg);
		result= false;
	    }
	}
    
	    // Check typing for all methods.
	nbrElements= methods->count();
	for (i= 0; i < nbrElements; i++) {
	    tmpMethod= methods->objectAt(i);
	    if (!tmpMethod->resolveTyping()) {
		if (tmpMethod->getReturnedType()->isPrimitive()) {
		    sprintf(errMsg, "In class %s, method uses undefined type",  this->getAsciiName(), tmpMethod->getAsciiValue());
		}
		else {
		    sprintf(errMsg, "In class %s, method %s returns undefined type %s",  this->getAsciiName(), tmpMethod->getAsciiValue(), tmpMethod->getReturnedType()->getTypeName()->getAsciiValue());
		}
		package->getCompiler()->addError(errMsg);
		result= false;
	    }
	}
    
	    // Check typing for all states.
	nbrElements= states->count();
	for (i= 0; i < nbrElements; i++) {
	    tmpState= states->objectAt(i);
	    if (!tmpState->resolveTyping()) {
		package->getCompiler()->addError("state is not resolved");
		result= false;
	    }
	    // ATTN: Must also do a check on integrity of modifiers.
	}

	resolutionLevel|= (result) ? members : 0;
    }
    return ((resolutionLevel & members) != 0);
}


bool JCType::resolveClassSymbols(void)
{
    return nameSpace->resolveAll();
}


void JCType::setLineRange(unsigned int firstLine, unsigned int lastLine)
{
    startLine= firstLine;
    endLine= lastLine;
}


JCResolved *JCType::getThisDeclarator(void)
{
    if (thisResolver == NULL) {
	JCVariableDeclaration *declarationTmp;
	JCDimIdentifier *tmpDimIdent;
	JCIdentifier *tmpIdent;

	tmpIdent= new JCIdentifier(JCCteUtf8::getWellKnownName(JCCteUtf8::thisIdent));
	tmpDimIdent= new JCDimIdentifier;
	tmpDimIdent->setName(tmpIdent);

	if (refEquivalent == NULL) refEquivalent= new JCReferencedType(this); 

	declarationTmp= new JCVariableDeclaration;
	declarationTmp->setName(tmpDimIdent);
	declarationTmp->setTyping(refEquivalent);

	thisResolver= new JCResolved(tmpIdent, declarationTmp, JCName::localVariable);
    }

    return thisResolver;
}


JCResolved *JCType::getSuperDeclarator(void)
{
    if (superResolver == NULL) {
	JCVariableDeclaration *declarationTmp;
	JCReferencedType *tmpRefType;
	JCDimIdentifier *tmpDimIdent;
	JCIdentifier *tmpIdent;

	tmpIdent= new JCIdentifier(JCCteUtf8::getWellKnownName(JCCteUtf8::superIdent));
	tmpDimIdent= new JCDimIdentifier;
	tmpDimIdent->setName(tmpIdent);

	declarationTmp= new JCVariableDeclaration;
	declarationTmp->setName(tmpDimIdent);
	declarationTmp->setTyping(rawSuper);

	superResolver= new JCResolved(tmpIdent, declarationTmp, JCName::localVariable);
    }

    return superResolver;
}


JCResolved *JCType::findSymbol(JCIdentifier *anIdent)
{
    JCType *tmpExtended;
    JCNameSpace *tmpSpace;
    JCResolved *result= NULL;

    // ATTN: Will return the first method name that match the identifier.  It is necessary
    // to perform additional tests to find the right method afterward.

    tmpSpace= nameSpace;
    tmpExtended= extended;

    while (tmpSpace != NULL) {
	if ((result= tmpSpace->findResolved(anIdent)) != NULL) {
	    break;
	}
	if (tmpExtended != NULL) {
	    tmpSpace= tmpExtended->nameSpace;
	    tmpExtended= tmpExtended->extended;
	}
	else
	    tmpSpace= NULL;
    }

    return result;
}


JCResolved *JCType::findCorrectMethod(JCIdentifier *anIdent, JCExpression *typing)
{
// ATTN: TODO.
    return NULL;
}


bool JCType::containsJCode(void)
{
    unsigned int i;

    for (i= 0; i < methods->count(); i++) {
	if (methods->objectAt(i)->hasSomeJCode()) return true;    // Warning: quick exit.
    }

    for (i= 0; i < states->count(); i++) {
	if (states->objectAt(i)->hasSomeJCode()) return true;    // Warning: quick exit.
    }

    return false;
}


JCReferencedType *JCType::getRefEquivalent(void)
{
    if (refEquivalent == NULL) {
	refEquivalent= new JCReferencedType(this); 
    }
   return refEquivalent;
}


void JCType::addUser(JCNamedExpr *anExpression)
{
    if (!nameSpace->relateNamedExpr(anExpression)) {
	// ERRMSG: Couldn't link the name in temporary type name space.
    }
}


void JCType::importUnknown(JCNameSpace *aSpace)
{
    nameSpace->importUnresolved(aSpace);
}


void JCType::importUnknown(JCUnresolved *unresList)
{
    nameSpace->importUnresolved(unresList);
}


JCResolved *JCType::findSymbol(JCUnresolved *anUnknown)
{
    JCType *tmpExtended;
    JCNameSpace *tmpSpace;
    JCResolved *result= NULL;

    if (extended != NULL) {
	tmpExtended= extended;
	tmpSpace= tmpExtended->nameSpace;

	while (tmpSpace != NULL) {
	    if ((result= tmpSpace->findResolved(anUnknown->getIdent())) != NULL) {
		break;
	    }
	    if (tmpExtended != NULL) {
		tmpSpace= tmpExtended->nameSpace;
		tmpExtended= tmpExtended->extended;
	    }
	    else
		tmpSpace= NULL;
	}
    }

    return result;
}


JCOverloadDictionary *JCType::getOverloadDictionary(void)
{
    if (overloadDict == NULL) {
	// TMPTMP-971119 [HD]:
	if ((methods->count() + states->count()) > 0) {
	    overloadDict= new JCOverloadDictionary(this);
	    if (extended != NULL) {
		JCOverloadDictionary *superDict;
		if ((superDict= extended->getOverloadDictionary()) != NULL) {
		    overloadDict->linkToSuper(superDict);
		}
	    }
	}
	else {
	    if (extended != NULL) {
		overloadDict= extended->getOverloadDictionary();
	    }
	}
    }

    return overloadDict;
}


JCCompiler *JCType::getCompiler(void)
{
    return package->getCompiler();
}


void JCType::setReference(JCReferencedType *aRef)
{
    if (refEquivalent != NULL) {
	delete refEquivalent;
    }
    refEquivalent= aRef;
}


/**************************************************
* Implementation: JCClass.
**************************************************/

JCClass::JCClass(void)
{
    classInitializers= new InitializersList;
}


JCClass::JCClass(JCIdentifier *aName, JCPackageDef *aPackage)
{
    classInitializers= new InitializersList;
    shortName= aName;
    package= aPackage;
    if (aPackage->defineType(aName, this, JCName::uClass)) {
	// ERRMSG: Probleme, peut pas inclure la classe dans son package.
    }
   nameSpace= new JCNameSpace();
}


bool JCClass::setSuperClass(JCReferencedType *aRefType)
{
    JCUnresolved *unknown;

    rawSuper= aRefType;
    if (!thePackage->bind(aRefType->getTypeName(), aRefType)) {
	unknown=  thePackage->addUnknown(aRefType);
	unknown->linkType(aRefType);
     }
    return false;
}


bool JCClass::addField(JCField *aField)
{
    bool result= true;

    if (JCType::addField(aField)) {
	if (aField->hasInitializer()) {
	    // ATTN: The initializer expressions must be added to an 'init' method somewhere.
	    // The question is: what to do if there is already constructors defined... they all get
	    // the field initializer expressions ??
	}
    }
    else result= false;

    return result;
}


bool JCClass::addClassInitializer(JCStaticInitializer *anInit)
{
// ATTN: Must make sure that the initializer can be put inside the class.  Return false if not.
    classInitializers->addObject(anInit);
    return true;
}

void JCClass::writeInto(JCOutClassFile *aClassFile)
{
    unsigned int i;

    aClassFile->saveFileHeader();
    aClassFile->buildConstantPool();
    aClassFile->saveConstantPool();
// DEBUG:
    aClassFile->dumpConstantPool();

    aClassFile->writeUShort(modifiers);
    aClassFile->saveTypeHeader();

    aClassFile->writeUShort(interfaces->count());
    for (i= 0; i < interfaces->count(); i++) {
	interfaces->objectAt(i)->writeInto(aClassFile);
    }
    aClassFile->writeUShort(fields->count());
    for (i= 0; i < fields->count(); i++) {
	fields->objectAt(i)->writeInto(aClassFile);
    }
    aClassFile->writeUShort(methods->count() + states->count());
    for (i= 0; i < methods->count(); i++) {
	methods->objectAt(i)->writeInto(aClassFile);
    }
    for (i= 0; i < states->count(); i++) {
	states->objectAt(i)->writeInto(aClassFile);
    }

    aClassFile->saveAttributes();
}


bool JCClass::isInterface(void)
{
	// Must be implemented by subclasses.
    return false;
}


JCType *JCClass::getSuper(void)
{
    return extended;
}


JCReferencedType *JCClass::getSuperType(void)
{
    return rawSuper;
}


bool JCClass::resolveStatements(void)
{
    JCMethod *tmpMethod;
    JCState *tmpState;
    unsigned int nbrElements, i;
    bool result= true;

    nbrElements= methods->count();
    for (i= 0; i < nbrElements; i++) {
	tmpMethod= methods->objectAt(i);
	if (!tmpMethod->resolveCode()) result= false;
    }
    nbrElements= states->count();
    for (i= 0; i < nbrElements; i++) {
	tmpState= states->objectAt(i);
	if (!tmpState->resolveCode()) result= false;
    }
    resolutionLevel|= (result) ? allCode : 0;

    return result;
}


void JCClass::debugDefineRootClass(void)
{
    JCMethod *tmpMethod;
    JCDimIdentifier *tmpDimName;
    JCIdentifier *methodName;
    JCCteNameAndType *tmpNameType;
    JCCteUtf8 *tmpSignature;
    char tmpTypeName[1024];

    rawSuper= NULL;
    package->composeClassName(tmpTypeName, this);
    shadow= new JCCteClass(JCCteUtf8::addUniqueInstance((unsigned short *)tmpTypeName));

	// Create <init> method.
    tmpDimName= new JCDimIdentifier();
    tmpDimName->setName((methodName= new JCIdentifier(JCCteUtf8::getWellKnownName(JCCteUtf8::initIdent))));
    tmpMethod= new JCMethod();
    tmpMethod->setModifiers(ACC_PUBLIC);
    tmpMethod->setName(tmpDimName);
    tmpMethod->setReturnedType(JCReferencedType::getVoidType());
    this->addMethod((JCMethod *)tmpMethod);  
    tmpMethod->bindToType(this);
    nameSpace->quickAddResolved(methodName, tmpMethod, JCName::uMethod);

	// Make a shadow for the method.
    tmpSignature= tmpMethod->buildCteSignature();
    tmpNameType= new JCCteNameAndType(methodName->getValue(), tmpSignature);
    tmpMethod->setShadow(new JCCteMethodRef(getShadow(), tmpNameType));
}


/**************************************************
* Implementation: JCInterface.
**************************************************/

JCInterface::JCInterface(void)
{

}


bool JCInterface::addClassInitializer(JCStaticInitializer *anInit)
{
    return false;
}


void JCInterface::writeInto(JCOutClassFile *aClassFile)
{
    // The interface definition must be writing itself as a ref or as the real thing ?
}


bool JCInterface::isInterface(void)
{
	// Must be implemented by subclasses.
    return true;
}


/**************************************************
* Implementation: JCMember.
**************************************************/

JCMember::JCMember(void)
{
    owner= NULL;
    next= NULL;
    rawType= NULL;
    nbrDimensions= 0;
    identName= NULL;
    shadow= NULL;
    attributes= new AttributesList();
    startLine= endLine= 0;
}


void JCMember::setNext(JCMember *nextElement)
{
    next= nextElement;
}


void JCMember::link(JCMember *nextElement)
{
    if (next == NULL) next= nextElement;
    else {
	JCMember *tmpNext= next;
	while (tmpNext->next != NULL) tmpNext= tmpNext->next;
	tmpNext->next= nextElement;
     }

}


JCMember *JCMember::getNext(void)
{
    return next;
}


bool JCMember::setReturnedType(JCReferencedType *aType)
{
    rawType= aType;
    nbrDimensions+= rawType->getNbrDimensions();
    return false;
}


bool JCMember::bindToType(JCType *aType)
{
    owner= aType;
    return false;
}


unsigned int JCMember::memberType(void)
{
    return ABSTRACT_MEMBER;
}


bool JCMember::resolveTyping(void)
{
    if (rawType != NULL) {
	resolutionLevel|= (rawType->isResolved()) ? returnType : 0;
    }
    else resolutionLevel^= returnType;
    if ((resolutionLevel & returnType)) {
	JCCteNameAndType *tmpNameType;
	JCCteUtf8 *tmpSignature;

	    // Make a shadow for the member.
	tmpSignature= buildCteSignature();
	tmpNameType= new JCCteNameAndType(identName, tmpSignature);
	if (memberType() == FIELD_MEMBER)
	    shadow= new JCCteFieldRef(owner->getShadow(), tmpNameType);
	else
	    shadow= new JCCteMethodRef(owner->getShadow(), tmpNameType);
    }
    return ((resolutionLevel & returnType) != 0);
}


void JCMember::writeInto(JCOutClassFile *aClassFile)
{
    CompilerObject::writeInto(aClassFile);
    shadow->writeNameType(aClassFile);
    aClassFile->writeUShort(attributes->count());
}


void JCMember::mapToPool(ConstantsList *aPool)
{
    // The JCCteFieldRef is added only when the field is used as a reference.
    shadow->getNameType()->addToPool(aPool);
}


JCCteUtf8 * JCMember::buildCteSignature(void)
{
    // must be implemented by subclass.
    return NULL;
}


void JCMember::setShadow(JCReference *aClassCte)
{
    shadow= aClassCte;
}


JCReference *JCMember::getShadow(void)
{
    return shadow;
}


char *JCMember::getAsciiValue(void)
{
    return identName->asciiString();
}


void JCMember::setLineRange(unsigned int firstLine, unsigned int lastLine)
{
    startLine= firstLine;
    endLine= lastLine;
}


void JCMember::getLineRange(unsigned int& firstLine, unsigned int& lastLine)
{
    firstLine= startLine;
    lastLine= endLine;
}


JCReferencedType *JCMember::getReturnedType(void)
{
    return rawType;
}


JCType *JCMember::getOwner(void)
{
    return owner;
}


unsigned int JCMember::getNbrDimensions(void)
{
    if (rawType != NULL) {
	return nbrDimensions;
    }
    else return nbrDimensions;
}


JCCteUtf8 *JCMember::getName(void)
{
    return identName;
}


/**************************************************
* Implementation: JCField.
**************************************************/

JCField::JCField(void)
{
    initializers= NULL;
    rawDeclaration= NULL;
}


bool JCField::setDeclarator(JCVariableDeclaration *varDeclarator)
{
    JCExpression *tmpExpr;

    identName= varDeclarator->getName()->getName()->getValue();
    rawDeclaration= varDeclarator;
    if (rawType != NULL) rawDeclaration->setTyping(rawType);
    nbrDimensions= rawDeclaration->getNbrDimensions();
    if ((tmpExpr= rawDeclaration->getInitializer()) != NULL) {
	initializers= new ExpressionsList();
	do {
	    initializers->addObject(tmpExpr);
	    tmpExpr= tmpExpr->getNext();
	} while (tmpExpr);
    }
    return false;
}


bool JCField::setReturnedType(JCReferencedType *aType)
{
    JCMember::setReturnedType(aType);
    rawDeclaration->setTyping(aType);
    nbrDimensions= rawDeclaration->getNbrDimensions();
    return false;
}


bool JCField::bindToType(JCType *aType)
{
    JCVariableDeclaration *tmpVarDecl;
    JCUnresolved *unknown;

    JCMember::bindToType(aType);
	// ATTN: Should do the following if super::bindToType didn't fail only.

    tmpVarDecl= rawDeclaration;
    if (!thePackage->defineField(tmpVarDecl->getUndimIdentifier(), this)) {
	// ERRMSG: Already defined variable name !
	cout << "Variable is already declared.\n";
     }
    if (tmpVarDecl->hasComplexType()) {
	if (!thePackage->bind(tmpVarDecl->getTypeName(), tmpVarDecl->typing())) {
	    unknown=  thePackage->addUnknown(tmpVarDecl->typing());
	 }
     }

    return false;
}


unsigned int JCField::memberType(void)
{
    return FIELD_MEMBER;
}


bool JCField::isClashing(JCMember *aMember)
{
    // Find the name, check if it is equal with ours.
// ATTN: TO IMPLEMENT.
    return false;
}


JCCteUtf8 *JCField::buildCteSignature(void)
{
    unsigned int tmpLength;
    static char tmpBuffer[1024];

    if ((tmpLength= nbrDimensions - rawType->getNbrDimensions()) > 0) {
	for (unsigned int i= 0; i < tmpLength; i++) tmpBuffer[i]= '[';
    }
    tmpLength+= rawType->composeSignature(&tmpBuffer[tmpLength]);
    tmpBuffer[tmpLength]= '\0';
    return JCCteUtf8::addUniqueInstance((unsigned short *)tmpBuffer);
}


bool JCField::resolveTyping(void)
{
    if ((resolutionLevel & returnType)) return true;	// Warning: quick exit.

    if (JCMember::resolveTyping()) {
	// Do a final check for name or type clash in class hierarchy:
	if (!owner->isInterface()) {
	    // ATTN: Can an interface do variable declaration ?
	    if (((JCClass *)owner)->getSuper()) {
		JCMember *clasher;
		if ((clasher= ((JCClass *)owner)->getSuper()->checkFieldForClash(this)) != NULL) {
		    cout << "ERRMSG: Field " << identName->asciiString() << " is clashing.\n";
		    cout << "ERRMSG: Problem with  " << clasher->getAsciiValue();
		    cout << " in class " << clasher->owner->getAsciiName() << ".\n";
		}
	    }
	}
    }
    return ((resolutionLevel & returnType) != 0);
}


ExpressionsList *JCField::getInitializer(void)
{
    return initializers;
}


bool JCField::hasInitializer(void)
{
    if (initializers != NULL)
	return (initializers->count() > 0);
    else
	return false;
}


/**************************************************
* Implementation: JCSpecialField.
**************************************************/

JCResolved *JCSpecialField::getField(JCSpecialField:: KnownSpecial aSpecial)
{
// TODO:
    return NULL;
}


/**************************************************
* Implementation: JCMethod.
**************************************************/

JCMethod::JCMethod(void)
{
    constructorFlag= false;
    nbrArguments= 0;
    argTypes= NULL;
    argNames= NULL;
    exceptions= NULL;
    mainBlock= NULL;
    rawName= NULL;
    rawArguments= NULL;
    rawExceptions= NULL;
    nameSpace= NULL;
    attributes= new AttributesList();
    synonyms= NULL;
}


bool JCMethod::setName(JCDimIdentifier *aName)
{
    rawName= aName;
    identName= aName->getName()->getValue();

/* MOD-970903 [HD]: Took this out, because it is called while the return type is not yet known.
    if (!thePackage->defineMethod(aName->getName(), this)) {
	// It is not an error to define multiple methods with the same names.
	// Their arguments typing must be different though.
     }
*/

    nbrDimensions+= rawName->getNbrDimensions();
    return false;
}


bool JCMethod::setParameters(JCVariableDeclaration *someDeclarations)
{
    JCVariableDeclaration *tmpVarDecl;
    JCUnresolved *unknown;

    rawArguments= someDeclarations;

    nameSpace= new JCMethodSpace(thePackage->getCurrentType());
    thePackage->pushNameSpace(nameSpace);

    if (rawArguments != NULL) {
	tmpVarDecl= rawArguments;
	while (tmpVarDecl != NULL) {
	    if (!thePackage->defineLocalVariable(tmpVarDecl->getUndimIdentifier(), tmpVarDecl)) {
		cout << "ERRMSG: Already defined variable name !\n";
	    }
	    else nbrArguments++;
	    if (tmpVarDecl->hasComplexType()) {
		if (!thePackage->bind(tmpVarDecl->getTypeName(), tmpVarDecl->typing())) {
		    unknown=  thePackage->addUnknown(tmpVarDecl->typing());
		}
	    }
	    tmpVarDecl= tmpVarDecl->getNext();
	 }
     }
    return false;
}


void JCMethod::setNameSpace(JCMethodSpace *aNameSpace)
{
    nameSpace= aNameSpace;
}


bool JCMethod::setExceptions(JCReferencedType *someTypes)
{
    rawExceptions= someTypes;
    return false;
}


bool JCMethod::setBody(JCActionBlock *aBlock)
{
    mainBlock= aBlock;
    thePackage->popNameSpace();
    return false;
}


bool JCMethod::bindToType(JCType *aType)
{
    JCUnresolved *unknown;
    JCReferencedType *tmpRawType;

    JCMember::bindToType(aType);
	// ATTN: Should do the following if super::bindToType didn't fail only.

	// ATTENTION: What must be done in binding the method to the type ?
    if (!rawType->isPrimitive()) {
	if (!thePackage->bind(rawType->getTypeName(), rawType)) {
	    unknown=  thePackage->addUnknown(rawType);
	 }
     }
    if (rawExceptions != NULL) {
	tmpRawType= rawExceptions;
	while (tmpRawType != NULL) {
	    if (!thePackage->bind(tmpRawType->getTypeName(), tmpRawType)) {
		unknown=  thePackage->addUnknown(tmpRawType);
	     }
	    tmpRawType= tmpRawType->getNext();
	 }
     }
    return false;
}


unsigned int JCMethod::memberType(void)
{
    return METHOD_MEMBER;
}


bool JCMethod::isClashing(JCMethod *aMethod)
{
    // Find the name, check if it is equal with ours.
    // If yes, then check if typing is different.
    // TODO.
    return false;
}


bool JCMethod::isClashing(JCField *aField)
{
    // Find the name, check if it is equal with ours.
    // TODO.
    return false;
}


void JCMethod::writeInto(JCOutClassFile *aClassFile)
{
    aClassFile->startCodeContext(this);
    makeAttributes(aClassFile);
    aClassFile->closeCodeContext();

	// Write header, followed by attributes.
    JCMember::writeInto(aClassFile);
    for (unsigned int i= 0; i < attributes->count(); i++) {
	attributes->objectAt(i)->writeInto(aClassFile);
    }
}


void JCMethod::makeAttributes(JCOutClassFile *aClassFile)
{
    JCOutAttribute *tmpAttribute;

    // The method has two attributes: Code, and Exceptions.

    // Code: scan le mainBlock, et fait de la descente dans chacune de ses actions.
    if (mainBlock) {
	tmpAttribute= new JCCodeAttr(aClassFile);
	if (tmpAttribute) {
	    ((JCCodeAttr *)tmpAttribute)->generateCode(aClassFile);
	    attributes->addObject(tmpAttribute);
	}
    }

    // Exceptions: elles sont donnees par le ExceptionsList.
    if (rawExceptions != NULL) {  	// ATTN: TMPTMP !
	tmpAttribute= new JCExceptionAttr(rawExceptions);
	if (tmpAttribute) attributes->addObject(tmpAttribute);
    }
}


void JCMethod::mapToPool(ConstantsList *aPool)
{
    unsigned int nbrWideArgs= 0;

    JCMember::mapToPool(aPool);

    // Add other items: 
    //  if option -g, add argument names:
    if (rawArguments != NULL) {
	JCVariableDeclaration *tmpVar= rawArguments;
	do {
	    tmpVar->getUndimIdentifier()->getValue()->addToPool(aPool);
	    if (tmpVar->hasWideType()) nbrWideArgs++;
	    tmpVar= tmpVar->getNext();
	} while (tmpVar != NULL);
    }

    // ATTN: must map exception types throwns.
    if (rawExceptions) {
	JCCteUtf8::getWellKnownName(JCCteUtf8::exceptions)->addToPool(aPool);
	// TODO-970514: map the types of exceptions.
    }

    // Finally, map actions block.
    mainBlock->mapToPool(aPool, getNbrArguments() + nbrWideArgs);
}


JCCteUtf8 *JCMethod::buildCteSignature(void)
{
    JCVariableDeclaration *tmpArgument;
    unsigned int tmpLength= 1, additionalDims, nbrExtraDims;
    static char tmpBuffer[1024]= { '(' };

    tmpArgument= rawArguments;
    while (tmpArgument != NULL) {
	if ((additionalDims= tmpArgument->getNbrDimensions() - tmpArgument->typing()->getNbrDimensions()) > 0) {
	    for (unsigned int i= 0; i < additionalDims; i++) tmpBuffer[tmpLength++]= '[';
	}
	tmpLength+= tmpArgument->typing()->composeSignature(&tmpBuffer[tmpLength]);
	tmpArgument= tmpArgument->getNext();
    }
    tmpBuffer[tmpLength++]= ')';
    if ((nbrExtraDims= nbrDimensions - rawType->getNbrDimensions()) > 0) {
	for (unsigned int i= 0; i < nbrExtraDims; i++) tmpBuffer[tmpLength++]= '[';
    }
    tmpLength+= rawType->composeSignature(&tmpBuffer[tmpLength]);
    tmpBuffer[tmpLength]= '\0';
    return JCCteUtf8::addUniqueInstance((unsigned short *)tmpBuffer);
}

void JCMethod::setConstructor(bool aValue)
{
    constructorFlag= aValue;
}


bool JCMethod::isConstructor(void)
{
    return constructorFlag;
}


bool JCMethod::resolveTyping(void)
{
    if (resolutionLevel & parameters) return true;	// Warning: quick exit.

    if (JCMember::resolveTyping()) {
	// Do a final check for name or type clash in class hierarchy:
	if (owner->isInterface()) {
	    // TODO !
	    // Must go through the interfaces extended and do the verification there (they are
	    // in the interfaces list.
	}
	else {
	    if (((JCClass *)owner)->getSuper()) {
		JCMember *clasher;
		if ((clasher= ((JCClass *)owner)->getSuper()->checkMethodForClash(this)) != NULL) {
		    cout << "ERRMSG: Method " << identName->asciiString() << " is clashing.\n";
		    cout << "ERRMSG: Problem with  " << clasher->getAsciiValue();
		    cout << " in class " << clasher->owner->getAsciiName() << ".\n";
		}
		else {
		    JCVariableDeclaration *tmpArgs= rawArguments;
		    unsigned int argIndex, argCursor= 0;

		    if (nbrArguments > 0) {
			argTypes= new JCReferencedType*[nbrArguments];
		    }
    
		    // Resolve all arguments.
		    argIndex= (isStatic()) ? 0 : 1;	// Skip 'this' if method is not static.
		    resolutionLevel|= parameters;	// Start by supposing that all is well.
		    while (tmpArgs != NULL) {
			tmpArgs->setIndex(argIndex++);
			if (tmpArgs->hasWideType()) argIndex++;
			if (!tmpArgs->isResolved()) {
			    resolutionLevel^= parameters;    // Some argument has no valid type !
			    cout << "ERRMSG: argument " << tmpArgs->getUndimIdentifier()->getAsciiValue();
			    cout << " has unknown type " << tmpArgs->getTypeName()->getAsciiValue() << ".\n";
			}
			argTypes[argCursor++]= tmpArgs->typing();
			tmpArgs= tmpArgs->getNext();
		    }
		    // Resolve thrown instances.
			    // ATTN: TO DO !
    		}
	    }
	}
    }
    return ((resolutionLevel & parameters) != 0);
}


unsigned int JCMethod::getNbrArguments(void)
{
    return nbrArguments + ((isStatic()) ? 0 : 1);
}


bool JCMethod::resolveCode(void)
{
    JCNameSpace *tmpSpace;

    if (resolutionLevel & actionBlock) return true;	// Warning: quick exit.

    tmpSpace= nameSpace;
    if (tmpSpace != NULL) {
	bool gotAllSymbols= true;

	do {
	    if (!tmpSpace->resolveAll(this)) gotAllSymbols= false;
	    if ((tmpSpace= tmpSpace->getNext()) == NULL) break;
	} while (tmpSpace->getKind() == JCNameSpace::kBlock);
	resolutionLevel|= (gotAllSymbols) ? actionBlock : 0;
    }
    else resolutionLevel|= actionBlock;

    return ((resolutionLevel & actionBlock) != 0);
}


bool JCMethod::hasSomeJCode(void)
{
	// ATTN: Imprecise test, the main block could contain no real statements.
    if (mainBlock != NULL) return true;
    else return false;
}


void JCMethod::quickExport(void)
{
    if (!thePackage->defineMethod(rawName->getName(), this)) {
	// It is not an error to define multiple methods with the same names.
	// Their arguments typing must be different though.
     }
}


bool JCMethod::resolveOverloading(JCInvokeExpr *anInvocation)
{
    JCMethod *rightOverload;
    JCReferencedType **typing;
    JCOverloadDictionary *overloadDict;
    unsigned int nbrArgs;
    bool result= false;

    nbrArgs= anInvocation->getNbrArguments();

    if (nbrArgs > 0) {
	JCImportManager *importer;
	JCType *aRealType;
	unsigned int i;

	typing= new JCReferencedType*[nbrArgs];
	anInvocation->spitArgumentTypes(typing);

	importer= owner->getCompiler()->getClassManager();
	for (i= 0; i < nbrArgs; i++) {
	    if (typing[i]->isPrimitive()) continue;
	    if (typing[i]->resolution() == NULL) {
		// Try to resolve the type.
		if ((aRealType= importer->findReferedType(typing[i])) != NULL) {
		    typing[i]->setResolution(aRealType->getRefEquivalent()->resolution());
		}
	    }
	}

    }



    overloadDict= owner->getOverloadDictionary();
    if ((rightOverload= overloadDict->getOverloadOf(this, typing, nbrArgs)) != NULL) {
	if (rightOverload != this) {
	    if (anInvocation->resolution()->getSituation() == JCName::resolved) {
		((JCResolved *)anInvocation->resolution())->setDefinition(rightOverload);
		result= true;
	    }
	    else {
		cout << "ERRMSG: Internal error: JCMethod::resolveOverloading found an JCInvokeExpr that has a JCUnresolved.\n";
	    }
	}
	else result= true;
    }

    if (nbrArgs > 0) delete[] typing;
    return result;
}


JCReferencedType **JCMethod::getTypeList(void)
{
    return argTypes;
}


void JCMethod::setSynonyms(JCSynonymTable *someSyns)
{
    synonyms= someSyns;
}


JCSynonymTable *JCMethod::getSynonyms(void)
{
    return synonyms;
}


/**************************************************
* Implementation: JCState.
**************************************************/

JCState::JCState(void) : JCMethod()
{
    rawType= JCReferencedType::getVoidType();
}


bool JCState::setName(JCDimIdentifier *aName)
{
    char *tmpName;
    unsigned int nameLength;
    
	// Add state name 'differentiator'.
    tmpName= new char[(nameLength= aName->getName()->nameLength()) + 2];
    strcpy(tmpName, aName->getName()->getAsciiValue());
    tmpName[nameLength]= '+';
    tmpName[nameLength+1]= '\0';
    identName= JCCteUtf8::addUniqueInstance((unsigned short *)tmpName);

	// Update the CteUtf8 in the identifier.
    aName->getName()->setValue(identName);
    delete tmpName;

    rawName= aName;
    if (!thePackage->defineState(aName->getName(), this)) {
	// It is not an error to define multiple methods with the same names.
	// Their arguments typing must be different though.
     }

    nbrDimensions= 0;
    return false;
}


bool JCState::bindToType(JCType *aType)
{
    JCUnresolved *unknown;
    JCReferencedType *tmpRawType;

    JCMember::bindToType(aType);
	// ATTN: Should do the following only if super::bindToType didn't fail.

	// ATTENTION: What must be done in binding the method to the type ?
    if (rawExceptions != NULL) {
	tmpRawType= rawExceptions;
	while (tmpRawType != NULL) {
	    if (!thePackage->bind(tmpRawType->getTypeName(), tmpRawType)) {
		unknown=  thePackage->addUnknown(tmpRawType);
	     }
	    tmpRawType= tmpRawType->getNext();
	 }
     }
    return false;
}


unsigned int JCState::memberType(void)
{
    return STATE_MEMBER;
}


void JCState::makeAttributes(JCOutClassFile *aClassFile)
{
    JCOutAttribute *tmpAttribute;

    // For now, the state has two attributes: Code, and transitions.

    // Code: scan le mainBlock, et fait de la descente dans chacune de ses actions.
    if (mainBlock) {
	tmpAttribute= new JCStateCodeAttr(aClassFile);
	if (tmpAttribute) {
	    ((JCCodeAttr *)tmpAttribute)->generateCode(aClassFile);
	    attributes->addObject(tmpAttribute);
	}
    }

/* Pour mettre les transitions dans le code.
*/

/* Ex: les exceptions pour la methode.
    if (rawExceptions != NULL) {  	// ATTN: TMPTMP !
	tmpAttribute= new JCExceptionAttr(rawExceptions);
	if (tmpAttribute) attributes->addObject(tmpAttribute);
    }
*/

}


void JCState::mapToPool(ConstantsList *aPool)
{
    unsigned int nbrWideArgs= 0;

    JCMember::mapToPool(aPool);
    // Add other items: 
    //  if option -g, add argument names:
    if (rawArguments != NULL) {
	JCVariableDeclaration *tmpVar= rawArguments;
	do {
	    aPool->addIndexedObject(tmpVar->getUndimIdentifier()->getValue());
	    if (tmpVar->hasWideType()) nbrWideArgs++;
	    tmpVar= tmpVar->getNext();
	} while (tmpVar != NULL);
    }
    mainBlock->mapToPool(aPool, getNbrArguments());
}


JCCteUtf8 *JCState::buildCteSignature(void)
{
    JCVariableDeclaration *tmpArgument;
    unsigned int tmpLength= 1, additionalDims;
    static char tmpBuffer[1024]= { '(' };

    tmpArgument= rawArguments;
    while (tmpArgument != NULL) {
	if ((additionalDims= tmpArgument->getNbrDimensions() - tmpArgument->typing()->getNbrDimensions()) > 0) {
	    for (unsigned int i= 0; i < additionalDims; i++) tmpBuffer[tmpLength++]= '[';
	}
	tmpLength+= tmpArgument->typing()->composeSignature(&tmpBuffer[tmpLength]);
	tmpArgument= tmpArgument->getNext();
    }
    tmpBuffer[tmpLength++]= ')';
    tmpBuffer[tmpLength++]= 'V';
    tmpBuffer[tmpLength]= '\0';
    return JCCteUtf8::addUniqueInstance((unsigned short *)tmpBuffer);
}


bool JCState::resolveTyping(void)
{
    JCCteNameAndType *tmpNameType;
    JCCteUtf8 *tmpSignature;

    if ((resolutionLevel & parameters) != 0) return true;	// Warning: quick exit.

	// Make a shadow for the field.
    tmpSignature= buildCteSignature();
    tmpNameType= new JCCteNameAndType(identName, tmpSignature);
    shadow= new JCCteMethodRef(owner->getShadow(), tmpNameType);

    // Do a final check for name or type clash in class hierarchy:
    if (owner->isInterface()) {
	// TODO !
	// Must go through the interfaces extended and do the verification there (they are
	// in the interfaces list.
    }
    else {
	if (((JCClass *)owner)->getSuper()) {
	    JCMember *clasher;
	    if ((clasher= ((JCClass *)owner)->getSuper()->checkStateForClash(this)) != NULL) {
		cout << "ERRMSG: State " << identName->asciiString() << " is clashing.\n";
		cout << "ERRMSG: Problem with  " << clasher->getAsciiValue();
		cout << " in class " << clasher->owner->getAsciiName() << ".\n";
	    }
	    else {
		JCVariableDeclaration *tmpArgs= rawArguments;
		unsigned int argIndex, argCursor= 0;

		if (nbrArguments > 0) {
		    argTypes= new JCReferencedType*[nbrArguments];
		}
    
		// Resolve all arguments.
//		argIndex= (isStatic()) ? 0 : 1;	// Can a state be static ??
		argIndex= 1;
		resolutionLevel|= parameters;	// Start by supposing that all is well.
		while (tmpArgs != NULL) {
		    tmpArgs->setIndex(argIndex++);
		    if (tmpArgs->hasWideType()) argIndex++;
		    if (!tmpArgs->isResolved()) {
			resolutionLevel^= parameters;    // Some argument has no valid type !
			cout << "ERRMSG: argument " << tmpArgs->getUndimIdentifier()->getAsciiValue();
			cout << " has unknown type " << tmpArgs->getTypeName()->getAsciiValue() << ".\n";
		    }
		    argTypes[argCursor++]= tmpArgs->typing();
		    tmpArgs= tmpArgs->getNext();
		}
    	    }
	    // ATTN: Must resolve the transitions defined.
	}
    }
    return ((resolutionLevel & parameters) != 0);
}


/**************************************************
* Implementation: JCStaticInitializer.
**************************************************/

/* StaticInitializer in a class must be collected and stored as a single
*  method called <clinit>.
*/


JCStaticInitializer::JCStaticInitializer()
{
    mainBlock= NULL;
}


bool JCStaticInitializer::setBlock(JCActionBlock *aBlock)
{
    mainBlock= aBlock;
    return false;
}


unsigned int JCStaticInitializer::memberType(void)
{
    return STATINIT_MEMBER;
}



#if defined(PLZEN_LEVEL_2)
/**************************************************
* Implementation: JCTransition.
**************************************************/

JCTransition::JCTransition(void)
{
    trigger= NULL;
    destination= NULL;
    modifiers= 0;
    startLine= endLine= 0;
}


JCTransition::~JCTransition(void)
{
    // TODO.
}


void JCTransition::setTriggers(JCExpression *someTriggers)
{
    trigger= someTriggers;
}


void JCTransition::setSpecialDestination(DestinationModifiers simpleDest)
{
    destination= NULL;
    modifiers= simpleDest;
}


void JCTransition::setDestination(JCStateInvokeExpr *aStateDest)
{
    destination= aStateDest;
}


void JCTransition::setLineRange(unsigned int firstLine, unsigned int lastLine)
{
    startLine= firstLine;
    endLine= lastLine;
}



void JCTransition::mapToPool(ConstantsList *aPool)
{
    if ((modifiers & tmDefaulter) == 0) {
	trigger->mapToPool(aPool);
    }
    if ((modifiers & (dmPassby | dmConsume | dmBreak)) == 0) {
	destination->mapToPool(aPool);
    }
}


unsigned int JCTransition::getModifiers(void)
{
    return modifiers;
}


JCExpression *JCTransition::getTriggers(void)
{
    return trigger;
}


JCStateInvokeExpr *JCTransition::getDestination(void)
{
    return destination;
}


bool JCTransition::setModifiers(unsigned int flags)
{
    modifiers|= flags;
    return true;
}

#endif
