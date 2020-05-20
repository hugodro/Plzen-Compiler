/**************************************************
* File: labelStack.cc.
* Desc: Contains the implementation of the address labels management classes.
* Module: AkraLog : JavaComp.
* Rev: 24 janvier 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "lists.h"
#include "labelStack.h"


/**************************************************
* Implementation: JCAddressLabel.
**************************************************/

JCAddressLabel::JCAddressLabel(void)
{
    pcLocation= 0;
    type= innerLabel;
    assigned= false;
    users= new OpCodeList();
}


JCAddressLabel::~JCAddressLabel(void)
{
    delete users;
}


int JCAddressLabel::distanceFrom(unsigned int aPosition)
{
    return (int)pcLocation - (int)aPosition;
}


void JCAddressLabel::addUser(JCOpCode *anOpcode)
{
    users->addObject(anOpcode);
}


void JCAddressLabel::defineAs(unsigned int instrOffset, unsigned int anAddress)
{
    assigned= true;
    value= instrOffset;
    pcLocation= anAddress;
}


unsigned int JCAddressLabel::getValue(void)
{
    return value;
}


unsigned int JCAddressLabel::getPCLocation(void)
{
    return pcLocation;
}


/**************************************************
* Implementation: JCLabelStack.
**************************************************/

JCLabelStack::JCLabelStack(void)
{
    labels= new LabelList();
    definedNewLabel= false;
}


JCLabelStack::~JCLabelStack(void)
{
    delete labels;
}


void JCLabelStack::reset(void)
{
    // TODO.
}


unsigned int JCLabelStack::allocBlock(unsigned int aSize, JCAddressLabel::Type aType)
{
    JCAddressLabel *tmpLabels;

	// ATTN: Create new labels according to the desired type.
    tmpLabels= new JCAddressLabel[aSize];

    tmpLabels[0].type= aType;
    for (unsigned int i= 0; i < aSize; i++) {
	labels->addObject(&tmpLabels[i]);
    }
    return labels->count() - aSize;
}


bool JCLabelStack::freeBlock(void)
{
    // TODO.
    return true;
}


JCAddressLabel *JCLabelStack::objectAt(unsigned int anOffset)
{
    return labels->objectAt(anOffset);
}


bool JCLabelStack::define(unsigned int anID, unsigned int instrOffset, unsigned int pc)
{
    JCAddressLabel *tmpLabel;

    tmpLabel= labels->objectAt(anID);
    if (tmpLabel != NULL) {
	tmpLabel->defineAs(instrOffset, pc);
    }
    definedNewLabel= false;
    return true;	/* MOD-MSC: Ajoute le 'return'. */
}


unsigned int JCLabelStack::backScanFor(JCAddressLabel::Type aType)
{
    return labels->backScanFor(aType);
}


bool JCLabelStack::flushNewLabel(void)
{
    if (definedNewLabel) {
	definedNewLabel= false;
	return true;		// Warning: quick exit.
    }
    return false;
}


