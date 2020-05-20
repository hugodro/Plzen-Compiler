/**************************************************
* File: outConstant.cc.
* Desc: Implementation of the JCOutCFConstant class.
* Module: AkraLog : JavaKit.
* Rev: 25 novembre 1995 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <stdio.h>
#include <fstream.h>
#include <string.h>
#include "constants.h"
#include "lists.h"
#include "outClassFile.h"
#include "hashManager.h"
#include "hashElement.h"
#include "outConstant.h"


/**************************************************
* Implementation: JCOutCFConstant.
**************************************************/

ConstantsList *JCOutCFConstant::allInstances= new ConstantsList(512);


 void JCOutCFConstant::resetIndexes(void)
 {
    allInstances->resetInstances();
 }


JCOutCFConstant::JCOutCFConstant(void)
{
    allInstances->addObject(this);
    myPoolIndex= 0;
}


JCOutCFConstant::~JCOutCFConstant(void)
{
    allInstances->removeObject(this);
}


void JCOutCFConstant::write(JCOutClassFile *aClassFile)
{
/* MOD-971111 [HD]: Took this out, and use now JCOutCFConstant as fillers for
*	fake second constant pool member of double words.
    // Should never be called.
    cout << "Error: JCOutCFConstant::write is called.\n";
*/
}


JCOutCFConstant::Kind JCOutCFConstant::getType(void)
{
    return general;
}


void JCOutCFConstant::resetIndex(void)
{
    myPoolIndex= 0;
}


void JCOutCFConstant::setIndex(unsigned int aPos)
{
    myPoolIndex= aPos;
}


unsigned int JCOutCFConstant::getIndex(void)
{
    return myPoolIndex;
}


bool JCOutCFConstant::hasNullIndex(void)
{
    return (myPoolIndex == 0);
}



void JCOutCFConstant::addToPool(ConstantsList *aPool)
{
    aPool->addIndexedObject(this);
}


/**************************************************
* Implementation: JCDoubleFiller.
**************************************************/

void JCDoubleFiller::unassemble(char *outBuffer)
{
    strcat(outBuffer, ".filler");
}


/**************************************************
* Implementation: JCCteClass.
**************************************************/

JCCteClass::JCCteClass(JCCteUtf8 *aCteName) : JCOutCFConstant()
{
    refName= aCteName;
}


JCOutCFConstant::Kind JCCteClass::getType(void)
{
    return kClass;
}


void JCCteClass::addToPool(ConstantsList *aPool)
{
    aPool->addIndexedObject(this);
    refName->addToPool(aPool);
}


void JCCteClass::write(JCOutClassFile *aClassFile)
{
    aClassFile->writeUByte(kClass);
    aClassFile->writeUShort(refName->getIndex());
}


void JCCteClass::unassemble(char *outBuffer)
{
    strcat(outBuffer, ".class: ");
    strcat(outBuffer + 8, refName->asciiString());
}


/**************************************************
* Implementation: JCReference.
**************************************************/

JCReference::JCReference(JCCteClass *aClass, JCCteNameAndType *aNameType) : JCOutCFConstant()
{
    typeIndex= aClass;
    nameType= aNameType;
}


void JCReference::addToPool(ConstantsList *aPool)
{
    aPool->addIndexedObject(this);
    typeIndex->addToPool(aPool);
    nameType->addToPool(aPool);
}


void JCReference::writeNameType(JCOutClassFile *aClassFile)
{
    nameType->writeIndexes(aClassFile);
}


void JCReference::write(JCOutClassFile *aClassFile)
{
    aClassFile->writeUByte(getType());
    aClassFile->writeUShort(typeIndex->getIndex());
    aClassFile->writeUShort(nameType->getIndex());
}


JCCteNameAndType *JCReference::getNameType(void)
{
    return nameType;
}


void JCReference::unassemble(char *outBuffer)
{
    sprintf(outBuffer, "class: %d, signature: %d", typeIndex->getIndex(), nameType->getIndex());
}


/**************************************************
* Implementation: JCCteFieldRef.
**************************************************/

JCOutCFConstant::Kind JCCteFieldRef::getType(void)
{
    return fieldRef;
}


