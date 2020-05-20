/**************************************************
* File: importClass.cc.
* Desc: Implementation of classes dealing with imported Java classes.
* Module: JavaKit : Compiler.
* Rev: 23 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include <string.h>
#include <akra/convertMacro.h>
#include "constants.h"
#include "inConstant.h"
#include "inAttributes.h"
#include "importedObjects.h"
#include "typing.h"
#include "inConstant.h"
#include "classFile.h"
#include "identifiers.h"
#include "compiler.h"
#include "importClass.h"


/**************************************************
* Implementation: JCImportClassFile.
**************************************************/

bool JCImportClassFile::readFromStream(istream *aStream)
{
    unsigned int i, tmpCteType;
    char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU4));
    magic= MakeUInteger(tmpBuffer);
    if (magic != 0x0cafebabe) return false;		// Not a class !
    aStream->read(tmpBuffer, sizeof(javaU2));
    version_minor= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));
    version_major= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));
    ctePoolSize= MakeUShort(tmpBuffer);

    if (ctePoolSize > 0) {		/* Read constant if there are some. */
	JCCFConstant *tmpPoolCte, *realCte;
	constantPool= new JCCFConstant*[ctePoolSize +1];
	tmpPoolCte= new JCCFConstant;
	for (i= 1; i < ctePoolSize; i++) {	// CtePool 0 is not provided by class stream.
	    tmpPoolCte->read(aStream, realCte);
	    constantPool[i]= realCte;
	    tmpCteType= constantPool[i]->type();
	    if ((tmpCteType == JCCFConstant::ctLong) ||
		    (tmpCteType == JCCFConstant::ctDouble)) {
		i++;		// 8-bytes constant count for two pool slots.
		constantPool[i]= realCte;
	    }
	}
    }

    aStream->read(tmpBuffer, sizeof(javaU2));		// Access Flags.
    accessFlags= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));		// This Class index.
    thisClass= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));		// Super Class index.
    superClass= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));		// Num. of interfaces.
    interfaceCount= MakeUShort(tmpBuffer);

    if (interfaceCount > 0) {
	    /* Read the interface indexes. */		
	interfaces= new unsigned int[interfaceCount];
	for (i= 0; i < interfaceCount; i++) {
	    aStream->read(tmpBuffer, sizeof(javaU2));
	    interfaces[i]= MakeUShort(tmpBuffer);
	}
    }

    aStream->read(tmpBuffer, sizeof(javaU2));		// Num of fields.
    fieldCount= MakeUShort(tmpBuffer);
    if (fieldCount > 0) {
	fields= new JCFieldInfo[fieldCount];
	for (i= 0; i < fieldCount; i++) {
	    fields[i].read(aStream, (JACFConstant **)constantPool);
	    fields[i].setOwner(this);
	}
    }

    aStream->read(tmpBuffer, sizeof(javaU2));		// Num of methods.
    methodCount= MakeUShort(tmpBuffer);
    if (methodCount > 0) {
	methods= new JCMethodInfo[methodCount];
	for (i= 0; i < methodCount; i++) {
	    methods[i].read(aStream, (JACFConstant **)constantPool);
	    methods[i].setOwner(this);
	}
    }

    aStream->read(tmpBuffer, sizeof(javaU2));		// Num of attributes.
    attributeCount= MakeUShort(tmpBuffer);
    if (attributeCount > 0) {
	JCAttributeInfo *tmpAttrInfo, *realAttribute;
	attributes= new JCAttributeInfo*[attributeCount];
	for (i= 0; i < attributeCount; i++) {
	    tmpAttrInfo= new JCAttributeInfo;
	    tmpAttrInfo->read(aStream, constantPool, realAttribute);
	    attributes[i]= realAttribute;
	    if (tmpAttrInfo != realAttribute) delete tmpAttrInfo;
	}
    }

    return true;
}


char *JCImportClassFile::getAsciiName(void)
{
    unsigned int nameIndex;

    nameIndex= ((JCCFClass *)constantPool[thisClass])->getNameIndex();
    return (char *)((JCCFUtf8 *)constantPool[nameIndex])->getAsciiValue();
}


