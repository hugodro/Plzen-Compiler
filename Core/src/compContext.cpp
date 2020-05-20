/**************************************************
* File: compContext.cc.
* Desc: Contains the definition of the byte-code compilation context.
* Module: AkraLog : JavaComp.
* Rev: 7 janvier 1997 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 6 mars 1997 : REV 0.1 : Hugo DesRosiers : Compilation sur MSVC++.
**************************************************/

/* MOD-MSC: Corrige des 'JCInstrSet' qui manquait devant des constantes, et
    change les "<< aCode" pour des "<< (int)aCode".
*/
												  
#include <stdlib.h>			// Used for 'abs' definition.
#include <iostream.h>
#include "labelStack.h"
#include "lists.h"
#include "codeBuffer.h"
#include "opcode.h"
#include "typing.h"
#include "constants.h"
#include "compileObjects.h"
#include "compContext.h"


/**************************************************
* Implementation: JCCompilationContext.
**************************************************/

JCCompilationContext::JCCompilationContext(JCCompiler *aCompiler)
{
    owner= aCompiler;
    labels= new JCLabelStack();
    currentMethod= NULL;
    instructions= new OpCodeList();
    lineNbrs= NULL;
    varDbgInfo= NULL;
    handlersTable= new HandlerList();
}


void JCCompilationContext::startMethod(JCMethod *aMethod)
{
    labels->reset();
    instructions->removeAll();
    currentMethod= aMethod;
    maxStackDepth= stackDepth= 0;
    doingAssignment= false;
    lineNbrs= new JCLineNbrAttr();
    varDbgInfo= NULL;
    handlersTable->removeAll();
    currentPC= 0;
}


void JCCompilationContext::endMethod(void)
{
	// ATTN: What to do at end of a main block compilation ?
	// Ceci a lieu lorsqu'on a fait l'attribut 'Code', qui lui meme a fait la
	// compilation et la generation de tous les attributs internes a 'Code'.
    // The code buffer and the attributes have be flushed to something.

    currentMethod= NULL;
    lineNbrs= NULL;
    varDbgInfo= NULL;
}


void JCCompilationContext::defineNamedLabel(JCIdentifier *aName)
{
    // TODO.
}


void JCCompilationContext::defineCaseLabel(JCExpression *anExpr)
{
    // TODO.
}


void JCCompilationContext::defineDefaultLabel(void)
{
    // TODO.
}


void JCCompilationContext::defineLabel(unsigned int labelID)
{
    labels->define(labelID, instructions->count(), currentPC);
}


unsigned int JCCompilationContext::getLabelBlock(unsigned int aCount, JCAddressLabel::Type aType)
{
    return labels->allocBlock(aCount, aType);    // ATTN: Should check for allocBlock error.
}


void JCCompilationContext::deleteLabelBlock(unsigned int aCount)
{
    // TODO: all labels in the block should now be defined.
}


void JCCompilationContext::solveLabels(void)
{
    // TODO: resolve actual addresses of all labels.
    // ATTN: Is there anything to do ? Destinations are computed at address
    // definition (defineLabel).
}


void JCCompilationContext::addInstruction(JCInstrSet::Instructions aCode)
{
    JCSimpleOpcode *tmpOpCode;

    tmpOpCode= new JCSimpleOpcode(aCode);
    tmpOpCode->setLabelArrival(labels->flushNewLabel());
    instructions->addObject(tmpOpCode);
    currentPC+= JCInstrSet::getSizeOf(aCode);
    stackDepth+= JCInstrSet::getStackUseOf(aCode);
    if (stackDepth > maxStackDepth) maxStackDepth= stackDepth;
}


// NOTE: addInstruction fix a given instruction, so that it uses the right
// form instead of the given generic one.

