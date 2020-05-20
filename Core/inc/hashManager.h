#ifndef _HASHMANAGER_H_
#define _HASHMANAGER_H_

/**************************************************
* File: hashManager.h.
* Desc: Definition of the AkHashManager class.
* Module: AkraLog : JavaKit.
* Rev: 29 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>


class AkHashBucket;
class AkHashElement;


class AkHashManager : public AkObject {
  public:
    static unsigned int smallPrimes[256];
    static unsigned int bigPrimes[256];

  private:
    static unsigned int stringHashOne(char *aKey);
    static unsigned int stringHashTwo(char *aKey);

  protected:
    unsigned int bucketSize;
    unsigned int nbrElements;
    unsigned int nbrBuckets;
    unsigned int (*hashOne)(char *aKey);
    unsigned int (*hashTwo)(char *aKey);
    AkHashBucket **buckets;

  public:
    AkHashManager(void);
    virtual ~AkHashManager(void);
    virtual bool findKey(char *aKey);
    virtual bool addUniqueItem(char *aKey, void *aValue, AkHashElement **resultElement);
    virtual void *getItem(char *aKey, bool & indicator);
};


#endif	/* _HASHMANAGER_H_ */

