#ifndef _HASHELEMENT_H_
#define _HASHELEMENT_H_

/**************************************************
* File: hashElement.h.
* Desc: Definition of the AkHashElement class.
* Module: AkraLog : JavaKit.
* Rev: 29 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class AkHashElement : public AkObject {
    friend class AkHashBucket;
  protected:
    AkHashElement *next;
    unsigned int bucketHash;
    char *key;
    void *value;

  public:
    AkHashElement(void);
    AkHashElement(AkHashElement *parent);
    virtual bool isMatching(char *aKey);
    virtual void setKey(char *aKey);
};


#endif	/* _HASHELEMENT_H_ */