void JCCompilationContext::addInstruction(JCInstrSet::Instructions aCode, unsigned int anArgument)
{
    JCAddressLabel *tmpLabel;
    JCOpCode *newOpcode;
    int distance;

    switch(aCode) {
	    // Label users, with compact (+/- 32k bytes range) and long form (+/- 2g bytes range).
	case JCInstrSet::goto_n:
	case JCInstrSet::jsr:
	    tmpLabel= labels->objectAt(anArgument);
	    if (abs((distance= tmpLabel->distanceFrom(currentPC))) >  32767) {
		    // We switch to long form of the instruction.
		if (aCode == JCInstrSet::goto_n)
		    aCode= JCInstrSet::goto_w;
		else
		    aCode= JCInstrSet::jsr_w;
	    }
	    newOpcode= new JCBranchOpcode(aCode, tmpLabel, currentPC);
	    newOpcode->setLabelArrival(labels->flushNewLabel());
	    tmpLabel->addUser(newOpcode);
	    instructions->addObject(newOpcode);
	    break;
	    // Label users, with unique form (+/- 32k bytes range).
	case JCInstrSet::ifeq:
	case JCInstrSet::ifne:
	case JCInstrSet::iflt:
	case JCInstrSet::ifle:
	case JCInstrSet::ifge:
	case JCInstrSet::ifgt:
	case JCInstrSet::if_icmpeq:
	case JCInstrSet::if_icmpne:
	case JCInstrSet::if_icmplt:
	case JCInstrSet::if_icmple:
	case JCInstrSet::if_icmpge:
	case JCInstrSet::if_icmpgt:
	case JCInstrSet::if_acmpeq:
	case JCInstrSet::if_acmpne:
	case JCInstrSet::ifnull:
	case JCInstrSet::ifnonnull:
	    tmpLabel= labels->objectAt(anArgument);
	    newOpcode= new JCBranchOpcode(aCode, tmpLabel, currentPC);
	    if (abs((distance= tmpLabel->distanceFrom(currentPC))) >  32767) {
		// ATTN: must inverse the test and branch after a goto_w, and put a
		// goto_w to the destination.
		cout << "ERRMSG: long jump necessary for instruction " << (int)aCode << ", not done !\n";
	    }
	    else {
		tmpLabel->addUser(newOpcode);
	    }
	    newOpcode->setLabelArrival(labels->flushNewLabel());
	    instructions->addObject(newOpcode);
	    break;

	    // Constant pool index users, unique form:
	case JCInstrSet::getfield:
	case JCInstrSet::getstatic:
	case JCInstrSet::putfield:
	case JCInstrSet::putstatic:
	case JCInstrSet::invokevirtual:
	case JCInstrSet::invokenonvirtual:
	case JCInstrSet::invokestatic:
	case JCInstrSet::instanceof:
	case JCInstrSet::checkcast:
	case JCInstrSet::anew:
	case JCInstrSet::anewarray:
#if defined(PLZEN_LEVEL_2)
	case JCInstrSet::fire:
	case JCInstrSet::firestatic:
	case JCInstrSet::firefield:
	case JCInstrSet::wait:
#endif
	    newOpcode= new JCPoolOpcode(aCode, anArgument);
	    newOpcode->setLabelArrival(labels->flushNewLabel());
	    instructions->addObject(newOpcode);
	    break;

	    // Local variable operators, optimized, compact and long form:
	case JCInstrSet::iload:
	case JCInstrSet::fload:
	case JCInstrSet::lload:
	case JCInstrSet::dload:
	case JCInstrSet::aload:
	case JCInstrSet::istore:
	case JCInstrSet::fstore:
	case JCInstrSet::lstore:
	case JCInstrSet::dstore:
	case JCInstrSet::astore:
	    if (anArgument > 3) {
		if (anArgument > 255) {
		    if (anArgument > 65535) {
			cout << "ERRMSG: index overflow for instruction " << (int)aCode << " !\n";
		    }

			// Insert long form index.
		    newOpcode= new JCByteOpcode(JCInstrSet::wide, (unsigned char)((anArgument & 0x0FF00) >> 8));
		    newOpcode->setLabelArrival(labels->flushNewLabel());
		    instructions->addObject(newOpcode);
		    currentPC+= JCInstrSet::getSizeOf(JCInstrSet::wide);
		    anArgument&= 0x0FF;
		}
		newOpcode= new JCByteOpcode(aCode, (unsigned char)anArgument);
		instructions->addObject(newOpcode);
	    }
	    else {
			// Find optimized operation.
		aCode= JCInstrSet::getOptimizedVersion(aCode, anArgument);
		if (aCode == 0) {
		    cout << "ERRMSG: Internal corrupted code (can't recognize load/store short form).\n";
		}
		newOpcode= new JCSimpleOpcode(aCode);
		newOpcode->setLabelArrival(labels->flushNewLabel());
		instructions->addObject(newOpcode);
	    }
	    break;

	    // Constant pool user, compact and long form:
	case JCInstrSet::ret:
	case JCInstrSet::ldc1:
	    if (anArgument > 255) {
		if (anArgument > 65535) {
		    cout << "ERRMSG: index overflow for instruction " << (int)aCode << " !\n";
		}
		newOpcode= new JCPoolOpcode((aCode == JCInstrSet::ldc1) ?
				(aCode= JCInstrSet::ldc2) : (aCode= JCInstrSet::ret_w), anArgument);
	    }
	    else {
		newOpcode= new JCByteOpcode(aCode, (unsigned char)anArgument);
	    }
	    newOpcode->setLabelArrival(labels->flushNewLabel());
	    instructions->addObject(newOpcode);
	    break;

	case JCInstrSet::ldc2w:
	    if (anArgument > 65535) {
		cout << "ERRMSG: ldc2w index overflow !\n";
	    }
	    newOpcode= new JCShortOpcode(JCInstrSet::ldc2w, (unsigned short)anArgument);
	    newOpcode->setLabelArrival(labels->flushNewLabel());
	    instructions->addObject(newOpcode);
	    break;

		// Byte opcode users.
	case JCInstrSet::bipush:
	case JCInstrSet::newarray:
	    newOpcode= new JCByteOpcode(aCode, (unsigned char)anArgument);
	    newOpcode->setLabelArrival(labels->flushNewLabel());
	    instructions->addObject(newOpcode);
	    break;

		// Short opcode users.
	case JCInstrSet::sipush:
	    newOpcode= new JCShortOpcode(aCode, (unsigned short)anArgument);
	    newOpcode->setLabelArrival(labels->flushNewLabel());
	    instructions->addObject(newOpcode);
	    break;

	default:
	    cout << "ERRMSG: Internal error, addInstruction 1 int arg with instruction " << JCInstrSet::getName(aCode) << ".\n";
	    return;		// Warning: quick exit.
    }
    currentPC+= JCInstrSet::getSizeOf(aCode);
    stackDepth+= JCInstrSet::getStackUseOf(aCode);
    if (stackDepth > maxStackDepth) maxStackDepth= stackDepth;
}