void JCCteFieldRef::unassemble(char *outBuffer)
{
    strcat(outBuffer, ".fieldRef: ");
    JCReference::unassemble(outBuffer+11);
}


/**************************************************
* Implementation: JCCteMethodRef.
**************************************************/

JCOutCFConstant::Kind JCCteMethodRef::getType(void)
{
    return methodRef;
}


void JCCteMethodRef::unassemble(char *outBuffer)
{
    strcat(outBuffer, ".methodRef: ");
    JCReference::unassemble(outBuffer+12);
}


/**************************************************
* Implementation: JCCteNameAndType.
**************************************************/

JCCteNameAndType::JCCteNameAndType(JCCteUtf8 *aName, JCCteUtf8 *aType) : JCOutCFConstant()
{
    name= aName;
    signature= aType;
}


JCOutCFConstant::Kind JCCteNameAndType::getType(void)
{
    return nameAndType;
}


void JCCteNameAndType::addToPool(ConstantsList *aPool)
{
    aPool->addIndexedObject(this);
    name->addToPool(aPool);
    signature->addToPool(aPool);
}


void JCCteNameAndType::write(JCOutClassFile *aClassFile)
{
    aClassFile->writeUByte(nameAndType);
    aClassFile->writeUShort(name->getIndex());
    aClassFile->writeUShort(signature->getIndex());
}


void JCCteNameAndType::writeIndexes(JCOutClassFile *aClassFile)
{
    aClassFile->writeUShort(name->getIndex());
    aClassFile->writeUShort(signature->getIndex());
}


void JCCteNameAndType::unassemble(char *outBuffer)
{
    strcat(outBuffer, ".declare: ");
    outBuffer+= 10;
    strcat(outBuffer, name->asciiString());
    strcat(outBuffer, " as ");
    strcat(outBuffer, signature->asciiString());
}


/**************************************************
* Implementation: JCCteString.
**************************************************/

ConstantsList *JCCteString::uniqueStringValues= new ConstantsList(256);


JCCteString::JCCteString(JCCteUtf8 *aUtf8)
{
    valueIndex= aUtf8;
}


JCCteString *JCCteString::addUnique(JCCteUtf8 *aValue)
{
    JCCteString *result;

    if ((result= (JCCteString *)uniqueStringValues->findStringValue(aValue)) == NULL) {
	result= new JCCteString(aValue);
	uniqueStringValues->addObject(result);
    }
    return result;
}


JCOutCFConstant::Kind JCCteString::getType(void)
{
    return string;
}



void JCCteString::addToPool(ConstantsList *aPool)
{
    aPool->addIndexedObject(this);
    valueIndex->addToPool(aPool);
}


void JCCteString::write(JCOutClassFile *aClassFile)
{
    aClassFile->writeUByte(string);
    aClassFile->writeUShort(valueIndex->getIndex());
}


void JCCteString::unassemble(char *outBuffer)
{
    strcat(outBuffer, ".string: ");
    strcat(outBuffer+9, valueIndex->asciiString());
}


bool JCCteString::isEqual(JCCteUtf8 *aUtfCte)
{
    return (aUtfCte == valueIndex);
}


/**************************************************
* Implementation: JCWord.
**************************************************/

ConstantsList *JCWord::uniqueIntValues= new ConstantsList(256);
ConstantsList *JCWord::uniqueFloatValues= new ConstantsList(256);
JCWord *JCWord::specialWordCte[nbrSpecialWordCtes]= { NULL };


void JCWord::initSpecialCte(void)
{
    specialWordCte[scIntZero]= new JCCteInteger(0);
    specialWordCte[scIntOne]= new JCCteInteger(1);
    specialWordCte[scIntMinusOne]= new JCCteInteger(-1);

    specialWordCte[scFloatZero]= new JCCteFloat(0.0);
    specialWordCte[scFloatOne]= new JCCteFloat(1.0);
    specialWordCte[scFloatMinusOne]= new JCCteFloat(-1.0);

    uniqueIntValues->addObject(specialWordCte[scIntZero]);
    uniqueIntValues->addObject(specialWordCte[scIntOne]);
    uniqueIntValues->addObject(specialWordCte[scIntMinusOne]);
    uniqueFloatValues->addObject(specialWordCte[scFloatZero]);
    uniqueFloatValues->addObject(specialWordCte[scFloatOne]);
    uniqueFloatValues->addObject(specialWordCte[scFloatMinusOne]);
}


