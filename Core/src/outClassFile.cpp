/**************************************************
* File: outClassFile.cc.
* Desc: Definition of the JCOutClassFile class.
* Module: AkraLog : JavaKit.
* Rev: 25 novembre 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <fstream.h>
#include <iostream.h>
using std::cout;

#include "lists.h"
#include "compileObjects.h"
#include "outConstant.h"
#include "compiler.h"
#include "compContext.h"
#include "outClassFile.h"

JCOutClassFile::JCOutClassFile(JCCompilationContext *aCompCtxt, JCType *aType)
{
    char *aName= NULL;

    compileCtxt= aCompCtxt;
    // Make a short name.
//    aName= aType->getShortName();
    init(aName, aType);
}


JCOutClassFile::JCOutClassFile(JCCompilationContext *aCompCtxt, char *aName, JCType *aType)
{
    compileCtxt= aCompCtxt;
    init(aName, aType);
}


JCOutClassFile::~JCOutClassFile(void)
{
    if (isOpened) {
	outStream->close();
	delete outStream;
    }
}


void JCOutClassFile::init(char *aName, JCType *aType)
{
    myClass= aType;
    magicNumber= 0x0CAFEBABE;
    majorVersion= 3;
    minorVersion= 45;

// ATTENTION: What is the 'error condition' for an ofstream ?
#if defined(_WIN32)
    if ((outStream= new ofstream(aName, ios::binary)) != (ofstream *)-1) {
#else
    if ((outStream= new ofstream(aName)) != (ofstream *)-1) {
#endif
	isOpened= true;
    }
    else {
	isOpened= false;
    }
    classNameIndex= superClassNameIndex= sourceFileNameIndex= 0;
    constantPool= new ConstantsList(256);
    attributes= new AttributesList();
}


bool JCOutClassFile::buildConstantPool(void)
{
    RealTypesList *interfaces;
    FieldsList *theFields;
    MethodsList *theMethods;
    StatesList *theStates;
    JCField *aField;
    JCOutCFConstant *tmpCte;
    JCCteUtf8 *tmpAttrName;
    unsigned int i;

    JCOutCFConstant::resetIndexes();

	// If compiler must give debug info, we insert immediatly the attribute names used
	// by the special attributes.
    JCCteUtf8::getWellKnownName(JCCteUtf8::sourceFile)->addToPool(constantPool);
    // TODO: the name of the source file must be added in the 'attributes' list as a JCSrcFileAttr.

    tmpCte= myClass->getShadow();
    tmpCte->addToPool(constantPool);
    if (((JCClass *)myClass)->getSuper() != NULL) {
	    // Attn: strong assumation that myClass is not a JCType....
	tmpCte= ((JCClass *)myClass)->getSuper()->getShadow();
	tmpCte->addToPool(constantPool);
    }

    // Add CteClass info for all interfaces.
    interfaces= myClass->getInterfaces();
    for (i= 0; i < interfaces->count(); i++) {
	tmpCte= interfaces->objectAt(i)->getShadow();
	tmpCte->addToPool(constantPool);
    }

    // For all fields of myClass, dump name and signature.
    theFields= myClass->getFields();
    for (i= 0; i < theFields->count(); i++) {
	theFields->objectAt(i)->mapToPool(constantPool);
    }

    // For all methods of myClass, dump name and signature, then do a descent in
    // the actionBlock to dump all used constants.

    if (myClass->containsJCode()) {
	JCCteUtf8::getWellKnownName(JCCteUtf8::code)->addToPool(constantPool);

	    // Should only go there if the compiler has -g option on.
	JCCteUtf8::getWellKnownName(JCCteUtf8::lineNumTbl)->addToPool(constantPool);
	JCCteUtf8::getWellKnownName(JCCteUtf8::localVarTbl)->addToPool(constantPool);
    }

    theMethods= myClass->getMethods();
    theStates= myClass->getStates();

    for (i= 0; i < theMethods->count(); i++) {
	theMethods->objectAt(i)->mapToPool(constantPool);
    }

    if (theStates->count() > 0) {
	JCCteUtf8::getWellKnownName(JCCteUtf8::transitions)->addToPool(constantPool);
		// ATTN: If it is possible to have methods without code (abstract), then this
		//	constant shouldn't be included in the output.
	JCCteUtf8::getWellKnownName(JCCteUtf8::stateCode)->addToPool(constantPool);
    }
    for (i= 0; i < theStates->count(); i++) {
	theStates->objectAt(i)->mapToPool(constantPool);
    }


    // ATTN: If the -g flag is on, we must add the Cte used for the filename attribute of the class.
    
    return true;
}


void JCOutClassFile::writeUInteger(unsigned int aNumber)
{
    static  char buffer[4];	// ATTN-980522 [HD]: Not multi-threadable.

    buffer[3]= (unsigned char)(aNumber & 0x0FF);
    buffer[2]= (unsigned char)((aNumber >> 8) & 0x0FF);
    buffer[1]= (unsigned char)((aNumber >> 16) & 0x0FF);
    buffer[0]= (unsigned char)((aNumber >> 24) & 0x0FF);
    outStream->write(buffer, 4);
}


void JCOutClassFile::writeUShort(unsigned int aNumber)
{
    static  char buffer[2];	// ATTN-980522 [HD]: Not multi-threadable.

    buffer[1]= (unsigned char)(aNumber & 0x0FF);
    buffer[0]= (unsigned char)((aNumber >> 8) & 0x0FF);
    outStream->write(buffer, 2);
}


void JCOutClassFile::writeUByte(unsigned char aByte)
{
    outStream->put(aByte);
}


void JCOutClassFile::writeByteArray(unsigned char *buffer, unsigned int length)
{
    outStream->write((char *)buffer, length);
}


void JCOutClassFile::save(void)
{
    myClass->writeInto(this);
}


void JCOutClassFile::saveFileHeader(void)
{
    writeUInteger(magicNumber);
    writeUShort(majorVersion);
    writeUShort(minorVersion);
}


void JCOutClassFile::saveConstantPool(void)
{
    unsigned int ctePoolSize= constantPool->count();

    writeUShort((ctePoolSize + 1));
    for (unsigned int i= 0; i < ctePoolSize; i++) {
	constantPool->objectAt(i)->write(this);
    }
}


void JCOutClassFile::saveTypeHeader(void)
{
    classNameIndex= myClass->getShadow()->getIndex();
	// Attn: strong assumation that myClass is not a JCType....
    if (((JCClass *)myClass)->getSuper() != NULL) {
	superClassNameIndex= ((JCClass *)myClass)->getSuper()->getShadow()->getIndex();
    }

    writeUShort(classNameIndex);
    writeUShort(superClassNameIndex);
}


void JCOutClassFile::saveAttributes(void)
{
    unsigned int nbrAttribs;

    writeUShort((nbrAttribs= attributes->count()));
    for (unsigned int i= 0; i < nbrAttribs; i++) {
	attributes->objectAt(i)->writeInto(this);
    }
}


bool JCOutClassFile::opened(void)
{
    return isOpened;
}


ConstantsList *JCOutClassFile::getConstantPool(void)
{
    return constantPool;
}


void JCOutClassFile::startCodeContext(JCMethod *aMethod)
{
    compileCtxt->startMethod(aMethod);
}


void JCOutClassFile::closeCodeContext(void)
{
    compileCtxt->endMethod();
}


JCCompilationContext * JCOutClassFile::getCodeContext(void)
{
    return compileCtxt;
}


void JCOutClassFile::dumpConstantPool(void)
{
    unsigned int ctePoolSize= constantPool->count();
    char tmpBuffer[2048];

    cout << "Constant Pool:\n";
    for (unsigned int i= 0; i < ctePoolSize; i++) {
	tmpBuffer[0]= '\0';
	constantPool->objectAt(i)->unassemble(tmpBuffer);
	cout << i+1 << ": " << tmpBuffer << "\n";
    }
    cout << "\n\n";
}
