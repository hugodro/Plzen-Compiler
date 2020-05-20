/**************************************************
* File: classFile.cc.
* Desc: Implementation of the JAClassFile class.
* Module: JavaKit : Compiler.
* Rev: 24 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/convertMacro.h>
#include "classFile.h"


/**************************************************
* Implementation: JAClassFile.
**************************************************/

JAClassFile::JAClassFile(void)
{
    magic= 0;
    
}


bool JAClassFile::isInterface(void)
{
    return false;
}


/**************************************************
* Implementation: JALoadedObject.
**************************************************/

JALoadedObject::JALoadedObject()
{
    isResolved= false;
}


/**************************************************
* Implementation: JAComponentInfo.
**************************************************/

bool JAComponentInfo::read(istream *aStream)
{
    return false;
}


bool JAComponentInfo::read(istream *aStream, JACFConstant **ctePool)
{
    char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU2));
    accessFlags= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU2));
    nameIndex= MakeUShort(tmpBuffer);

    return true;
}


bool JAComponentInfo::isNamed(char *aName, JACFConstant **ctePool)
{
    return ((JACFString *)ctePool[nameIndex])->isStrEqual(aName);
}


void JAComponentInfo::setOwner(JAClassFile *classFile)
{
    owner= classFile;
}


JAClassFile *JAComponentInfo::getOwner(void)
{
    return owner;
}


bool JAComponentInfo::isStatic(void)
{
    return ((accessFlags & JAClassFile::afStatic) != 0);
}


/**************************************************
* Implementation: JAMemberInfo.
**************************************************/

bool JAMemberInfo::read(istream *aStream, JACFConstant **ctePool)
{
    char tmpBuffer[4];

    if (JAComponentInfo::read(aStream, ctePool) == true) {
	aStream->read(tmpBuffer, sizeof(javaU2));
	signatureIndex= MakeUShort(tmpBuffer);
	readAttributes(aStream, ctePool);
	return true;
    }
    return false;
}


bool JAMemberInfo::readAttributes(istream *aStream, JACFConstant **ctePool)
{
    return false;
}


/**************************************************
* Implementation: JAFieldInfo.
**************************************************/

/**************************************************
* Implementation: JAMethodInfo.
**************************************************/

bool JAMethodInfo::read(istream *aStream, JACFConstant **ctePool)
{
    return false;
}

bool JAMethodInfo::isFromInterface(void)
{
    return (owner->isInterface());
}


/**************************************************
* Implementation: JACFConstant.
**************************************************/

bool JACFConstant::read(istream *aStream)
{
    return false;
}


/**************************************************
* Implementation: JACFString.
**************************************************/

bool JACFString::isStrEqual(char *aStr)
{
    return false;
}

