/**************************************************
* File: hashElement.cc.
* Desc: Implementation of the AkHashElement class.
* Module: AkraLog : JavaKit.
* Rev: 29 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <string.h>
#include "hashElement.h"


AkHashElement::AkHashElement(void)
{
    next= NULL;
    bucketHash= 0;
    key= NULL;
    value= NULL;
}


AkHashElement::AkHashElement(AkHashElement *parent)
{
    next= parent->next;
    bucketHash= parent->bucketHash;
    key= parent->key;
    value= parent->value;
    parent->next= this;
}


bool AkHashElement::isMatching(char *aKey)
{
    return (strcmp(aKey, key) == 0);
}


void AkHashElement::setKey(char *aKey)
{
    key= aKey;
}
