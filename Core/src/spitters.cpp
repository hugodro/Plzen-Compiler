/**************************************************
* File: spitters.cc.
* Desc: .
* Module: AkraLog : JavaComp.
* Rev: 5 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include "identifiers.h"
#include "variables.h"
#include "constants.h"
#include "nameSpace.h"
#include "outConstant.h"
#include "compContext.h"
#include "instructions.h"
#include "compileObjects.h"
#include "actions.h"
#include "expressions.h"


/**************************************************
* Implementation: JCExpression.
**************************************************/

void JCExpression::spitTo(JCCompilationContext *codeContext)
{
    // TODO.
    cout << "ERRMSG: JCExpression::spitTo is called.\n";
}


void JCExpression::spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    this->spitTo(codeContext);
/* MOD-970902 [HD]: Added a test of the expression. */
    codeContext->addInstruction((inverseTest) ? JCInstrSet::ifne : JCInstrSet::ifeq, falseLabel);
}


void JCExpression::spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    this->spitTo(codeContext);
/* MOD-970902 [HD]: Added a test of the expression. */
    codeContext->addInstruction((inverseTest) ? JCInstrSet::ifeq : JCInstrSet::ifne, trueLabel);
}


/**************************************************
* Implementation: JCCteExpr.
**************************************************/

void JCCteExpr::spitTo(JCCompilationContext *codeContext)
{
    switch(typing) {
	case JCReferencedType::popBoolean:
	    if (((unsigned int)shadow) == 0)
		codeContext->addInstruction(JCInstrSet::iconst_0);
	    else
		codeContext->addInstruction(JCInstrSet::iconst_1);
	    break;
	case JCReferencedType::popChar:
	    codeContext->addInstruction(JCInstrSet::bipush, (unsigned int)shadow);
	    break;
	case JCReferencedType::popByte:
	    codeContext->addInstruction(JCInstrSet::bipush, (unsigned int)shadow);
	    break;
	case JCReferencedType::popShort:
	    codeContext->addInstruction(JCInstrSet::sipush, (unsigned int)shadow);
	    break;
	case JCReferencedType::popInteger:
	    if (((JCCteInteger *)shadow)->isEqual(-1)) {
		codeContext->addInstruction(JCInstrSet::iconst_m1);
	    }
	    else if (((JCCteInteger *)shadow)->isEqual(0)) {
		codeContext->addInstruction(JCInstrSet::iconst_0);
	    }
	    else if (((JCCteInteger *)shadow)->isEqual(1)) {
		codeContext->addInstruction(JCInstrSet::iconst_1);
	    }
	    else if (((JCCteInteger *)shadow)->isEqual(2)) {
		codeContext->addInstruction(JCInstrSet::iconst_2);
	    }
	    else if (((JCCteInteger *)shadow)->isEqual(3)) {
		codeContext->addInstruction(JCInstrSet::iconst_3);
	    }
	    else if (((JCCteInteger *)shadow)->isEqual(4)) {
		codeContext->addInstruction(JCInstrSet::iconst_4);
	    }
	    else if (((JCCteInteger *)shadow)->isEqual(5)) {
		codeContext->addInstruction(JCInstrSet::iconst_5);
	    }
	    else if ((getIntValue() > -129) && (getIntValue() < 128)) {
		codeContext->addInstruction(JCInstrSet::bipush, (unsigned int)getIntValue());
	    }
	    else if ((getIntValue() > -32769) && (getIntValue() < 32768)) {
		codeContext->addInstruction(JCInstrSet::sipush, (unsigned int)getIntValue());
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::ldc1, shadow->getIndex());
	    }
	    break;
	case JCReferencedType::popFloat:
	    if (((JCCteFloat *)shadow)->isEqual(0.0)) {
		codeContext->addInstruction(JCInstrSet::fconst_0);
	    }
	    else if (((JCCteFloat *)shadow)->isEqual(1.0)) {
		codeContext->addInstruction(JCInstrSet::fconst_1);
	    }
	    else if (((JCCteFloat *)shadow)->isEqual(2.0)) {
		codeContext->addInstruction(JCInstrSet::fconst_2);
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::ldc1, shadow->getIndex());
	    }
	    break;
	case JCReferencedType::popLong:
	    if (((JCCteLong *)shadow)->isEqual(0, 0)) {
		codeContext->addInstruction(JCInstrSet::lconst_0);
	    }
	    else if (((JCCteLong *)shadow)->isEqual(0, 1)) {
		codeContext->addInstruction(JCInstrSet::lconst_1);
	    }
	    else if (((JCCteLong *)shadow)->isEqual(0x0FFFFFFFF, 0x0FFFFFFFF)) {
		codeContext->addInstruction(JCInstrSet::lconst_1);
		codeContext->addInstruction(JCInstrSet::lneg);
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::ldc2w, shadow->getIndex());
	    }
	    break;
	case JCReferencedType::popDouble:
	    if (((JCCteDouble *)shadow)->isEqual(0.0)) {
		codeContext->addInstruction(JCInstrSet::dconst_0);
	    }
	    else if (((JCCteDouble *)shadow)->isEqual(1.0)) {
		codeContext->addInstruction(JCInstrSet::dconst_1);
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::ldc2w, shadow->getIndex());
	    }
	    break;
	case JCReferencedType::popString:
	    codeContext->addInstruction(JCInstrSet::ldc1, shadow->getIndex());
	    break;
	case JCReferencedType::popNullObject:
	    codeContext->addInstruction(JCInstrSet::aconst_null);
	    break;
	default:		// Internal error.
	    cout << "ERRMSG: JCCteExpr has encountered an unknown contant type.\n";
	    break;
    }
}


/**************************************************
* Implementation: JCVarAccess.
**************************************************/

