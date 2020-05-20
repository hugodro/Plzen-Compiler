#ifndef _HASHBUCKET_H_
#define _HASHBUCKET_H_

/**************************************************
* File: hashBucket.h.
* Desc: Definition of the AkHashBucket class.
* Module: AkraLog : JavaKit.
* Rev: 29 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class AkHashElement;


class AkHashBucket : public AkObject {
  protected:
    unsigned int nbrElements;
    unsigned int collisionCount;
    AkHashElement **elements;

  public:
    AkHashBucket(unsigned int tableSize);
    virtual ~AkHashBucket(void);
    virtual bool locateKeyAt(char *aKey, unsigned int aPos);
    virtual bool addElementAt(char *aKey, void *aValue, unsigned int aPos, unsigned int aHashing, AkHashElement **resultEntry);
    virtual unsigned int getCollisions(void);
    virtual void *getItemAt(char *aKey, unsigned int aPos, bool & indicator);
};


#endif	/* _HASHBUCKET_H_ */

