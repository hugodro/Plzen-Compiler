/**************************************************
* File: typing.cc.
* Desc: Implementation of the JCReferencedType class.
* Module: AkraLog : JavaComp.
* Rev: 5 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <string.h>
#include "identifiers.h"
#include "nameSpace.h"
#include "constants.h"
#include "compileObjects.h"
#include "outConstant.h"
#include "typing.h"


JCReferencedType *JCReferencedType::populars[nbrPopular]= { NULL };


JCReferencedType::PopularType JCReferencedType::letterToPopType(char aLetter)
 {
    switch(aLetter) {
	case JVM_TYPE_VOID: return popVoid;
	case JVM_TYPE_BOOLEAN: return popBoolean;
	case JVM_TYPE_SIGNED_BYTE: return popByte;
	case JVM_TYPE_CHAR: return popChar;
	case JVM_TYPE_UNSIGNED_SHORT: return popShort;
	case JVM_TYPE_INTEGER: return popInteger;
	case JVM_TYPE_FLOAT: return popFloat;
	case JVM_TYPE_LONG: return popLong;
	case JVM_TYPE_DOUBLE: return popDouble;
    }

    return popVoid;
 }
 


void JCReferencedType::initPopularType(void)
{
    populars[popVoid]= new JCReferencedType(JVM_TYPE_VOID); 
    populars[popBoolean]= new JCReferencedType(JVM_TYPE_BOOLEAN);
    populars[popByte]= new JCReferencedType(JVM_TYPE_SIGNED_BYTE);
    populars[popChar]= new JCReferencedType(JVM_TYPE_CHAR);
    populars[popShort]= new JCReferencedType(JVM_TYPE_UNSIGNED_SHORT);
    populars[popInteger]= new JCReferencedType(JVM_TYPE_INTEGER);
    populars[popFloat]= new JCReferencedType(JVM_TYPE_FLOAT);
    populars[popLong]= new JCReferencedType(JVM_TYPE_LONG);
    populars[popDouble]= new JCReferencedType(JVM_TYPE_DOUBLE);

/* ATTN: Must implement the non-primitive types.
    populars[popThrowable]= new JCReferencedType(JVM_TYPE_DOUBLE);
*/

    populars[popString]= new JCReferencedType();
    JCIdentifier *tmpName[3];
    tmpName[0]= new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)"java"));
    tmpName[1]= new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)"lang"));
    tmpName[2]= new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)"String"));
    tmpName[0]->addComponent(tmpName[1]);
    tmpName[1]->addComponent(tmpName[2]);
    populars[popString]->setTypeName(tmpName[0]);
    populars[popString]->setKind(TYPE_CLASS);

	// ATTN: Must get instead the root class from the compiler.
    populars[popNullObject]= new JCReferencedType();
    populars[popNullObject]->setTypeName(new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)"Object")));
    populars[popNullObject]->setKind(TYPE_CLASS);
}


JCReferencedType *JCReferencedType::getVoidType(void)
{
    return getPopularType(popVoid);
}


JCReferencedType *JCReferencedType::getPopularType(PopularType aType)
{
    if (populars[popVoid] != NULL) {
	return populars[aType];
    }
    else {
	initPopularType();
	return populars[aType];
    }
}


int JCReferencedType::typeCompatibility(JCReferencedType *first, JCReferencedType *second)
{
// TODO: compute if first type extends second (-1), or second extends first (1), or there is no relationship (0), or they are the same (2).
    return 1;
}


JCReferencedType *JCReferencedType::binaryPromotion(JCReferencedType *first, JCReferencedType *second)
{
    if (populars[popVoid] == NULL) {
	initPopularType();
    }

    if ((first->primitiveType == JVM_TYPE_DOUBLE) || (second->primitiveType == JVM_TYPE_DOUBLE)) {
	return populars[popDouble];
    }
    else if ((first->primitiveType == JVM_TYPE_FLOAT) || (second->primitiveType == JVM_TYPE_FLOAT)) {
	return populars[popFloat];
    }
    else if ((first->primitiveType == JVM_TYPE_LONG) || (second->primitiveType == JVM_TYPE_LONG)) {
	return populars[popLong];
    }
    else {
	return populars[popInteger];
    }
}