JCWord *JCWord::getSpecialCte(SpecialWordCte anCte)
{
    if (specialWordCte[0] == NULL) {
	initSpecialCte();
    }
    return specialWordCte[anCte];
}


bool JCWord::isSpecialCte(JCWord *aCte)
{
    if ((aCte == specialWordCte[scIntZero])
	    || (aCte == specialWordCte[scIntOne])
	    || (aCte == specialWordCte[scIntMinusOne])
	    || (aCte == specialWordCte[scFloatZero])
	    || (aCte == specialWordCte[scFloatOne])
	    || (aCte == specialWordCte[scFloatMinusOne])) {
	return true;
    }
    return false;
}


JCWord::JCWord() : JCOutCFConstant()
{

}


JCWord *JCWord::addUnique(int aValue)
{
    JCWord *result;

    if ((result= (JCWord *)uniqueIntValues->findIntValue(aValue)) == NULL) {
	result= new JCCteInteger(aValue);
	uniqueIntValues->addObject(result);
    }
    return result;
}


JCWord *JCWord::addUnique(float aValue)
{
    JCWord *result;

    if ((result= (JCWord *)uniqueFloatValues->findFloatValue(aValue)) == NULL) {
	result= new JCCteFloat(aValue);
	uniqueFloatValues->addObject(result);
    }
    return result;
}


void JCWord::write(JCOutClassFile *aClassFile)
{
    aClassFile->writeUByte(getType());
    aClassFile->writeUInteger(bytes);
}


JCWord *JCWord::arithmeticNegation(void)
{
    if (this == specialWordCte[scIntZero])
	return this;
    else if (this == specialWordCte[scIntOne])
	return specialWordCte[scIntMinusOne];
    else if (this == specialWordCte[scIntMinusOne])
	return specialWordCte[scIntOne];
    else if (this == specialWordCte[scFloatZero])
	return this;
    else if (this == specialWordCte[scFloatOne])
	return specialWordCte[scFloatMinusOne];
    else if (this == specialWordCte[scFloatMinusOne])
	return specialWordCte[scFloatOne];
    return specialWordCte[scIntZero];	/* MOD-MSC: Ajoute ce return pour VC++. */
}


/**************************************************
* Implementation: JCCteInteger.
**************************************************/

JCCteInteger::JCCteInteger(int aValue) : JCWord()
{
    bytes= (unsigned int)aValue;
}


JCOutCFConstant::Kind JCCteInteger::getType(void)
{
    return integer;
}


bool JCCteInteger::isEqual(int aValue)
{
    return (bytes == aValue);
}


int JCCteInteger::intValue(void)
{
    return (int)bytes;
}


void JCCteInteger::unassemble(char *outBuffer)
{
    sprintf(outBuffer, ".int: %d", bytes);
}


/**************************************************
* Implementation: JCCteFloat.
**************************************************/

JCCteFloat::JCCteFloat(float aValue) : JCWord()
{
    *((float *)&bytes)= aValue;
}


JCOutCFConstant::Kind JCCteFloat::getType(void)
{
    return kFloat;
}


bool JCCteFloat::isEqual(float aValue)
{
    return (*((float *)&bytes) == aValue);
}


float JCCteFloat::floatValue(void)
{
    return *((float *)&bytes);
}


void JCCteFloat::unassemble(char *outBuffer)
{
    sprintf(outBuffer, ".float: %f", *(float *)&bytes);
}


/**************************************************
* Implementation: JCDoubleWord.
**************************************************/

ConstantsList *JCDoubleWord::uniqueLongValues= new ConstantsList(256);
ConstantsList *JCDoubleWord::uniqueDoubleValues= new ConstantsList(256);
JCDoubleWord *JCDoubleWord::specialDblWordCte[nbrSpecialDblWordCtes]= { NULL };


