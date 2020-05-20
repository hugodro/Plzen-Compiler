/**************************************************
* File: sqlActions.cc.
* Desc: Implementation of the JCSqlStatement hierarchy.
* Module: AkraLog : JavaKit.
* Rev: 1 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include "sql3Support.h"
#include "sqlCompContext.h"
#include "sqlExpressions.h"
#include "sqlClauses.h"
#include "expressions.h"
#include "instructions.h"
#include "compContext.h"
#include "constants.h"
#include "sqlSpitters.h"
#include "sqlIdentifier.h"
#include "sqlActions.h"


/**************************************************
* Implementation: JCSqlStatement.
**************************************************/

JCSqlStatement::JCSqlStatement(void)
{
    actionType= SQL_STAT;
    category= cUnknown;
    compiledValue= new JCCteExpr[2];
    compiledValue[0].linkExpression(&compiledValue[1]);
    nbrEmbedded= 0;
    embeddeds= NULL;
}


JCSqlStatement::JCSqlStatement(Category aCategory)
{
    actionType= SQL_STAT;
    category= aCategory;
    compiledValue= new JCCteExpr[2];
    compiledValue[0].linkExpression(&compiledValue[1]);
    nbrEmbedded= 0;
    embeddeds= NULL;
}


void JCSqlStatement::link(JCSqlStatement *aStatement)
{
    next= aStatement;
}


void JCSqlStatement::spitHolesTo(JCCompilationContext *codeContext)
{
    if (nbrEmbedded > 0) {
	for (unsigned int i= 0; i < nbrEmbedded; i++) {
	    embeddeds[i]->spitTo(codeContext);
	}
    }
}


void JCSqlStatement::spitTruePostscriptum(JCCompilationContext *codeContext, unsigned int falseLabel)
{
    codeContext->addInstruction(JCInstrSet::ifeq, falseLabel);
	// Make sure that 'true' was sent back.
}


void JCSqlStatement::spitFalsePostscriptum(JCCompilationContext *codeContext)
{
// TODO: Anything to clean-up ??
}


void JCSqlStatement::consolidate(void)
{
    cout << "ERRMSG: internal error, JCSqlStatement generic consolidate is called.\n";
}


void JCSqlStatement::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    generateTokens();
    if (compiledValue != NULL) {
	compiledValue[0].mapToPool(aPool);
	compiledValue[1].mapToPool(aPool);
    }
    if (nbrEmbedded > 0) {
	for (unsigned int i= 0; i < nbrEmbedded; i++) {
	    embeddeds[i]->mapToPool(aPool);
	}
    }
}


void JCSqlStatement::attachInvoker(JCExecSqlInvoke *anInvoker)
{
    anInvoker->useArguments(compiledValue);
}


void JCSqlStatement::generateTokens(void)
{
    // Do nothing ?
}


/**************************************************
* Implementation: JCSqlOpen.
**************************************************/

JCSqlOpen::JCSqlOpen(JCIdentifier *aCursor)
    : JCSqlStatement(JCSqlStatement::cOpen)
{
// TODO.
}


/**************************************************
* Implementation: JCSqlFetch.
**************************************************/

JCSqlFetch::JCSqlFetch(JCSqlFetchOrientation *anOrder, JCSqlIdentifier *anIdent, JCSqlTargetList *varList)
    : JCSqlStatement(cFetch)
{
    orientation= anOrder;
    cursor= anIdent;
    localVars= varList;
    outCountArg= new JCCteExpr();
    compiledValue[1].linkExpression(outCountArg);
}


void JCSqlFetch::consolidate(void)
{
    unsigned int i;

    if (localVars == NULL) {
	// Note: This is a fetch without any result taken.  Should it be legal ?
	outCountArg->setIntValue(0);	// No output is expected.
    }
    else {
    	// Note: The count must be matched with the 'cursor' definition.
	outCountArg->setIntValue(localVars->count());
    }
}


