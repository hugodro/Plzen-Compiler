#ifndef _LABELSTACK_H_
#define _LABELSTACK_H_
/**************************************************
* File: labelStack.h.
* Desc: Contains the definition of the address labels management classes.
* Module: AkraLog : JavaComp.
* Rev: 22 decembre 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"

class JCOpCode;
class OpCodeList;
class LabelList;

class JCAddressLabel : public AkObject {
    friend class JCLabelStack;
    friend class LabelList;
  public:
    enum Type {
	ifType, switchType,
	whileType, doType, forType,
	tryFinalType, tryCatchType, tryFullType,
	orOperType, andOperType,
	eqOperType, ineqOperType,
	orTestType, andTestType,
	eqTestType, ineqTestType
	, breakScan, continueScan
	, innerLabel
	, startTransition, endTransition
    };
  protected:
    unsigned int pcLocation;	// Position of the label in a compact byte-code.
    Type type;
    bool assigned;			// Indicates if the label was assigned to an instruction.
    OpCodeList *users;		// Instructions that refer to this label.
    unsigned int value;		// Offset of the instruction (in the OpList) at the label.

  public:
    JCAddressLabel(void);
    virtual ~JCAddressLabel(void);
    virtual int distanceFrom(unsigned int aPosition);
    virtual void addUser(JCOpCode *anOpcode);
    virtual void defineAs(unsigned int instrOffset, unsigned int anAddress);
    virtual unsigned int getValue(void);
    virtual unsigned int getPCLocation(void);
};


class JCLabelReference : public AkObject {
  protected:
    unsigned int addrOfUse;
    
  public:

};


class JCLabelStack : public AkObject {
  protected:
    LabelList *labels;
    bool definedNewLabel;

  public:
    JCLabelStack(void);
    virtual ~JCLabelStack(void);
    virtual void reset(void);
    virtual unsigned int allocBlock(unsigned int aSize, JCAddressLabel::Type aType);
    virtual bool freeBlock(void);
    virtual JCAddressLabel *objectAt(unsigned int anOffset);
    virtual bool define(unsigned int anID, unsigned int instrOffset, unsigned int pc);
    virtual unsigned int backScanFor(JCAddressLabel::Type aType);
    virtual bool flushNewLabel(void);
};

#endif		/* _LABELSTACK_H_ */
