#ifndef _OVERLOADDICT_H_
#define _OVERLOADDICT_H_
/**************************************************
* File: overloadDict.h.
* Desc: Definition of the JCOverloadDictionary class.
* Module: Plzen : Compiler.
* Rev: 19 novembre 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>


class JCMethod;
class JCReferencedType;
class GenericList;
class JCType;


class JCSynonymTable : public AkObject {
  protected:	// Instance variables.
    JCSynonymTable *superSynonyms;
    unsigned int nbrElements;
    JCMethod **elements;
    unsigned int *nbrArguments;
    JCReferencedType ***methodTypes;

  public:	// Instance methods.
    JCSynonymTable(void);
    virtual ~JCSynonymTable(void);
    virtual void linkToSuper(JCSynonymTable *aSuper);
    virtual void buildFrom(GenericList *set, unsigned int setOffset, unsigned int nbrSyns, char *synMap, unsigned int bitOffset);
    virtual bool matchSynonym(JCSynonymTable *aSynTable);
    virtual unsigned int findMatch(JCReferencedType **typing, unsigned int nbrTypes, JCMethod **bestMethod);
    virtual unsigned int testMatching(JCReferencedType **typing, JCReferencedType **paramTypes, unsigned int nbrParams, JCMethod **bestResult, JCMethod *candidate);

};


class JCOverloadDictionary : public AkObject {
  protected:
    JCOverloadDictionary *superDict;
    unsigned int nbrOverloads;
    JCSynonymTable *overloads;

  public:	// Instance methods.
    JCOverloadDictionary(JCType *reference);
    virtual ~JCOverloadDictionary(void);
    virtual void linkToSuper(JCOverloadDictionary *aSuper);
    virtual void fuseOverload(JCSynonymTable *someSynonyms);
    virtual JCMethod *getOverloadOf(JCMethod *aMethod, JCReferencedType **argTypes, unsigned int nbrArgs);
};

#endif		/* _OVERLOADDICT_H_ */
