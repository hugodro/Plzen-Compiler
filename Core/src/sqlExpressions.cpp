/**************************************************
* File: sqlExpressions.cc.
* Desc: Implementation of the JCSqlExpression hierarchy.
* Module: AkraLog : JavaKit.
* Rev: 2 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include "sqlCompContext.h"
#include "sqlClauses.h"
#include "sqlSpitters.h"
#include "sqlIdentifier.h"
#include "identifiers.h"
#include "expressions.h"
#include "instructions.h"
#include "compContext.h"
#include "nameSpace.h"
#include "compileObjects.h"
#include "sqlExpressions.h"


/**************************************************
* Implementation: JCSqlExpression.
**************************************************/

JCSqlExpression::JCSqlExpression(void)
{
    kind= kUnknown;
}


JCSqlExpression::JCSqlExpression(Kind aKind)
{
    kind= aKind;
}


JCSqlExpression::Kind JCSqlExpression::getKind(void)
{
    return kind;
}


bool JCSqlExpression::spitTo(SqlCompileContext *aContext)
{
    cout << "ERRMSG: internal error, JCSqlExpression generic spitTo is called.\n";
    return false;
}


/**************************************************
* Implementation: JCSqlSelect.
**************************************************/

JCSqlSelect::JCSqlSelect(JCSqlSelectList *aList, JCSqlTableClause *tables)
    : JCSqlExpression(JCSqlExpression::kSelect)
{
    resultQuantifier= JCSqlConstants::noSetQuantifier;
    selectList= aList;
    tableDef= tables;
}


void JCSqlSelect::quantifySelection(JCSqlConstants::SetQuantifier aQuantification)
{
    resultQuantifier= aQuantification;
}


JCSqlSelectList *JCSqlSelect::getSelectList(void)
{
    return selectList;
}


bool JCSqlSelect::spitTo(SqlCompileContext *aContext)
{
    JCSqlExpression *qualifier;
    JCSqlTableRefList *sourceTables;
    JCSqlTableRef *tmpCursor;

    aContext->emitByte(JCSqlTokens::queryExpr);
    switch(resultQuantifier) {
	case JCSqlConstants::noSetQuantifier:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::quantUnspec);
	    break;
	case JCSqlConstants::distinctElements:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::quantDistinct);
	    break;
	case JCSqlConstants::allElements:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::quantAll);
	    break;
	default:
	    // TODO: Internal error message.
	    break;
    }
    selectList->spitTo(aContext);

    sourceTables= tableDef->getSourceTables();
    if (sourceTables->count() > 1) {
	aContext->emitByte(JCSqlTokens::list);
	aContext->emitShort(sourceTables->count());
    }
    tmpCursor= sourceTables->getFirstElement();
    while (tmpCursor != NULL) {
	tmpCursor->spitTo(aContext);
	tmpCursor= tmpCursor->getNext();
    }

    aContext->emitByte(JCSqlTokens::immediateConstant | tableDef->getOptionsIndicator());

    if ((qualifier= tableDef->getQualifier()) != NULL) {
	qualifier->spitTo(aContext);
    }

    return true;		// TMP: For now, always succed.
}


/**************************************************
* Implementation: JCSqlSynonym.
**************************************************/

JCSqlSynonym::JCSqlSynonym(JCSqlExpression *anExpression, JCSqlIdentifier *anIdentifier)
    : JCSqlExpression(JCSqlExpression::kSynonym)
{
    expression= anExpression;
    synonym= anIdentifier;
}


bool JCSqlSynonym::spitTo(SqlCompileContext *aContext)
{
    aContext->emitByte(JCSqlTokens::synonymExpr);
    aContext->mapIdentifier(synonym);
    aContext->emitByte(JCSqlTokens::identReference);
    aContext->emitShort(aContext->getReferenceID(synonym->getSimpleIdentifier()));
    expression->spitTo(aContext);

    return true;
}


/**************************************************
* Implementation: JCSqlColumnExpr.
**************************************************/

JCSqlColumnExpr::JCSqlColumnExpr(JCSqlIdentifier *anIdent)
    : JCSqlExpression(JCSqlExpression::kColumn)
{
    column= anIdent;
}