void JCDoubleWord::initSpecialCte(void)
{
    unsigned int tmpLong[2];

    tmpLong[0]= 0; tmpLong[1]= 0;
    specialDblWordCte[scLongZero]= new JCCteLong(tmpLong);
    tmpLong[0]= 1;
    specialDblWordCte[scLongOne]= new JCCteLong(tmpLong);
    tmpLong[0]= 0x0FFFFFFFF; tmpLong[1]= 0x0FFFFFFFF;
    specialDblWordCte[scLongMinusOne]= new JCCteLong(tmpLong);

    specialDblWordCte[scDoubleZero]= new JCCteDouble(0.0);
    specialDblWordCte[scDoubleOne]= new JCCteDouble(1.0);
    specialDblWordCte[scDoubleMinusOne]= new JCCteDouble(-1.0);

    uniqueLongValues->addObject(specialDblWordCte[scLongZero]);
    uniqueLongValues->addObject(specialDblWordCte[scLongOne]);
    uniqueLongValues->addObject(specialDblWordCte[scLongMinusOne]);
    uniqueDoubleValues->addObject(specialDblWordCte[scDoubleZero]);
    uniqueDoubleValues->addObject(specialDblWordCte[scDoubleOne]);
    uniqueDoubleValues->addObject(specialDblWordCte[scDoubleMinusOne]);
}


JCDoubleWord *JCDoubleWord::getSpecialCte(SpecialDblWordCte anCte)
{
    if (specialDblWordCte[0] == NULL) {
	initSpecialCte();
    }
    return specialDblWordCte[anCte];
}


bool JCDoubleWord::isSpecialCte(JCDoubleWord *aCte)
{
    if ((aCte == specialDblWordCte[scLongZero])
	    || (aCte == specialDblWordCte[scLongOne])
	    || (aCte == specialDblWordCte[scLongMinusOne])
	    || (aCte == specialDblWordCte[scDoubleZero])
	    || (aCte == specialDblWordCte[scDoubleOne])
	    || (aCte == specialDblWordCte[scDoubleMinusOne])) {
	return true;
    }
    return false;
}


JCDoubleWord::JCDoubleWord() : JCOutCFConstant()
{
}


JCDoubleWord *JCDoubleWord::addUnique(unsigned int *aValue)
{
    JCDoubleWord *result;

    if ((result= (JCDoubleWord *)uniqueLongValues->findLongValue(aValue)) == NULL) {
	result= new JCCteLong(aValue);
	uniqueLongValues->addObject(result);
    }
    return result;
}


JCDoubleWord *JCDoubleWord::addUnique(double aValue)
{
    JCDoubleWord *result;

    if ((result= (JCDoubleWord *)uniqueDoubleValues->findDoubleValue(aValue)) == NULL) {
	result= new JCCteDouble(aValue);
	uniqueDoubleValues->addObject(result);
    }
    return result;
}


void JCDoubleWord::addToPool(ConstantsList *aPool)
{
    aPool->addIndexedObject(this);
    aPool->addIndexedObject(new JCDoubleFiller());
}


void JCDoubleWord::write(JCOutClassFile *aClassFile)
{
    aClassFile->writeUByte(getType());
    aClassFile->writeUInteger(highBytes);
    aClassFile->writeUInteger(lowBytes);
}


JCDoubleWord *JCDoubleWord::arithmeticNegation(void)
{
    if (this == specialDblWordCte[scLongZero])
	return this;
    else if (this == specialDblWordCte[scLongOne])
	return specialDblWordCte[scLongMinusOne];
    else if (this == specialDblWordCte[scLongMinusOne])
	return specialDblWordCte[scLongOne];
    else if (this == specialDblWordCte[scDoubleZero])
	return this;
    else if (this == specialDblWordCte[scDoubleOne])
	return specialDblWordCte[scDoubleMinusOne];
    else if (this == specialDblWordCte[scDoubleMinusOne])
	return specialDblWordCte[scDoubleOne];
    return specialDblWordCte[scLongZero];	/* MOD-MSC: Ajoute ce return pour VC++. */
}


/**************************************************
* Implementation: JCCteLong.
**************************************************/

JCCteLong::JCCteLong(unsigned int *aValue) : JCDoubleWord()
{
    lowBytes= aValue[0];
    highBytes= aValue[1];
}


JCOutCFConstant::Kind JCCteLong::getType(void)
{
    return kLong;
}