void JCCompilationContext::addInstruction(JCInstrSet::Instructions aCode, unsigned int firstArg, unsigned int secondArg)
{
    JCOpCode *newOpcode;

    if (aCode == JCInstrSet::invokeinterface) {
	newOpcode= new JCIntegerOpcode(aCode, (((firstArg & 0x0FFFF) << 16)
			| ((secondArg & 0x0FF) << 8)));
    }
    else if (aCode == JCInstrSet::iinc) {
	newOpcode= new JCShortOpcode(aCode, (unsigned short) (((firstArg & 0x0FF00) << 8) | (secondArg & 0x0FF)));
    }
    else if (aCode == JCInstrSet::multianewarray) {
	newOpcode= new JC3BytesOpcode(aCode, (unsigned short)firstArg, (unsigned char)secondArg);
    }
    else {
	cout << "ERRMSG: Internal error, addInstruction 2 int arg with instruction " << JCInstrSet::getName(aCode) << ".\n";
	return;		// Warning: quick exit.
    }
    newOpcode->setLabelArrival(labels->flushNewLabel());
    instructions->addObject(newOpcode);
    currentPC+= JCInstrSet::getSizeOf(aCode);
    stackDepth+= JCInstrSet::getStackUseOf(aCode);
    if (stackDepth > maxStackDepth) maxStackDepth= stackDepth;
}