JCCFUtf8 *JCImportClassFile::getSuper(void)
{
    if ((superClass > 0) && (superClass < ctePoolSize)) {
	unsigned int superIndex= ((JCCFClass *)constantPool[superClass])->getNameIndex();
	return (JCCFUtf8 *)constantPool[superIndex];
    }
    return NULL;
}


JCFieldInfo *JCImportClassFile::getField(JCIdentifier *aName)
{
    JCFieldInfo *result= NULL;
    unsigned int i;

    for (i= 0; i < fieldCount; i++) {
	if (fields[i].isNamed(aName, constantPool)) {
	    result= &fields[i];
	    break;
	 }
     }

    return result;
}


JCMethodInfo *JCImportClassFile::getBaseMethod(JCIdentifier *aName)
{
    JCMethodInfo *result= NULL;
    unsigned int i;

    for (i= 0; i < methodCount; i++) {
	if (methods[i].isNamed(aName, constantPool)) {
	    result= &methods[i];
	    break;
	 }
     }

    return result;
}


void JCImportClassFile::setDual(JCImportedClass *aClass)
{
    dual= aClass;
}


JCImportedClass *JCImportClassFile::getDual(void)
{
    return dual;
}


JCMethodInfo *JCImportClassFile::getNextMethod(JCMethodInfo *aMethod)
{
    JCMethodInfo *result= NULL;
    unsigned int i;

    for (i= 0; i < methodCount; i++) {
	if (&methods[i] == aMethod) {
	    i++;
	    break;
	 }
     }
    for (; i < methodCount; i++) {
	if (methods[i].isSynonym(aMethod, constantPool)) {
	    result= &methods[i];
	    break;
	}
     }

    return result;
}


/**************************************************
* Implementation: JCComponentInfo.
**************************************************/

#if defined(TO_FIX)
bool JCComponentInfo::readAttributes(istream *aStream, JACFConstant **ctePool)
{
    char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU2));
    attributeCount= MakeUShort(tmpBuffer);
    if (attributeCount > 0) {
	JCAttributeInfo *tmpAttrInfo, *realAttribute;
	attributes= new JCAttributeInfo*[attributeCount];
	for (unsigned int i= 0; i < attributeCount; i++) {
	    tmpAttrInfo= new JCAttributeInfo;
	    tmpAttrInfo->read(aStream, ctePool, realAttribute);
	    attributes[i]= realAttribute;
	    if (tmpAttrInfo != realAttribute) delete tmpAttrInfo;
	 }
     }
    return true;
}
#endif


/**************************************************
* Implementation: JCFieldInfo.
**************************************************/

