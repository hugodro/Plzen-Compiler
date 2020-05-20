#ifndef _JCOPCODE_H_
#define _JCOPCODE_H_
/**************************************************
* File: opcode.h.
* Desc: Contains the declaration of the JCOpCode class.
* Module: AkraLog : JavaComp.
* Rev: 7 janvier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"
#include "instructions.h"

class JCAddressLabel;
class ostream;


class JCOpCode : public AkObject {
  protected:
    JCInstrSet::Instructions opcode;
    bool expandFlag;
    bool labelArrival;

  public:
    JCOpCode(JCInstrSet::Instructions aCode);
    virtual bool isArrival(void);
    virtual void setLabelArrival(bool aFlag);
    virtual void unassemble(char *buffer);
    virtual unsigned char const *encode(void);
    virtual unsigned int byteSize(void);
    virtual JCInstrSet::Instructions getOpCode(void);
};


class JCSimpleOpcode : public JCOpCode {
  protected:

  public:
    JCSimpleOpcode(JCInstrSet::Instructions aCode);
};


class JCByteOpcode : public JCOpCode {
  protected:
    unsigned char argument;

  public:
    JCByteOpcode(JCInstrSet::Instructions aCode, unsigned char aByte);
    virtual void unassemble(char *buffer);
    virtual unsigned char const *encode(void);
};


class JCShortOpcode : public JCOpCode {
  protected:
    unsigned short argument;

  public:
    JCShortOpcode(JCInstrSet::Instructions aCode, unsigned short aShort);
    virtual void unassemble(char *buffer);
    virtual unsigned char const *encode(void);
};


class JC3BytesOpcode : public JCOpCode {
  protected:
    unsigned short argument;
    unsigned char extraArgument;

  public:
    JC3BytesOpcode(JCInstrSet::Instructions aCode, unsigned short aShort, unsigned char aByte);
    virtual void unassemble(char *buffer);
    virtual unsigned char const *encode(void);
};


class JCIntegerOpcode : public JCOpCode {
  protected:
    unsigned int argument;

  public:
    JCIntegerOpcode(JCInstrSet::Instructions aCode, unsigned int anInt);
    virtual void unassemble(char *buffer);
    virtual unsigned char const *encode(void);
};


class JCBranchOpcode : public JCOpCode {
  protected:
    JCAddressLabel *destination;
    unsigned int tmpCurPC;

  public:
    JCBranchOpcode(JCInstrSet::Instructions aCode, JCAddressLabel *aLabel, unsigned int tmpPC);
    virtual void unassemble(char *buffer);
    virtual unsigned char const *encode(void);
};


class JCPoolOpcode : public JCOpCode {
  protected:
    unsigned int poolCte; 

  public:
    JCPoolOpcode(JCInstrSet::Instructions aCode, unsigned int anIndex);
    virtual void unassemble(char *buffer);
    virtual unsigned char const *encode(void);

};

#endif		/* _JCOPCODE_H_ */
