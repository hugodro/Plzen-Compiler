#ifndef _SQLSUBCLAUSES_H_
#define _SQLSUBCLAUSES_H_
/**************************************************
* File: sqlClauses.h.
* Desc: Definition of the JCSqlClause hierarchy.
* Module: AkraLog : JavaKit.
* Rev: 2 aout 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>
#include "sqlConstants.h"

class JCSqlSelectItem;
class JCSqlEmbedded;
class JCSqlExpression;
class JCSqlTableRef;
class JCSqlIdentifier;
class JCSqlIdentList;
class JCSqlSortItem;
class JCSqlGroupItem;
class JCIdentifier;
class SqlCompileContext;
class JCSqlRowValue;

// ATTN-980601 [HD]: All the lists should be collapsed into a
//    general clause items holder.
class JCSqlClause : public AkObject {
  public:
    enum Kinds {
	selectList, targetList, selectItem, tableRefList, tableRef,
	sortList, sortItem, groupList, groupItem, table,
	rowValueList, rowValue, valueList, rvConstrList
    };

  public:
    virtual Kinds getKind(void)= 0;
};


class JCSqlSelectList : public JCSqlClause {
  protected:
    unsigned int nbrElements;
    JCSqlSelectItem *elements, *lastElement;

  public:	// Instance methods.
    JCSqlSelectList(void);
    JCSqlSelectList(JCSqlSelectItem *anElement);
    virtual void setStar(void);	// Define to be all columns in table.
    virtual void addElement(JCSqlSelectItem *anElement);
    virtual unsigned int count();
    virtual bool isStar(void);
    virtual bool spitTo(SqlCompileContext *aContext);
    virtual Kinds getKind(void);
};


class JCSqlTargetList : public JCSqlClause {
  protected:	// Instance variables.
    unsigned int nbrElements;
    JCSqlEmbedded *elements, *lastElement;

  public:		// Instance methods.
    JCSqlTargetList(JCSqlEmbedded *anElement);
    virtual void addElement(JCSqlEmbedded *anElement);
    virtual unsigned int count(void);
    virtual JCSqlEmbedded *getFirstElement(void);
    virtual Kinds getKind(void);
};


class JCSqlSelectItem : public JCSqlClause {
  public:
    enum ContentType {
	ctExpression= 0, ctIdentifier
	, ctStar= 0x080
    };

  protected:
    JCSqlSelectItem *next;
    ContentType type;
    void *content;
 
  public:
    JCSqlSelectItem(JCSqlExpression *anExpression);
    JCSqlSelectItem(JCSqlIdentifier *anExpression);
    virtual void setStar(void);	// Define to be all columns in item.
    virtual void link(JCSqlSelectItem *anItem);
    virtual JCSqlSelectItem *getNext(void);
    virtual bool spitTo(SqlCompileContext *aContext);
    virtual Kinds getKind(void);
};


class JCSqlTableRefList : public JCSqlClause {
  protected:
    unsigned int nbrElements;
    JCSqlTableRef *elements, *lastElement;

  public:
    JCSqlTableRefList(JCSqlTableRef *aReference);
    virtual void addElement(JCSqlTableRef *aReference);
    virtual unsigned int count(void);
    virtual JCSqlTableRef *getFirstElement(void);
    virtual Kinds getKind(void);
};


class JCSqlTableRef : public JCSqlClause {
  public:
    enum Details {
	nameSource= 1, subquerySource= 2
	, simpleName=  (1 << 3), synonymName= (2 << 3), joinName= (3 << 3)
    };

  protected:	// Instance variables.
    JCSqlTableRef *next;
    unsigned char flags;
    JCSqlIdentifier *name;
    void *source;
    JCSqlIdentList *derivedColumns;

  public:		// Instance methods.
    JCSqlTableRef(JCSqlIdentifier *aTableName);
    JCSqlTableRef(JCIdentifier *anIdent);	// Utilise par TableReferenceEndPart.
    JCSqlTableRef(JCSqlExpression *aJoin);
    virtual void setDerivedColumns(JCSqlIdentList *someColumns);
    virtual void setSource(JCSqlIdentifier *aTableName);
    virtual void setSource(JCSqlExpression *aSubQuery);
    virtual void link(JCSqlTableRef *anElement);
    virtual bool spitTo(SqlCompileContext *aContext);
    virtual JCSqlTableRef *getNext(void);
    virtual Kinds getKind(void);
};


class JCSqlSortList : public JCSqlClause {
  public:
    JCSqlSortList(JCSqlSortItem *anItem);
    virtual void addElement(JCSqlSortItem *anItem);
    virtual Kinds getKind(void);
};


class JCSqlSortItem : public JCSqlClause {
  public:
    JCSqlSortItem(JCSqlIdentifier *anIdent, JCSqlIdentifier *collater, JCSqlConstants::SortOrder aSortDir);
    virtual Kinds getKind(void);
};


class JCSqlGroupList : public JCSqlClause {
  public:
    JCSqlGroupList(JCSqlGroupItem *anItem);
    virtual void addElement(JCSqlGroupItem *anItem);
    virtual Kinds getKind(void);
};


class JCSqlGroupItem : public JCSqlClause {
  public:
    JCSqlGroupItem(JCSqlIdentifier *aColumnIdent);
    JCSqlGroupItem(JCSqlIdentifier *aColumnIdent, JCSqlIdentifier *collater);
    virtual Kinds getKind(void);
};


class JCSqlTableClause : public JCSqlClause {
  protected:	// Instance variables.
    JCSqlTableRefList *tables;
    JCSqlExpression *qualifier;		// Where.
    JCSqlGroupList *groupment;		// Group by.
    JCSqlExpression *focuser;		// Having.
    JCSqlSortList *ordering;			// Order by.
    
  public:		// Instance methods.
    JCSqlTableClause(JCSqlTableRefList *from, JCSqlExpression *where, JCSqlGroupList*group, JCSqlSortList *order, JCSqlExpression *having);
    virtual JCSqlTableRefList *getSourceTables(void);
    virtual JCSqlExpression *getQualifier(void);
    virtual unsigned char getOptionsIndicator(void);
    virtual Kinds getKind(void);
};


class JCSqlRowValueList : public JCSqlClause {
  protected:
    unsigned int nbrElements;
     JCSqlRowValue *elements, *lastElement;

  public:		// Instance methods.
    JCSqlRowValueList(JCSqlRowValue *aRowConstructor);
    virtual void addElement(JCSqlRowValue *aRowConstructor);
    virtual unsigned int count(void);
    virtual JCSqlRowValue *getFirstElement(void);
    virtual Kinds getKind(void);
};


class JCSqlRowValue : public JCSqlClause {
  protected:
    JCSqlRowValue *next;
    JCSqlExpression *value;

  public:
    JCSqlRowValue(JCSqlExpression *anExpression);
    virtual void link(JCSqlRowValue *aValue);
    virtual JCSqlRowValue *getNext(void);
    virtual JCSqlExpression *getValue(void);
    virtual Kinds getKind(void);
};


class JCSqlValueList : public JCSqlClause {
  public:
    JCSqlValueList(JCSqlExpression *anExpression);
    virtual void addElement(JCSqlExpression *anExpression);
    virtual Kinds getKind(void);
};

// ATTN-980601 [HD]: JCSqlRowValueList and JCSqlRVConstrList are the
//	same thing; can there be a simplification ?
class JCSqlRVConstrList : public JCSqlClause {
  protected:
    unsigned int nbrElements;
     JCSqlRowValue *elements, *lastElement;

  public:
    JCSqlRVConstrList(JCSqlRowValue *anElement);
    virtual void addElement(JCSqlRowValue *anElement);
    virtual Kinds getKind(void);
    virtual unsigned int count(void);
    virtual JCSqlRowValue *getFirstElement(void);
};


#endif		/* _SQLSUBCLAUSES_H_ */