int JCFieldInfo::parseSignature(char *aSignature, JCReferencedType **type)
{
    JCReferencedType *lastArrayDef;
    JCReferencedType *tmpTypeDef, *theType= NULL;
    int result= 0;
    unsigned int nbrArgs= 0, optionalSize= 0, parentLevel;
    char *tmpPtr, *currentClassName;
    bool inClassName= false, inArraySpec= false;

    tmpPtr= &aSignature[0];
    if (*tmpPtr != '\0') {
	while (*tmpPtr != '\0') {	// Scan the args.
	    switch (*tmpPtr) {
		case 'C':		// Basic type, or char of class name.
		case 'D':
		case 'F':
		case 'I':
		case 'J':
		case 'S':
		case 'Z':
		case 'B':
		case 'V':		// Should only occur when parentLevel == 0.
		    if (inClassName) {
			// Do nothing, part of class name.
		     }
		    else {
			if (*tmpPtr == 'V') {
			    if (parentLevel != 0) {	// Weird situation, not looking at the return type.
			     }
			 }
			tmpTypeDef= JCReferencedType::getPopularType(JCReferencedType::letterToPopType(*tmpPtr));
			if (inArraySpec) {
			    // End of array spec.
			    lastArrayDef->setOfReferencedType(tmpTypeDef);
			    inArraySpec= false;
			 }
			else {
			    if (theType != NULL) delete theType;    // Erase previous definition.
			    theType= tmpTypeDef;
			    nbrArgs++;
			 }
		     }
		    break;
		case 'L':		// Beginning of class name.
		    if (!inClassName) {
			inClassName= true;
			currentClassName= tmpPtr + 1;
		     }
		    else {
			// Part of class name, do nothing.
		     }
		    break;
		case ';':		// End of object name.
		    if (inClassName) {
			if (tmpPtr > currentClassName) {
			    tmpTypeDef= new JCReferencedType(currentClassName, (tmpPtr - currentClassName));
			    tmpTypeDef->setKind(TYPE_CLASS);
			    if (inArraySpec) {
				lastArrayDef->setOfReferencedType(tmpTypeDef);
				inArraySpec= false;
			     }
			    else {	// Individual argument definition.
				theType= tmpTypeDef;
				nbrArgs++;
			     }
			 }
			else {		// Weird situation, name length is 0.
			 }
			inClassName= false;
		     }
		    else {		// Weird situation, unknown type ';'.
		     }
		    break;
		case '[':		// Array type.
		    if (inClassName) {
			// Part of class name (!!), do nothing.
		     }
		    else {
			if (inArraySpec) {
			    lastArrayDef->incrementNbrDimensions();
			 }
			else {
			    lastArrayDef= new JCReferencedType();
			    lastArrayDef->setKind(TYPE_ARRAY);
			    lastArrayDef->incrementNbrDimensions();    // Set dim to 1.
			    if (theType != NULL) delete theType;    // Erase previous definition.
			    theType= lastArrayDef;
			    nbrArgs++;
			 }

			inArraySpec= true;
			optionalSize= 0;
		     }
		    break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		    if (inArraySpec) {
			optionalSize= optionalSize * 10 + (unsigned int)(*tmpPtr - '0');
		     }
		    else if (inClassName) {
			// Ok, do nothing, part of class name.
		     }
		    else {		// Weird situation.
		     }
		    break;
		case '(':
		    // Should it ever occur ??.
		    parentLevel++;
		    break;
		case ')':
		    // Should denote end of arguments.
		    parentLevel--;
		    break;
		default:		// Unknown type.
		    if (inClassName) {
			// Ok, do nothing part of class name.
		     }
		    else {		// Weird situation, unknown type.
			optionalSize= 0;
		     }
		    break;
	     }
	    tmpPtr++;
	 }

     }

    if (nbrArgs != 1) result= -1;
    *type= theType;

    return result;
}


JCFieldInfo::JCFieldInfo(void)
{
    dereference= NULL;
}


bool JCFieldInfo::readAttributes(istream *aStream, JACFConstant **ctePool)
{
    char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU2));
    attributeCount= MakeUShort(tmpBuffer);
    if (attributeCount > 0) {
	JCAttributeInfo *tmpAttrInfo, *realAttribute;
	attributes= new JCAttributeInfo*[attributeCount];
	for (unsigned int i= 0; i < attributeCount; i++) {
	    tmpAttrInfo= new JCAttributeInfo;
	    tmpAttrInfo->read(aStream, (JCCFConstant **)ctePool, realAttribute);
	    attributes[i]= realAttribute;
	    if (tmpAttrInfo != realAttribute) delete tmpAttrInfo;
	 }
     }
    return true;
}


JCField *JCFieldInfo::resolve(JCCompiler *compiler)
{
    if (!isResolved) {
	JCReferencedType *fieldType;
	char className[512];
	char fieldName[256];
	bool knownType= true;

	((JCCFUtf8 *)((JCImportClassFile *)owner)->constantPool[signatureIndex])->writeAsciiValue((unsigned char *)className);
		// ATTN: Should make sure that parseSignature returns 0.
	parseSignature(className, &fieldType);
	((JCCFUtf8 *)((JCImportClassFile *)owner)->constantPool[nameIndex])->writeAsciiValue((unsigned char *)fieldName);
	if (!fieldType->isPrimitive()) {
	    if (!compiler->findRealType(fieldType)) knownType= false;
	}
	if (knownType) {
	    dereference= new JCImportedField(((JCImportClassFile *)owner)->getDual(), fieldName, fieldType);
	    ((JCImportedField *)dereference)->setModifiers(accessFlags);
	    ((JCImportedField *)dereference)->buildShadow(className);
	    isResolved= true;
	}
	else {
	    if (!fieldType->isPrimitive()) delete fieldType;
	}
    }
    return dereference;
}


