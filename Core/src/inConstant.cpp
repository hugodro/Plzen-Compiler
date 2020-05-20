/**************************************************
* File: inConstant.h.
* Desc: Definition of the JCCFConstant, used to read the constant pool of an imported class.
* Module: JavaKit : Compiler.
* Rev: 24 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <string.h>
#include <akra/convertMacro.h>
#include "inConstant.h"


bool JCCFConstant::readAttributes(istream *aStream, JACFConstant **ctePool)
{
  // TODO.
    return false;
}


bool JCCFConstant::read(istream *aStream, JCCFConstant* &realCte)
{
    unsigned int tag;
    char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU1));
    tag= MakeUByte(tmpBuffer);
    switch (tag) {
	case JACFConstant::ctClass:
	    realCte= new JCCFClass;
	    break;
	case JACFConstant::ctFieldRef:
	    realCte= new JCCFFieldRef;
	    break;
	case JACFConstant::ctMethodRef:
	    realCte= new JCCFMethodRef;
	    break;
	case JACFConstant::ctString:
	    realCte= new JCCFString;
	    break;
	case JACFConstant::ctInteger:
	    realCte= new JCCFInteger;
	    break;
	case JACFConstant::ctFloat:
	    realCte= new JCCFFloat;
	    break;
	case JACFConstant::ctLong:
	    realCte= new JCCFLong;
	    break;
	case JACFConstant::ctDouble:
	    realCte= new JCCFDouble;
	    break;
	case JACFConstant::ctInterfaceMethodRef:
	    realCte= new JCCFInterfaceMethodRef;
	    break;
	case JACFConstant::ctNameAndType:
	    realCte= new JCCFNameAndType;
	    break;
	case JACFConstant::ctUtf8:
	    realCte= new JCCFUtf8;
	    break;
	case JACFConstant::ctUnicode:
	    realCte= new JCCFUnicode;
	    break;
	default:
	    cout << "Unknown constant.\n";
	    realCte= this;
	    break;
     }
    realCte->read(aStream);
    return true;
}


bool JCCFConstant::read(istream *aStream)
{
    return false;
}


JACFConstant::ConstantTypes JCCFConstant::type(void)
{
    return JACFConstant::ctUnknown;
}


/**************************************************
* Implementation: JCCFClass.
**************************************************/

bool JCCFClass::read(istream *aStream)
{
     char tmpBuffer[2];

    aStream->read(tmpBuffer, sizeof(javaU2));
    index= MakeUShort(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFClass::type(void)
{
    return JACFConstant::ctClass;
}

unsigned int JCCFClass::getNameIndex(void)
{
    return index;
}


/**************************************************
* Implementation: JCCFFieldRef.
**************************************************/

bool JCCFFieldRef::read(istream *aStream)
{
     char tmpBuffer[2];

    aStream->read(tmpBuffer, sizeof(javaU2));
    index= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));
    nameTypeIndex= MakeUShort(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFFieldRef::type(void)
{
    return JACFConstant::ctFieldRef;
}


/**************************************************
* Implementation: JCCFMethodRef.
**************************************************/

bool JCCFMethodRef::read(istream *aStream)
{
     char tmpBuffer[2];

    aStream->read(tmpBuffer, sizeof(javaU2));
    index= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));
    nameTypeIndex= MakeUShort(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFMethodRef::type(void)
{
    return JACFConstant::ctMethodRef;
}


/**************************************************
* Implementation: JCCFString.
**************************************************/

bool JCCFString::read(istream *aStream)
{
     char tmpBuffer[2];

    aStream->read(tmpBuffer, sizeof(javaU2));
    index= MakeUShort(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFString::type(void)
{
    return JACFConstant::ctString;
}


/**************************************************
* Implementation: JCCFInteger.
**************************************************/

bool JCCFInteger::read(istream *aStream)
{
     char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU4));
    bytes= MakeUInteger(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFInteger::type(void)
{
    return JACFConstant::ctInteger;
}


/**************************************************
* Implementation: JCCFFloat.
**************************************************/

bool JCCFFloat::read(istream *aStream)
{
     char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU4));
    bytes= MakeUInteger(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFFloat::type(void)
{
    return JACFConstant::ctFloat;
}


/**************************************************
* Implementation: JCCFLong.
**************************************************/

bool JCCFLong::read(istream *aStream)
{
     char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU4));
    bytes= MakeUInteger(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU4));
    high_bytes= MakeUInteger(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFLong::type(void)
{
    return JACFConstant::ctLong;
}


/**************************************************
* Implementation: JCCFDouble.
**************************************************/

bool JCCFDouble::read(istream *aStream)
{
     char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU4));
    bytes= MakeUInteger(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU4));
    high_bytes= MakeUInteger(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFDouble::type(void)
{
    return JACFConstant::ctDouble;
}


/**************************************************
* Implementation: JCCFInterfaceMethodRef.
**************************************************/

bool JCCFInterfaceMethodRef::read(istream *aStream)
{
     char tmpBuffer[2];

    aStream->read(tmpBuffer, sizeof(javaU2));
    index= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));
    nameTypeIndex= MakeUShort(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFInterfaceMethodRef::type(void)
{
    return JACFConstant::ctInterfaceMethodRef;
}


/**************************************************
* Implementation: JCCFNameAndType.
**************************************************/

bool JCCFNameAndType::read(istream *aStream)
{
     char tmpBuffer[2];

    aStream->read(tmpBuffer, sizeof(javaU2));
    index= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));
    signatureIndex= MakeUShort(tmpBuffer);
    return true;
}

JACFConstant::ConstantTypes JCCFNameAndType::type(void)
{
    return JACFConstant::ctNameAndType;
}


/**************************************************
* Implementation: JCCFUtf8.
**************************************************/

bool JCCFUtf8::read(istream *aStream)
{
     char tmpBuffer[2];

    aStream->read(tmpBuffer, sizeof(javaU2));
    length= MakeUShort(tmpBuffer);
    bytes= new unsigned char[length+1];
    aStream->read((char *)bytes, length * sizeof(javaU1));
    bytes[length]= '\0';
    return true;
}

JACFConstant::ConstantTypes JCCFUtf8::type(void)
{
    return JACFConstant::ctUtf8;
}


unsigned char *JCCFUtf8::getAsciiValue(void)
{
    return bytes;
}


void JCCFUtf8::writeAsciiValue(unsigned char *aBuffer)
{
    memcpy(aBuffer, bytes, length * sizeof(unsigned char));
    aBuffer[length]= '\0';
}


unsigned int JCCFUtf8::getLength(void)
{
    return length;
}


bool JCCFUtf8::isEqual(JCCFUtf8 *anUtf)
{
    if (length == anUtf->length) {
	if (length > 0) {
	    unsigned int i= length;

	    do {
		i--;
		if (bytes[i] != anUtf->bytes[i]) {
		    return false;		// Warning: quick exit.
		}
	    } while (i != 0);
	}
	return true;		// Warning: quick exit.
    }
    return false;
}


/**************************************************
* Implementation: JCCFUnicode.
**************************************************/

bool JCCFUnicode::read(istream *aStream)
{
     char tmpBuffer[2];

    aStream->read(tmpBuffer, sizeof(javaU2));
    length= MakeUShort(tmpBuffer);
    bytes= new unsigned char[length+2];
    aStream->read((char *)bytes, length * sizeof(javaU1));
    bytes[length]= (unsigned char)0x0C0;
    bytes[length+1]= (unsigned char)0x080;
    return true;
}

JACFConstant::ConstantTypes JCCFUnicode::type(void)
{
    return JACFConstant::ctUnicode;
}


