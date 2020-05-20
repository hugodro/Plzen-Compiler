/**************************************************
* File: lists.cc.
* Desc: Contains the definitions of the different lists used in the compilation process.
* Module: AkraLog : JavaComp.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <stdio.h>
#include <memory.h>
}
#include <iostream.h>
#include "outConstant.h"
#include "opcode.h"
#if defined(PLZEN_LEVEL_3)
#include "sqlActions.h"
#endif
#include "lists.h"


/**************************************************
* Implementation: GenericList.
**************************************************/

GenericList::GenericList()
{
    init(32);
}


GenericList::GenericList(unsigned int initSize)
{
    init(initSize);
}


GenericList::~GenericList(void)
{
    delete[] elements;
}

void GenericList::init(unsigned int initSize)
{
    maxElements= initSize;
    elements= new void*[maxElements];
    memset(elements, 0, maxElements);
    nbrElements= 0;
}


unsigned int GenericList::count(void)
{
    return nbrElements;
}


bool GenericList::addObject(void *object)
{
    if (nbrElements < maxElements) {
	elements[nbrElements++]= object;
     }
    else {
	maxElements*=  2;
	void **tmpElements= new void *[maxElements];
	memcpy(tmpElements, elements, sizeof(void *) * nbrElements);
	tmpElements[nbrElements++]= object;
	elements= tmpElements;
     }

    return true;	// ATTN: Should do a memory check and return conditional result.
}


bool GenericList::removeObject(void *object)
{
    bool result= false;
    for (unsigned int i= 0; i < nbrElements; i++) {
	if (elements[i] == object) {
	    result= true;
	    for (unsigned int j= i+1; j < nbrElements; j++, i++) {
		elements[i]= elements[j];
	    }
	    break;
	}
    }

    return result;
}


bool GenericList::removeObjectAt(unsigned int position)
{
    bool result= true;

    if (position < nbrElements) {
	elements[position]= NULL;
     }
    else result= false;

    return result;
}


bool GenericList::removeLastObject(void)
{
    bool result= true;

    if (nbrElements > 0) {
	nbrElements--;
	elements[nbrElements]= NULL;
     }
    else result= false;
    return result;
}


void *GenericList::voidObjectAt(unsigned int position)
{
    void *result= NULL;
    if (position < nbrElements) {
	result= elements[position];
     }

    return result;
}


void *GenericList::lastObject(void)
{
    void *result= NULL;
    if (nbrElements > 0) {
	result= elements[nbrElements-1];
     }

    return result;
}


void GenericList::removeAll(void)
{
    for (unsigned int i= 0; i < nbrElements; i++) elements[i]= NULL;
    nbrElements= 0;
}


/**************************************************
* Implementation: TypesList.
**************************************************/

bool TypesList::addObject(JCReferencedType *object)
{
    return GenericList::addObject((void *)object);
}