void JCSqlFetch::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCSqlStatement::mapToPool(aPool, varIndexOffset);

    if (outCountArg != NULL) {
	outCountArg->mapToPool(aPool);
    }
    if (localVars != NULL) {
	JCSqlEmbedded *tmpCursor;

	tmpCursor= localVars->getFirstElement();
	while (tmpCursor != NULL) {
	    tmpCursor->mapToPool(aPool);
	    tmpCursor= tmpCursor->getNext();
	}
    }
}


void JCSqlFetch::spitTruePostscriptum(JCCompilationContext *codeContext, unsigned int falseLabel)
{
    JCSqlStatement::spitTruePostscriptum(codeContext, falseLabel);
	// Generate all code for the return of values.

    if (localVars != NULL) {
	JCSqlEmbedded *tmpCursor;

	tmpCursor= localVars->getFirstElement();
	while (tmpCursor != NULL) {
	    tmpCursor->spitBCodeTo(codeContext);
	    tmpCursor= tmpCursor->getNext();
	}
    }

}


void JCSqlFetch::generateTokens(void)
{
    JCTokenBuffer *tokenBuffer;
    SqlCompileContext *context;
    unsigned int i;
    char *sqlTokens, *signOut;

    tokenBuffer= new JCTokenBuffer();
    context= new SqlCompileContext(tokenBuffer);

    tokenBuffer->addByte(FETCH_DATA);
    orientation->spitTo(context);
    context->mapIdentifier(cursor);
    context->emitByte(JCSqlTokens::identReference);
    context->emitShort(context->getReferenceID(cursor->getSimpleIdentifier()));

    if (localVars != NULL) {
	if (localVars->count() > 0) {
	    unsigned int tmpLocalCount;
	    JCSqlEmbedded *tmpCursor;
	    JCReferencedType *tmpType;

	    tmpLocalCount= localVars->count();
	    signOut= new char[tmpLocalCount  * 2 + 1];    // Allocate enough place for indicator types.
    
	    tmpCursor= localVars->getFirstElement();
	    i= 0;
	    while (tmpCursor != NULL) {
		tmpType= tmpCursor->getExpression()->getFinalType();
		if (tmpType->isPrimitive()) {
		    tmpType->composeSignature(&signOut[i++]);
		}
		else if (tmpType->isString()) {
		    signOut[i++]= AKR_TYPE_STRING;
		}
		else {
		    cout << "ERRMSG: JCSqlFetchStat::consolidate: complex types are not yet supported.\n";
		}
		if (tmpCursor->getIndicator() != NULL) {
		    tmpType= tmpCursor->getIndicator()->getFinalType();
		    if (tmpType->isPrimitive()) {
			tmpType->composeSignature(&signOut[i++]);
		    }
		    else if (tmpType->isString()) {
			signOut[i++]= AKR_TYPE_STRING;
		    }
		    else {
			cout << "ERRMSG: JCSqlFetchStat::consolidate: complex types are not yet supported.\n";
		    }
		}
    
		tmpCursor= tmpCursor->getNext();
	    }
    
	    signOut[i]= '\0';
	}
	else {		// This should never happen !
	    signOut= new char[2];
	    signOut[0]= 'V';
	    signOut[1]= '\0';
	}
    }
    else {
	// The fetch is not sending results anywhere.  Should it be legal ?
	signOut= new char[2];
	signOut[0]= 'V';
	signOut[1]= '\0';
    }

    context->saveTokens(&sqlTokens, NULL, signOut);
    compiledValue[0].setStringValue((unsigned short *)sqlTokens);
/* TODO: Support the possibility of having embedded values in the fetch orientation component.
    compiledValue[1].setIntValue(nbrEmbedded);
*/

    delete signOut;
    delete context;
}


/**************************************************
* Implementation: JCSqlClose.
**************************************************/

JCSqlClose::JCSqlClose(JCIdentifier *aCursor)
    : JCSqlStatement(JCSqlStatement::cClose)
{
// TODO.
}


/**************************************************
* Implementation: JCSqlDelete.
**************************************************/

