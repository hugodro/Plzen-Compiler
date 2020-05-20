#ifndef _LISTS_H_
#define _LISTS_H_
/**************************************************
* File: lists.h.
* Desc: Contains the definitions of the different lists used in the compilation process.
* Module: AkraLog : JavaComp.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 6 mars 1997 : REV 0.1 : Hugo DesRosiers: MOD-MSC: ajoute 'public' a toutes les derivations de Generic.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"
#include "labelStack.h"
#include "attributes.h"

class JCReferencedType;
class JCType;
class JCField;
class JCMethod;
class JCState;
class JCStaticInitializer;
class JCOutCFConstant;
class JCImportedPackage;
class JCOpCode;
class JCSubLocalVarAttr;
class JCSubLineNbrAttr;
class JCHandlerAttr;
class JCCteUtf8;
class ostream;
class JCImportedGhost;
class JCUnresolved;
class JCTransition;
#if defined(PLZEN_LEVEL_3)
class JCSqlStatement;
#endif


/* MOD-960701 [HD]: Plus besoin de ca ?
class GenericElement : AkObject {
    GenericElement *prev, *next;
    void *content;
 };
*/


class GenericList : public AkObject {
  protected:
    unsigned int nbrElements;
    unsigned int maxElements;
    void **elements;

  public:
    GenericList(unsigned int initSize);
    GenericList(void);
    virtual ~GenericList(void);

    virtual void init(unsigned int initSize);
    virtual unsigned int count(void);
    virtual bool addObject(void *object);
    virtual bool removeObject(void *object);
    virtual bool removeObjectAt(unsigned int position);
    virtual bool removeLastObject(void);
    virtual void *voidObjectAt(unsigned int position);
    virtual void *lastObject(void);
    virtual void removeAll(void);
 };


class TypesList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCReferencedType *object);
    virtual JCReferencedType *objectAt(unsigned int position);
 };


class FieldsList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCField *object);
    virtual JCField *objectAt(unsigned int position);
 };

class MethodsList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCMethod *object);
    virtual JCMethod *objectAt(unsigned int position);
 };

class StatesList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCState *object);
    virtual JCState *objectAt(unsigned int position);
 };

class InitializersList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCStaticInitializer *object);
    virtual JCStaticInitializer *objectAt(unsigned int position);
 };


class ExpressionsList : public GenericList {
  protected:
  public:
 };


class AttributesList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCOutAttribute *object);
    virtual JCOutAttribute *objectAt(unsigned int position);
};


class VarDbgList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCSubLocalVarAttr *object);
    virtual JCSubLocalVarAttr *objectAt(unsigned int position);
};


class LineNbrList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCSubLineNbrAttr *object);
    virtual JCSubLineNbrAttr *objectAt(unsigned int position);
};


class HandlerList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCHandlerAttr *object);
    virtual JCHandlerAttr *objectAt(unsigned int position);
};


class ConstantsList : public GenericList {
  protected:

  public:
    ConstantsList(unsigned int aSize) : GenericList(aSize) {};

//    getAttributeConstant(JCOutAttribute::Kind aKind);    // TODO.
    virtual bool addObject(JCOutCFConstant *object);
    virtual JCOutCFConstant *objectAt(unsigned int position);
    virtual JCOutCFConstant *findAsciiValue(char *aString);
    virtual void resetInstances(void);
    virtual bool addIndexedObject(JCOutCFConstant *object);
    virtual JCOutCFConstant *findIntValue(int aValue);
    virtual JCOutCFConstant *findFloatValue(float aValue);
    virtual JCOutCFConstant *findLongValue(unsigned int *aValue);
    virtual JCOutCFConstant *findDoubleValue(double aValue);
    virtual JCOutCFConstant *findStringValue(JCCteUtf8 *aValue);
};


class RealTypesList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCType *object);
    virtual JCType *objectAt(unsigned int position);
 };


class PackagesList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCImportedPackage *object);
    virtual JCImportedPackage *objectAt(unsigned int position);
 };


class CountList : public GenericList {
  protected:
  public:
    virtual bool addValue(unsigned int aCount);
    virtual unsigned int getValueAt(unsigned int position);
    virtual void incLastValue(void);
    virtual unsigned int getLastValue(void);
    virtual void removeLastValue(void);
 };


class OpCodeList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCOpCode *object);
    virtual JCOpCode *objectAt(unsigned int position);
    virtual void unassemble(ostream &output);
 };


class LabelList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCAddressLabel *object);
    virtual JCAddressLabel *objectAt(unsigned int position);
    virtual unsigned int backScanFor(JCAddressLabel::Type aType);
 };


class ImportTypeList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCImportedGhost *object);
    virtual JCImportedGhost *objectAt(unsigned int position);
 };


class UnresolvedList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCUnresolved *object);
    virtual JCUnresolved *objectAt(unsigned int position);
};


class TransitionList : public GenericList {
  protected:
  public:
    virtual bool addObject(JCTransition *object);
    virtual JCTransition *objectAt(unsigned int position);
 };


#if defined(PLZEN_LEVEL_3)
/********************************************************
* Class: SqlStatementList.
* Desc: Implements a list manager only interested in adding and then
*	parsing sequentially the elements.
* Class variables:
* Instance variables:
* Super-Class: AkObject.
* Module: JavaKit : Compiler.
********************************************************/

class SqlStatementList : public AkObject {
  protected:
    JCSqlStatement *head;
    JCSqlStatement *tail;

  public:
    SqlStatementList(JCSqlStatement *aStatement);
    virtual void addStatement(JCSqlStatement *aStatement);
    virtual JCSqlStatement *getFirst(void);
};
#endif		/* PLZEN_LEVEL_3 */

#endif	/* _LISTS_H_ */