bool JCSqlColumnExpr::spitTo(SqlCompileContext *aContext)
{
    JCIdentifier *jcIdent, *nextJCIdent;

    if (column->isModuleHeader()) {
	aContext->emitByte(JCSqlTokens::moduleIdentifier);
    }

    aContext->mapIdentifier(column);
    jcIdent= column->getSimpleIdentifier();
    do {
	if ((nextJCIdent= jcIdent->getComponent()) == NULL) {
	    aContext->emitByte(JCSqlTokens::identReference);
	}
	else {
	    aContext->emitByte(JCSqlTokens::containerReference);
	}
	aContext->emitShort(aContext->getReferenceID(jcIdent));
    } while (nextJCIdent != NULL);

    return true;
}


/**************************************************
* Implementation: JCSqlEmbedded.
**************************************************/

JCSqlEmbedded::JCSqlEmbedded(JCExpression *anExpression)
    : JCSqlExpression(JCSqlExpression::kEmbeddedVar)
{
    next= NULL;
    javaExpr= anExpression;
    javaIndicator= NULL;
}


JCSqlEmbedded::JCSqlEmbedded(JCExpression *anExpression, JCExpression *anIndicator)
    : JCSqlExpression(JCSqlExpression::kEmbeddedVar)
{
    next= NULL;
    javaExpr= anExpression;
	// ATTN-980521 [HD]: The presence of the indicator is not always legal.
	// This has to be checked by the grammar parser. 
    javaIndicator= anIndicator;
}


void JCSqlEmbedded::link(JCSqlEmbedded *anEmbedded)
{
    next= anEmbedded;
}


JCSqlEmbedded *JCSqlEmbedded::getNext(void)
{
    return next;
}


void JCSqlEmbedded::mapToPool(ConstantsList *aPool)
{
    javaExpr->mapToPool(aPool);
    if (javaIndicator != NULL) javaIndicator->mapToPool(aPool);
}


bool JCSqlEmbedded::spitTo(SqlCompileContext *aContext)
{
    aContext->emitByte(JCSqlTokens::nativeHolder);
    aContext->emitShort(aContext->getHolderID(javaExpr));
    if (javaIndicator != NULL) {
	aContext->emitByte(JCSqlTokens::indicatorHolder);
	aContext->emitShort(aContext->getHolderID(javaIndicator));
    }
    return true;
}


void JCSqlEmbedded::spitBCodeTo(JCCompilationContext *aContext)
{
    spitIntoReceiver(aContext,  javaExpr);

    if (javaIndicator != NULL) {
	spitIntoReceiver(aContext,  javaIndicator);
    }
}


void JCSqlEmbedded::spitIntoReceiver(JCCompilationContext *aContext, JCExpression *aReceiver)
{
    bool leftIsScalar= true, isAssigned= aContext->isAssigning();

    aContext->setIfAssigning(false);

    switch(aReceiver->getCategory()) {		// fetch the receiver container, if necessary.
	case JCExpression::eVariable:
	    if (((JCVarAccess *)aReceiver)->resolution()->getCategory() == JCName::fieldVariable) {
		JCField *aField;

		aField= (JCField *)((JCResolved *)((JCVarAccess *)aReceiver)->resolution())->getDefinition();
		if (!aField->isStatic()) {
		    aContext->addInstruction(JCInstrSet::aload_0);
		    aContext->addInstruction(JCInstrSet::swap);
		}
	    }
	    break;
	case JCExpression::eField:
		// ATTN-980522 [HD]: Isn't there a check for 'static' necessary ?
	    if (((JCNamedExpr *)aReceiver)->getSubExpression() != NULL) {
		((JCNamedExpr *)aReceiver)->getSubExpression()->spitTo(aContext);
	    }
	    else {
// MOD-980511 [HD]: Replaced a 'iload_0' by a 'aload_0' (that was a bug).
		aContext->addInstruction(JCInstrSet::aload_0);
	    }
	    aContext->addInstruction(JCInstrSet::swap);
	    break;
	case JCExpression::eArray:
	    aContext->setIfAssigning(true);
	    aReceiver->spitTo(aContext);
	    aContext->setIfAssigning(false);
	    leftIsScalar= false;
	    aContext->addInstruction(JCInstrSet::swap);
	    break;
	default:	// Do nothing ?
	    cout << "ERRMSG: JCSqlEmbedded::spitIntoReceiver can not deal with category " << (int)aReceiver->getCategory() << ".\n";
	    break;
    }

    if (leftIsScalar) {
	aContext->setIfAssigning(true);
	aReceiver->spitTo(aContext);
    }
    else {
	((JCArrayAccess *)aReceiver)->spitStorerTo(aContext);
    }
    aContext->setIfAssigning(isAssigned);
}