JCSqlDelete::JCSqlDelete()
    : JCSqlStatement(JCSqlStatement::cDelete)
{
// TODO.
}


/**************************************************
* Implementation: JCSqlInsert.
**************************************************/

JCSqlInsert::JCSqlInsert()
    : JCSqlStatement(JCSqlStatement::cInsert)
{
    tableName= NULL;
    columnTargets= NULL;
    values= NULL;
// TMP: This is always going to be zero...  Must find a better way to indicate that the statement
//	has no output.
    outCountArg= new JCCteExpr();
    outCountArg->setIntValue(0);
    compiledValue[1].linkExpression(outCountArg);
}

JCSqlInsert::JCSqlInsert(JCSqlIdentifier *aName, JCSqlIdentList *someNames, JCSqlExpression *valueSpec)
{
    tableName= aName;
    columnTargets= someNames;
    values= valueSpec;
// TMP: This is always going to be zero...  Must find a better way to indicate that the statement
//	has no output.
    outCountArg= new JCCteExpr();
    outCountArg->setIntValue(0);
    compiledValue[1].linkExpression(outCountArg);
}


void JCSqlInsert::setTableName(JCSqlIdentifier *aName)
{
    tableName= aName;
}


void JCSqlInsert::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCSqlStatement::mapToPool(aPool, varIndexOffset);

    if (outCountArg != NULL) {
	outCountArg->mapToPool(aPool);
    }
}


void JCSqlInsert::generateTokens(void)
{
    JCTokenBuffer *tokenBuffer;
    SqlCompileContext *context;
    JCReferencedType *tmpType;
    JCSqlIdentifier *tmpCursor;
    unsigned int i;
    char *sqlTokens, *signIn;
    unsigned char formatFlags= 0;

    tokenBuffer= new JCTokenBuffer();
    context= new SqlCompileContext(tokenBuffer);
    tokenBuffer->addByte(INSERT_DATA);

    context->mapIdentifier(tableName);
    context->emitByte(JCSqlTokens::identReference);
    context->emitShort(context->getReferenceID(tableName->getSimpleIdentifier()));

    // The formatFlags is made of the following bits:
    //	0: 0 => DEFAULT VALUES.
    //	1: 0 => expression.
    //	2: 0 => table name; 1 => values.
    //	3: 1 => column names are given.

    if ((columnTargets != NULL) || (values != NULL)) formatFlags= 1;
    if (columnTargets != NULL) {
	formatFlags|= 8;
    }
    if (values != NULL) {
	if (values->getKind() == JCSqlExpression::kContainer) {
	    formatFlags|= 2;
	    if (((JCSqlContainerExpr *)values)->getOperation() == JCSqlContainerExpr::values) {
		formatFlags|= 4;
	    }
	}
    }
    context->emitByte(JCSqlTokens::immediateConstant | formatFlags);

    if (columnTargets != NULL) {
	i= columnTargets->count();
	tmpCursor= columnTargets->getFirstElement();
	context->emitByte(JCSqlTokens::list);
	context->emitShort(i);
	while (tmpCursor != NULL) {
	    context->mapIdentifier(tmpCursor);
	    context->emitByte(JCSqlTokens::identReference);
	    context->emitShort(context->getReferenceID(tmpCursor->getSimpleIdentifier()));
	    tmpCursor= tmpCursor->getNext();
	}
    }

    if (values != NULL) {
	if (formatFlags & 2) {	// The values contains a table name or a row list.
	    if (formatFlags & 4) {		// Row values list.
		JCSqlRowValueList *valueList;
		JCSqlRowValue *rowCursor;

		valueList= (JCSqlRowValueList *)((JCSqlContainerExpr *)values)->getValue();
		i= valueList->count();
		if (i > 1) {
		    context->emitByte(JCSqlTokens::list);
		    context->emitShort(i);
		}
		rowCursor= valueList->getFirstElement();
		while (rowCursor != NULL) {
		    rowCursor->getValue()->spitTo(context);
		    rowCursor= rowCursor->getNext();
		}
	    }
	    else {		// Explicit table name.
		tmpCursor= (JCSqlIdentifier *)((JCSqlContainerExpr *)values)->getValue();
		context->mapIdentifier(tmpCursor);
		context->emitByte(JCSqlTokens::identReference);
		context->emitShort(context->getReferenceID(tmpCursor->getSimpleIdentifier()));
	    }
	}
	else {
	    ((JCSqlExpression *)values)->spitTo(context);
	}
    }

    if ((nbrEmbedded= context->getEmbeddedCount()) != 0) {
	JCExpression **tmpEmbedded= context->getEmbedded();

	signIn= new char[nbrEmbedded + 1];
	embeddeds= new JCExpression *[nbrEmbedded];

	for (i= 0; i < nbrEmbedded; i++) {
	    embeddeds[i]= *tmpEmbedded++;
	    tmpType= embeddeds[i]->getFinalType();
	    if (tmpType->isPrimitive()) {
		tmpType->composeSignature(&signIn[i]);
	    }
	    else if (tmpType->isString()) {
		signIn[i]= AKR_TYPE_STRING;
	    }
	    else {
		cout << "ERRMSG: JCSqlInsertStat::consolidate: complex types are not yet supported.\n";
	    }
	}
	signIn[i]= '\0';
    }
    else {
	signIn= new char[2];
	signIn[0]= 'V';
	signIn[1]= '\0';
    }

    context->saveTokens(&sqlTokens, signIn, NULL);
    compiledValue[0].setStringValue((unsigned short *)sqlTokens);
    compiledValue[1].setIntValue(nbrEmbedded);

    delete signIn;
    delete context;
}


