#ifndef _VARIABLES_H_
#define _VARIABLES_H_
/**************************************************
* File: variables.h.
* Desc: Contains the definitions of the classes used to manage variables declarations.
* Module: AkraLog : JavaComp.
* Rev: 5 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"


class JCReferencedType;
class JCDimIdentifier;
class JCExpression;
class JCCteNameAndType;
class ConstantsList;

class JCVariableDeclaration : public AkObject {
  private:
    JCVariableDeclaration *next;
    JCDimIdentifier *name;
    JCReferencedType *type;
    JCExpression *initializer;
    JCCteNameAndType *shadow;	// Used only for the debugging attributes.
    unsigned int index;		// Index of the variable in the exec frame.
    unsigned int accessCount;
    unsigned int assignCount;

  public:
    JCVariableDeclaration::JCVariableDeclaration();
    virtual void link(JCVariableDeclaration *nextDecl);
    virtual JCVariableDeclaration *getNext(void);
    virtual bool setName(JCDimIdentifier *anIdent);
    virtual JCIdentifier *getUndimIdentifier(void);
    virtual bool setInitializator(JCExpression *anExpression);
    virtual bool setTyping(JCReferencedType *aType);
    virtual JCReferencedType *typing(void);
    virtual bool hasComplexType(void);
    virtual JCIdentifier *getTypeName(void);
    virtual unsigned int getNbrDimensions(void);
    virtual JCDimIdentifier *getName();
    virtual JCExpression *getInitializer(void);
    virtual void mapToPool(ConstantsList *aPool);
    virtual bool isResolved(void);	// return the resolution status of its refType.
    virtual void setIndex(unsigned int anIndex);
    virtual bool incAccess(void);
    virtual void incAssign(void);
    virtual JCCteNameAndType *getShadow(void);
    virtual unsigned int getIndex(void);
    virtual bool hasWideType(void);
};


#endif	/* _VARIABLES_H_ */