JCReferencedType *TypesList::objectAt(unsigned int position)
{
    return (JCReferencedType *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: FieldsList.
**************************************************/

bool FieldsList::addObject(JCField *object)
{
    return GenericList::addObject((void *)object);
}


JCField *FieldsList::objectAt(unsigned int position)
{
    return (JCField *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: MethodsList.
**************************************************/

bool MethodsList::addObject(JCMethod *object)
{
    return GenericList::addObject((void *)object);
}


JCMethod *MethodsList::objectAt(unsigned int position)
{
    return (JCMethod *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: StatesList.
**************************************************/

bool StatesList::addObject(JCState *object)
{
    return GenericList::addObject((void *)object);
}


JCState *StatesList::objectAt(unsigned int position)
{
    return (JCState *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: InitializersList.
**************************************************/

bool InitializersList::addObject(JCStaticInitializer *object)
{
    return GenericList::addObject((void *)object);
}


JCStaticInitializer *InitializersList::objectAt(unsigned int position)
{
    return (JCStaticInitializer *)GenericList::voidObjectAt(position);
}



/**************************************************
* Implementation: AttributesList.
**************************************************/

bool AttributesList::addObject(JCOutAttribute *object)
{
    return GenericList::addObject((void *)object);
}


JCOutAttribute *AttributesList::objectAt(unsigned int position)
{
    return (JCOutAttribute *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: VarDbgList.
**************************************************/

bool VarDbgList::addObject(JCSubLocalVarAttr *object)
{
    return GenericList::addObject((void *)object);
}


JCSubLocalVarAttr *VarDbgList::objectAt(unsigned int position)
{
    return (JCSubLocalVarAttr *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: LineNbrList.
**************************************************/

bool LineNbrList::addObject(JCSubLineNbrAttr *object)
{
    return GenericList::addObject((void *)object);
}


JCSubLineNbrAttr *LineNbrList::objectAt(unsigned int position)
{
    return (JCSubLineNbrAttr *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: HandlerList.
**************************************************/

bool HandlerList::addObject(JCHandlerAttr *object)
{
    return GenericList::addObject((void *)object);
}


JCHandlerAttr *HandlerList::objectAt(unsigned int position)
{
    return (JCHandlerAttr *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: ConstantsList.
**************************************************/

bool ConstantsList::addObject(JCOutCFConstant *object)
{
    return GenericList::addObject((void *)object);
}


JCOutCFConstant *ConstantsList::objectAt(unsigned int position)
{
    return (JCOutCFConstant *)GenericList::voidObjectAt(position);
}


JCOutCFConstant *ConstantsList::findAsciiValue(char *aString)
{
    for (unsigned int i= 0; i < nbrElements; i++) {
	if (((JCCteUtf8 *)elements[i])->isAsciiEqual((unsigned char *)aString)) {
	    return ((JCOutCFConstant *)elements[i]);
	}
    }
   return NULL;
}


void ConstantsList::resetInstances(void)
{
    for (unsigned int i= 0; i < nbrElements; i++) {
	((JCOutCFConstant *)elements[i])->resetIndex();
    }
}


bool ConstantsList::addIndexedObject(JCOutCFConstant *object)
{
    if (object->hasNullIndex()) {
	bool tmpResult= GenericList::addObject((void *)object);
	if (tmpResult) object->setIndex(nbrElements);
	return tmpResult;
    }
    else return true;
}


JCOutCFConstant *ConstantsList::findIntValue(int aValue)
{
    for (unsigned int i= 0; i < nbrElements; i++) {
	if (((JCCteInteger *)elements[i])->isEqual(aValue)) {
	    return ((JCOutCFConstant *)elements[i]);
	}
    }
   return NULL;
}


JCOutCFConstant *ConstantsList::findFloatValue(float aValue)
{
    for (unsigned int i= 0; i < nbrElements; i++) {
	if (((JCCteFloat *)elements[i])->isEqual(aValue)) {
	    return ((JCOutCFConstant *)elements[i]);
	}
    }
   return NULL;
}


JCOutCFConstant *ConstantsList::findLongValue(unsigned int *aValue)
{
    for (unsigned int i= 0; i < nbrElements; i++) {
	if (((JCCteLong *)elements[i])->isEqual(aValue)) {
	    return ((JCOutCFConstant *)elements[i]);
	}
    }
   return NULL;
}


JCOutCFConstant *ConstantsList::findDoubleValue(double aValue)
{
    for (unsigned int i= 0; i < nbrElements; i++) {
	if (((JCCteDouble *)elements[i])->isEqual(aValue)) {
	    return ((JCOutCFConstant *)elements[i]);
	}
    }
   return NULL;
}


JCOutCFConstant *ConstantsList::findStringValue(JCCteUtf8 *aValue)
{
    for (unsigned int i= 0; i < nbrElements; i++) {
	if (((JCCteString *)elements[i])->isEqual(aValue)) {
	    return ((JCOutCFConstant *)elements[i]);
	}
    }
    return NULL;
}


/**************************************************
* Implementation: RealTypesList.
**************************************************/

bool RealTypesList::addObject(JCType *object)
{
    return GenericList::addObject((void *)object);
}


JCType *RealTypesList::objectAt(unsigned int position)
{
    return (JCType *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: PackagesList.
**************************************************/

bool PackagesList::addObject(JCImportedPackage *object)
{
    return GenericList::addObject((void *)object);
}


JCImportedPackage *PackagesList::objectAt(unsigned int position)
{
    return (JCImportedPackage *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: CountList.
**************************************************/

bool CountList::addValue(unsigned int aCount)
{
    return GenericList::addObject((void *)aCount);
}


unsigned int CountList::getValueAt(unsigned int position)
{
    return (unsigned int)GenericList::voidObjectAt(position);
}


void CountList::incLastValue(void)
{
    ((unsigned int *)elements)[nbrElements-1]++;
}


unsigned int CountList::getLastValue(void)
{
    return (unsigned int)GenericList::lastObject();
}


void CountList::removeLastValue(void)
{
    GenericList::removeLastObject();
}


/**************************************************
* Implementation: OpCodeList.
**************************************************/

bool OpCodeList::addObject(JCOpCode *object)
{
    return GenericList::addObject((void *)object);
}


JCOpCode *OpCodeList::objectAt(unsigned int position)
{
    return (JCOpCode *)GenericList::voidObjectAt(position);
}


void OpCodeList::unassemble(ostream &output)
{
    unsigned int i, offset;
    char tmpBuffer[256];

    for (i= 0; i < nbrElements; i++) {
	sprintf(tmpBuffer, "%d:\t", i);
	offset= (i < 10) ? 3 : (i < 100) ? 4 : (i < 1000) ? 5 : (i < 10000) ? 6 : 7;
	((JCOpCode *)elements[i])->unassemble(tmpBuffer+offset);
	output << tmpBuffer;
    }
}


/**************************************************
* Implementation: LabelList.
**************************************************/

bool LabelList::addObject(JCAddressLabel *object)
{
    return GenericList::addObject((void *)object);
}


JCAddressLabel *LabelList::objectAt(unsigned int position)
{
    return (JCAddressLabel *)GenericList::voidObjectAt(position);
}


unsigned int LabelList::backScanFor(JCAddressLabel::Type aType)
{
    unsigned int i;

    if (aType == JCAddressLabel::breakScan) {
	for (i= nbrElements; i > 0;) {
	    i--;
	    if ((((JCAddressLabel *)elements[i])->type == JCAddressLabel::switchType)
		    || (((JCAddressLabel *)elements[i])->type == JCAddressLabel::whileType)
		    || (((JCAddressLabel *)elements[i])->type == JCAddressLabel::doType)
		    || (((JCAddressLabel *)elements[i])->type == JCAddressLabel::forType)) {
		return i;
	    }
	}
    }
    else if (aType == JCAddressLabel::continueScan) {
	for (i= nbrElements; i > 0;) {
	    i--;
	    if ((((JCAddressLabel *)elements[i])->type == JCAddressLabel::whileType)
		    || (((JCAddressLabel *)elements[i])->type == JCAddressLabel::doType)
		    || (((JCAddressLabel *)elements[i])->type == JCAddressLabel::forType)) {
		return i+2;
	    }
	}
    }
    return 0;	    /* MOD-MSC: Ajoute le return. */
}


/**************************************************
* Implementation: ImportTypeList.
**************************************************/

bool ImportTypeList::addObject(JCImportedGhost *object)
{
    return GenericList::addObject((void *)object);
}


JCImportedGhost *ImportTypeList::objectAt(unsigned int position)
{
    return (JCImportedGhost *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: UnresolvedList.
**************************************************/

bool UnresolvedList::addObject(JCUnresolved *object)
{
    return GenericList::addObject((void *)object);
}


JCUnresolved *UnresolvedList::objectAt(unsigned int position)
{
    return (JCUnresolved *)GenericList::voidObjectAt(position);
}


/**************************************************
* Implementation: TransitionList.
**************************************************/

bool TransitionList::addObject(JCTransition *object)
{
    return GenericList::addObject((void *)object);
}


JCTransition *TransitionList::objectAt(unsigned int position)
{
    return (JCTransition *)GenericList::voidObjectAt(position);
}


#if defined(PLZEN_LEVEL_3)
/**************************************************
* Implementation: SqlStatementList.
**************************************************/

SqlStatementList::SqlStatementList(JCSqlStatement *aStatement)
{
    tail= head= aStatement;
}


void SqlStatementList::addStatement(JCSqlStatement *aStatement)
{
    if (tail != NULL) {
	tail->link(aStatement);
    }
    else {
	head= aStatement;	// The head should always be in sync with the tail.
    }
    tail= aStatement;
}


JCSqlStatement *SqlStatementList::getFirst(void)
{
    return head;
}

#endif