void JCCompilationContext::addInstruction(JCInstrSet::Instructions aCode, JCReferencedType *aType)
{
    JCOpCode *newOpcode;
    unsigned int primaryType;

    switch(aCode) {
	case JCInstrSet::vreturn:
	    if (aType->isPrimitive() && !aType->isArray()) {
		if ((primaryType= aType->getPrimitiveType()) != JVM_TYPE_VOID) {
			// Update instruction for correct type.
		    if ((aCode= JCInstrSet::getTypedOp(aCode, primaryType)) == JCInstrSet::nop) {
			cout << "ERRMSG: Internal error, addInstruction referenced type not known for instruction " << (int)aCode << ".\n";
			return;		// Warning: quick exit.
		    }
		}
		newOpcode= new JCSimpleOpcode(aCode);
	    }
	    else {
		newOpcode= new JCSimpleOpcode(JCInstrSet::areturn);
	    }
	    break;
	case JCInstrSet::iadd:
	case JCInstrSet::isub:
	case JCInstrSet::imul:
	case JCInstrSet::idiv:
	case JCInstrSet::irem:
	case JCInstrSet::ineg:
	    if (aType->isPrimitive()) {
		if ((primaryType= aType->getPrimitiveType()) != JVM_TYPE_INTEGER) {
			// Update instruction for correct type.
		    if ((aCode= JCInstrSet::getTypedOp(aCode, primaryType)) == JCInstrSet::nop) {
			cout << "ERRMSG: Internal error, addInstruction referenced type not known for instruction " << (int)aCode << ".\n";
			return;		// Warning: quick exit.
		    }
		}
		newOpcode= new JCSimpleOpcode(aCode);
	    }
	    else {
		cout << "ERRMSG: Internal error, addInstruction referenced type is not primary for instruction " << (int)aCode << ".\n";
		return;		// Warning: quick exit.
	    }
	    break;
	case JCInstrSet::iastore:
	case JCInstrSet::iaload:
	    if (aType->isPrimitive()) {
		if ((primaryType= aType->getPrimitiveType()) != JVM_TYPE_INTEGER) {
			// Update instruction for correct type.
		    if ((aCode= JCInstrSet::getTypedOp(aCode, primaryType)) == JCInstrSet::nop) {
			cout << "ERRMSG: Internal error, addInstruction referenced type not known for instruction " << (int)aCode << ".\n";
			return;		// Warning: quick exit.
		    }
		}
	    }
	    else {
		aCode= (aCode == JCInstrSet::iastore) ? JCInstrSet::aastore : JCInstrSet::aaload;
	    }
	    newOpcode= new JCSimpleOpcode(aCode);
	    break;
	default:
	    cout << "ERRMSG: Internal error, addInstruction referenced type arg with instruction " << JCInstrSet::getName(aCode) << ".\n";
	    return;		// Warning: quick exit.
    }
    newOpcode->setLabelArrival(labels->flushNewLabel());
    instructions->addObject(newOpcode);
    currentPC+= JCInstrSet::getSizeOf(aCode);
    stackDepth+= JCInstrSet::getStackUseOf(aCode);
    if (stackDepth > maxStackDepth) maxStackDepth= stackDepth;
}


void JCCompilationContext::addInstruction(JCInstrSet::Instructions aCode, unsigned int anArgument, JCReferencedType *aType)
{
    unsigned int primaryType;

    switch(aCode) {
        case JCInstrSet::istore:
	case JCInstrSet::iload:
	    if (aType->isPrimitive() && !aType->isArray()) {
		if ((primaryType= aType->getPrimitiveType()) != JVM_TYPE_INTEGER) {
			// Update instruction for correct type.
		    if ((aCode= JCInstrSet::getTypedOp(aCode, primaryType)) == JCInstrSet::nop) {
			cout << "ERRMSG: Internal error, addInstruction addInstruction with int+type has referenced type unknown for instruction " << JCInstrSet::getName(aCode) << ".\n";
			return;		// Warning: quick exit.
		    }
		}
		addInstruction(aCode, anArgument);
	    }
	    else {
		addInstruction((aCode == JCInstrSet::istore) ? JCInstrSet::astore : JCInstrSet::aload, anArgument);
	    }
	    break;
	default:
	    cout << "ERRMSG: Internal error, addInstruction with int and referenced type args on unknown instruction " << JCInstrSet::getName(aCode) << ".\n";
	    return;		// Warning: quick exit.
    }
}


