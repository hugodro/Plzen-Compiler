/**************************************************
* File: sqlClauses.cc.
* Desc: Implementation of the JCSqlClause hierarchy.
* Module: AkraLog : JavaKit.
* Rev: 2 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include "sqlExpressions.h"
#include "sqlIdentifier.h"
#include "sqlCompContext.h"
#include "sqlSpitters.h"
#include "identifiers.h"
#include "sqlClauses.h"


/**************************************************
* Implementation: JCSqlClause.
**************************************************/


/**************************************************
* Implementation: JCSqlSelectList.
**************************************************/

JCSqlSelectList::JCSqlSelectList(void)
{
    nbrElements= 0;
    elements= lastElement= NULL;
}


JCSqlSelectList::JCSqlSelectList(JCSqlSelectItem *anElement)
{
    nbrElements= 1;
    elements= lastElement= anElement;
}


void JCSqlSelectList::setStar(void)
{
    nbrElements= 0x0FFFFFFFF;
    elements= lastElement= NULL;
}


void JCSqlSelectList::addElement(JCSqlSelectItem *anElement)
{
    if (nbrElements != 0x0FFFFFFFF) {
	if (nbrElements == 0) {
	    elements= anElement;
	}
	else {
	    lastElement->link(anElement);
	}
	nbrElements++;
	lastElement= anElement;
    }
}


unsigned int JCSqlSelectList::count()
{
    if (nbrElements == 0x0FFFFFFFF) return 1;
    else return nbrElements;
}


bool JCSqlSelectList::isStar(void)
{
    if (nbrElements == 0x0FFFFFFFF) return true;
    else return false;
}


bool JCSqlSelectList::spitTo(SqlCompileContext *aContext)
{
    if (nbrElements == 0x0FFFFFFFF) {
	aContext->emitByte(JCSqlTokens::starIdentifier);
    }
    else if (nbrElements == 1) {
	elements->spitTo(aContext);
    }
    else {
	JCSqlSelectItem *tmpCursor= elements;

	aContext->emitByte(JCSqlTokens::list);
	aContext->emitShort(nbrElements);
	while (tmpCursor != NULL) {
	    tmpCursor->spitTo(aContext);
	    tmpCursor= tmpCursor->getNext();
	}
    }
    return true;
}


JCSqlClause::Kinds JCSqlSelectList::getKind(void)
{
    return selectList;
}


/**************************************************
* Implementation: JCSqlTargetList.
**************************************************/

JCSqlTargetList::JCSqlTargetList(JCSqlEmbedded *anElement)
{
    nbrElements= 1;
    elements= lastElement= anElement;
}


void JCSqlTargetList::addElement(JCSqlEmbedded *anElement)
{
    if (nbrElements == 0) {
	elements= anElement;
    }
    else {
	lastElement->link(anElement);
    }
    nbrElements++;
    lastElement= anElement;
}


unsigned int JCSqlTargetList::count(void)
{
    return nbrElements;
}


JCSqlEmbedded *JCSqlTargetList::getFirstElement(void)
{
    return elements;
}


JCSqlClause::Kinds JCSqlTargetList::getKind(void)
{
    return targetList;
}


/**************************************************
* Implementation: JCSqlSelectItem.
**************************************************/

JCSqlSelectItem::JCSqlSelectItem(JCSqlExpression *anExpression)
{
    next= NULL;
    type= ctExpression;
    content= (void *)anExpression;
}


JCSqlSelectItem::JCSqlSelectItem(JCSqlIdentifier *anExpression)
{
    next= NULL;
    type= ctIdentifier;
    content= (void *)anExpression;
}


void JCSqlSelectItem::setStar(void)
{
    type= (ContentType)(type | ctStar);
}


void JCSqlSelectItem::link(JCSqlSelectItem *anItem)
{
    next= anItem;
}


JCSqlSelectItem *JCSqlSelectItem::getNext(void)
{
    return next;
}


bool JCSqlSelectItem::spitTo(SqlCompileContext *aContext)
{
    JCSqlExpression *anExpr;
    JCSqlIdentifier *anIdent;
    JCIdentifier *jcIdent, *nextIdent;

    switch (type & 0x07F) {
	case ctExpression:
	    anExpr= (JCSqlExpression *)content;
	    anExpr->spitTo(aContext);
	    break;
	case ctIdentifier:
	    anIdent= (JCSqlIdentifier *)content;
	    if (anIdent->isModuleHeader()) {
		aContext->emitByte(JCSqlTokens::moduleIdentifier);
	    }
	    aContext->mapIdentifier(anIdent);
	    jcIdent= anIdent->getSimpleIdentifier();
	    do {
		if (((nextIdent= jcIdent->getComponent()) == NULL) && ((type & ctStar) == 0)) {
		    aContext->emitByte(JCSqlTokens::identReference);
		}
		else {
		    aContext->emitByte(JCSqlTokens::containerReference);
		}
		aContext->emitShort(aContext->getReferenceID(jcIdent));
	    } while (nextIdent != NULL);
	    if (type & ctStar) {
		aContext->emitByte(JCSqlTokens::starIdentifier);
	    }
	    break;
	default:
	    // TODO: Signal internal error.
	    break;
    }

    return true;		// TMPTMP: For now, always succeed.
}


