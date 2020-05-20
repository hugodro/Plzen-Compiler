#ifndef _NAMESPACE_H_
#define _NAMESPACE_H_
/**************************************************
* File: nameSpace.h.
* Desc: Contains the definition of the name space handling classes.
* Module: AkraLog : JavaComp.
* Rev: 10 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"


class JCExpression;
class JCResolved;
class JCReferencedType;
class JCIdentifier;
class JCClass;
class JCVarAccess;
class JCNamedExpr;
class JCType;
class JCMethod;
class JCName;
class JCImportedType;
class JCImportManager;
class UnresolvedList;


class JCHolder : public AkObject {
    friend class JCUnresolved;
    friend class JCNameSpace;

  public:
    enum HolderType {
	hExpression, hType
    };

  protected:
    JCHolder *next;
    void *myContent;

  public:
    virtual void setContentResolver(JCName *aName)= 0;
    virtual JCHolder *getNext(void);
    virtual void setNext(JCHolder *another);
    virtual HolderType getCategory(void)= 0;
};


class JCExprHolder : public JCHolder {
    friend class JCUnresolved;

  public:
    JCExprHolder(JCExpression *anExpression, JCHolder *aHolder);
    virtual void setContent(JCExpression *anExpression);
    virtual JCExpression *content(void);
    virtual void setContentResolver(JCName *aName);
    virtual HolderType getCategory(void);
 };


class JCTypeHolder : public JCHolder {
    friend class JCUnresolved;

  public:
    JCTypeHolder(JCReferencedType *aType, JCHolder *aHolder);
    virtual void setContent(JCReferencedType *aType);
    virtual JCReferencedType *content(void);
    virtual void setContentResolver(JCName *aName);
    virtual HolderType getCategory(void);
 };


class JCName : public AkObject {
    friend class JCNameSpace;
    friend class JCMethodSpace;
    friend class JCClassSpace;
// TMPTMP:
    friend class JCImportedGhost;

  public:
    enum Situation {
	resolved, unresolved
    };

    enum UnitType {
	noClue= 0,
	uType, uClass, uInterface,		// Unit which is some kind of type.
	unknownVariable, localVariable, fieldVariable,   // Unit which is a data holder.
	uMethod, uState,		// Unit which is a comput. section.
	importation,			// Name introduced as an importation, but of unknown category.
	package,				// Importation known as package name.
	uEvent				// Event type.
    };

  public:	/* MOD-MSC: Change la proctection de 'protected' a 'public. */
    JCName *prev, *next;
    JCIdentifier *ident;
    UnitType nameType;		// Describe what type of compilation unit this name is.

  public:
    static const char *getCategoryNameFor(UnitType aType);

  public:
    JCName(void);
    JCName(JCIdentifier *anIdent);
    JCName *getNext(void);
    virtual void link(JCName *another);
    virtual Situation getSituation(void)= 0;
    virtual UnitType getCategory(void);

    virtual void setIdent(JCIdentifier *anIdent);
    virtual JCIdentifier *getIdent(void);
    virtual bool isMatching(JCIdentifier *anIdent);
    virtual bool isCompatible(UnitType aKind);

// TMP DEBUG:
    virtual void dumpInfo(void);
 };


class JCUnresolved : public JCName {
    friend class JCNameSpace;
    friend class JCMethodSpace;
    friend class JCClassSpace;
  protected:
    JCName *root;			// Prefix name.
    JCUnresolved *subNames;	// Names that are rooted at this name.
    JCHolder *users;		// Types or expressions, depending on the identType.

  public:
    JCUnresolved(void);
    JCUnresolved(JCReferencedType *aRefType);
    JCUnresolved(JCExpression *anExpression);
    virtual ~JCUnresolved(void);
    virtual Situation getSituation(void);

    virtual void setIdent(JCIdentifier *anIdent);
    virtual bool isMatching(JCResolved *aResolver);
    virtual bool isMatching(JCIdentifier *anIdent);
    virtual void linkExpression(JCExpression *anExpression);
    virtual bool solveExpressions(JCResolved *resolver);
    virtual void linkType(JCReferencedType *aType);
    virtual bool solveTypes(JCResolved *resolver);
    virtual JCHolder *flushUsers(void);
    virtual JCUnresolved *getSubNames(void);

// TMP DEBUG:
    virtual void dumpInfo(void);

// Work in progress:
    virtual void setRoot(JCName *aName);
    virtual void updateNoClue(JCResolved *aSolution);
    virtual void updateNoClue(JCUnresolved *aClue);
    virtual void updateNoClue(JCName::UnitType newType);
    virtual bool isRootless(void);
};


class JCResolved : public JCName {
    friend class JCNameSpace;
    friend class JCMethodSpace;
    friend class JCClassSpace;
  protected:
    void *dereference;		// Actual value for the symbol.

  public:
    JCResolved(void);
    JCResolved(JCResolved *aResolved);	// Copy constructor.
    JCResolved(JCIdentifier *anIdent, void *aTangible, UnitType aType);
    virtual Situation getSituation(void);

    virtual void setDefinition(void *aTangible);
    virtual void setDefType(UnitType aType);
    virtual UnitType getDefType(void);	// ATTN: Must be replaced by JCName::getCategory.
    virtual void *getDefinition(void);

// TMP DEBUG:
    virtual void dumpInfo(void);
 };


