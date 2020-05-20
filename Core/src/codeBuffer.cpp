/**************************************************
* File: codeBuffer.c.
* Desc: Contains the implementation of the CodeBuffer class.
* Module: AkraLog : JavaComp.
* Rev: 24 janvier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <string.h>	/* MOD-MSC: Ajoute pour memcpy. */
#include "outClassFile.h"
#include "codeBuffer.h"


/**************************************************
* Implementation: JCCodeBuffer.
**************************************************/

JCCodeBuffer::JCCodeBuffer(void)
{
    availableSize= usedSize= 0;
    currentPC= 0;
    bytes= NULL;
}


JCCodeBuffer::~JCCodeBuffer(void)
{
    delete[] bytes;
}


void JCCodeBuffer::reset(void)
{
    currentPC= 0;
}


unsigned int JCCodeBuffer::getLength(void)
{
    return currentPC;
}


void JCCodeBuffer::writeInto(JCOutClassFile *aClassFile)
{
    aClassFile->writeByteArray(bytes, currentPC);
}


void JCCodeBuffer::allocFor(unsigned int aLength)
{
    if (aLength > availableSize) {
	delete[] bytes;
	bytes= new unsigned char[aLength];
	availableSize= aLength;
    }
    usedSize= aLength;
}


bool JCCodeBuffer::load(const char *code, unsigned int aLength)
{
    if (currentPC + aLength > usedSize) return false;

    memcpy(bytes+currentPC, code, aLength * sizeof(char));
    currentPC+= aLength;
    return true;
}