void JCCompilationContext::handleNamedBreak(JCIdentifier *aName)
{
    // TODO.
}

void JCCompilationContext::handleNamedContinue(JCIdentifier *aName)
{
    // TODO.
}


unsigned int JCCompilationContext::getCurrentPC(void)
{
    return currentPC;
}


void JCCompilationContext::startHandler(unsigned int startPC, unsigned int endPC, JCVariableDeclaration *aTrapDecl)
{
    // TODO.
}

void JCCompilationContext::endHandler(void)
{
    // TODO.
}


bool JCCompilationContext::isAssigning(void)
{
    return doingAssignment;
}


void JCCompilationContext::setIfAssigning(bool aValue)
{
    doingAssignment= aValue;
}


void JCCompilationContext::addTestBranch(void)
{
    // TODO.
}


void JCCompilationContext::addCteMinusOne(JCReferencedType *aType)
{
    // TODO.
}


void JCCompilationContext::startTryBlock(void)
{
    // TODO.
}


void JCCompilationContext::endTryBlock(void)
{
    // TODO.
}


void JCCompilationContext::optimizeCode(void)
{
    // TODO.
}


unsigned int JCCompilationContext::getStackDepth(void)
{
    return maxStackDepth;
}


void JCCompilationContext::dumpCode(JCCodeBuffer *aBuffer)
{
    unsigned int startLine, endLine, i;

    // TODO: fait passer le code du OpCodeList a un JCCodeBuffer.
    /* 1- Compte combien d'espace il faut.
    	2- alloue un buffer.
	3- pour chaque instruction, reecrie dans le buffer, inc le pc.
    */

// Debug:
    currentMethod->getLineRange(startLine, endLine);
    if (currentMethod->memberType() == METHOD_MEMBER) {
	cout << "Method: " << currentMethod->getAsciiValue();
    }
    else {
	cout << "State: " << currentMethod->getAsciiValue();
    }
    cout  << " [" << startLine << ":" << endLine << "]\n";
    instructions->unassemble(cout);
    cout << "\n";

    aBuffer->allocFor(currentPC);

    for (i= 0; i < instructions->count(); i++) {
	if (!aBuffer->load((const char *)instructions->objectAt(i)->encode(), instructions->objectAt(i)->byteSize())) {
	    cout << "ERRMSG: JCCompilationContext::dumpCode can't load all instructions !\n";
	    break;
	}
    }
}


void JCCompilationContext::addVarInfo(JCVariableDeclaration *varDecls)
{
    if (varDbgInfo == NULL) {
	varDbgInfo= new JCLocalVarAttr(varDecls, 0);
    }
    else varDbgInfo->addDeclarations(varDecls); 
}


unsigned int JCCompilationContext::getLabel(JCAddressLabel::Type aType)
{
	// ATTN: Should insure that a match was found.
    return labels->backScanFor(aType);
}


bool JCCompilationContext::hasDebugInfoFor(JCCompileOptions::BasicOptions anOption)
{
    bool result= false;

    // ATTN: Must add the check from the compiler options.
    switch(anOption) {
	case JCCompileOptions::describeLocalVars:
	    if (varDbgInfo != NULL) {
		if (varDbgInfo->getCount() > 0) result= true;
	    }
	    break;
	case JCCompileOptions::describeLineNumbers:
	    if (lineNbrs != NULL) {
		if (lineNbrs->getCount() > 0) result= true;
	    }
	    break;
    }

    return false;
}


void JCCompilationContext::addImplicitReturn()
{
    JCOpCode *lastOpcode;
    bool mustAddReturn= true;

    lastOpcode= (JCOpCode *)instructions->lastObject();

    if (lastOpcode != NULL) {
	if (JCInstrSet::isAReturn(lastOpcode->getOpCode())) mustAddReturn= false;
    }
    if (mustAddReturn) {
	addInstruction(JCInstrSet::vreturn);
    }
}


unsigned int JCCompilationContext::getPcForLabel(unsigned int labelID)
{
    JCAddressLabel *target;

    if ((target= labels->objectAt(labelID)) != NULL) {
	return target->getPCLocation();
    }
    return 0x0FFFFFFFF;		// It should throw instead of taking an 'improbable' address.
}