bool JCCteLong::isEqual(unsigned int *aValue)
{
    return ((lowBytes == aValue[0]) && (highBytes == aValue[1]));
}


bool JCCteLong::isEqual(unsigned int high, unsigned int low)
{
    return ((lowBytes == low) && (highBytes == high));
}


void JCCteLong::longValue(unsigned int *aValue)
{
    aValue[0]= lowBytes;
    aValue[1]= highBytes;
}


void JCCteLong::unassemble(char *outBuffer)
{
    sprintf(outBuffer, ".long: %08x%08x", highBytes, lowBytes);
}


/**************************************************
* Implementation: JCCteDouble.
**************************************************/

JCCteDouble::JCCteDouble(double aValue) : JCDoubleWord()
{
    unsigned int tmpValue[2];
    *((double *)&tmpValue)= aValue;
    lowBytes= tmpValue[0];
    highBytes= tmpValue[1];
}


JCOutCFConstant::Kind JCCteDouble::getType(void)
{
    return kDouble;
}


bool JCCteDouble::isEqual(double aValue)
{
    unsigned int *tmpValue;
    tmpValue= (unsigned int *)&aValue;
    return ((lowBytes == tmpValue[0]) && (highBytes == tmpValue[1]));
}


double JCCteDouble::doubleValue(void)
{
    unsigned int tmpValue[2];

    tmpValue[0]= lowBytes;
    tmpValue[1]= highBytes;
    return *((double *)&tmpValue);
}


void JCCteDouble::unassemble(char *outBuffer)
{
    unsigned int tmpInt[2];
    tmpInt[0]= lowBytes; tmpInt[1]= highBytes;
    sprintf(outBuffer, ".double: %g", *(double *)tmpInt);
}


/**************************************************
* Implementation: JCCteInterfaceMethodRef.
**************************************************/

JCOutCFConstant::Kind JCCteInterfaceMethodRef::getType(void)
{
    return interfaceMethodRef;
}


void JCCteInterfaceMethodRef::unassemble(char *outBuffer)
{
    strcat(outBuffer, ".interfaceMethodRef: ");
    JCReference::unassemble(outBuffer+21);
}


/**************************************************
* Implementation: JCCharString.
**************************************************/

JCCharString::JCCharString(void) : JCOutCFConstant()
{
    length= 0;
    bytes= NULL;
}


JCCharString::~JCCharString(void)
{
    delete[] bytes;
    this->JCOutCFConstant::~JCOutCFConstant();    /* MOD-MSC: Ajoute la classe du destructeur parent. */
}


void JCCharString::write(JCOutClassFile *aClassFile)
{
    aClassFile->writeUByte(utf8);
    aClassFile->writeUShort(length);
    aClassFile->writeByteArray(bytes, length);
}


void JCCharString::unassemble(char *outBuffer)
{
    *outBuffer++= '"';
    memcpy(outBuffer, bytes, length);
    outBuffer+= length;
    *outBuffer++= '"';
    *outBuffer= '\0';
}


/**************************************************
* Implementation: JCCteUtf8.
**************************************************/

ConstantsList *JCCteUtf8::uniqueInstances= new ConstantsList(256);
AkHashManager *JCCteUtf8::hashManager= new AkHashManager();
JCCteUtf8 *JCCteUtf8::wellKnownNames= NULL;

JCCteUtf8 *JCCteUtf8::addUniqueInstance(unsigned short *byteArray)
{
#if defined(LIST_CODE)

    JCCteUtf8 *result;

    if ((result= (JCCteUtf8 *)uniqueInstances->findAsciiValue((char *)byteArray)) == NULL) {
	result= new JCCteUtf8();
	result->setValue(byteArray);
	uniqueInstances->addObject(result);
    }
    return result;

#else

    static JCCteUtf8 *newValue= new JCCteUtf8();
    JCCteUtf8 *result;
    AkHashElement *newElement;

    if (hashManager->addUniqueItem((char *)byteArray, newValue, &newElement)) {
	result= newValue;
	newValue->setValue(byteArray);
	    // Update the key to point to the unique data section.
	newElement->setKey((char *)newValue->bytes);	// MODNT-971218.
	newValue= new JCCteUtf8();
    }
    else {
	bool indicator;
	result= (JCCteUtf8 *)hashManager->getItem((char *)byteArray, indicator);
    }

    return result;

#endif	/* LIST_CODE */
}