JCSqlClause::Kinds JCSqlSelectItem::getKind(void)
{
    return selectItem;
}


/**************************************************
* Implementation: JCSqlTableRefList.
**************************************************/

JCSqlTableRefList::JCSqlTableRefList(JCSqlTableRef *aReference)
{
    nbrElements= 1;
    elements= lastElement= aReference;
}


void JCSqlTableRefList::addElement(JCSqlTableRef *aReference)
{
    if (nbrElements == 0) {
	elements= aReference;
    }
    else {
	lastElement->link(aReference);
    }
    nbrElements++;
    lastElement= aReference;
}


unsigned int JCSqlTableRefList::count(void)
{
    return nbrElements;
}


JCSqlTableRef *JCSqlTableRefList::getFirstElement(void)
{
    return elements;
}


JCSqlClause::Kinds JCSqlTableRefList::getKind(void)
{
    return tableRefList;
}


/**************************************************
* Implementation: JCSqlTableRef.
**************************************************/

JCSqlTableRef::JCSqlTableRef(JCSqlIdentifier *aTableName)
{
    next= NULL;
    flags= simpleName;
    name= aTableName;
    source= NULL;
    derivedColumns= NULL;
}


JCSqlTableRef::JCSqlTableRef(JCIdentifier *anIdent)
{
    next= NULL;
    flags= synonymName;
    name= new JCSqlIdentifier(anIdent);
    source= NULL;
    derivedColumns= NULL;
}

	// Utilise par TableReferenceEndPart.
JCSqlTableRef::JCSqlTableRef(JCSqlExpression *aJoin)
{
    next= NULL;
    flags= joinName;
    name= NULL;
    source= aJoin;
    derivedColumns= NULL;
}


void JCSqlTableRef::setDerivedColumns(JCSqlIdentList *someColumns)
{
    derivedColumns= someColumns;
}


void JCSqlTableRef::setSource(JCSqlIdentifier *aTableName)
{
    source= (void *)aTableName;
    flags|= nameSource;
}


void JCSqlTableRef::setSource(JCSqlExpression *aSubQuery)
{
    source= (void *)aSubQuery;
    flags|= subquerySource;
}


void JCSqlTableRef::link(JCSqlTableRef *anElement)
{
    next= anElement;
}


JCSqlTableRef *JCSqlTableRef::getNext(void)
{
    return next;
}


bool JCSqlTableRef::spitTo(SqlCompileContext *aContext)
{
    if ((flags & 0x038) == synonymName) {
	if (derivedColumns != NULL) {
	    JCSqlIdentifier *tmpIdent;

	    aContext->emitByte(JCSqlTokens::extSynonymExpr);
	    aContext->emitByte(JCSqlTokens::list);
	    aContext->emitShort(derivedColumns->count());
	    tmpIdent= derivedColumns->getFirstElement();
	    while (tmpIdent != NULL) {
		aContext->mapIdentifier(tmpIdent);
		aContext->emitByte(JCSqlTokens::identReference);
		aContext->emitShort(aContext->getReferenceID(tmpIdent->getSimpleIdentifier()));
		tmpIdent= tmpIdent->getNext();
	    }
	}
	else {
	    aContext->emitByte(JCSqlTokens::synonymExpr);
	}
	aContext->mapIdentifier(name);
	aContext->emitByte(JCSqlTokens::identReference);
	aContext->emitShort(aContext->getReferenceID(name->getSimpleIdentifier()));
	if ((flags & 0x07) == nameSource) {
	    JCSqlIdentifier *tmpName= (JCSqlIdentifier *)source;
	    aContext->mapIdentifier(name);
	    aContext->emitByte(JCSqlTokens::identReference);
	    aContext->emitShort(aContext->getReferenceID(name->getSimpleIdentifier()));
	}
	else if ((flags & 0x07) == subquerySource) {
	    JCSqlExpression *tmpExpr= (JCSqlExpression *)source;
	    tmpExpr->spitTo(aContext);
	}
	else {
	    cout << "ERRMSG: internal error, JCSqlTableRef with synonym has unknown source.\n";
	}
    }
    else if ((flags & 0x038) == simpleName) {
	aContext->mapIdentifier(name);
	aContext->emitByte(JCSqlTokens::identReference);
	aContext->emitShort(aContext->getReferenceID(name->getSimpleIdentifier()));
    }
    else if ((flags & 0x038) == joinName) {
	JCSqlExpression *tmpExpr= (JCSqlExpression *)source;
	tmpExpr->spitTo(aContext);
    }
    else {
	cout << "ERRMSG: internal error, JCSqlTableRef with unknown content.\n";
    }

    return true;
}


JCSqlClause::Kinds JCSqlTableRef::getKind(void)
{
    return tableRef;
}


/**************************************************
* Implementation: JCSqlSortList.
**************************************************/

JCSqlSortList::JCSqlSortList(JCSqlSortItem *anItem)
{
// TODO.
}