class JCNameSpace : public AkObject {
  public:
    enum Kind {
	kClass, kMethod, kBlock
    };
  public:	/* MOD-MSC: Change la protection de 'protected' a 'public'. */
    JCNameSpace *prev, *next;
    JCNameSpace *superLevel;
    JCNameSpace *subLevel;
    JCUnresolved *unresolved, *lastUnresolved;
    JCResolved *resolved, *lastResolved;
	// ATTN-971119 [HD]: For now, we keep a head/tail list of method users in the namespace.
	//  There is no serious need for head/tail, and in fact, the expr should go closer to
	//  a post-processing list in the current compiler.
    JCExprHolder *methodHolders, *lastMethodHolder;

  public:
    JCNameSpace(void);
    virtual Kind getKind(void);

    virtual void link(JCNameSpace *aNameSpace);
    virtual void linkAsSuper(JCNameSpace *aNameSpace);
    virtual JCNameSpace *getNext(void);
    virtual JCUnresolved *addUnresolved(JCReferencedType *aRefType);
    virtual JCUnresolved *addUnresolved(JCExpression *anExpr);
    virtual JCUnresolved *addUnresolved(JCIdentifier *anIdent);
    virtual JCUnresolved *findUnresolved(JCIdentifier *anIdent);
    virtual JCUnresolved *findUnresolved(JCIdentifier *anIdent, JCName *aRootName);
    virtual JCResolved *findResolved(JCIdentifier *anIdent);
    virtual JCResolved *findResolved(JCIdentifier *anIdent, JCName::UnitType aKind);
    virtual JCResolved *findResolved(JCIdentifier *anIdent, JCResolved *srcResolver);
    virtual JCResolved *quickAddResolved(JCIdentifier *anIdent, void *aTangible, JCName::UnitType aType);    // Add a resolution without doing checking.
    virtual JCResolved *addResolution(JCIdentifier *anIdent, void *aTangible, JCName::UnitType aType);    // Return a resolver if there is no such resolved name yet.
    virtual bool applyResolution(JCResolved *aResolved);    // Goes through the set of unresolved and replace any if it is aResolved.
    virtual void applyResolution(JCResolved *resolver, JCUnresolved *anUnknown);    // Apply resolution for a precise unknown.
    virtual JCNameSpace *getUpperLevel(void);
    virtual JCNameSpace *getLastLevel(void);
    virtual bool addALevel(JCNameSpace *newLevel);
    virtual bool removeLastLevel(void);
    virtual bool flushUnresolved(void);

// TMP DEBUG:
    virtual void dumpContent(void);

// Work in progress.
    virtual bool hasUnresolved(void);
    virtual void seekUnresolvedFrom(JCNameSpace *aSpace);
    virtual void includeResolutions(JCResolved *resolvers);
    virtual JCResolved *getResolvers(void);
    virtual bool relateSimpleVar(JCVarAccess *aSimpleVar);
    virtual bool relateNamedExpr(JCNamedExpr *aNamedExpr);

    virtual JCReferencedType *getSuperClassType(void);
    virtual JCResolved *getThisVariable(void);
    virtual JCResolved *getSuperVariable(void);
    virtual bool mergeToSuperSpace(JCUnresolved *aSymbol);
    virtual bool resolveAll(void);
    virtual bool resolveAll(JCMethod *aContext);
    virtual void importUnresolved(JCUnresolved *aUnresList);   // ATTN: Should go in JCClassSpace.
    virtual void importUnresolved(JCNameSpace *aSpace);   // ATTN: Should go in JCClassSpace.
    virtual JCUnresolved *getFirstUnresolved(void);
    virtual void removeUnresolved(JCUnresolved *anUnres);
    virtual void addMethodUsers(JCExprHolder *someUsers);
    virtual bool resolveMethodUsers(void);
 };


class JCMethodSpace : public JCNameSpace {
  protected:
    JCResolved *thisVar;
    JCResolved *superVar;

  public:
    JCMethodSpace(JCType *aType);
    virtual Kind getKind(void);
    virtual void setThisResolver(JCResolved *aResolution);
    virtual JCResolved *getThisVariable(void);
    virtual JCResolved *getSuperVariable(void);
    virtual bool flushUnresolved(void);
};


class JCClassSpace : public JCNameSpace {
  protected:
    JCClass *currentClass;
    UnresolvedList *noClueList;

  public:
    JCClassSpace(JCClass *aClass);
    virtual Kind getKind(void);
    virtual JCClass *getCurrentClass(void);
    virtual JCReferencedType *getSuperClassType(void);
    virtual bool flushUnresolved(void);
    virtual bool resolveAll(void);
};


class JCImportSpace : public JCNameSpace {
  protected:	// Instance variables.
    JCImportedType *ourType;

  public:		// Instance methods.
    JCImportSpace(JCImportedType *aType);
    virtual bool resolveAll(void);
    virtual bool resolveAll(JCImportManager *aManager);
    virtual JCResolved *findResolved(JCIdentifier *anIdent);
};

#endif	/* _NAMESPACE_H_ */
