#ifndef _JCCODEBUFFER_H_
#define _JCCODEBUFFER_H_
/**************************************************
* File: codeBuffer.h.
* Desc: Contains the declaration of the CodeBuffer class.
* Module: AkraLog : JavaComp.
* Rev: 22 decembre 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"


class JCOutClassFile;


class JCCodeBuffer : public AkObject {
  protected:	// Instance variables.
    unsigned char *bytes;
    unsigned int currentPC;
    unsigned int availableSize, usedSize;

  public:		// Instance methods.
    JCCodeBuffer(void);
    virtual ~JCCodeBuffer(void);
    virtual void reset(void);
    virtual unsigned int getLength(void);
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual void allocFor(unsigned int aLength);
    virtual bool load(const char *code, unsigned int aLength);
};

#endif		/* _JCCODEBUFFER_H_ */
