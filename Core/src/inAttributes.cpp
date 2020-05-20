/**************************************************
* File: inAttributes.cc.
* Desc: Definition of the JCAttributeInfo classes.
* Module: AkraLog : JavaKit.
* Rev: 26 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(__APPLE__)
#include <istream>
using std::istream;
using std::ios_base;
#else
#include <iostream.h>
#endif
#include <akra/convertMacro.h>
#include "inAttributes.h"


bool JCAttributeInfo::read(istream *aStream, JCCFConstant **ctePool, JCAttributeInfo * &readAttribute)
{
    unsigned int tag, length;
     char tmpBuffer[4];

    aStream->read(tmpBuffer, sizeof(javaU2));
    tag= MakeUShort(tmpBuffer);
    aStream->read(tmpBuffer, sizeof(javaU4));
    length= MakeUInteger(tmpBuffer);

    aStream->seekg((istream::off_type)length, ios_base::cur);

    readAttribute= this;
    return false;
}