JCReferencedType *JCReferencedType::unaryPromotion(JCReferencedType *aType)
{
    if (populars[popVoid] == NULL) {
	initPopularType();
    }

    if ((aType->primitiveType == JVM_TYPE_SIGNED_BYTE) || (aType->primitiveType == JVM_TYPE_UNSIGNED_SHORT)) {
	return populars[popInteger];
    }
    else return aType;
}


JCReferencedType::JCReferencedType(void)
{
    next= NULL;
    kind= 0;
    primitiveType= 0;
    nbrDimensions= 0;
    typeName= NULL;
    subType= NULL;
    resolver= NULL;
    tmpNameSpace= NULL;
}


JCReferencedType::JCReferencedType(unsigned int aPrimitive)
{
    next= NULL;
    kind= TYPE_BASIC;
    primitiveType= aPrimitive;
    nbrDimensions= 0;
    typeName= NULL;
    subType= NULL;
    resolver= NULL;
    tmpNameSpace= NULL;
}


JCReferencedType::JCReferencedType(JCType *aType)
{
    next= NULL;
    kind= (aType->isInterface()) ? TYPE_INTERFACE : TYPE_CLASS;
    primitiveType= 0;
    nbrDimensions= 0;
    typeName= aType->getName();
    subType= NULL;
    resolver= new JCResolved(typeName, aType,  (aType->isInterface()) ? JCName::uInterface : JCName::uClass);
    tmpNameSpace= NULL;
}


JCReferencedType::JCReferencedType(unsigned int aKind, JCIdentifier *aName, JCResolved *aResolver)
{
    next= NULL;
    kind= aKind;
    primitiveType= 0;
    nbrDimensions= 0;
    typeName= aName;
    subType= NULL;
    resolver= aResolver;
    tmpNameSpace= NULL;
}


JCReferencedType::JCReferencedType(char *aFullName, unsigned int nameLength)
{
    next= NULL;
    kind= TYPE_CLASS;
    primitiveType= 0;
    nbrDimensions= 0;
    typeName= NULL;
    subType= NULL;
    resolver= NULL;
    tmpNameSpace= NULL;

    if ((typeName= JCIdentifier::getFromPathName(aFullName, nameLength)) == NULL) {
	// TODO: Handle this error.
    }

}


void JCReferencedType::setNext(JCReferencedType *nextElement)
{
    next= nextElement;
}


JCReferencedType * JCReferencedType::getNext(void)
{
    return next;
}


bool JCReferencedType::setKind(unsigned int aKind)
{
    kind= aKind;
    return false;
}


bool JCReferencedType::setTypeName(JCIdentifier *aName)
{
    typeName= aName;
    return false;
}


bool JCReferencedType::setOfPrimitiveType(unsigned int aBType)
{
    kind= TYPE_BASIC;
    primitiveType= aBType;
    return false;
}


bool JCReferencedType::setOfReferencedType(JCReferencedType *aType)
{
    subType= aType;
    return false;
}


void JCReferencedType::incrementNbrDimensions(void)
{
    nbrDimensions++;
}


void JCReferencedType::incNbrDimBy(unsigned int aSize)
{
    nbrDimensions+= aSize;
}


void JCReferencedType::setNbrDimensions(unsigned int aSize)
{
    nbrDimensions= aSize;
}


bool JCReferencedType::isPrimitive(void)
{
    if (kind == TYPE_ARRAY) {
	if (primitiveType == 0) return subType->isPrimitive();
	else return true;
     }
    else return (kind == TYPE_BASIC);
}


bool JCReferencedType::isArray(void)
{
    return (kind == TYPE_ARRAY);
}


bool JCReferencedType::isVoid(void)
{
    return (primitiveType == JVM_TYPE_VOID);
}