void JCVarAccess::spitTo(JCCompilationContext *codeContext)
{
    JCField *aField;
    JCVariableDeclaration *aDecl;
    JCReferencedType *refType;
    bool isAssigned= codeContext->isAssigning();

    codeContext->setIfAssigning(false);

    switch(resolver->getCategory()) {
	case JCName::localVariable:
	    aDecl= (JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition();
	    refType= aDecl->typing();
/* MOD-970205 [HD]: An array can be accessed as a scalar var.
	    if (refType->isArray()) {
		cout << "ERRMSG: JCVarAccess::spitTo received an array variable.\n";
	    }
	    else {
	    }
*/
/* MOD-970916 [HD]: Handle the case of the ident having extra dims, and the type being scalar. */
	    if (aDecl->getNbrDimensions() > refType->getNbrDimensions()) {
		JCReferencedType tmpType;
		if (!refType->isArray()) {
		    tmpType.setKind(TYPE_ARRAY);
		    tmpType.setOfReferencedType(refType);
		}
		else {
		    tmpType= *refType;
		}
		tmpType.incNbrDimBy(aDecl->getNbrDimensions() - refType->getNbrDimensions());
		codeContext->addInstruction(isAssigned ? JCInstrSet::istore : JCInstrSet::iload, aDecl->getIndex(), &tmpType);
	    }
	    else {
		codeContext->addInstruction(isAssigned ? JCInstrSet::istore : JCInstrSet::iload, aDecl->getIndex(), refType);
	    }
	    break;
	case JCName::fieldVariable:
	    aField= (JCField *)((JCResolved *)resolver)->getDefinition();
	    refType= aField->getReturnedType();
/* MOD-970205 [HD]: An array can be accessed as a scalar var.
	    if (refType->isArray()) {
		cout << "ERRMSG: JCVarAccess::spitTo received an array variable.\n";
	    }
	    else {
	    }
*/
		if (aField->isStatic()) {
		    if (aField->testFlags(ACC_FINAL) && refType->isPrimitive()) {
			// TODO: Insert a direct storage of the value.
			cout << "ERRMSG: JCFieldAccess::spitTo has to spit a final static primitive field, NOT IMPLEMENTED !\n";
		    }
		    else {
			codeContext->addInstruction(isAssigned ? JCInstrSet::putstatic : JCInstrSet::getstatic, aField->getShadow()->getIndex());
		    }
		}
		else {
		    if (isAssigned) {
			codeContext->addInstruction(JCInstrSet::putfield, aField->getShadow()->getIndex());
		    }
		    else {
			codeContext->addInstruction(JCInstrSet::aload_0);
			codeContext->addInstruction(JCInstrSet::getfield, aField->getShadow()->getIndex());
		    }
		}
	    break;
	default:
	    cout << "ERRMSG:  JCVarAccess::spitTo dealing with unknown resolver ";
	    cout << "of type " << (int)resolver->getCategory() << " !\n";
	    break;
    }

    codeContext->setIfAssigning(isAssigned);
}


void JCVarAccess::spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    this->spitTo(codeContext);
    codeContext->addInstruction((inverseTest) ? JCInstrSet::ifne : JCInstrSet::ifeq, falseLabel);
}


void JCVarAccess::spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    this->spitTo(codeContext);
    codeContext->addInstruction((inverseTest) ? JCInstrSet::ifeq : JCInstrSet::ifne, trueLabel);
}


/**************************************************
* Implementation: JCFieldAccess.
**************************************************/

void JCFieldAccess::spitTo(JCCompilationContext *codeContext)
{
    JCField *aField;
    JCReferencedType *refType;
    bool isAssigned= codeContext->isAssigning();

    codeContext->setIfAssigning(false);

    if (!isAssigned) {
	if (subExpression != NULL) {
	    subExpression->spitTo(codeContext);
	}
	else {
	    codeContext->addInstruction(JCInstrSet::aload_0);
	}
    }

    aField= (JCField *)((JCResolved *)resolver)->getDefinition();
    refType= aField->getReturnedType();
    if (refType->isArray()) {
// ATTN: This happens when an array var is receiving an array object.
// A check must have been done before (in typing checking) to see that the dimensions
// are matching between the field and its source/destination.
	if (aField->isStatic()) {
	    if (aField->testFlags(ACC_FINAL) && refType->isPrimitive()) {
		// TODO: Insert a direct storage of the value.
		cout << "ERRMSG: JCFieldAccess::spitTo has to spit a final static primitive field, NOT IMPLEMENTED !\n";
	    }
	    else {
		codeContext->addInstruction(isAssigned ? JCInstrSet::putstatic : JCInstrSet::getstatic, aField->getShadow()->getIndex());
	    }
	}
	else {
	    codeContext->addInstruction(isAssigned ? JCInstrSet::putfield : JCInstrSet::getfield, aField->getShadow()->getIndex());
	}
    }
    else {
	if (aField->isStatic()) {
	    codeContext->addInstruction(isAssigned ? JCInstrSet::putstatic : JCInstrSet::getstatic, aField->getShadow()->getIndex());
	}
	else {
	    codeContext->addInstruction(isAssigned ? JCInstrSet::putfield : JCInstrSet::getfield, aField->getShadow()->getIndex());
	}
    }
    codeContext->setIfAssigning(isAssigned);
}


void JCFieldAccess::spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    this->spitTo(codeContext);
    codeContext->addInstruction((inverseTest) ? JCInstrSet::ifne : JCInstrSet::ifeq, falseLabel);
}


void JCFieldAccess::spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    this->spitTo(codeContext);
    codeContext->addInstruction((inverseTest) ? JCInstrSet::ifeq : JCInstrSet::ifne, trueLabel);
}


/**************************************************
* Implementation: JCArrayAccess.
**************************************************/

