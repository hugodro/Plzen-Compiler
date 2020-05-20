#ifndef _JCCOMPCONTEXT_H_
#define _JCCOMPCONTEXT_H_
/**************************************************
* File: compContext.h.
* Desc: Contains the definition of the byte-code compilation context.
* Module: AkraLog : JavaComp.
* Rev: 7 janvier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"
#include "labelStack.h"
#include "options.h"
#include "instructions.h"


class JCLabelStack;
class JCMethod;
class JCIdentifier;
class JCExpression;
class JCReferencedType;
class JCCompiler;
class JCOutAttribute;
class JCVariableDeclaration;
class JCCodeBuffer;
class JCLineNbrAttr;
class JCLocalVarAttr;
class HandlerList;
class JCSubExceptAttr;

class JCCompilationContext : public AkObject {
    friend class JCCodeAttr;
    friend class JCStateCodeAttr;

  protected:
    JCCompiler *owner;
    JCLabelStack *labels;
    JCMethod *currentMethod;
    unsigned int maxStackDepth;
    unsigned int stackDepth;
    bool doingAssignment;
    OpCodeList *instructions;		// Assembly instructions.
    unsigned int currentPC;		// Approximate PC counter.
	// Attributes for a Code section.
    JCLineNbrAttr *lineNbrs;		// Holds the line number mapping generated during the 'spitTo'.
    JCLocalVarAttr *varDbgInfo;	// Holds the local var info generated during the 'spitTo'.
    HandlerList *handlersTable;	// Holds the handlers block hit during the 'spitTo'.

  public:
    JCCompilationContext(JCCompiler *aCompiler);
    virtual void startMethod(JCMethod *aMethod);
    virtual void endMethod(void);
    virtual void defineNamedLabel(JCIdentifier *aName);
    virtual void defineCaseLabel(JCExpression *anExpr);
    virtual void defineDefaultLabel(void);
    virtual void defineLabel(unsigned int labelID);
    virtual unsigned int getLabelBlock(unsigned int aCount, JCAddressLabel::Type aType);
    virtual void deleteLabelBlock(unsigned int aCount);
    virtual void solveLabels(void);
    virtual void addInstruction(JCInstrSet::Instructions aCode);
    virtual void addInstruction(JCInstrSet::Instructions aCode, unsigned int anArgument);
    virtual void addInstruction(JCInstrSet::Instructions aCode, unsigned int firstArg, unsigned int secondArg);
    virtual void addInstruction(JCInstrSet::Instructions aCode, JCReferencedType *aType);
    virtual void addInstruction(JCInstrSet::Instructions aCode, unsigned int anArgument, JCReferencedType *aType);
    virtual void handleNamedBreak(JCIdentifier *aName);
    virtual void handleNamedContinue(JCIdentifier *aName);
    virtual unsigned int getCurrentPC(void);
    virtual void startHandler(unsigned int startPC, unsigned int endPC, JCVariableDeclaration *aTrapDecl);
    virtual void endHandler(void);
    virtual bool isAssigning(void);
    virtual void setIfAssigning(bool aValue);
    virtual void addTestBranch(void);
    virtual void addCteMinusOne(JCReferencedType *aType);
    virtual void startTryBlock(void);
    virtual void endTryBlock(void);
    virtual void optimizeCode(void);
    virtual unsigned int getStackDepth(void);
    virtual void dumpCode(JCCodeBuffer *aBuffer);
    virtual void addVarInfo(JCVariableDeclaration *varDecls);
    virtual unsigned int getLabel(JCAddressLabel::Type aType);
    virtual bool hasDebugInfoFor(JCCompileOptions::BasicOptions anOption);
    virtual void addImplicitReturn(void);
    virtual unsigned int getPcForLabel(unsigned int labelID);
};


#endif		/* _JCCOMPCONTEXT_H_ */