JCExpression *JCSqlEmbedded::getExpression(void)
{
    return javaExpr;
}


JCExpression *JCSqlEmbedded::getIndicator(void)
{
    return javaIndicator;
}


/**************************************************
* Implementation: JCSqlContainerExpr.
**************************************************/

JCSqlContainerExpr::JCSqlContainerExpr(void *aValue, JCSqlContainerExpr::Operators anOperator)
    : JCSqlExpression(JCSqlExpression::kContainer)
{
    containee= aValue;
    operation= anOperator;
}


bool JCSqlContainerExpr::spitTo(SqlCompileContext *aContext)
{
    return true;		// TMP: always succeed.
}


JCSqlContainerExpr::Operators JCSqlContainerExpr::getOperation(void)
{
    return operation;
}


void *JCSqlContainerExpr::getValue(void)
{
    return containee;
}


/**************************************************
* Implementation: JCSqlOperExpr.
**************************************************/

JCSqlOperExpr::Operators JCSqlOperExpr::mergeSetOperators(Operators anOp, JCSqlConstants::SetQuantifier quantifier)
{
    if (quantifier == JCSqlConstants::allElements) {
	switch(anOp) {
	    case JCSqlOperExpr::equal:
		return JCSqlOperExpr::eqAll;
		break;
	    case JCSqlOperExpr::notEqual:
		return JCSqlOperExpr::neAll;
		break;
	    case JCSqlOperExpr::lt:
		return JCSqlOperExpr::ltAll;
		break;
	    case JCSqlOperExpr::gt:
		return JCSqlOperExpr::gtAll;
		break;
	    case JCSqlOperExpr::le:
		return JCSqlOperExpr::leAll;
		break;
	    case JCSqlOperExpr::ge:
		return JCSqlOperExpr::geAll;
		break;
	}
    }
    else if (quantifier == JCSqlConstants::some) {
	switch(anOp) {
	    case JCSqlOperExpr::equal:
		return JCSqlOperExpr::eqSome;
		break;
	    case JCSqlOperExpr::notEqual:
		return JCSqlOperExpr::neSome;
		break;
	    case JCSqlOperExpr::lt:
		return JCSqlOperExpr::ltSome;
		break;
	    case JCSqlOperExpr::gt:
		return JCSqlOperExpr::gtSome;
		break;
	    case JCSqlOperExpr::le:
		return JCSqlOperExpr::leSome;
		break;
	    case JCSqlOperExpr::ge:
		return JCSqlOperExpr::geSome;
		break;
	}
    }
    else if (quantifier == JCSqlConstants::any) {
	switch(anOp) {
	    case JCSqlOperExpr::equal:
		return JCSqlOperExpr::eqAny;
		break;
	    case JCSqlOperExpr::notEqual:
		return JCSqlOperExpr::neAny;
		break;
	    case JCSqlOperExpr::lt:
		return JCSqlOperExpr::ltAny;
		break;
	    case JCSqlOperExpr::gt:
		return JCSqlOperExpr::gtAny;
		break;
	    case JCSqlOperExpr::le:
		return JCSqlOperExpr::leAny;
		break;
	    case JCSqlOperExpr::ge:
		return JCSqlOperExpr::geAny;
		break;
	}
    }
    else {
	// ATTN: Signal the internal error !
	return anOp;
    }
    return anOp;
}


JCSqlOperExpr::JCSqlOperExpr(JCSqlExpression *leftOperand, JCSqlExpression *rightOperand, Operators anOperator)
    : JCSqlExpression(JCSqlExpression::kOperation)
{
    left= leftOperand;
    right= rightOperand;
    operation= anOperator;
}


bool JCSqlOperExpr::spitTo(SqlCompileContext *aContext)
{
    aContext->emitByte(JCSqlTokens::mapOperToToken(operation));
    if (left != NULL) {
	left->spitTo(aContext);
    }
    if (right != NULL) {
	right->spitTo(aContext);
    }
    return true;
}


/**************************************************
* Implementation: JCSqlFunction.
**************************************************/

JCSqlFunction *JCSqlFunction::builtinFcts[JCSqlFunction::nbrBuiltIn]= { NULL };


