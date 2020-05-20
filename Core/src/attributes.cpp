/**************************************************
* File: attributes.cc.
* Desc: Implementation of the JCOutAttributes classes.
* Module: AkraLog : JavaKit.
* Rev: 26 novembre 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "actions.h"
#include "lists.h"
#include "compileObjects.h"
#include "compiler.h"
#include "variables.h"
#include "outClassFile.h"
#include "typing.h"
#include "outConstant.h"
#include "compContext.h"
#include "codeBuffer.h"
#include "expressions.h"
#include "nameSpace.h"
#include "attributes.h"


/**************************************************
* Implementation: JCOutAttribute.
**************************************************/

void JCOutAttribute::writeInto(JCOutClassFile *aClassFile)
{
/* Il faut sauver:
    u2 attribute_name_index;
    u4 attribute_length;
    u1 info[attribute_length] => implante par la sous-classe.
*/
    aClassFile->writeUShort(nameIndex);
    aClassFile->writeUInteger(getSize());
}


/**************************************************
* Implementation: JCSrcFileAttr.
**************************************************/

unsigned int JCSrcFileAttr::getSize(void)
{
    return sizeof(unsigned int);
}


/**************************************************
* Implementation: JCConstantAttr.
**************************************************/

unsigned int JCConstantAttr::getSize(void)
{
    return sizeof(unsigned int);
}


/**************************************************
* Implementation: JCCodeAttr.
**************************************************/

JCCodeAttr::JCCodeAttr(JCOutClassFile *classFile)
{
    JCCompilationContext *codeCtxt;

    nameIndex= JCCteUtf8::getWellKnownName(JCCteUtf8::code)->getIndex();
    attributes= new AttributesList;
    maxStack= 0;
    codeBuffer= new JCCodeBuffer();

    codeCtxt= classFile->getCodeContext();
    maxLocals= codeCtxt->currentMethod->mainBlock->getVarCount() + codeCtxt->currentMethod->getNbrArguments();

    // En mode -g, il faut creer des JCLineNbrAttr et des JCLocalVarAttr.

	// Local vars: construites a partir des arguments, puis des var rencontrees dans le mainBlock.
	// Should do the local var attributes only if the compiler must emit debug info in the .class.

	// Note: using 'nbrArguments' doesn't include the implicit variable 'this'.  We don't save any
	// info about that one, it is too redundant.
    if (codeCtxt->currentMethod->nbrArguments > 0) {
	codeCtxt->varDbgInfo= new JCLocalVarAttr(codeCtxt->currentMethod->rawArguments, codeCtxt->currentMethod->nbrArguments);
    }

}


JCCodeAttr::~JCCodeAttr(void)
{
    delete attributes;
    delete handlerTable;
    delete codeBuffer;
}


void JCCodeAttr::generateCode(JCOutClassFile *classFile)
{
    JCCompilationContext *codeCtxt;

    codeCtxt= classFile->getCodeContext();
    prepareSpitting(codeCtxt);
    doMainJob(codeCtxt);
    endSpitting(codeCtxt);

	// Depending on compilation options, we may do a code optimization.
    codeCtxt->optimizeCode();

    saveCode(codeCtxt);
    makeAttributes(codeCtxt);
}


void JCCodeAttr::prepareSpitting(JCCompilationContext *codeContext)
{
	// Nothing to prepare, for the moment.
    return;
}


void JCCodeAttr::doMainJob(JCCompilationContext *codeContext)
{
   // Re-initialise le stack d'etiquettes du compilateur.
    // prend la liste d'actions du main block, et on en fait un spit.
    codeContext->currentMethod->mainBlock->spitTo(codeContext);

}


void JCCodeAttr::endSpitting(JCCompilationContext *codeContext)
{
    codeContext->addImplicitReturn();

}


void JCCodeAttr::saveCode(JCCompilationContext *codeContext)
{
	// Get maximum stack usage, after optimization.
    maxStack= codeContext->getStackDepth();

	// Resolve all addresses and transfer the code.
    codeContext->solveLabels();
    codeContext->dumpCode(codeBuffer);

}


void JCCodeAttr::makeAttributes(JCCompilationContext *codeContext)
{
    handlerTable= codeContext->handlersTable;
    // Transfer the attributes.
	// ATTN: debug attributes are only present if the compiler switch -g is used.
    if (codeContext->hasDebugInfoFor(JCCompileOptions::describeLocalVars)) {
	attributes->addObject(codeContext->varDbgInfo);
    }
    if (codeContext->hasDebugInfoFor(JCCompileOptions::describeLineNumbers)) {
	attributes->addObject(codeContext->lineNbrs);
    }

}