void JCSqlSortList::addElement(JCSqlSortItem *anItem)
{
// TODO.
}


JCSqlClause::Kinds JCSqlSortList::getKind(void)
{
    return sortList;
}


/**************************************************
* Implementation: JCSqlSortItem.
**************************************************/

JCSqlSortItem::JCSqlSortItem(JCSqlIdentifier *anIdent, JCSqlIdentifier *collater, JCSqlConstants::SortOrder aSortDir)
{
// TODO.
}


JCSqlClause::Kinds JCSqlSortItem::getKind(void)
{
    return sortItem;
}


/**************************************************
* Implementation: JCSqlGroupList.
**************************************************/

JCSqlGroupList::JCSqlGroupList(JCSqlGroupItem *anItem)
{
// TODO.
}


void JCSqlGroupList::addElement(JCSqlGroupItem *anItem)
{
// TODO.
}


JCSqlClause::Kinds JCSqlGroupList::getKind(void)
{
    return groupList;
}


/**************************************************
* Implementation: JCSqlGroupItem.
**************************************************/

JCSqlGroupItem::JCSqlGroupItem(JCSqlIdentifier *aColumnIdent)
{
// TODO.
}


JCSqlGroupItem::JCSqlGroupItem(JCSqlIdentifier *aColumnIdent, JCSqlIdentifier *collater)
{
// TODO.
}


JCSqlClause::Kinds JCSqlGroupItem::getKind(void)
{
    return groupItem;
}


/**************************************************
* Implementation: JCSqlTableClause.
**************************************************/

JCSqlTableClause::JCSqlTableClause(JCSqlTableRefList *from, JCSqlExpression *where, JCSqlGroupList*group, JCSqlSortList *order, JCSqlExpression *having)
{
    tables= from;
    qualifier= where;
    groupment= group;
    ordering= order;
    focuser= having;
}


JCSqlTableRefList *JCSqlTableClause::getSourceTables(void)
{
    return tables;
}


JCSqlExpression *JCSqlTableClause::getQualifier(void)
{
    return qualifier;
}


unsigned char JCSqlTableClause::getOptionsIndicator(void)
{
    return (((qualifier != NULL) ? 1 : 0) | ((groupment != NULL) ? 2 : 0)
		| ((focuser != NULL) ? 4 : 0) | ((ordering != NULL) ? 8 : 0));
}


JCSqlClause::Kinds JCSqlTableClause::getKind(void)
{
    return table;
}


/**************************************************
* Implementation: JCSqlRowValueList.
**************************************************/

JCSqlRowValueList::JCSqlRowValueList(JCSqlRowValue *aRowConstructor)
{
    nbrElements= 1;
    elements= lastElement= aRowConstructor;
}


void JCSqlRowValueList::addElement(JCSqlRowValue *aRowConstructor)
{
    if (nbrElements == 0) {
	elements= aRowConstructor;
    }
    else {
	lastElement->link(aRowConstructor);
    }
    nbrElements++;
    lastElement= aRowConstructor;
}


unsigned int JCSqlRowValueList::count(void)
{
    return nbrElements;
}


JCSqlRowValue *JCSqlRowValueList::getFirstElement(void)
{
    return elements;
}


JCSqlClause::Kinds JCSqlRowValueList::getKind(void)
{
    return rowValueList;
}


/**************************************************
* Implementation: JCSqlRowValue.
**************************************************/

JCSqlRowValue::JCSqlRowValue(JCSqlExpression *anExpression)
{
    next= NULL;
    value= anExpression;
}


void JCSqlRowValue::link(JCSqlRowValue *aValue)
{
    next= aValue;
}


JCSqlRowValue *JCSqlRowValue::getNext(void)
{
    return next;
}


JCSqlExpression *JCSqlRowValue::getValue(void)
{
    return value;
}


JCSqlClause::Kinds JCSqlRowValue::getKind(void)
{
    return rowValue;
}


/**************************************************
* Implementation: JCSqlValueList.
**************************************************/

JCSqlValueList::JCSqlValueList(JCSqlExpression *anExpression)
{
// TODO.
}


void JCSqlValueList::addElement(JCSqlExpression *anExpression)
{
// TODO.
}


JCSqlClause::Kinds JCSqlValueList::getKind(void)
{
    return valueList;
}


/**************************************************
* Implementation: JCSqlRVConstrList.
**************************************************/

JCSqlRVConstrList::JCSqlRVConstrList(JCSqlRowValue *aRowConstructor)
{
    nbrElements= 1;
    elements= lastElement= aRowConstructor;
}


void JCSqlRVConstrList::addElement(JCSqlRowValue *aRowConstructor)
{
    if (nbrElements == 0) {
	elements= aRowConstructor;
    }
    else {
	lastElement->link(aRowConstructor);
    }
    nbrElements++;
    lastElement= aRowConstructor;
}


unsigned int JCSqlRVConstrList::count(void)
{
    return nbrElements;
}


JCSqlRowValue *JCSqlRVConstrList::getFirstElement(void)
{
    return elements;
}


JCSqlClause::Kinds JCSqlRVConstrList::getKind(void)
{
    return rvConstrList;
}