bool JCFieldInfo::isNamed(JCIdentifier *aName, JCCFConstant **ctePool)
{
    return (strcmp((const char *)((JCCFUtf8 *)ctePool[nameIndex])->getAsciiValue(), aName->getAsciiValue()) == 0);
}


/**************************************************
* Implementation: JCMethodInfo.
**************************************************/


/**************************************************
* Method: parseArguments.
* Desc: Parse a method's signature and decompose it in a list of
*	JCReferencedType.
* Para: 1- aSignature => [char *] the signature as an ascii string.
*	2- types => [JCReferencedType ***] the receiver of the array of types created by the
*				parsing.
* Return: [int] the number of arguments found, plus one for the return type.
**************************************************/

int JCMethodInfo::parseArguments(char *aSignature, JCReferencedType ***types)
{
    JCReferencedType *lastArrayDef;
    JCReferencedType *tmpTypingArray[257], *tmpTypeDef;    // Can scan up to 256 arguments.
    unsigned int nbrArgs= 0, optionalSize= 0, parentLevel;
    char *tmpPtr, *currentClassName;
    bool inClassName= false, inArraySpec= false;

    if (aSignature[0] == '(') {		// Well started signature.
	tmpPtr= &aSignature[1];
	parentLevel= 1;
	while (*tmpPtr != '\0') {	// Scan the args.

	    switch (*tmpPtr) {
		case 'C':		// Basic type, or char of class name.
		case 'D':
		case 'F':
		case 'I':
		case 'J':
		case 'S':
		case 'Z':
		case 'B':
		case 'V':		// Should only occur when parentLevel == 0.
		    if (inClassName) {
			// Do nothing, part of class name.
		     }
		    else {
			if (*tmpPtr == 'V') {
			    if (parentLevel != 0) {	// Weird situation, not looking at the return type.
			     }
			 }
			tmpTypeDef= JCReferencedType::getPopularType(JCReferencedType::letterToPopType(*tmpPtr));
			if (inArraySpec) {
			    // End of array spec.
			    lastArrayDef->setOfReferencedType(tmpTypeDef);
			    inArraySpec= false;
			 }
			else {
			    tmpTypingArray[nbrArgs++]= tmpTypeDef;
			 }
		     }
		    break;
		case 'L':		// Beginning of class name.
		    if (!inClassName) {
			inClassName= true;
			currentClassName= tmpPtr + 1;
		     }
		    else {
			// Part of class name, do nothing.
		     }
		    break;
		case ';':		// End of object name.
		    if (inClassName) {
			if (tmpPtr > currentClassName) {
			    tmpTypeDef= new JCReferencedType(currentClassName, (tmpPtr - currentClassName));
			    if (inArraySpec) {
				lastArrayDef->setOfReferencedType(tmpTypeDef);
				inArraySpec= false;
			     }
			    else {	// Individual argument definition.
				tmpTypingArray[nbrArgs++]= tmpTypeDef;
			     }
			 }
			else {		// Weird situation, name length is 0.
			 }
			inClassName= false;
		     }
		    else {		// Weird situation, unknown type ';'.
		     }
		    break;
		case '[':		// Array type.
		    if (inClassName) {
			// Part of class name (!!), do nothing.
		     }
		    else {
			if (inArraySpec) {
			    lastArrayDef->incrementNbrDimensions();
			 }
			else {
			    tmpTypingArray[nbrArgs++]= tmpTypeDef;
			 }
			lastArrayDef= tmpTypeDef= new JCReferencedType();
			lastArrayDef->setKind(TYPE_ARRAY);
			inArraySpec= true;
			optionalSize= 0;
		     }
		    break;
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		    if (inArraySpec) {
			optionalSize= optionalSize * 10 + (unsigned int)(*tmpPtr - '0');
		     }
		    else if (inClassName) {
			// Ok, do nothing, part of class name.
		     }
		    else {		// Weird situation.
		     }
		    break;
		case '(':
		    // Should it ever occur ??.
		    parentLevel++;
		    break;
		case ')':
		    // Should denote end of arguments.
		    parentLevel--;
		    break;
		default:		// Unknown type.
		    if (inClassName) {
			// Ok, do nothing part of class name.
		     }
		    else {		// Weird situation, unknown type.
			optionalSize= 0;
		     }
		    break;
	     }
	    tmpPtr++;
	 }
	// Normally, read all arguments and return type.
	if (nbrArgs > 0) {
	    *types= new JCReferencedType*[nbrArgs];
	    for (unsigned int i= 1; i < nbrArgs; i++) {
		(*types)[i]= tmpTypingArray[i-1];
	     }
		(*types)[0]= tmpTypingArray[nbrArgs-1];
	 }
     }
    else {
	// Maybe the '('')' pair was not there.  Verify if there is a valid description.
     }
    return nbrArgs;
}