void JCCodeAttr::writeInto(JCOutClassFile *aClassFile)
{
    unsigned int i;

/* Il faut sauver:
    u2 max_stack;
    u2 max_locals;
    u4 code_length;
    u1 code[code_length];
    u2 exception_table_length;
    {
	u2    start_pc;
	u2    end_pc;
	u2    handler_pc;
	u2    catch_type;
    }  exception_table[exception_table_length];
    u2 attributes_count;
    attribute_info attributes[attribute_count];
*/

    JCOutAttribute::writeInto(aClassFile);

    aClassFile->writeUShort(maxStack);
    aClassFile->writeUShort(maxLocals);
    aClassFile->writeUInteger(codeBuffer->getLength());
    codeBuffer->writeInto(aClassFile);
    aClassFile->writeUShort(handlerTable->count());
    for (i= 0; i < handlerTable->count(); i++) {
	handlerTable->objectAt(i)->writeInto(aClassFile);
    }

    aClassFile->writeUShort(attributes->count());
    for (i= 0; i < attributes->count(); i++) {
	attributes->objectAt(i)->writeInto(aClassFile);
    }
}


unsigned int JCCodeAttr::getSize(void)
{
    unsigned int i, attribSize;

    for (attribSize= i= 0; i < attributes->count(); i++) {
// MOD-980507 [HD]: Added the 6 bytes that make the header of an attribute.
	attribSize+= attributes->objectAt(i)->getSize() + 6;
    }

    return 12 + codeBuffer->getLength() + 8 * handlerTable->count() + attribSize;
}


/**************************************************
* Implementation: JCHandlerAttr.
**************************************************/

unsigned int JCHandlerAttr::getInstanceSize(void)
{
    return 4;
}


void JCHandlerAttr::writeInto(JCOutClassFile *aClassFile)
{
    // TODO.
}


/**************************************************
* Implementation: JCExceptionAttr.
**************************************************/

JCExceptionAttr::JCExceptionAttr(JCReferencedType *typeListHead)
{
    JCReferencedType *tmpRefType;
    unsigned int i;

    count= 0;
    do {		// This attribute is created only if there are exceptions, so the list is not null.
	count++;
	tmpRefType= tmpRefType->getNext();
    } while (tmpRefType != NULL);

    exceptionTable= new unsigned int[count];
    i= 0;
    do {		// This attribute is created only if there are exceptions, so the list is not null.
	exceptionTable[i++]= tmpRefType->getTypeShadow()->getIndex();
	tmpRefType= tmpRefType->getNext();
    } while (tmpRefType != NULL);

}


JCExceptionAttr:: ~JCExceptionAttr(void)
{
    delete[] exceptionTable;
}


unsigned int JCExceptionAttr::getCount(void)
{
    return count;
}


unsigned int JCExceptionAttr::getSize(void)
{
    return count * sizeof(int);
}


/**************************************************
* Implementation: JCLocalVarAttr.
**************************************************/

JCLocalVarAttr::JCLocalVarAttr(JCVariableDeclaration *varHead, unsigned int nbrVars)
{
    JCSubLocalVarAttr *tmpSubAttr;

    table= new VarDbgList();

	// ATTN: Is the nbr of vars usefull for anything ??
    while (varHead != NULL) {
	tmpSubAttr= new JCSubLocalVarAttr(varHead);
	table->addObject(tmpSubAttr);
	varHead= varHead->getNext();
    }
}


JCLocalVarAttr::~JCLocalVarAttr(void)
{
    delete table;
}


void JCLocalVarAttr::addDeclarations(JCVariableDeclaration *varHead)
{
    JCSubLocalVarAttr *tmpSubAttr;

    while (varHead != NULL) {
	tmpSubAttr= new JCSubLocalVarAttr(varHead);
	table->addObject(tmpSubAttr);
	varHead= varHead->getNext();
    }
}


unsigned int JCLocalVarAttr::getCount(void)
{
    return table->count();
}


unsigned int JCLocalVarAttr::getSize(void)
{
    return table->count() * JCSubLocalVarAttr::getInstanceSize();
}


/**************************************************
* Implementation: JCLineNbrAttr.
**************************************************/

JCLineNbrAttr::JCLineNbrAttr(void)
{
    table= new LineNbrList();
}


JCLineNbrAttr::~JCLineNbrAttr(void)
{
    delete table;
}


unsigned int JCLineNbrAttr::getCount(void)
{
    return table->count();
}


unsigned int JCLineNbrAttr::getSize(void)
{
    return table->count() * JCSubLineNbrAttr::getInstanceSize();
}


/**************************************************
* Implementation: JCSubLocalVarAttr.
**************************************************/

unsigned int JCSubLocalVarAttr::getInstanceSize(void)
{
    return 10;
}


JCSubLocalVarAttr::JCSubLocalVarAttr(JCVariableDeclaration *varDecl)
{
    startPC= 0;
    length= 0;
    varShadow= varDecl->getShadow();
    slot= varDecl->getIndex();
}


/**************************************************
* Implementation: JCSubLineNbrAttr.
**************************************************/

unsigned int JCSubLineNbrAttr::getInstanceSize(void)
{
    return 4;
}