void JCSqlFunction::initBuiltinFunctions(void)
{
    builtinFcts[0]= new JCSqlFunction[5];
    for (unsigned int i= 0; i < nbrBuiltIn-1; i++) {
	builtinFcts[i+1]= builtinFcts[i]+1;
    }
    builtinFcts[countStar]->function= countStar;
    builtinFcts[avg]->function= avg;
    builtinFcts[max]->function= max;
    builtinFcts[min]->function= min;
    builtinFcts[sum]->function= sum;
    builtinFcts[count]->function= count;
}


JCSqlFunction *JCSqlFunction::getBuiltin(BuiltinFcts aFct)
{
    if (builtinFcts[0] == NULL) {
	initBuiltinFunctions();
    }
    if ((aFct >= countStar) && (aFct < nbrBuiltIn)) {
	return builtinFcts[aFct];
    }
    else return NULL;
}


JCSqlFunction::JCSqlFunction()
    : JCSqlExpression(kFunction)
{
    function= customFunction;
    operQuantifier= JCSqlConstants::noSetQuantifier;
    operand= NULL;
}


void JCSqlFunction::setQuantifier(JCSqlConstants::SetQuantifier aQuantifier)
{
    operQuantifier= aQuantifier;
}


void JCSqlFunction::setOperands(JCSqlExpression *anOperand)
{
    operand= anOperand;
}


bool JCSqlFunction::spitTo(SqlCompileContext *aContext)
{
    bool result= false;

    if (function != customFunction) {
	aContext->emitByte(JCSqlTokens::functionCall);
	if (function == countStar) {
	    aContext->emitByte(JCSqlTokens::fctCountStar);
	    result= true;
	}
	else {	// Function with parameter.
	    switch(function) {
		case avg:
		    aContext->emitByte(JCSqlTokens::fctAvg);
		    break;
		case max:
		    aContext->emitByte(JCSqlTokens::fctMax);
		    break;
		case min:
		    aContext->emitByte(JCSqlTokens::fctMin);
		    break;
		case sum:
		    aContext->emitByte(JCSqlTokens::fctSum);
		    break;
		case count:
		    aContext->emitByte(JCSqlTokens::fctCount);
		    break;
		default:
		    // TODO: Internal error message.
		    break;
	    }
	    switch(operQuantifier) {
		case JCSqlConstants::noSetQuantifier:
		    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::quantUnspec);
		    break;
		case JCSqlConstants::distinctElements:
		    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::quantDistinct);
		    break;
		case JCSqlConstants::allElements:
		    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::quantAll);
		    break;
		default:
		    // TODO: Internal error message.
		    break;
	    }
	    operand->spitTo(aContext);
	    result= true;
	}
    }
    else {
	// TODO: Handle prefix for custom functions.
    }
    return result;
}


/**************************************************
* Implementation: JCSqlConstantExpr.
**************************************************/

JCSqlConstantExpr *JCSqlConstantExpr::popularValues[JCSqlConstantExpr::nbrPopulars]= { NULL };

JCSqlConstantExpr *JCSqlConstantExpr::getPopularConstant(Populars aPopular)
{
    if (popularValues[popNullCte] == NULL) {
	popularValues[0]= new JCSqlConstantExpr[nbrPopulars];
	for (unsigned int i= 0; i < nbrPopulars-1; i++) {
	    popularValues[i+1]= popularValues[i]+1;
	}
	popularValues[popNullCte]->setSpecial(popNullCte);
	popularValues[popDefaultCte]->setSpecial(popDefaultCte);
	popularValues[popUser]->setSpecial(popUser);
	popularValues[popCurrent]->setSpecial(popCurrent);
	popularValues[popSession]->setSpecial(popSession);
	popularValues[popSystem]->setSpecial(popSystem);
	popularValues[popValue]->setSpecial(popValue);
    }

    if ((aPopular >= popNullCte) && (aPopular < nbrPopulars)) {
	return popularValues[aPopular];
    }
    else return NULL;
}


JCSqlConstantExpr::JCSqlConstantExpr(void)
    : JCSqlExpression(JCSqlExpression::kConstant)
{
    type= tSpecial;
    value= (void *)popNullCte;
}


JCSqlConstantExpr::JCSqlConstantExpr(Type aType)
    : JCSqlExpression(JCSqlExpression::kConstant)
{
    type= aType;
}


void JCSqlConstantExpr::setSpecial(Populars aPop)
{
    type= tSpecial;
    value= (void *)aPop;
}