/**************************************************
* Implementation: JCSqlUpdate.
**************************************************/

JCSqlUpdate::JCSqlUpdate()
    : JCSqlStatement(JCSqlStatement::cUpdate)
{
// TODO.
}


/**************************************************
* Implementation: JCSqlSelectStat.
**************************************************/

JCSqlSelectStat::JCSqlSelectStat(JCSqlSelect *selectExpr, JCSqlTargetList *intos)
    : JCSqlStatement(JCSqlStatement::cSelect)
{
    select= selectExpr;
    localVars= intos;
    outCountArg= new JCCteExpr();
    compiledValue[1].linkExpression(outCountArg);
}


void JCSqlSelectStat::consolidate(void)
{
    unsigned int i;

    if (localVars == NULL) {
	// The select is not an 'into'.  This kind of select should only be used with
	// a cursor and fetch match.
	outCountArg->setIntValue(0);	// No output is expected.
    }
    else {
	if (select->getSelectList()->isStar()) {
	    // TMP: If there is no direct match, we complain.  When NameSpace is available,
	    // the match will have to be done precisely, and '*' will be meaningful.
	    cout << "ERRMSG: JCSqlSelectStat: star selection not yet allowed.\n";
	    return;		// Warning: quick exit.
	}
	else if (select->getSelectList()->count() != localVars->count()) {
	    // TMP: If there is no direct match, we complain.  When NameSpace is available,
	    // the match will have to be done precisely, and '*' will be meaningful.
	    cout << "ERRMSG: JCSqlSelectStat: mismatch in select and target count.\n";
	    return;		// Warning: quick exit.
	}
    
	outCountArg->setIntValue(localVars->count());
    }
}


void JCSqlSelectStat::mapToPool(ConstantsList *aPool, unsigned int varIndexOffset)
{
    JCSqlStatement::mapToPool(aPool, varIndexOffset);

    if (outCountArg != NULL) {
	outCountArg->mapToPool(aPool);
    }
    if (localVars != NULL) {
	JCSqlEmbedded *tmpCursor;

	tmpCursor= localVars->getFirstElement();
	while (tmpCursor != NULL) {
	    tmpCursor->mapToPool(aPool);
	    tmpCursor= tmpCursor->getNext();
	}
    }
}