JCSubLineNbrAttr::JCSubLineNbrAttr(void)
{
    // TODO.
}


#if defined(PLZEN_LEVEL_2)

/**************************************************
* Implementation: JCStateCodeAttr.
**************************************************/

JCStateCodeAttr::JCStateCodeAttr(JCOutClassFile *aClassFile) : JCCodeAttr(aClassFile)
{
    nameIndex= JCCteUtf8::getWellKnownName(JCCteUtf8::stateCode)->getIndex();
}


void JCStateCodeAttr::endSpitting(JCCompilationContext *codeContext)
{
    JCStateInvokeExpr *destination;
    TransitionList *transitions= ((JCStateActionBlock *)((JCState *)codeContext->currentMethod)->mainBlock)->getTransitions();

    codeContext->addImplicitReturn();

    for (unsigned int i= 0; i < transitions->count(); i++) {
	if ((destination= transitions->objectAt(i)->getDestination()) != NULL) {
	    destination->spitTo(codeContext);
	}
    }
}


void JCStateCodeAttr::makeAttributes(JCCompilationContext *codeContext)
{
    JCStateInvokeExpr *destination;
    JCOutAttribute *tmpAttr;
    TransitionList *transitions= ((JCStateActionBlock *)((JCState *)codeContext->currentMethod)->mainBlock)->getTransitions();

    JCCodeAttr::makeAttributes(codeContext);
    // TODO: Genere les attributs pour les sections critiques.

    // TODO: Genere les attributes pour les transitions.
    for (unsigned int i= 0; i < transitions->count(); i++) {
	tmpAttr= new JCTransitionAttr(transitions->objectAt(i), codeContext);
	attributes->addObject(tmpAttr);
    }
}


/**************************************************
* Implementation: JCTransitionAttr.
**************************************************/


JCTransitionAttr::JCTransitionAttr(JCTransition *aTransition, JCCompilationContext *codeContext)
{
    JCExpression *trigger;
    JCStateInvokeExpr *stateDest;
    unsigned int tmpModifiers;

    nameIndex= JCCteUtf8::getWellKnownName(JCCteUtf8::transitions)->getIndex();

    tmpModifiers= aTransition->getModifiers();
    // TODO: Translate the internal modifiers in class-file modifiers.
    modifiers= 0;
    if (tmpModifiers & JCTransition::tmBlocking) {
	modifiers|= blocking;
    }
    if (tmpModifiers & JCTransition::tmImmediate) {
	modifiers|= immediate;
    }
    if (tmpModifiers & JCTransition::tmParallel) {
	modifiers|= parallel;
    }
    if (tmpModifiers & JCTransition::tmImplicit) {
	modifiers|= implicit;
    }

    if (tmpModifiers & JCTransition::tmDefaulter) {
	modifiers|= mDefault;
    }

    if (tmpModifiers & JCTransition::dmPush) {
	modifiers|= push;
    }
    if (tmpModifiers & JCTransition::dmPop) {
	modifiers|= pop;
    }
    if (tmpModifiers & JCTransition::dmRollback) {
	modifiers|= rollback;
    }
    if (tmpModifiers & JCTransition::dmPassby) {
	modifiers|= passby;
    }
    if (tmpModifiers & JCTransition::dmConsume) {
	modifiers|= consume;
    }
    if (tmpModifiers & JCTransition::dmBreak) {
	modifiers|= mBreak;
    }


    if ((trigger= aTransition->getTriggers()) != NULL) {
	if (((JCResolved *)((JCVarAccess *)trigger)->resolution())->getCategory() == JCName::localVariable) {
	    JCVariableDeclaration *aVar= (JCVariableDeclaration *)((JCResolved *)((JCVarAccess *)trigger)->resolution())->getDefinition();
	    event= aVar->getIndex();
	}
	else {
	    JCField *aVar= (JCField *)((JCResolved *)((JCVarAccess *)trigger)->resolution())->getDefinition();
	    event= aVar->getShadow()->getIndex();
	    modifiers|= field;
	}
    }
    else {
	event= 0;
    }

    if ((stateDest= aTransition->getDestination()) != NULL) {
	JCMethod *aMethod= (JCMethod *)((JCResolved *)((JCStateInvokeExpr *)stateDest)->resolution())->getDefinition();
	unsigned int start, stop;

	destination= aMethod->getShadow()->getIndex();
	stateDest->getLabels(start, stop);
	startPC= codeContext->getPcForLabel(start);
    }
    else {
	destination= 0;
	startPC= 0;
    }

}


void JCTransitionAttr::writeInto(JCOutClassFile *aClassFile)
{
    JCOutAttribute::writeInto(aClassFile);

    aClassFile->writeUShort(modifiers);
    aClassFile->writeUShort(event);
    aClassFile->writeUShort(destination);
    aClassFile->writeUInteger(startPC);
}


unsigned int JCTransitionAttr::getSize(void)
{
    return 10;
}



#endif