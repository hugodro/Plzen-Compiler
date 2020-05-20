/**************************************************
* File: identifiers.cc.
* Desc: .
* Module: AkraLog : JavaComp.
* Rev: 5 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <string.h>
 }

#include "iostream.h"

#include "typing.h"
#include "outConstant.h"
#include "identifiers.h"


/**************************************************
* Implementation: JCIdentifier.
**************************************************/

 JCIdentifier *JCIdentifier::getFromPathName(char *aFullName, unsigned int nameLength)
 {
    JCIdentifier *result= NULL;

    if (aFullName != NULL) {
	if (nameLength > 0) {
	    JCIdentifier *aName;
	    char *charPtr= aFullName, *nameStart, tmpChar;

	    if (*charPtr == '/') {
		charPtr++;
		nameLength--;
	    }
	    nameStart= charPtr;
		// Scan the name to see if it is multi-parts.
	    while (nameLength > 0) {
		if (*charPtr == '/') {
		    if ((charPtr - nameStart) > 0) {
			*charPtr= '\0';		// Put a temporary stop.
			aName= new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)nameStart));
			if (result != NULL) {
			    result->addComponent(aName);
			}
			else {
			    result= aName;
			}
			*charPtr= '/';		// Undo the change.
		    }
		    charPtr++;
		    nameStart= charPtr;
		}
		else {
		    if (*charPtr == '\0') break;		// Sanity check.
		    charPtr++;
		}
		nameLength--;
	    }

	    tmpChar= *charPtr;
	    *charPtr= '\0';
	    aName= new JCIdentifier(JCCteUtf8::addUniqueInstance((unsigned short *)nameStart));
	    *charPtr= tmpChar;
	    if (result != NULL) {
		result->addComponent(aName);
	    }
	    else {
		result= aName;
	    }
	}
    }	

    return result;
 }


JCIdentifier::JCIdentifier()
{
    category= 0;
    reservedName= snNormal;
    next= NULL;
    subComponent= NULL;
    name= NULL;
}


JCIdentifier::JCIdentifier(JCCteUtf8 *aName)
{
    category= 0;
    reservedName= snNormal;
    next= NULL;
    subComponent= NULL;
    name= aName;
}


void JCIdentifier::link(JCIdentifier *nextIdent)
{
    if (next == NULL) next= nextIdent;
    else {
	JCIdentifier *tmpNext= next;
	while (tmpNext->next != NULL) tmpNext= tmpNext->next;
	tmpNext->next= nextIdent;
     }
}


JCIdentifier *JCIdentifier::getNext(void)
{
    return next;
}


bool JCIdentifier::setValue(JCCteUtf8 *aName)
{
    name= aName;
    return false;
}


/* ATTN: Should go.
bool JCIdentifier::setNarrowValue(char *aName)
{
    name= (wchar *)aName;
    return false;
}
*/


JCCteUtf8 *JCIdentifier::getValue(void)
{
    return name;
}


char *JCIdentifier::getAsciiValue(void)
{
    return (name != NULL) ? name->asciiString() : NULL;
}


unsigned int JCIdentifier::nameLength(void)
{
    if (name != NULL) {
	return name->asciiLength();
     }
    else return 0;
}


bool JCIdentifier::addComponent(JCIdentifier *nextComponent)
{
    if (subComponent == NULL) {
	subComponent= nextComponent;
     }
    else {
	JCIdentifier *tmpSub;
	tmpSub= subComponent;
	while (tmpSub->subComponent != NULL) tmpSub= tmpSub->subComponent;
	tmpSub->subComponent= nextComponent;
     }
    return false;
}


JCIdentifier *JCIdentifier::getComponent(void)
{
    return subComponent;
}


JCIdentifier *JCIdentifier::removeSuffix(void)
{
    if (subComponent != NULL) {
	JCIdentifier *result= subComponent, *lastIdent= this;
	while (result->subComponent != NULL) {
	    lastIdent= result;
	    result= result->subComponent;
	}
	lastIdent->subComponent= NULL;
	return result;
    }
    else {
	// ATTN: Is this the right way to threat a non-existing suffix ?
	return NULL;
    }
}


JCIdentifier *JCIdentifier::removePrefix(void)
{
    JCIdentifier *tmpResult;

    if ((tmpResult= subComponent) != NULL) {
	subComponent= NULL;
    }
    return tmpResult;
}


void JCIdentifier::resolveToSelf(void)
{
    reservedName= snThis;
}


void JCIdentifier::resolveToSuper(void)
{
    reservedName= snSuper;
}


void JCIdentifier::resolveToNull(void)
{
    reservedName= snNull;
}


void JCIdentifier::resolveToFinalCatcher(void)
{
    reservedName= snFinalCatch;
}



JCIdentifier::SpecialName JCIdentifier::getSpecialName(void)
{
    return reservedName;
}


bool JCIdentifier::isReserved(void)
{
    return (reservedName != snNormal);
}


bool JCIdentifier::isComposed(void)
{
    return (subComponent != NULL);
}


bool JCIdentifier::isMatching(JCIdentifier *anIdent)
{
    if (reservedName != snNormal) {
	return (reservedName == anIdent->reservedName);
     }
    else {
	return (name->isEqual(anIdent->name));
     }
}


// TMP Debug:
void JCIdentifier::dumpInfo(void)
{
    JCIdentifier *tmpSub;

    if (reservedName == snNormal) {
	cout << name->asciiString();
     }
    else {
	switch (reservedName) {
	    case snThis: cout << "this"; break;
	    case snSuper: cout << "super"; break;
	    case snNull: cout << "null"; break;
	    default: cout << "INTERNAL ERROR"; break;
	 }
     }
    if (subComponent != NULL) {
	cout << ".";
	subComponent->dumpInfo();
     }
}

/**************************************************
* Implementation: JCDimIdentifier.
**************************************************/

JCDimIdentifier::JCDimIdentifier()
{
    nbrDimensions= 0;
    name= NULL;
}


bool JCDimIdentifier::setName(JCIdentifier *aName)
{
    name= aName;
    return false;
}


JCIdentifier * JCDimIdentifier::getName(void)
{
    return name;
}


bool JCDimIdentifier::setNbrDimensions(unsigned int aSize)
{
    nbrDimensions= aSize;
    return false;
}


unsigned int JCDimIdentifier::getNbrDimensions(void)
{
    return nbrDimensions;
}

