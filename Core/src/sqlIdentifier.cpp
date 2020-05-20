/**************************************************
* File: sqlIdentifier.cc.
* Desc: Implementation of the JCSqlIdentifier class.
* Module: AkraLog : JavaKit.
* Rev: 2 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/portableDefs.h>
#include "identifiers.h"
#include "sqlIdentifier.h"


/**************************************************
* Implementation: JCSqlIdentifier.
**************************************************/

JCSqlIdentifier::JCSqlIdentifier(void)
{
    next= NULL;
    moduleFlag= false;
    identifier= NULL;
}


JCSqlIdentifier::JCSqlIdentifier(JCIdentifier *anIdent)
{
    next= NULL;
    moduleFlag= false;
    identifier= anIdent;
}


void JCSqlIdentifier::addComponent(JCIdentifier *anIdent)
{
    identifier->addComponent(anIdent);
}


void JCSqlIdentifier::link(JCSqlIdentifier *anIdent)
{
    next= anIdent;
}


JCSqlIdentifier *JCSqlIdentifier::getNext(void)
{
    return next;
}


void JCSqlIdentifier::setModuleHeader(void)
{
    moduleFlag= true;
}


bool JCSqlIdentifier::isModuleHeader(void)
{
    return moduleFlag;
}


JCIdentifier *JCSqlIdentifier::getSimpleIdentifier(void)
{
    return identifier;
}


/**************************************************
* Implementation: JCSqlIdentList.
**************************************************/

JCSqlIdentList::JCSqlIdentList(JCSqlIdentifier *anIdent)
{
    nbrElements=1;
    elements= lastElement= anIdent;
}


void JCSqlIdentList::addElement(JCSqlIdentifier *anIdent)
{
    if (nbrElements == 0) {
	elements= anIdent;
    }
    else {
	lastElement->link(anIdent);
    }
    nbrElements++;
    lastElement= anIdent;
}


unsigned int JCSqlIdentList::count(void)
{
    return nbrElements;
}


JCSqlIdentifier *JCSqlIdentList::getFirstElement(void)
{
    return elements;
}