void JCArrayAccess::spitTo(JCCompilationContext *codeContext)
{
    JCField *aField;
    JCVariableDeclaration *aDecl;
    JCReferencedType *refType;
    JCExpression *tmpExpr;
    unsigned int i, declaredNbrDims;
    bool isAssigned= codeContext->isAssigning();

    codeContext->setIfAssigning(false);

    if (subExpression != NULL) subExpression->spitTo(codeContext);

	// Get self on stack.
    switch (resolver->getCategory()) {
	case JCName::localVariable:
	    aDecl= (JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition();
	    refType= aDecl->typing();
	    if ((declaredNbrDims= aDecl->getNbrDimensions()) == 0) {
		cout << "ERRMSG: JCArrayAccess::spitTo received a scalar variable !!\n";
	    }
	    else {
/* MOD-970916 [HD]: Handle the case of the ident having extra dims, and the type being scalar. */
		if (aDecl->getNbrDimensions() > refType->getNbrDimensions()) {
		    JCReferencedType tmpType;
		    if (!refType->isArray()) {
			tmpType.setKind(TYPE_ARRAY);
			tmpType.setOfReferencedType(refType);
		    }
		    else {
			tmpType= *refType;
		    }
		    tmpType.incNbrDimBy(aDecl->getNbrDimensions() - refType->getNbrDimensions());
		    codeContext->addInstruction(JCInstrSet::iload, aDecl->getIndex(), &tmpType);
		}
		else {
		    codeContext->addInstruction(JCInstrSet::iload, aDecl->getIndex(), aDecl->typing());
		}
	    }
	    break;
	case JCName::fieldVariable:
	    aField= (JCField *)((JCResolved *)resolver)->getDefinition();
	    refType= aField->getReturnedType();
	    if ((declaredNbrDims= aField->getNbrDimensions()) == 0) {
		cout << "ERRMSG: JCArrayAccess::spitTo received a scalar field.\n";
	    }
	    else {
		if (aField->isStatic()) {
		    codeContext->addInstruction(JCInstrSet::getstatic, aField->getShadow()->getIndex());
		}
		else {
		    if (subExpression == NULL) {
			codeContext->addInstruction(JCInstrSet::aload_0);
		    }
		    codeContext->addInstruction(JCInstrSet::getfield, aField->getShadow()->getIndex());
		}
	    }
	    break;
	default:
	    cout << "ERRMSG: Internal error, JCArrayAccess::spitTo has to deal with unknown resolver.\n";
	    return;
	    break;
    }

    tmpExpr= valueOffset;
    for (i= 0; i < nbrOffsets-1; i++) {
	tmpExpr->spitTo(codeContext);
	codeContext->addInstruction(JCInstrSet::aaload);
	tmpExpr= tmpExpr->next;
    }
    tmpExpr->spitTo(codeContext);

	// Spit right side.

    if (!isAssigned) {
	if (nbrOffsets == declaredNbrDims) {
	    codeContext->addInstruction(JCInstrSet::iaload, refType);
	}
	else {
	    codeContext->addInstruction(JCInstrSet::aaload);
	}
    }
    codeContext->setIfAssigning(isAssigned);
}


void JCArrayAccess::spitStorerTo(JCCompilationContext *codeContext)
{
    JCField *aField;
    JCVariableDeclaration *aDecl;
    JCReferencedType *refType;
    unsigned int declaredNbrDims;

    switch (resolver->getCategory()) {
	case JCName::localVariable:
	    aDecl= (JCVariableDeclaration *)((JCResolved *)resolver)->getDefinition();
	    declaredNbrDims= aDecl->getNbrDimensions();
	    refType= aDecl->typing();
	    break;
	case JCName::fieldVariable:
	    aField= (JCField *)((JCResolved *)resolver)->getDefinition();
	    refType= aField->getReturnedType();
	    declaredNbrDims= aField->getNbrDimensions();
	    break;
	default:
	    cout << "ERRMSG: Internal error, JCArrayAccess::spitStorerTo has to deal with unknown resolver.\n";
	    return;
    }
    if (nbrOffsets == declaredNbrDims) {
	codeContext->addInstruction(JCInstrSet::iastore, refType);
    }
    else {
	codeContext->addInstruction(JCInstrSet::aastore);
    }
}


/**************************************************
* Implementation: JCOperExpr.
**************************************************/

void JCOperExpr::spitTo(JCCompilationContext *codeContext)
{
    if ((builtinOp == PREINCR_OPER) || (builtinOp == PREDECR_OPER)
	    || (builtinOp == POSTINCR_OPER) || (builtinOp == POSTDECR_OPER)) {
	// TODO. Deal with out-of-flow operations.
    }
    else {
	if (builtinOp == BITFLIP_OPER) {
	    right->spitTo(codeContext);
	    codeContext->addCteMinusOne(resultType);
	    codeContext->addInstruction(JCInstrSet::ixor, resultType);
	}
	else if (builtinOp == NOT_OPER) {
	    right->spitTo(codeContext);
	    codeContext->addInstruction(JCInstrSet::iconst_1);
	    codeContext->addInstruction(JCInstrSet::ixor);
	}
	else if (builtinOp == NEGATE_OPER) {
	    right->spitTo(codeContext);
	    codeContext->addInstruction(JCInstrSet::ineg, resultType);
	}
	else if (builtinOp == POSATE_OPER) {
	    right->spitTo(codeContext);
	}
	else {
	    unsigned int tmpType;
	    unsigned int labelID;

	    switch(builtinOp) {
		case OROR_OPER:	// Produces a boolean result (0 or 1) as soon as
							// true is found or both expressions are scanned.
		    labelID= codeContext->getLabelBlock(4, JCAddressLabel::orOperType);
		    left->spitToAsTrueTest(codeContext, labelID+1, labelID+3, false);
			// Start of the other test (got here => left is false).
		    codeContext->defineLabel(labelID+3);
		    right->spitToAsFalseTest(codeContext, labelID+1, labelID+2, false);
			// Start of the "expr is true" code.
		    codeContext->defineLabel(labelID+1);
		    codeContext->addInstruction(JCInstrSet::iconst_1);
		    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
			// Start of the "expr is false" code.
		    codeContext->defineLabel(labelID+2);
		    codeContext->addInstruction(JCInstrSet::iconst_0);
		    codeContext->defineLabel(labelID);
		    codeContext->deleteLabelBlock(4);
		    break;
		case ANDAND_OPER:	// Produces a boolean result (0 or 1) as soon as
							// false is found or both expressions are scanned
		    labelID= codeContext->getLabelBlock(4, JCAddressLabel::andOperType);
		    left->spitToAsFalseTest(codeContext, labelID+1, labelID+3, false);
			// Start of the other test (got here => left is true).
		    codeContext->defineLabel(labelID+1);
		    right->spitToAsFalseTest(codeContext, labelID+2, labelID+3, false);
			// Start of the "expr is true" code.
		    codeContext->defineLabel(labelID+2);
		    codeContext->addInstruction(JCInstrSet::iconst_1);
		    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
			// Start of the "expr is false" code.
		    codeContext->defineLabel(labelID+3);
		    codeContext->addInstruction(JCInstrSet::iconst_0);
		    codeContext->defineLabel(labelID);
		    codeContext->deleteLabelBlock(4);
		    break;
		case EQ_OPER:
		case NE_OPER:
			// ATTN: We should flip left and right so that if there is a constant in one
			// of the expressions, it is in right.
		    left->spitTo(codeContext);
		    labelID= codeContext->getLabelBlock(2, JCAddressLabel::eqOperType);
		    if (resultType->isPrimitive()) {
			    // ATTN: Must add optimization for the case of int constant 0.
			right->spitTo(codeContext);
			tmpType= right->getFinalType()->getPrimitiveType();
			if ((tmpType == JVM_TYPE_BOOLEAN) || (tmpType == JVM_TYPE_SIGNED_BYTE)
				|| (tmpType == JVM_TYPE_CHAR)
				|| (tmpType == JVM_TYPE_UNSIGNED_SHORT)
				|| (tmpType == JVM_TYPE_INTEGER)) {
			    codeContext->addInstruction((builtinOp == EQ_OPER) ?
						    JCInstrSet::if_icmpeq : JCInstrSet::if_icmpne, labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_0);
			    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
			    codeContext->defineLabel(labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_1);
			    codeContext->defineLabel(labelID);
			}
			else {
			    if (tmpType == JVM_TYPE_FLOAT) {
				codeContext->addInstruction(JCInstrSet::fcmpl);
			    }
			    else if (tmpType == JVM_TYPE_LONG) {
				codeContext->addInstruction(JCInstrSet::lcmp);
			    }
			    else if (tmpType == JVM_TYPE_DOUBLE) {
				codeContext->addInstruction(JCInstrSet::dcmpl);
			    }
			    else {
				cout << "ERRMSG: JCOperExpr::spitTo found an unknown primitve type.\n";
				codeContext->deleteLabelBlock(2);
				return;
			    }
			    codeContext->addInstruction((builtinOp == EQ_OPER) ?
						    JCInstrSet::ifeq : JCInstrSet::ifne, labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_0);
			    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
			    codeContext->defineLabel(labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_1);
			    codeContext->defineLabel(labelID);
			}
		    }
		    else {
			if (right->category == eConstant) {
			    if (((JCCteExpr *)right)->isNullCte()) {
				codeContext->addInstruction((builtinOp == EQ_OPER) ?
							JCInstrSet::ifnull : JCInstrSet::ifnonnull, labelID+1);
				codeContext->addInstruction(JCInstrSet::iconst_0);
				codeContext->addInstruction(JCInstrSet::goto_n, labelID);
				codeContext->defineLabel(labelID+1);
				codeContext->addInstruction(JCInstrSet::iconst_1);
				codeContext->defineLabel(labelID);
			    }
			    else {	// Object constant.  In java, it is only a string object.
				((JCCteExpr *)right)->spitTo(codeContext);    // Should give a ldc{1|2}.
				codeContext->addInstruction((builtinOp == EQ_OPER) ?
							JCInstrSet::if_acmpeq : JCInstrSet::if_acmpne, labelID+1);
				codeContext->addInstruction(JCInstrSet::iconst_0);
				codeContext->addInstruction(JCInstrSet::goto_n, labelID);
				codeContext->defineLabel(labelID+1);
				codeContext->addInstruction(JCInstrSet::iconst_1);
				codeContext->defineLabel(labelID);
			    }
			}
			else {
			    right->spitTo(codeContext);
			    codeContext->addInstruction((builtinOp == EQ_OPER) ?
							JCInstrSet::if_acmpeq : JCInstrSet::if_acmpne, labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_0);
			    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
			    codeContext->defineLabel(labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_1);
			    codeContext->defineLabel(labelID);
			}
		    }
		    codeContext->deleteLabelBlock(2);
		    break;
		case LE_OPER:
		case GE_OPER:
		case GT_OPER:
		case LT_OPER:
		    if (resultType->isPrimitive()) {
			left->spitTo(codeContext);
			right->spitTo(codeContext);
			labelID= codeContext->getLabelBlock(2, JCAddressLabel::ineqOperType);
			tmpType= right->getFinalType()->getPrimitiveType();
			if ((tmpType == JVM_TYPE_BOOLEAN) || (tmpType == JVM_TYPE_SIGNED_BYTE)
				|| (tmpType == JVM_TYPE_CHAR)
				|| (tmpType == JVM_TYPE_UNSIGNED_SHORT)
				|| (tmpType == JVM_TYPE_INTEGER)) {
			    codeContext->addInstruction((builtinOp == LE_OPER) ? JCInstrSet::if_icmple :
			    		(builtinOp == GE_OPER) ? JCInstrSet::if_icmpge :
					(builtinOp == GT_OPER) ? JCInstrSet::if_icmpgt :
					JCInstrSet::if_icmplt, labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_0);
			    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
			    codeContext->defineLabel(labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_1);
			    codeContext->defineLabel(labelID);
			}
			else {
			    if (tmpType == JVM_TYPE_FLOAT) {
				codeContext->addInstruction(((builtinOp == LE_OPER)
						|| (builtinOp == LT_OPER)) ? JCInstrSet::fcmpg : JCInstrSet::fcmpl);
			    }
			    else if (tmpType == JVM_TYPE_LONG) {
				codeContext->addInstruction(JCInstrSet::lcmp);
			    }
			    else if (tmpType == JVM_TYPE_DOUBLE) {
				codeContext->addInstruction(((builtinOp == LE_OPER)
						|| (builtinOp == LT_OPER)) ? JCInstrSet::dcmpg : JCInstrSet::dcmpl);
			    }
			    else {
				cout << "ERRMSG: JCOperExpr::spitTo found an unknown primitve type.\n";
				codeContext->deleteLabelBlock(2);
				return;
			    }
			    codeContext->addInstruction((builtinOp == LE_OPER) ? JCInstrSet::ifle :
			    		(builtinOp == GE_OPER) ? JCInstrSet::ifge :
					(builtinOp == GT_OPER) ? JCInstrSet::ifgt :
					JCInstrSet::iflt, labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_0);
			    codeContext->addInstruction(JCInstrSet::goto_n, labelID);
			    codeContext->defineLabel(labelID+1);
			    codeContext->addInstruction(JCInstrSet::iconst_1);
			    codeContext->defineLabel(labelID);
			}
			codeContext->deleteLabelBlock(2);
		    }
		    else {
			cout << "ERRMSG: JCOperExpr::spitTo got a non primitive type in a relation test.\n";
		    }
		    break;
		case OR_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    if (resultType->is64Bits())
			codeContext->addInstruction(JCInstrSet::lor);
		    else
			codeContext->addInstruction(JCInstrSet::ior);
		    break;
		case AND_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    if (resultType->is64Bits())
			codeContext->addInstruction(JCInstrSet::land);
		    else
			codeContext->addInstruction(JCInstrSet::iand);
		    break;
		case XOR_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    if (resultType->is64Bits())
			codeContext->addInstruction(JCInstrSet::lxor);
		    else
			codeContext->addInstruction(JCInstrSet::ixor);
		    break;
		case URS_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    if (resultType->is64Bits())
			codeContext->addInstruction(JCInstrSet::lushr);
		    else
			codeContext->addInstruction(JCInstrSet::iushr);
		    break;
		case RS_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    if (resultType->is64Bits())
			codeContext->addInstruction(JCInstrSet::lshr);
		    else
			codeContext->addInstruction(JCInstrSet::ishr);
		    break;
		case LS_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    if (resultType->is64Bits())
			codeContext->addInstruction(JCInstrSet::lshl);
		    else
			codeContext->addInstruction(JCInstrSet::ishl);
		    break;
		case ADD_OPER:
			// ATTN: Implement optimization to use 'iinc' instruction on var/small cte pair.
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    codeContext->addInstruction(JCInstrSet::iadd, resultType);
		    break;
		case SUBST_OPER:
			// ATTN: Implement optimization to use 'iinc' instruction on var/small cte pair.
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    codeContext->addInstruction(JCInstrSet::isub, resultType);
		    break;
		case MULTIPLY_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    codeContext->addInstruction(JCInstrSet::imul, resultType);
		    break;
		case DIVIDE_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    codeContext->addInstruction(JCInstrSet::idiv, resultType);
		    break;
		case MODULO_OPER:
		    left->spitTo(codeContext);
		    right->spitTo(codeContext);
		    codeContext->addInstruction(JCInstrSet::irem, resultType);
		    break;
		default:
		    cout << "ERRMSG: JCOperExpr::spitTo has encountered an unknown operator.\n";
		    break;
	    }
	}
    }
}


void JCOperExpr::spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    unsigned int labelID, tmpType;

    switch(builtinOp) {
	case OROR_OPER:
	    labelID= codeContext->getLabelBlock(1, JCAddressLabel::orTestType);
	    if (inverseTest) {
		// TODO.
	    }
	    else {
		left->spitToAsTrueTest(codeContext, trueLabel, labelID, false);
		codeContext->defineLabel(labelID);
		right->spitToAsFalseTest(codeContext, trueLabel, falseLabel, false);
	    }
	    codeContext->deleteLabelBlock(1);
	    break;
	case ANDAND_OPER:
	    labelID= codeContext->getLabelBlock(1, JCAddressLabel::andTestType);
	    if (inverseTest) {
		// TODO.
	    }
	    else {
		left->spitToAsFalseTest(codeContext, labelID, falseLabel, false);
		codeContext->defineLabel(labelID);
		right->spitToAsFalseTest(codeContext, trueLabel, falseLabel, false);
	    }
	    codeContext->deleteLabelBlock(1);
	    break;
	case NOT_OPER:
	    right->spitToAsFalseTest(codeContext, trueLabel, falseLabel, !inverseTest);
	    break;
	case EQ_OPER:
	case NE_OPER:
	    // TODO: tenir compte de la situation inverse.
/* MOD-970821 [HD]: Using instead the 'left' element to find out the type of operands.
	    if (resultType->isPrimitive()) {
*/
	    if (left->getFinalType()->getPrimitiveType()) {
		left->spitTo(codeContext);
		right->spitTo(codeContext);
		    // ATTN: Must add optimization for the case of int constant 0.
		tmpType= right->getFinalType()->getPrimitiveType();
		if ((tmpType == JVM_TYPE_BOOLEAN) || (tmpType == JVM_TYPE_SIGNED_BYTE)
			|| (tmpType == JVM_TYPE_CHAR)
			|| (tmpType == JVM_TYPE_UNSIGNED_SHORT)
			|| (tmpType == JVM_TYPE_INTEGER)) {
		    codeContext->addInstruction((builtinOp == NE_OPER) ?
					    JCInstrSet::if_icmpeq : JCInstrSet::if_icmpne, falseLabel);
		}
		else {
		    if (tmpType == JVM_TYPE_FLOAT) {
			codeContext->addInstruction(JCInstrSet::fcmpl);
		    }
		    else if (tmpType == JVM_TYPE_LONG) {
			codeContext->addInstruction(JCInstrSet::lcmp);
		    }
		    else if (tmpType == JVM_TYPE_DOUBLE) {
			codeContext->addInstruction(JCInstrSet::dcmpl);
		    }
		    else {
			cout << "ERRMSG: JCOperExpr::spitTo found an unknown primitve type.\n";
			codeContext->deleteLabelBlock(2);
			return;
		    }
		    codeContext->addInstruction((builtinOp == NE_OPER) ?
					    JCInstrSet::ifeq : JCInstrSet::ifne, falseLabel);
		}
	    }
	    else {
		left->spitTo(codeContext);
		if (right->category == eConstant) {
		    if (((JCCteExpr *)right)->isNullCte()) {
			codeContext->addInstruction((builtinOp == NE_OPER) ?
						JCInstrSet::ifnull : JCInstrSet::ifnonnull, falseLabel);
		    }
		    else {	// Object constant.  In java, it is only a string object.
			((JCCteExpr *)right)->spitTo(codeContext);    // Should give a ldc{1|2}.
			codeContext->addInstruction((builtinOp == NE_OPER) ?
						JCInstrSet::if_acmpeq : JCInstrSet::if_acmpne, falseLabel);
		    }
		}
		else {
		    right->spitTo(codeContext);
		    codeContext->addInstruction((builtinOp == NE_OPER) ?
						JCInstrSet::if_acmpeq : JCInstrSet::if_acmpne, falseLabel);
		}
	    }
	     break;
	case LE_OPER:
	case GE_OPER:
	case GT_OPER:
	case LT_OPER:
	    // TODO: tenir compte de la situation inverse.
	    if (resultType->isPrimitive()) {
		left->spitTo(codeContext);
		right->spitTo(codeContext);
		tmpType= right->getFinalType()->getPrimitiveType();
		if ((tmpType == JVM_TYPE_SIGNED_BYTE)
			|| (tmpType == JVM_TYPE_CHAR)
			|| (tmpType == JVM_TYPE_UNSIGNED_SHORT)
			|| (tmpType == JVM_TYPE_INTEGER)) {
		    codeContext->addInstruction((builtinOp == GT_OPER) ? JCInstrSet::if_icmple
			    : (builtinOp == LT_OPER) ? JCInstrSet::if_icmpge
			    : (builtinOp == LE_OPER) ? JCInstrSet::if_icmpgt
			    : JCInstrSet::if_icmplt,
			    falseLabel);
		}
		else {
		    if (tmpType == JVM_TYPE_FLOAT) {
			codeContext->addInstruction(((builtinOp == LE_OPER)
					|| (builtinOp == LT_OPER)) ? JCInstrSet::fcmpg : JCInstrSet::fcmpl);
		    }
		    else if (tmpType == JVM_TYPE_LONG) {
			codeContext->addInstruction(JCInstrSet::lcmp);
		    }
		    else if (tmpType == JVM_TYPE_DOUBLE) {
			codeContext->addInstruction(((builtinOp == LE_OPER)
					|| (builtinOp == LT_OPER)) ? JCInstrSet::dcmpg : JCInstrSet::dcmpl);
		    }
		    else {
			cout << "ERRMSG: JCOperExpr::spitTo found an unknown primitve type.\n";
			codeContext->deleteLabelBlock(2);
			return;
		    }
		    codeContext->addInstruction((builtinOp == GT_OPER) ? JCInstrSet::ifle
			    : (builtinOp == LT_OPER) ? JCInstrSet::ifge
			    : (builtinOp == LE_OPER) ? JCInstrSet::ifgt
			    : JCInstrSet::iflt,
			    falseLabel);
		}
	    }
	    else {
		cout << "ERRMSG: JCOperExpr::spitTo got a non primitive type in a relation test.\n";
	    }
	    break;
	default:
	    cout << "ERRMSG: Received an expression as test which isn't a boolean producer.\n";
	    break;
    }
}


