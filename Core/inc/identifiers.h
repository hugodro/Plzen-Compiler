#ifndef _IDENTIFIERS_H_
#define _IDENTIFIERS_H_
/**************************************************
* File: identifiers.h.
* Desc: Contains the definitions of classes used to manage identifiers.
* Module: AkraLog : JavaComp.
* Rev: 5 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"


class JCReferencedType;
class JCCteUtf8;


class JCIdentifier : public AkObject {
  public:
    enum SpecialName {
	snNormal= 0, snThis, snSuper, snNull, snFinalCatch
    };

  public:		// Class methods.
    static JCIdentifier *getFromPathName(char *aFullName, unsigned int nameLength);

  protected:
    JCIdentifier *next;			// Next element in a list of identifiers.
    JCCteUtf8 *name;		// Name of the Identifier.
    SpecialName reservedName;	// Indicates that the identifier has a special name (this, super, null).
    unsigned int category;		// 0 indicates 'unknown', (var, type, package, etc).
    JCIdentifier *subComponent;	// Next component of a Qualifed identifier.

  public:
    JCIdentifier::JCIdentifier();
    JCIdentifier::JCIdentifier(JCCteUtf8 *aName);
    virtual void link(JCIdentifier *nextIdent);
    virtual JCIdentifier *getNext(void);
 
    virtual bool setValue(JCCteUtf8 *aNameCte);
//    virtual bool setNarrowValue(char *aName);    ATTN: SHOULD GO.
    virtual JCCteUtf8 *getValue(void);
    virtual char *getAsciiValue(void);
    virtual unsigned int nameLength(void);
 
    virtual bool addComponent(JCIdentifier *nextComponent);
    virtual JCIdentifier *getComponent(void);
    virtual JCIdentifier *removeSuffix(void);	// Return the suffix which is removed.
    virtual JCIdentifier *removePrefix(void);	// Return what is the new prefix.
    virtual void resolveToSelf(void);
    virtual void resolveToSuper(void);
    virtual void resolveToNull(void);
    virtual void resolveToFinalCatcher(void);
    virtual SpecialName getSpecialName(void);
    virtual bool isReserved(void);
    virtual bool isComposed(void);

    virtual bool isMatching(JCIdentifier *anIdent);

    virtual void dumpInfo(void);
 };


class JCDimIdentifier : public AkObject {
  protected:
    unsigned int nbrDimensions;
    JCIdentifier *name;			// Name of the DimIdentifier.

  public:
    JCDimIdentifier::JCDimIdentifier();
    virtual bool setName(JCIdentifier *aName);
    virtual JCIdentifier * getName(void);
    virtual bool setNbrDimensions(unsigned int aSize);
    virtual unsigned int getNbrDimensions(void);
 };


#endif	/* _IDENTIFIERS_H_ */