JCMethodInfo::JCMethodInfo(void)
{
    dereference= NULL;
    isStateInfo= false;
}


bool JCMethodInfo::read(istream *aStream, JACFConstant **ctePool)
{
    if (JAMemberInfo::read(aStream, ctePool)) {
	char methodName[80];

	((JCCFUtf8 *)ctePool[nameIndex])->writeAsciiValue((unsigned char *)methodName);
	if (methodName[((JCCFUtf8 *)ctePool[nameIndex])->getLength()-1] == '+') {
	    isStateInfo= true;
	}
	return true;
    }
    return false;
}


bool JCMethodInfo::readAttributes(istream *aStream, JACFConstant **ctePool)
{
    char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU2));
    attributeCount= MakeUShort(tmpBuffer);
    if (attributeCount > 0) {
	JCAttributeInfo *tmpAttrInfo, *realAttribute;
	attributes= new JCAttributeInfo*[attributeCount];
	for (unsigned int i= 0; i < attributeCount; i++) {
	    tmpAttrInfo= new JCAttributeInfo;
	    tmpAttrInfo->read(aStream, (JCCFConstant **)ctePool, realAttribute);
	    attributes[i]= realAttribute;
	    if (tmpAttrInfo != realAttribute) delete tmpAttrInfo;
	 }
     }
    return true;
}


bool JCMethodInfo::isState(void)
{
    return isStateInfo;
}


JCMethod *JCMethodInfo::resolve(JCCompiler *compiler)
{
    if (!isResolved) {
	JCReferencedType **memberTypes;
	unsigned int nbrArgs;
	char className[512];
	char memberName[256];
	bool hasAllTypes= true;

	((JCCFUtf8 *)((JCImportClassFile *)owner)->constantPool[signatureIndex])->writeAsciiValue((unsigned char *)className);
	nbrArgs= parseArguments(className, &memberTypes);  // nbrArgs counts returned type.
	((JCCFUtf8 *)((JCImportClassFile *)owner)->constantPool[nameIndex])->writeAsciiValue((unsigned char *)memberName);

	for (unsigned int i= 0; i < nbrArgs; i++) {
	    if (!memberTypes[i]->isPrimitive()) {
		if (!compiler->findRealType(memberTypes[i])) hasAllTypes= false;
	    }
	}
	if (hasAllTypes) {
	    if (isStateInfo) {
		dereference= new JCImportedState(((JCImportClassFile *)owner)->getDual(), memberName, nbrArgs, memberTypes);
	    }
	    else {
		dereference= new JCImportedMethod(((JCImportClassFile *)owner)->getDual(), memberName, nbrArgs, memberTypes);
	    }
/* MOD-970822 [HD]:  Using a more appropriate way of construction the typing info.
	    dereference->JCMember::resolveTyping();
*/
	    ((JCImportedMethod *)dereference)->setModifiers(accessFlags);
	    ((JCImportedMethod *)dereference)->buildShadow(className);
	    isResolved= true;
	}
    }
    return dereference;
}


bool JCMethodInfo::isNamed(JCIdentifier *aName, JCCFConstant **ctePool)
{
    return (strcmp((const char *)((JCCFUtf8 *)ctePool[nameIndex])->getAsciiValue(), aName->getAsciiValue()) == 0);
}


bool JCMethodInfo::isSynonym(JCMethodInfo *aMethod, JCCFConstant **ctePool)
{
    if (nameIndex == aMethod->nameIndex) {
	return true;	// Warning: quick exit.
    }
    else if (((JCCFUtf8 *)ctePool[nameIndex])->isEqual((JCCFUtf8 *)ctePool[aMethod->nameIndex])) {
	return true;	// Warning: quick exit.
    }
    return false;
}