void JCOperExpr::spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    unsigned int labelID, tmpType;

    switch(builtinOp) {
	case OROR_OPER:
	    if (inverseTest) {
		// TODO.
	    }
	    else {
		left->spitToAsTrueTest(codeContext, trueLabel, falseLabel, false);
		right->spitToAsTrueTest(codeContext, trueLabel, falseLabel, false);
	    }
	    break;
	case ANDAND_OPER:
	    labelID= codeContext->getLabelBlock(1, JCAddressLabel::andTestType);
	    if (inverseTest) {
		// TODO.
	    }
	    else {
		left->spitToAsFalseTest(codeContext, labelID, falseLabel, false);
		codeContext->defineLabel(labelID);
		right->spitToAsTrueTest(codeContext, trueLabel, falseLabel, false);
	    }
	    codeContext->deleteLabelBlock(1);
	    break;
	case NOT_OPER:
	    right->spitToAsTrueTest(codeContext, trueLabel, falseLabel, !inverseTest);
	    break;
	case EQ_OPER:
	case NE_OPER:
	    left->spitTo(codeContext);
	    right->spitTo(codeContext);
	    if (resultType->isPrimitive()) {
		    // ATTN: Must add optimization for the case of int constant 0.
		tmpType= right->getFinalType()->getPrimitiveType();
		if ((tmpType == JVM_TYPE_BOOLEAN) || (tmpType == JVM_TYPE_SIGNED_BYTE)
			|| (tmpType == JVM_TYPE_CHAR)
			|| (tmpType == JVM_TYPE_UNSIGNED_SHORT)
			|| (tmpType == JVM_TYPE_INTEGER)) {
		    codeContext->addInstruction((builtinOp == EQ_OPER) ?
					    JCInstrSet::if_icmpeq : JCInstrSet::if_icmpne, trueLabel);
		}
		else {
		    if (tmpType == JVM_TYPE_FLOAT) {
			codeContext->addInstruction(JCInstrSet::fcmpl);
		    }
		    else if (tmpType == JVM_TYPE_LONG) {
			codeContext->addInstruction(JCInstrSet::lcmp);
		    }
		    else if (tmpType == JVM_TYPE_DOUBLE) {
			codeContext->addInstruction(JCInstrSet::dcmpl);
		    }
		    else {
			cout << "ERRMSG: JCOperExpr::spitTo found an unknown primitve type.\n";
			codeContext->deleteLabelBlock(2);
			return;
		    }
		    codeContext->addInstruction((builtinOp == EQ_OPER) ?
					    JCInstrSet::ifeq : JCInstrSet::ifne, trueLabel);
		}
	    }
	    else {
		if (right->category == eConstant) {
		    if (((JCCteExpr *)right)->isNullCte()) {
			codeContext->addInstruction((builtinOp == EQ_OPER) ?
						JCInstrSet::ifnull : JCInstrSet::ifnonnull, trueLabel);
		    }
		    else {	// Object constant.  In java, it is only a string object.
			((JCCteExpr *)right)->spitTo(codeContext);    // Should give a ldc{1|2}.
			codeContext->addInstruction((builtinOp == EQ_OPER) ?
						JCInstrSet::if_acmpeq : JCInstrSet::if_acmpne, trueLabel);
		    }
		}
		else {
		    right->spitTo(codeContext);
		    codeContext->addInstruction((builtinOp == EQ_OPER) ?
						JCInstrSet::if_acmpeq : JCInstrSet::if_acmpne, trueLabel);
		}
	    }
	     break;
	case LE_OPER:
	case GE_OPER:
	case GT_OPER:
	case LT_OPER:
	    if (resultType->isPrimitive()) {
		left->spitTo(codeContext);
		right->spitTo(codeContext);
		tmpType= right->getFinalType()->getPrimitiveType();
		if ((tmpType == JVM_TYPE_SIGNED_BYTE)
			|| (tmpType == JVM_TYPE_CHAR)
			|| (tmpType == JVM_TYPE_UNSIGNED_SHORT)
			|| (tmpType == JVM_TYPE_INTEGER)) {
		    codeContext->addInstruction((builtinOp == LE_OPER) ? JCInstrSet::if_icmple
				: (builtinOp == GE_OPER) ? JCInstrSet::if_icmpge
				: (builtinOp == GT_OPER) ? JCInstrSet::if_icmpgt
				: JCInstrSet::if_icmplt,
				trueLabel);
		}
		else {
		    if (tmpType == JVM_TYPE_FLOAT) {
			codeContext->addInstruction(((builtinOp == LE_OPER)
					|| (builtinOp == LT_OPER)) ? JCInstrSet::fcmpg : JCInstrSet::fcmpl);
		    }
		    else if (tmpType == JVM_TYPE_LONG) {
			codeContext->addInstruction(JCInstrSet::lcmp);
		    }
		    else if (tmpType == JVM_TYPE_DOUBLE) {
			codeContext->addInstruction(((builtinOp == LE_OPER)
					|| (builtinOp == LT_OPER)) ? JCInstrSet::dcmpg : JCInstrSet::dcmpl);
		    }
		    else {
			cout << "ERRMSG: JCOperExpr::spitTo found an unknown primitve type.\n";
			codeContext->deleteLabelBlock(2);
			return;
		    }
		    codeContext->addInstruction((builtinOp == LE_OPER) ? JCInstrSet::ifle
				: (builtinOp == GE_OPER) ? JCInstrSet::ifge
				: (builtinOp == GT_OPER) ? JCInstrSet::ifgt
				: JCInstrSet::iflt,
				trueLabel);
		}
	    }
	    else {
		cout << "ERRMSG: JCOperExpr::spitTo got a non primitive type in a relation test.\n";
	    }
	    break;
	default:
	    cout << "ERRMSG: Received an expression as test which isn't a boolean producer.\n";
	    break;
    }
}


