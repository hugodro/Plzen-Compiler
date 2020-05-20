/**************************************************
* File: opcode.h.
* Desc: Contains the declaration of the JCOpCode class.
* Module: AkraLog : JavaComp.
* Rev: 24 janvier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include <stdio.h>
#include <string.h>
#include "labelStack.h"
#include "opcode.h"


/**************************************************
* Implementation: JCOpCode.
**************************************************/

JCOpCode::JCOpCode(JCInstrSet::Instructions aCode)
{
    opcode= aCode;
    labelArrival= expandFlag= false;
}


bool JCOpCode::isArrival(void)
{
    return labelArrival;
}


void JCOpCode::setLabelArrival(bool aFlag)
{
    labelArrival= aFlag;
}


void JCOpCode::unassemble(char *buffer)
{
  strcat(buffer, JCInstrSet::getName(opcode));
  strcat(buffer, "\n");
}


unsigned char const *JCOpCode::encode(void)
{
    static unsigned char buffer[1];

    buffer[0]= (unsigned char)JCInstrSet::instructionIDs[opcode];
    return buffer;
}


unsigned int JCOpCode::byteSize(void)
{
    return JCInstrSet::getSizeOf(opcode);
}


JCInstrSet::Instructions JCOpCode::getOpCode(void)
{
    return opcode;
}


/**************************************************
* Implementation: JCSimpleOpcode.
**************************************************/

JCSimpleOpcode::JCSimpleOpcode(JCInstrSet::Instructions aCode) : JCOpCode(aCode)
{
}


/**************************************************
* Implementation: JCByteOpcode.
**************************************************/

JCByteOpcode::JCByteOpcode(JCInstrSet::Instructions aCode, unsigned char aByte) : JCOpCode(aCode)
{
    argument= aByte;
}


void JCByteOpcode::unassemble(char *buffer)
{
    if ((opcode == JCInstrSet::ldc1) || (opcode == JCInstrSet::ret)) {
	sprintf(buffer, "%s [%d]\n", JCInstrSet::getName(opcode), argument);
    }
    else {
	sprintf(buffer, "%s #%d\n", JCInstrSet::getName(opcode), argument);
    }
}


unsigned char const *JCByteOpcode::encode(void)
{
    static unsigned char buffer[2];

    buffer[0]= (unsigned char)JCInstrSet::instructionIDs[opcode];
    buffer[1]= (unsigned char)argument;
    return buffer;
}


/**************************************************
* Implementation: JCShortOpcode.
**************************************************/

JCShortOpcode::JCShortOpcode(JCInstrSet::Instructions aCode, unsigned short aShort) : JCOpCode(aCode)
{
    argument= aShort;
}


void JCShortOpcode::unassemble(char *buffer)
{
  sprintf(buffer, "%s #%d\n", JCInstrSet::getName(opcode), argument);
}


unsigned char const *JCShortOpcode::encode(void)
{
    static unsigned char buffer[3];

    buffer[0]= (unsigned char)JCInstrSet::instructionIDs[opcode];
    buffer[1]= (unsigned char)((argument >> 8) & 0x0FF);
    buffer[2]= (unsigned char)(argument & 0x0FF);
    return buffer;
}


/**************************************************
* Implementation: JC3BytesOpcode.
**************************************************/

JC3BytesOpcode::JC3BytesOpcode(JCInstrSet::Instructions aCode, unsigned short aShort, unsigned char aByte) : JCOpCode(aCode)
{
    argument= aShort;
    extraArgument= aByte;
}


void JC3BytesOpcode::unassemble(char *buffer)
{
    sprintf(buffer, "%s [%d], #%d\n", JCInstrSet::getName(opcode), argument, extraArgument);
}


unsigned char const *JC3BytesOpcode::encode(void)
{
    static unsigned char buffer[4];

    buffer[0]= (unsigned char)JCInstrSet::instructionIDs[opcode];
    buffer[1]= (unsigned char)((argument >> 8) & 0x0FF);
    buffer[2]= (unsigned char)(argument & 0x0FF);
    buffer[3]= (unsigned char)extraArgument;
    return buffer;
}


/**************************************************
* Implementation: JCIntegerOpcode.
**************************************************/

JCIntegerOpcode::JCIntegerOpcode(JCInstrSet::Instructions aCode, unsigned int anInt) : JCOpCode(aCode)
{
    argument= anInt;
}


void JCIntegerOpcode::unassemble(char *buffer)
{
  sprintf(buffer, "%s #%d\n", JCInstrSet::getName(opcode), argument);
}


unsigned char const *JCIntegerOpcode::encode(void)
{
    static unsigned char buffer[5];

    buffer[0]= (unsigned char)JCInstrSet::instructionIDs[opcode];
    buffer[1]= (unsigned char)((argument >> 24) & 0x0FF);
    buffer[2]= (unsigned char)((argument >> 16) & 0x0FF);
    buffer[3]= (unsigned char)((argument >> 8) & 0x0FF);
    buffer[4]= (unsigned char)(argument & 0x0FF);
    return buffer;
}


/**************************************************
* Implementation: JCBranchOpcode.
**************************************************/

JCBranchOpcode::JCBranchOpcode(JCInstrSet::Instructions aCode, JCAddressLabel *aLabel, unsigned int tmpPC) : JCOpCode(aCode)
{
    destination= aLabel;
    tmpCurPC= tmpPC;
}


void JCBranchOpcode::unassemble(char *buffer)
{
  sprintf(buffer, "%s <%d>\n", JCInstrSet::getName(opcode), destination->getValue());
}


// TODO: S'occuper des instructions a taille variable !

unsigned char const *JCBranchOpcode::encode(void)
{
    static unsigned char buffer[3];

    buffer[0]= (unsigned char)JCInstrSet::instructionIDs[opcode];
    buffer[1]= (unsigned char)((destination->distanceFrom(tmpCurPC) >> 8) & 0x0FF);
    buffer[2]= (unsigned char)(destination->distanceFrom(tmpCurPC) & 0x0FF);
    return buffer;
}


/**************************************************
* Implementation: JCPoolOpcode.
**************************************************/

JCPoolOpcode::JCPoolOpcode(JCInstrSet::Instructions aCode, unsigned int anIndex) : JCOpCode(aCode)
{
    poolCte= anIndex;
}


void JCPoolOpcode::unassemble(char *buffer)
{
  sprintf(buffer, "%s [%d]\n", JCInstrSet::getName(opcode), poolCte);
}


unsigned char const *JCPoolOpcode::encode(void)
{
    static unsigned char buffer[3];

    buffer[0]= (unsigned char)JCInstrSet::instructionIDs[opcode];
    buffer[1]= (unsigned char)((poolCte >> 8) & 0x0FF);
    buffer[2]= (unsigned char)(poolCte & 0x0FF);
    return buffer;
}