bool JCReferencedType::isResolved(void)
{
    if (kind == TYPE_BASIC)
	return true;
    else if (kind == TYPE_ARRAY) {
	if (primitiveType == 0) return (resolver != NULL);
	else return true;
     }
    else {
	return (resolver != NULL);
    }
}


JCIdentifier *JCReferencedType::getTypeName(void)
{
    if (subType != NULL) return subType->getTypeName();
    else return typeName;
}


void JCReferencedType::setResolution(JCResolved *aResolver)
{
    resolver= aResolver;
    if (tmpNameSpace != NULL) {
	((JCType *)resolver->getDefinition())->importUnknown(tmpNameSpace);
	delete tmpNameSpace;
	tmpNameSpace= NULL;
    }
}


JCResolved *JCReferencedType::resolution(void)
{
    return resolver;
}


unsigned int JCReferencedType:: getNbrDimensions(void)
{
    return nbrDimensions;
}


unsigned int JCReferencedType::composeSignature(char *aBuffer)
{
    unsigned int length, i;    /* MOD-MSC: mis la definition de 'i' ici plutot que dans le switch, VC++ n'est pas capable de le prendre.*/
    bool noFullName= true;

    switch(kind) {
	case TYPE_BASIC:  // Primitive.
	    *aBuffer= (char)primitiveType;
	    length= 1;
	    break;
	case TYPE_CLASS:	// Instance.
	case TYPE_INTERFACE:	// Like instance.
	    *aBuffer++= 'L';
	    if (resolver != NULL) {
		if ((resolver->getDefType() == JCName::uClass)
			|| (resolver->getDefType()) == JCName::uInterface) {
			JCType *tmpType= (JCType *)resolver->getDefinition();
			length= tmpType->storeFullName(aBuffer);
			aBuffer+= length;
			noFullName= false;
		}
	    }
	    if (noFullName) {
		strcpy(aBuffer, typeName->getAsciiValue());
		aBuffer+= (length= typeName->nameLength());
	    }
	    length+= 2;
	    *aBuffer= ';';
	    break;
	case TYPE_ARRAY:	// Array of.
	    for (i= 0; i < nbrDimensions; i++, aBuffer++) *aBuffer= '[';
	    length= nbrDimensions;
	    if (primitiveType == 0) {
		length+= subType->composeSignature(aBuffer);
	    }
	    else {
		*aBuffer= (char)primitiveType;
		length++;
	    }
	    break;
	default:
	    // ERRMSG: internal, got a bad type category.
	    length= 0;
	    break;
    }
    return length;
}


JCCteClass *JCReferencedType::getTypeShadow(void)
{
    if (kind == TYPE_ARRAY) {
	return subType->getTypeShadow();
    }
    else {
	if (resolver != NULL) {
	    JCType *tmpType= (JCType *)resolver->getDefinition();
	    return tmpType->getShadow();
	}
	else return NULL;
    }
}


JCType *JCReferencedType:: getRealType(void)
{
    if (resolver) {
	if (resolver->getDefType() == JCName::uClass) {
	    return (JCType *)resolver->getDefinition();
	}
	else return NULL;
    }
    else return NULL;
}


unsigned int JCReferencedType::getPrimitiveType(void)
{
    if (kind == TYPE_ARRAY) {
	if (primitiveType == 0) return subType->getPrimitiveType();
	else return primitiveType;
     }
    else if (kind == TYPE_BASIC) {
	return primitiveType;
    }
    else return 0;
}


bool JCReferencedType::is64Bits(void)
{
    if (kind == TYPE_BASIC) {
	return ((primitiveType == JVM_TYPE_LONG) || (primitiveType == JVM_TYPE_DOUBLE));
    }
    else return false;
}