/**************************************************
* Implementation: JCCastExpr.
**************************************************/

void JCCastExpr::spitTo(JCCompilationContext *codeContext)
{
	// ATTN: Must revise to make sure that the casting rules are well applied.
	// (specially in widening).

    right->spitTo(codeContext);

    if (builtinOp == ISA_OPER) {
	codeContext->addInstruction(JCInstrSet::instanceof, resultType->getTypeShadow()->getIndex());
    }
    else {
	if (resultType->isPrimitive()) {
	    unsigned int fromType= right->getFinalType()->getPrimitiveType();

	    switch(resultType->getPrimitiveType()) {
		case JVM_TYPE_SIGNED_BYTE:
		    switch(fromType) {
			case JVM_TYPE_DOUBLE:
			    codeContext->addInstruction(JCInstrSet::d2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
			case JVM_TYPE_LONG:
			    codeContext->addInstruction(JCInstrSet::l2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
			case JVM_TYPE_FLOAT:
			    codeContext->addInstruction(JCInstrSet::f2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
		    }
		    if (fromType == JVM_TYPE_INTEGER) {
			codeContext->addInstruction(JCInstrSet::int2byte);
		    }
		    break;
		case JVM_TYPE_CHAR:
		    switch(fromType) {
			case JVM_TYPE_DOUBLE:
			    codeContext->addInstruction(JCInstrSet::d2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
			case JVM_TYPE_LONG:
			    codeContext->addInstruction(JCInstrSet::l2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
			case JVM_TYPE_FLOAT:
			    codeContext->addInstruction(JCInstrSet::f2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
		    }
		    if (fromType == JVM_TYPE_INTEGER) {
			codeContext->addInstruction(JCInstrSet::int2char);
		    }
		    break;
		case JVM_TYPE_UNSIGNED_SHORT:
		    switch(fromType) {
			case JVM_TYPE_DOUBLE:
			    codeContext->addInstruction(JCInstrSet::d2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
			case JVM_TYPE_LONG:
			    codeContext->addInstruction(JCInstrSet::l2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
			case JVM_TYPE_FLOAT:
			    codeContext->addInstruction(JCInstrSet::f2i);
			    fromType= JVM_TYPE_INTEGER;
			    break;
		    }
		    if (fromType == JVM_TYPE_INTEGER) {
			codeContext->addInstruction(JCInstrSet::int2short);
		    }
		    break;
		case JVM_TYPE_INTEGER:
		    switch(fromType) {
			case JVM_TYPE_DOUBLE:
			    codeContext->addInstruction(JCInstrSet::d2i);
			    break;
			case JVM_TYPE_LONG:
			    codeContext->addInstruction(JCInstrSet::l2i);
			    break;
			case JVM_TYPE_FLOAT:
			    codeContext->addInstruction(JCInstrSet::f2i);
			    break;
		    }
		    break;
		case JVM_TYPE_FLOAT:
		    switch(fromType) {
			case JVM_TYPE_DOUBLE:
			    codeContext->addInstruction(JCInstrSet::d2f);
			    break;
			case JVM_TYPE_LONG:
			    codeContext->addInstruction(JCInstrSet::l2f);
			    break;
			case JVM_TYPE_SIGNED_BYTE:
			case JVM_TYPE_CHAR:
			case JVM_TYPE_UNSIGNED_SHORT:
			case JVM_TYPE_INTEGER:
			    codeContext->addInstruction(JCInstrSet::i2f);
			    break;
		    }
		    break;
		case JVM_TYPE_LONG:
		    switch(fromType) {
			case JVM_TYPE_DOUBLE:
			    codeContext->addInstruction(JCInstrSet::d2l);
			    break;
			case JVM_TYPE_FLOAT:
			    codeContext->addInstruction(JCInstrSet::f2l);
			    break;
			case JVM_TYPE_SIGNED_BYTE:
			case JVM_TYPE_CHAR:
			case JVM_TYPE_UNSIGNED_SHORT:
			case JVM_TYPE_INTEGER:
			    codeContext->addInstruction(JCInstrSet::i2l);
			    break;
		    }
		    break;
		case JVM_TYPE_DOUBLE:
		    switch(fromType) {
			case JVM_TYPE_LONG:
			    codeContext->addInstruction(JCInstrSet::l2d);
			    break;
			case JVM_TYPE_FLOAT:
			    codeContext->addInstruction(JCInstrSet::f2d);
			    break;
			case JVM_TYPE_SIGNED_BYTE:
			case JVM_TYPE_CHAR:
			case JVM_TYPE_UNSIGNED_SHORT:
			case JVM_TYPE_INTEGER:
			    codeContext->addInstruction(JCInstrSet::i2d);
			    break;
		    }
		    break;
		default:
		    cout << "ERRMSG: JCCastExpr:spitTo has an unknonw primitive type conversion to do.\n";
		    break;
	    }
	}
	else {	// Instance type cast.
	    codeContext->addInstruction(JCInstrSet::checkcast, resultType->getTypeShadow()->getIndex());
	}
    }
}


/**************************************************
* Implementation: JCAssignExpr.
**************************************************/

void JCAssignExpr::spitAssignmentFor(JCCompilationContext *codeContext, JCVariableDeclaration *aDecl)
{
    JCReferencedType *refType;
    bool isAssigned= codeContext->isAssigning();

    codeContext->setIfAssigning(true);

    refType= aDecl->typing();
    if (aDecl->getNbrDimensions() > 0) {
	cout << "ERRMSG: JCAssignExpr::spitAssignmentFor received an array variable (of primitive type).\n";
    }
    else {
	codeContext->addInstruction(JCInstrSet::istore, aDecl->getIndex(), refType);
    }

    codeContext->setIfAssigning(isAssigned);
}


void JCAssignExpr::spitAssignmentFor(JCCompilationContext *codeContext, JCVariableDeclaration *aDecl, unsigned int anIndex)
{
    bool isAssigned= codeContext->isAssigning();

    codeContext->setIfAssigning(true);
    // TODO: Do the assignment of the array.
    codeContext->setIfAssigning(isAssigned);
}


void JCAssignExpr::spitTo(JCCompilationContext *codeContext)
{
    bool isAssigned= codeContext->isAssigning();
    bool leftIsScalar= true;

    codeContext->setIfAssigning(false);
    switch(left->getCategory()) {		// fetch the receiver container, if necessary.
	case eVariable:
	    if (((JCVarAccess *)left)->resolution()->getCategory() == JCName::fieldVariable) {
		JCField *aField;

		aField= (JCField *)((JCResolved *)((JCVarAccess *)left)->resolution())->getDefinition();
		if (!aField->isStatic()) {
		    codeContext->addInstruction(JCInstrSet::aload_0);
		}
	    }
	    break;
	case eField:
		// ATTN-980522 [HD]: Isn't there a check for 'static' necessary ?
	    if (((JCNamedExpr *)left)->getSubExpression() != NULL) {
		((JCNamedExpr *)left)->getSubExpression()->spitTo(codeContext);
	    }
	    else {
// MOD-980511 [HD]: Replaced a 'iload_0' by a 'aload_0' (that was a bug).
		codeContext->addInstruction(JCInstrSet::aload_0);
	    }
	    break;
	case eArray:
	    codeContext->setIfAssigning(true);
	    left->spitTo(codeContext);
	    codeContext->setIfAssigning(false);
	    leftIsScalar= false;
	    break;
	default:	// Do nothing ?
	    break;
    }

    if (builtinOp != SIMPLEASS_OPER) {
	left->spitTo(codeContext);
	right->spitTo(codeContext);
	switch(builtinOp) {
	    case PLUSASS_OPER:
		codeContext->addInstruction(JCInstrSet::iadd, right->getFinalType());
		break;
	    case MINUSASS_OPER:
		codeContext->addInstruction(JCInstrSet::isub, right->getFinalType());
		break;
	    case TIMEASS_OPER:
		codeContext->addInstruction(JCInstrSet::imul, right->getFinalType());
		break;
	    case DIVIDEASS_OPER:
		codeContext->addInstruction(JCInstrSet::idiv, right->getFinalType());
		break;
	    case MODASS_OPER:
		codeContext->addInstruction(JCInstrSet::irem, right->getFinalType());
		break;
	    case ANDASS_OPER:
		codeContext->addInstruction(JCInstrSet::iand, right->getFinalType());
		break;
	    case ORASS_OPER:
		codeContext->addInstruction(JCInstrSet::ior, right->getFinalType());
		break;
	    case NOTASS_OPER:
		// ATTN: Is this the right operator ??
		codeContext->addInstruction(JCInstrSet::ixor, right->getFinalType());
		break;
	    case LSASS_OPER:
		codeContext->addInstruction(JCInstrSet::ishl, right->getFinalType());
		break;
	    case RSASS_OPER:
		codeContext->addInstruction(JCInstrSet::ishr, right->getFinalType());
		break;
	    case URSASS_OPER:
		codeContext->addInstruction(JCInstrSet::iushr, right->getFinalType());
		break;
	    default:	// Internal error.
		cout << "ERRMSG: JCAssignExpr::spitTo has found an unknown operator in assignment.\n";
		break;
	}
    }
    else {
	right->spitTo(codeContext);
    }


    if (owner != NULL) {
	if (owner->getContainerType() == JCContainer::expression) {
	    if (leftIsScalar) {
		codeContext->addInstruction(JCInstrSet::dup);
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::dup_x2);
	    }
	}
    }

    if (leftIsScalar) {
	codeContext->setIfAssigning(true);
	left->spitTo(codeContext);
    }
    else {
	((JCArrayAccess *)left)->spitStorerTo(codeContext);
    }
    codeContext->setIfAssigning(isAssigned);
}


/**************************************************
* Implementation: JCInvokeExpr.
**************************************************/

void JCInvokeExpr::spitTo(JCCompilationContext *codeContext)
{
    bool mustPop;

    if (owner == NULL) {
	mustPop= true;
    }
    else if (owner->getContainerType() == (unsigned int)JCContainer::action) {
	if (((JCAction *)owner)->getActionType() == JUMP_STAT) {
	    if (((JCStatement *)owner)->getSubCategory() != RETURN_JUMP) {
		mustPop= true;
	    }
	    else mustPop= false;
	}
	else {
	    mustPop= true;
	}
    }
    else mustPop= false;

    this->mainSpitTo(codeContext, mustPop);
}


void JCInvokeExpr::mainSpitTo(JCCompilationContext *codeContext, bool mustPop)
{
    JCMethod *aMethod;
    JCExpression *tmpExpr;

    aMethod= (JCMethod *)((JCResolved *)resolver)->getDefinition();
    if (subExpression != NULL) {
	subExpression->spitTo(codeContext);
    }
    else {
	// This is a left-most situation, must spit the implied object receiver if non-static.
	if (!aMethod->isStatic()) {
	    codeContext->addInstruction(JCInstrSet::aload_0);
	}
    }

    if ((tmpExpr= arguments) != NULL) {
	do {
	    tmpExpr->spitTo(codeContext);
	    tmpExpr= tmpExpr->next;
	} while (tmpExpr);
    }

    if (aMethod->getOwner()->isInterface()) {
	    codeContext->addInstruction(JCInstrSet::invokeinterface, aMethod->getShadow()->getIndex(),
			aMethod->getNbrArguments());
    }
    else {
	if (aMethod->isStatic()) {
	    codeContext->addInstruction(JCInstrSet::invokestatic,
	    			aMethod->getShadow()->getIndex());
	}
	else {
		// ATTN: Comment decide-t'on d'appeler un nonvirtual au lieu d'un virtual ?
		//	On utilise le non-virtuel pour un alloc et un 'super'.
	    if (cantBeVirtual) {
		codeContext->addInstruction(JCInstrSet::invokenonvirtual,
				aMethod->getShadow()->getIndex());
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::invokevirtual,
				aMethod->getShadow()->getIndex());
	    }
	}
    }

    if (mustPop) {
	if (!aMethod->getReturnedType()->isVoid()) {
	    if (aMethod->getReturnedType()->is64Bits()) {
		codeContext->addInstruction(JCInstrSet::pop);
	    }
	    codeContext->addInstruction(JCInstrSet::pop);
	}
    }
}

void JCInvokeExpr::spitToAsFalseTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    this->mainSpitTo(codeContext, false);
    codeContext->addInstruction((inverseTest) ? JCInstrSet::ifne : JCInstrSet::ifeq, falseLabel);
}


void JCInvokeExpr::spitToAsTrueTest(JCCompilationContext *codeContext, unsigned int trueLabel, unsigned int falseLabel, bool inverseTest)
{
    this->mainSpitTo(codeContext, false);
    codeContext->addInstruction((inverseTest) ? JCInstrSet::ifeq : JCInstrSet::ifne, trueLabel);
}



/**************************************************
* Implementation: JCAllocExpr.
**************************************************/

void JCAllocExpr::spitTo(JCCompilationContext *codeContext)
{
    if (nbrSizes > 0) {	// This is an vectorial allocation.
	JCExpression *tmpExpr;

	tmpExpr= dimensionSizes;
	while (tmpExpr != NULL) {
	    tmpExpr->spitTo(codeContext);
	    tmpExpr= tmpExpr->next;
	}

	if (nbrSizes == 1) {
	    if (type->isPrimitive() && (nbrEmptyDims == 0)) {
		codeContext->addInstruction(JCInstrSet::newarray, JCInstrSet::primaryTypeToByteCode(type->getPrimitiveType()));
	    }
	    else {
		codeContext->addInstruction(JCInstrSet::anewarray, (shadow != NULL) ? shadow->getIndex() : type->getTypeShadow()->getIndex());
	    }
	}
	else {
	    // If there is more than one dimension, we use the multianewarray.
	    codeContext->addInstruction(JCInstrSet::multianewarray,
	    		(shadow != NULL) ? shadow->getIndex() : type->getTypeShadow()->getIndex(),
			nbrSizes);
	}
    }
    else {		// This is a scalar allocation.
	codeContext->addInstruction(JCInstrSet::anew, type->getTypeShadow()->getIndex());
	if (owner != NULL) {
	    codeContext->addInstruction(JCInstrSet::dup);
	}
	initializer->spitTo(codeContext);	
    }

}


/**************************************************
* Implementation: JCCondExpr.
**************************************************/

/**************************************************
* Implementation: JCInitInvoke.
**************************************************/

void JCInitInvoke::spitTo(JCCompilationContext *codeContext)
{
    JCMethod *aMethod;
    JCExpression *tmpExpr;

    aMethod= (JCMethod *)((JCResolved *)resolver)->getDefinition();
    if ((tmpExpr= arguments) != NULL) {
	do {
	    tmpExpr->spitTo(codeContext);
	    tmpExpr= tmpExpr->next;
	} while (tmpExpr);
    }
    codeContext->addInstruction(JCInstrSet::invokenonvirtual,
		    aMethod->getShadow()->getIndex());
}


/**************************************************
* Implementation: JCStateInvokeExpr.
**************************************************/

void JCStateInvokeExpr::spitTo(JCCompilationContext *codeContext)
{
    JCExpression *tmpExpr;
    unsigned int startLabel;

    startLabel= codeContext->getLabelBlock(2, JCAddressLabel::startTransition);
    codeContext->defineLabel(startLabel);

    if ((tmpExpr= arguments) != NULL) {
	do {
	    tmpExpr->spitTo(codeContext);
	    tmpExpr= tmpExpr->next;
	} while (tmpExpr);

	codeContext->addInstruction(JCInstrSet::vreturn);
    }
    else {
	codeContext->defineLabel(startLabel+1);
    }
    setLabels(startLabel, startLabel + 1);
    codeContext->deleteLabelBlock(2);
}