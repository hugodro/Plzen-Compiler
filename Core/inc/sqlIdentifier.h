#ifndef _SQLIDENTIFIER_H_
#define _SQLIDENTIFIER_H_
/**************************************************
* File: sqlIdentifier.h.
* Desc: Definition of the JCSqlIdentifier class.
* Module: AkraLog : JavaKit.
* Rev: 2 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>


class JCIdentifier;


class JCSqlIdentifier : public AkObject {
  protected:
    JCSqlIdentifier *next;
    JCIdentifier *identifier;
    bool moduleFlag;

  public:
    JCSqlIdentifier(void);
    JCSqlIdentifier(JCIdentifier *anIdent);
    virtual void addComponent(JCIdentifier *anIdent);
    virtual void link(JCSqlIdentifier *anIdent);
    virtual JCSqlIdentifier *getNext(void);
    virtual void setModuleHeader(void);
    virtual bool isModuleHeader(void);
    virtual JCIdentifier *getSimpleIdentifier(void);
};


class JCSqlIdentList : public AkObject {
  protected:
    unsigned int nbrElements;
    JCSqlIdentifier *elements, *lastElement;

  public:
    JCSqlIdentList(JCSqlIdentifier *anIdent);
    virtual void addElement(JCSqlIdentifier *anIdent);
    virtual unsigned int count(void);
    virtual JCSqlIdentifier *getFirstElement(void);
};

#endif	/* _SQLIDENTIFIER_H_ */