bool JCReferencedType::isArithmetic(void)
{
    if (kind == TYPE_BASIC) {
	return ((primitiveType == JVM_TYPE_SIGNED_BYTE)
			|| (primitiveType == JVM_TYPE_UNSIGNED_SHORT)
			|| (primitiveType == JVM_TYPE_INTEGER)
			|| (primitiveType == JVM_TYPE_FLOAT)
			|| (primitiveType == JVM_TYPE_LONG)
			|| (primitiveType == JVM_TYPE_DOUBLE));
    }
    else return false;

}


bool JCReferencedType::isInstance(void)
{
    return ((kind == TYPE_CLASS) || (kind == TYPE_ARRAY));
}


bool JCReferencedType::isIntegral(void)
{
    if (kind == TYPE_BASIC) {
	return ((primitiveType == JVM_TYPE_SIGNED_BYTE)
			|| (primitiveType == JVM_TYPE_UNSIGNED_SHORT)
			|| (primitiveType == JVM_TYPE_INTEGER)
			|| (primitiveType == JVM_TYPE_LONG));
    }
    else return false;
}


bool JCReferencedType::isBoolean(void)
{
    return ((kind == TYPE_BASIC) && (primitiveType == JVM_TYPE_BOOLEAN));
}


bool JCReferencedType::isChar(void)
{
    return ((kind == TYPE_BASIC) && (primitiveType == JVM_TYPE_CHAR));
}


bool JCReferencedType::isString(void)
{
	// ATTN: Is this correct ?
    if (resolver != NULL) {
	JCType *realType= (JCType *)resolver->getDefinition();
	if (realType->getRefEquivalent() == populars[popString]) {
	    return true;
	}
    }
    return (this == populars[popString]);
}


void JCReferencedType::addUser(JCNamedExpr *anExpression)
{
    // TODO: links an expression we know is going into that type name space.

    if (resolver != NULL) {
	((JCType *)resolver->getDefinition())->addUser(anExpression);
    }
    else {
	if (tmpNameSpace == NULL) {
	    tmpNameSpace= new JCNameSpace();
	}
	if (!tmpNameSpace->relateNamedExpr(anExpression)) {
	    // ERRMSG: Couldn't link the name in temporary type name space.
	}
    }
}


JCReferencedType *JCReferencedType::getArrayBaseType(void)
{
    if (kind == TYPE_ARRAY) {
	return subType;
    }
    else return NULL;
}


void JCReferencedType::importUnknown(JCUnresolved *unresList)
{
    if (resolver != NULL) {
	((JCType *)resolver->getDefinition())->importUnknown(unresList);
    }
    else {
	if (tmpNameSpace == NULL) {
	    tmpNameSpace= new JCNameSpace();
	}
	tmpNameSpace->importUnresolved(unresList);
    }
}


bool JCReferencedType::isParameterCompatible(JCReferencedType *aRefType)
{
    if (kind == TYPE_BASIC) {
	if (aRefType->kind != TYPE_BASIC) return false;
	else {
	    if (primitiveType == JVM_TYPE_BOOLEAN) {
		return (aRefType->primitiveType == JVM_TYPE_BOOLEAN);
	    }
	    else {
		return true;		// ATTN-971120 [HD]: Is this good ??
	    }
	}
    }
    else if (kind == TYPE_CLASS) {
	return true;	// ATTN: TODO.
    }
    else if (kind == TYPE_INTERFACE) {
	return true;	// ATTN: TODO.
    }
    else if (kind == TYPE_ARRAY) {
	if ((aRefType->primitiveType == TYPE_BASIC) || (aRefType->primitiveType == TYPE_BASIC)) {
	    return false;
	}
	else if (aRefType->primitiveType == TYPE_CLASS) {
	    // Must check that it is java.lang.Object.
	    return true;	// ATTN: TODO.
	}
	else {
	    // Must deal with the internal type.
	    return true;	// ATTN: TODO.
	}
    }

    return false;		// Warning: should never come to that point.
}


bool JCReferencedType::isInterfaceImplemented(JCReferencedType *aRefType)
{
    return false;
}


bool JCReferencedType::isGE(JCReferencedType *aType)
{
    return true;
}