void JCSqlSelectStat::spitTruePostscriptum(JCCompilationContext *codeContext, unsigned int falseLabel)
{
    JCSqlStatement::spitTruePostscriptum(codeContext, falseLabel);
	// Generate all code for the return of values.

    if (localVars != NULL) {
	JCSqlEmbedded *tmpCursor;

	tmpCursor= localVars->getFirstElement();
	while (tmpCursor != NULL) {
	    tmpCursor->spitBCodeTo(codeContext);
	    tmpCursor= tmpCursor->getNext();
	}
    }

}


void JCSqlSelectStat::generateTokens(void)
{
    JCTokenBuffer *tokenBuffer;
    SqlCompileContext *context;
    JCReferencedType *tmpType;
    unsigned int i;
    char *sqlTokens, *signIn, *signOut;

    tokenBuffer= new JCTokenBuffer();
    context= new SqlCompileContext(tokenBuffer);
    tokenBuffer->addByte(SELECT_SNG_DATA);
    select->spitTo(context);

    if ((nbrEmbedded= context->getEmbeddedCount()) != 0) {
	JCExpression **tmpEmbedded= context->getEmbedded();

	signIn= new char[nbrEmbedded + 1];
	embeddeds= new JCExpression *[nbrEmbedded];

	for (i= 0; i < nbrEmbedded; i++) {
	    embeddeds[i]= *tmpEmbedded++;
	    tmpType= embeddeds[i]->getFinalType();
	    if (tmpType->isPrimitive()) {
		tmpType->composeSignature(&signIn[i]);
	    }
	    else if (tmpType->isString()) {
		signIn[i]= AKR_TYPE_STRING;
	    }
	    else {
		cout << "ERRMSG: JCSqlSelectStat::consolidate: complex types are not yet supported.\n";
	    }
	}
	signIn[i]= '\0';
    }
    else {
	signIn= new char[2];
	signIn[0]= 'V';
	signIn[1]= '\0';
    }

    if (localVars != NULL) {
	if (localVars->count() > 0) {
	    unsigned int tmpLocalCount;
	    JCSqlEmbedded *tmpCursor;
    
	    tmpLocalCount= localVars->count();
	    signOut= new char[tmpLocalCount  * 2 + 1];    // Allocate enough place for indicator types.
    
	    tmpCursor= localVars->getFirstElement();
	    i= 0;
	    while (tmpCursor != NULL) {
		tmpType= tmpCursor->getExpression()->getFinalType();
		if (tmpType->isPrimitive()) {
		    tmpType->composeSignature(&signOut[i++]);
		}
		else if (tmpType->isString()) {
		    signOut[i++]= AKR_TYPE_STRING;
		}
		else {
		    cout << "ERRMSG: JCSqlSelectStat::consolidate: complex types are not yet supported.\n";
		}
		if (tmpCursor->getIndicator() != NULL) {
		    tmpType= tmpCursor->getIndicator()->getFinalType();
		    if (tmpType->isPrimitive()) {
			tmpType->composeSignature(&signOut[i++]);
		    }
		    else if (tmpType->isString()) {
			signOut[i++]= AKR_TYPE_STRING;
		    }
		    else {
			cout << "ERRMSG: JCSqlSelectStat::consolidate: complex types are not yet supported.\n";
		    }
		}
    
		tmpCursor= tmpCursor->getNext();
	    }
    
	    signOut[i]= '\0';
	}
	else {		// This should never happen !
	    signOut= new char[2];
	    signOut[0]= 'V';
	    signOut[1]= '\0';
	}
    }
    else {
	// The select is not an 'into'.
	signOut= new char[2];
	signOut[0]= 'V';
	signOut[1]= '\0';
    }

    context->saveTokens(&sqlTokens, signIn, signOut);
    compiledValue[0].setStringValue((unsigned short *)sqlTokens);
    compiledValue[1].setIntValue(nbrEmbedded);

    delete signIn;
    delete signOut;
    delete context;
}