bool JCSqlConstantExpr::spitTo(SqlCompileContext *aContext)
{
    if (type == tSpecial) {
	if (value == (void *)popNullCte) {
	    aContext->emitByte(JCSqlTokens::nullIdentifier);
	}
	else {
	    char aByte;

	    aContext->emitByte(JCSqlTokens::specialConstant);
	    switch((Populars)(int)value) {
		case popDefaultCte:
		    aByte= JCSqlTokens::defaultCte;
		    break;
		case popUser:
		    aByte= JCSqlTokens::user;
		    break;
		case popCurrent:
		    aByte= JCSqlTokens::current;
		    break;
		case popSession:
		    aByte= JCSqlTokens::session;
		    break;
		case popSystem:
		    aByte= JCSqlTokens::system;
		    break;
		case popValue:
		    aByte= JCSqlTokens::value;
		    break;
		default:
		    aByte= JCSqlTokens::defaultCte;
		    cout << "ERRMSG: internal error, JcSqlConstanExpr::spitTo deals with unknown special constant.\n";
		    break;
	    }
	    aContext->emitByte(JCSqlTokens::immediateConstant | aByte);
	}
    }
    else if (type == tEnumerated) {
	aContext->emitByte(JCSqlTokens::enumConstant);
	aContext->emitShort(0);		// TMPTMP: Must emit the id of the value in the enum list.
    }
    else {		// All other constant types should be spitted by their proper sub-classes.
	cout << "ERRMSG: internal error, JcSqlConstanExpr::spitTo deals with unknown type of value.\n";
    }

    return true;
}


/**************************************************
* Implementation: JCSqlNumericCte.
**************************************************/

JCSqlNumericCte::JCSqlNumericCte(unsigned int anInt)
    : JCSqlConstantExpr(JCSqlConstantExpr::tInteger)
{
    value= (void *)anInt;
}


JCSqlNumericCte::JCSqlNumericCte(float aFloat)
    : JCSqlConstantExpr(JCSqlConstantExpr::tReal)
{
    float *bridge= &aFloat;
    int *intBridge;

    intBridge= (int *)bridge;
    value= (void *)*intBridge;
}


void JCSqlNumericCte::posate(void)
{
    // ATTN-980520 [HD]: Anything to do ?
}


void JCSqlNumericCte::negate(void)
{
    if (type == tReal) {
	float *bridge;
	unsigned int intBridge= (unsigned int)value;

	bridge= (float *)&intBridge;
	(*bridge)*= -1.0f;
	value= (void *)intBridge;
    }
    else if (type == tInteger) {
	value= (void *)(-(int)value);
    }
}


bool JCSqlNumericCte::spitTo(SqlCompileContext *aContext)
{
    if (type == tInteger) {
	aContext->emitByte(JCSqlTokens::integerLiteral);
	aContext->emitInteger((unsigned int)value);
    }
    else if (type == tReal) {
	aContext->emitByte(JCSqlTokens::floatLiteral);
	aContext->emitInteger((unsigned int)value);
    }
    else {
	cout << "ERRMSG: internal error, JCSqlNumericCte::spitTo deals with unknown type of value.\n";
    }
    return true;
}


/**************************************************
* Implementation: JCSqlBoolCte.
**************************************************/

JCSqlBoolCte::JCSqlBoolCte(JCSqlConstants::TruthValues aValue)
    : JCSqlConstantExpr(JCSqlConstantExpr::tBoolean)
{
    if (aValue == JCSqlConstants::tvTrue) {
	value= (void *)0x01;
    }
    else if (aValue == JCSqlConstants::tvFalse) {
	value= (void *)0x00;
    }
    else if (aValue == JCSqlConstants::tvUnknown) {
	value= (void *)0x0FFFFFFFF;
    }
}


bool JCSqlBoolCte::spitTo(SqlCompileContext *aContext)
{
    switch((unsigned int)value) {
	case 0x01:
	    aContext->emitByte(JCSqlTokens::trueBoolLiteral);
	    break;
	case 0x00:
	    aContext->emitByte(JCSqlTokens::falseBoolLiteral);
	    break;
	case 0x0FFFFFFFF:
	    aContext->emitByte(JCSqlTokens::maybeBoolLiteral);
	    break;
	default:
	    cout << "ERRMSG: Internal error, JCSqlBoolCte::spitTo deals with unknown value.\n";
	    break;
    }
    return true;
}