void JCCteUtf8::initCteUtf8Class(void)
{
    AkHashElement *newElement;

    if (wellKnownNames == NULL) {	// If not already initialized.
	wellKnownNames= new JCCteUtf8[nbrWellKnownNames];
	wellKnownNames[sourceFile].setValue((unsigned short *)"SourceFile");
	wellKnownNames[constantValue].setValue((unsigned short *)"ConstantValue");
	wellKnownNames[code].setValue((unsigned short *)"Code");
	wellKnownNames[exceptions].setValue((unsigned short *)"Exceptions");
	wellKnownNames[lineNumTbl].setValue((unsigned short *)"LineNumberTable");
	wellKnownNames[localVarTbl].setValue((unsigned short *)"LocalVariableTable");
	wellKnownNames[thisIdent].setValue((unsigned short *)"this");
	wellKnownNames[superIdent].setValue((unsigned short *)"super");
	wellKnownNames[initIdent].setValue((unsigned short *)"<init>");
	wellKnownNames[clinitIdent].setValue((unsigned short *)"<clinit>");
#if defined(PLZEN_LEVEL_2)
	wellKnownNames[transitions].setValue((unsigned short *)"Transitions");
	wellKnownNames[stateCode].setValue((unsigned short *)"StateCode");
	wellKnownNames[pinitIdent].setValue((unsigned short *)"<pinit>");
#endif
#if defined(PLZEN_LEVEL_3)
	wellKnownNames[execSql].setValue((unsigned short *)"execSql");
#endif

	for (unsigned int i= 0; i < nbrWellKnownNames; i++) {
#if defined(LIST_CODE)

	    uniqueInstances->addObject(&wellKnownNames[i]);

#else

	    hashManager->addUniqueItem(wellKnownNames[i].asciiString(), &wellKnownNames[i], &newElement);

#endif	/* LIST_CODE */

	}
    }
}


JCCteUtf8 *JCCteUtf8::getWellKnownName(WellKnownNames aNameID)
{
    if ((aNameID >= sourceFile) && (aNameID < nbrWellKnownNames)) {
	return &wellKnownNames[aNameID];
    }
    else return NULL;
}


JCOutCFConstant::Kind JCCteUtf8::getType(void)
{
    return utf8;
}


void JCCteUtf8::setValue(unsigned short *byteArray)
{
// ATTN: Doesn't do UTF8 processing for now.  Work with 8bit chars.
    if (byteArray == NULL) {
	length= 0;
	bytes= NULL;
    }
    else {
	char *tmpPtr= (char *)byteArray;

	length= 0;
	while (*tmpPtr != '\0') {
	    length++;
	    tmpPtr++;
	    if (length > 1022) {
		// ERRMSG: String too long.
		break;
	    }
	}
	bytes= new unsigned char[length+1];
	memcpy(bytes, byteArray, length * sizeof(unsigned char));
	bytes[length]= '\0';
    }
}


char *JCCteUtf8::asciiString(void)
{
// ATTN: Doesn't do UTF8 processing for now.
    return (char *)bytes;
}


unsigned int JCCteUtf8::asciiLength(void)
{
// ATTN: Doesn't do UTF8 processing for now.
    return length;
}


bool JCCteUtf8::isAsciiEqual(unsigned char *aString)
{
    return (strcmp((const char *)bytes, (const char *)aString) == 0);
}


bool JCCteUtf8::isEqual(JCCteUtf8 *anUtf8)
{
    if (this == anUtf8) return true;
    else return (strcmp((const char *)bytes, (const char *)anUtf8->bytes) == 0);
}


void JCCteUtf8::unassemble(char *outBuffer)
{
    strcat(outBuffer, ".utf: ");
    JCCharString::unassemble(outBuffer+6);
}


/**************************************************
* Implementation: JCCteUnicode.
**************************************************/

ConstantsList *JCCteUnicode::uniqueInstances= new ConstantsList(256);


JCOutCFConstant::Kind JCCteUnicode::getType(void)
{
    return unicode;
}


