/**************************************************
* File: hashBucket.cc.
* Desc: Implementation of the AkHashBucket class.
* Module: AkraLog : JavaKit.
* Rev: 29 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <stdlib.h>
#include "hashElement.h"
#include "hashBucket.h"


AkHashBucket::AkHashBucket(unsigned int tableSize)
{
    elements= new AkHashElement*[tableSize];
    elements[0]= new AkHashElement[tableSize];
    for (unsigned int i= 1; i < tableSize; i++) {
	elements[i]= elements[0] + i;
    }

    nbrElements= collisionCount= 0;
}


AkHashBucket::~AkHashBucket(void)
{
    delete elements[0];
    delete elements;
}


bool AkHashBucket::locateKeyAt(char *aKey, unsigned int aPos)
{
    if (elements[aPos]->key != NULL) {
	AkHashElement *tmpElement= elements[aPos];

	do {
	    if (tmpElement->isMatching(aKey)) break;
	    tmpElement= tmpElement->next;
	} while (tmpElement != NULL);

	return (tmpElement != NULL);
    }

    return false;
}


bool AkHashBucket::addElementAt(char *aKey, void *aValue, unsigned int aPos, unsigned int aHashing, AkHashElement **resultEntry)
{
    nbrElements++;
    if (elements[aPos]->key != NULL) {
        AkHashElement *tmpElement= new AkHashElement(elements[aPos]);
        elements[aPos]->key= aKey;
        elements[aPos]->value= aValue;
        elements[aPos]->bucketHash= aHashing;
        collisionCount++;
	*resultEntry= elements[aPos];
        return true;
    }
    else {
	elements[aPos]->key= aKey;
	elements[aPos]->value= aValue;
	elements[aPos]->bucketHash= aHashing;
	*resultEntry= elements[aPos];
    }
    return false;
}


unsigned int AkHashBucket::getCollisions(void)
{
    return collisionCount;
}


void *AkHashBucket::getItemAt(char *aKey, unsigned int aPos, bool & indicator)
{
    if (elements[aPos]->key != NULL) {
	AkHashElement *tmpElement= elements[aPos];

	do {
	    if (tmpElement->isMatching(aKey)) break;
	    tmpElement= tmpElement->next;
	} while (tmpElement != NULL);

	indicator= (tmpElement != NULL);
	if (tmpElement != NULL) return tmpElement->value;
    }
    else {
	indicator= false;
    }
    return NULL;
}