/**************************************************
* Implementation: JCSqlCharCte.
**************************************************/
JCSqlCharCte::JCSqlCharCte(wchar *aCharArray)
    : JCSqlConstantExpr(JCSqlConstantExpr::tChar)
{
    unsigned int totalLength= 0;
    wchar *tmpWideChar= aCharArray;
    char *tmpChar;

    while ((*tmpWideChar) != 0) { tmpWideChar++; totalLength++; };
    value= tmpChar= new char[totalLength + 1];
    while ((*aCharArray) != 0) { *tmpChar++= (char)(*aCharArray++ & 0x0FF); }
    *tmpChar= '\0';
}


bool JCSqlCharCte::spitTo(SqlCompileContext *aContext)
{
    aContext->emitByte(JCSqlTokens::charLiteral);
    aContext->emitShort(aContext->getStringID(value));
    return true;
}


/**************************************************
* Implementation: JCSqlListExpr.
**************************************************/

JCSqlListExpr::JCSqlListExpr(JCSqlClause *aClause)
    : JCSqlExpression(JCSqlExpression::kList)
{
    clause= aClause;
}


bool JCSqlListExpr::spitTo(SqlCompileContext *aContext)
{
    JCSqlRowValue *rowValueCursor;
    unsigned int i;

    switch(clause->getKind()) {
	case JCSqlClause::rvConstrList:
	    i= ((JCSqlRowValueList *)clause)->count();
	    if (i > 1) {
		aContext->emitByte(JCSqlTokens::list);
		aContext->emitShort(i);
	    }
	    rowValueCursor= ((JCSqlRowValueList *)clause)->getFirstElement();
	    while (rowValueCursor != NULL) {
		rowValueCursor->getValue()->spitTo(aContext);
		rowValueCursor= rowValueCursor->getNext();
	    }
	    break;
    }
    return true;		// TMP: always succeed.
}


/**************************************************
* Implementation: JCSqlFetchOrientation.
**************************************************/

JCSqlFetchOrientation *JCSqlFetchOrientation::simpleOrientation[JCSqlFetchOrientation::nbrSimpleOrientations]= { NULL };


JCSqlFetchOrientation *JCSqlFetchOrientation::getSimpleOrientation(JCSqlConstants::FetchOrder anOrder)
{
    if (simpleOrientation[0] == NULL) {
	simpleOrientation[0]= new JCSqlFetchOrientation[nbrSimpleOrientations];
	for (unsigned int i= 0; i < nbrSimpleOrientations-1; i++) {
	    simpleOrientation[i+1]= simpleOrientation[i]+1;
	}
	simpleOrientation[JCSqlConstants::foNatural]->orientation= JCSqlConstants::foNatural;
	simpleOrientation[JCSqlConstants::foNext]->orientation= JCSqlConstants::foNext;
	simpleOrientation[JCSqlConstants::foPrior]->orientation= JCSqlConstants::foPrior;
	simpleOrientation[JCSqlConstants::foFirst]->orientation= JCSqlConstants::foFirst;
	simpleOrientation[JCSqlConstants::foLast]->orientation= JCSqlConstants::foLast;
    }
    if ((anOrder >= JCSqlConstants::foNatural) && (anOrder < nbrSimpleOrientations)) {
	return simpleOrientation[anOrder];
    }
    else return NULL;
}


JCSqlFetchOrientation::JCSqlFetchOrientation(void)
    : JCSqlExpression(kFetchOrientation)
{
    orientation= JCSqlConstants::foNatural;
    baseValue= NULL;
}


JCSqlFetchOrientation::JCSqlFetchOrientation(JCSqlConstants::FetchOrder anOrder, JCSqlExpression *anExpr)
    : JCSqlExpression(kFetchOrientation)
{
    orientation= anOrder;
    baseValue= anExpr;
}


bool JCSqlFetchOrientation::spitTo(SqlCompileContext *aContext)
{
    bool result= true;

    switch(orientation) {
	case JCSqlConstants::foNext:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::ordNext);
	    break;
	case JCSqlConstants::foPrior:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::ordPrior);
	    break;
	case JCSqlConstants::foFirst:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::ordFirst);
	    break;
	case JCSqlConstants::foLast:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::ordLast);
	    break;
	case JCSqlConstants::foAbsolute:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::ordAbsolute);
	    break;
	case JCSqlConstants::foRelative:
	    aContext->emitByte(JCSqlTokens::immediateConstant | JCSqlTokens::ordRelative);
	    break;
    }
    if ((orientation == JCSqlConstants::foAbsolute) || (orientation == JCSqlConstants::foRelative)) {
	result= baseValue->spitTo(aContext);
    }

    return result;
}
