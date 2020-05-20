/**************************************************
* File: overloadDict.cc.
* Desc: Implementation of the JCOverloadDictionary class.
* Module: Plzen : Compiler.
* Rev: 19 novembre 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>

#include <memory.h>
#include "compileObjects.h"
#include "lists.h"
#include "typing.h"
#include "outConstant.h"
#include "overloadDict.h"


/**************************************************
* Implementation: JCSynonymTable.
**************************************************/

JCSynonymTable:: JCSynonymTable(void)
{
    nbrElements= 0;
    elements= NULL;
    nbrArguments= NULL;
    methodTypes= NULL;
    superSynonyms= NULL;
}


JCSynonymTable::~JCSynonymTable(void)
{
cout << "JCSynonymTable: doing a delete.\n";

    if (nbrElements > 0) {
	delete[] methodTypes;
	delete[] nbrArguments;
	delete[] elements;
    }
}


void JCSynonymTable::linkToSuper(JCSynonymTable *aSuper)
{
    superSynonyms= aSuper;
}


void JCSynonymTable::buildFrom(GenericList *set, unsigned int setOffset, unsigned int nbrSyns, char *synMap, unsigned int bitOffset)
{
    JCMethod *tmpMethod;
    unsigned int i, methodCursor;

    if (nbrSyns == 0) {
	    // Trick to save a big pointer !
	elements= (JCMethod **)set->voidObjectAt(setOffset);
	((JCMethod *)elements)->setSynonyms(this);
    }
    else {
	nbrElements= nbrSyns + 1;
	elements= new JCMethod*[nbrElements];
	nbrArguments= new unsigned int[nbrElements];
	methodTypes= new JCReferencedType**[nbrElements];

	tmpMethod= elements[0]= (JCMethod *)set->voidObjectAt(setOffset);
	nbrArguments[0]= tmpMethod->getNbrArguments();
	if (!tmpMethod->isStatic()) nbrArguments[0]--;
	if (nbrArguments[0] > 0) {
	    methodTypes[0]= tmpMethod->getTypeList();
	}
	tmpMethod->setSynonyms(this);

	for (methodCursor= 1, i= 0; i < set->count() - setOffset; i++) {
	    if ((synMap[(bitOffset + i) >> 3] & (1 << ((bitOffset + i) & 0x07))) != 0) {
		tmpMethod= elements[methodCursor]= (JCMethod *)set->voidObjectAt(setOffset + i + 1);
		nbrArguments[methodCursor]= tmpMethod->getNbrArguments();
		if (!tmpMethod->isStatic()) nbrArguments[methodCursor]--;
		if (nbrArguments[methodCursor] > 0) {
		    methodTypes[methodCursor]= tmpMethod->getTypeList();
		}
		tmpMethod->setSynonyms(this);
		if (methodCursor == nbrSyns) break;
		methodCursor++;
	    }
	}
    }
}


bool JCSynonymTable::matchSynonym(JCSynonymTable *aSynTable)
{
    if (nbrElements == 0) {
	if (aSynTable->nbrElements == 0) {
	    return (((JCMethod *)elements)->getName()->isEqual(((JCMethod *)aSynTable->elements)->getName()));
	}
	else {
	    return (((JCMethod *)elements)->getName()->isEqual(aSynTable->elements[0]->getName()));
	}
    }
    else {
	if (aSynTable->nbrElements == 0) {
	    return (elements[0]->getName()->isEqual(((JCMethod *)aSynTable->elements)->getName()));
	}
	else {
	    return (elements[0]->getName()->isEqual(aSynTable->elements[0]->getName()));
	}
    }
}


unsigned int JCSynonymTable::findMatch(JCReferencedType **typing, unsigned int nbrTypes, JCMethod **bestMethod)
{
    unsigned int matchQuality= 0x0FFFFFFFF;
    unsigned int i;

    if (nbrElements == 0) {
	unsigned int nbrParams;

	nbrParams= ((JCMethod *)elements)->getNbrArguments();
	if (!((JCMethod *)elements)->isStatic()) nbrParams--;
	if (nbrParams != nbrTypes) {
	    if (superSynonyms != NULL) {
		matchQuality= superSynonyms->findMatch(typing, nbrTypes, bestMethod);
	    }
	}
	else {
	    JCReferencedType **tmpTypes;
	    if (nbrParams == 0) {
		*bestMethod= ((JCMethod *)elements);
		matchQuality= 0;
	    }
	    else {
		tmpTypes= ((JCMethod *)elements)->getTypeList();
		matchQuality= testMatching(typing, tmpTypes, nbrParams, bestMethod, ((JCMethod *)elements));
		if (matchQuality != 0) {
		    if (superSynonyms != NULL) {
			matchQuality= superSynonyms->findMatch(typing, nbrTypes, bestMethod);
		    }
		}
	    }
	}
    }
    else {
	unsigned int tmpQuality= 0x0FFFFFFFF;

	for (i= 0; i < nbrElements; i++) {
	    if (nbrArguments[i] == nbrTypes) {
		if (nbrArguments[i] == 0) {
			// First match does the job.
		    *bestMethod= elements[i];
		    matchQuality= 0;
		    break;
		}
		else {
		    tmpQuality= testMatching(typing, methodTypes[i], nbrArguments[i], bestMethod, elements[i]);
		    if (tmpQuality < matchQuality) {
			matchQuality= tmpQuality;
		    }
		    if (matchQuality != 0) {
			if (superSynonyms != NULL) {
			    matchQuality= superSynonyms->findMatch(typing, nbrTypes, bestMethod);
			}
		    }		
		}
	    }
	}

	if (matchQuality != 0) {
	    if (superSynonyms != NULL) {
		matchQuality= superSynonyms->findMatch(typing, nbrTypes, bestMethod);
	    }
	}
    }

    return matchQuality;
}


unsigned int JCSynonymTable::testMatching(JCReferencedType **typing, JCReferencedType **paramTypes, unsigned int nbrParams, JCMethod **bestResult , JCMethod *candidate)
{
    unsigned int i, result= 0;
    bool possibleMatch;

    possibleMatch= true;
	// First, check for simple parameter compatibility.
    for (i= 0; i < nbrParams; i++) {
	if (!typing[i]->isParameterCompatible(paramTypes[i])) {
	    possibleMatch= false;
	    break;
	}
    }

	// Second, check for full parameter compatibility.
	// Only non-primary types need to be checked.
    if (possibleMatch) {

	for (i= 0; (i < nbrParams) && possibleMatch; i++) {
	    if (paramTypes[i]->isInstance()) {
		if (paramTypes[i]->isArray()) {
		    if (paramTypes[i]->isPrimitive()) {
			if (typing[i]->isPrimitive()) {
			    if (paramTypes[i]->getPrimitiveType() != typing[i]->getPrimitiveType()) {
				possibleMatch= false;
			    }
			}
			else {
			    possibleMatch= false;
			}
		    }
		    else {	// If non-primitive array situation.
			JCReferencedType *paramScalar, *argScalar;
			paramScalar= paramTypes[i]->getArrayBaseType();
			paramScalar= typing[i]->getArrayBaseType();
			if (!paramScalar->isGE(paramScalar)) {
			    possibleMatch= false;
			}
			else {
			    if (paramTypes[i]->getNbrDimensions() > typing[i]->getNbrDimensions()) {
				possibleMatch= false;
			    }
			}
		    }
		}
		else {	// If non-vectorial situation.
			// ATTN-971121 [HD]: This doesn't take care of the interface situation.
		    if (!typing[i]->isGE(paramTypes[i])) {
			possibleMatch= false;
		    }
		}
	    }
	    else {
		if (paramTypes[i]->getPrimitiveType() != typing[i]->getPrimitiveType()) {
		    result++;
		}
	    }
	}

    }

    	// Third, check to see if it is a better match than the current one.
    if (possibleMatch) {
	if (bestResult != NULL) {
		// TODO: Test the best result vs the candidate !
	    *bestResult= candidate;
	}
	else {
	    *bestResult= candidate;
	}
    }
    else {
	result= 0x0FFFFFFFF;
    }

    return result;
}


/**************************************************
* Implementation: JCOverloadDictionary.
**************************************************/

JCOverloadDictionary::JCOverloadDictionary(JCType *reference)
{
    MethodsList *methods;
    StatesList *states;
    unsigned int nbrMethods, nbrStates;
    unsigned int *methodScanCount, *stateScanCount;
    char *methodScanner, *stateScanner;

    methods= reference->getMethods();
    states= reference->getStates();
    nbrMethods= methods->count();
    nbrStates= states->count();

    if ((nbrMethods + nbrStates) > 0) {
	JCCteUtf8 *baseName;
	unsigned int nbrAntoMethods= 0, nbrAntoStates= 0;
	unsigned int i, j, bitOffset;
	unsigned int nbrScanElements;

	if (methods->count() > 0) {
	    nbrScanElements= nbrMethods * (nbrMethods + 1) / 2;
	    bitOffset= nbrMethods;

	    nbrScanElements= (nbrScanElements >> 3) + (((nbrScanElements % 8) != 0) ? 1 : 0);
	    methodScanner= new char[nbrScanElements];
	    memset(methodScanner, 0, nbrScanElements);
	    methodScanCount= new unsigned int[nbrMethods];
    
	    for (i= 0; i < nbrMethods; i++) {
		methodScanCount[i]= 0;
		if ((methodScanner[(i >> 3)] & (1 << (i & 0x07))) == 0) {
		    nbrAntoMethods++;
		    baseName= methods->objectAt(i)->getName();
		    for (j= i+1; j < nbrMethods; j++) {
			if (baseName->isEqual(methods->objectAt(j)->getName())) {
			    // il faut stamper le tableau global, et aussi le tableau de i.
			    methodScanner[((j) >> 3)]|= (1 << ((j) & 0x07));
			    methodScanner[(bitOffset + j - i - 1) >> 3]|= (1 << ((bitOffset + j - i - 1) & 0x07));
			    methodScanCount[i]++;
			}
		    }
		}
		bitOffset+= nbrMethods - i - 1;
	    }
	}

	if (states->count() > 0) {
	    nbrScanElements= nbrStates * (nbrStates + 1) / 2;
	    bitOffset= nbrStates;

	    nbrScanElements= (nbrScanElements >> 3) + (((nbrScanElements % 8) != 0) ? 1 : 0);
	    stateScanner= new char[nbrScanElements];
	    memset(stateScanner, 0, nbrScanElements);
	    stateScanCount= new unsigned int[nbrStates];
    
	    for (i= 0; i < nbrStates; i++) {
		stateScanCount[i]= 0;
		if ((stateScanner[(i >> 3)] & (1 << (i & 0x07))) == 0) {
		    nbrAntoStates++;
		    baseName= states->objectAt(i)->getName();
		    for (j= i+1; j < nbrStates; j++) {
			if (baseName->isEqual(states->objectAt(j)->getName())) {
			    // il faut stamper le tableau global, et aussi le tableau de i.
			    stateScanner[(j >> 3)]|= (1 << (j & 0x07));
			    stateScanner[(bitOffset + j - i - 1) >> 3]|= (1 << ((bitOffset + j - i - 1) & 0x07));
			    stateScanCount[i]++;
			}
		    }
		}
		bitOffset+= nbrStates - i - 1;
	    }
	}

	nbrOverloads= nbrAntoMethods + nbrAntoStates;
	overloads= new JCSynonymTable[nbrOverloads];

	j= 0;
	for (bitOffset= nbrMethods, i= 0; i < nbrMethods; i++) {
	    if ((methodScanner[(i >> 3)] & (1 << (i & 0x07))) == 0) {
		overloads[j++].buildFrom(methods, i, methodScanCount[i], methodScanner, bitOffset);
	    }
	    bitOffset+= nbrMethods - i - 1;
	}

	for (bitOffset= nbrStates, i= 0; i < nbrStates; i++) {
	    if ((stateScanner[(i >> 3)] & (1 << (i & 0x07))) == 0) {
		overloads[j++].buildFrom(states, i, stateScanCount[i], stateScanner, bitOffset);
	    }
	    bitOffset+= nbrStates - i - 1;
	}

	if (nbrMethods > 0) {
	    delete[] methodScanner;
	    delete[] methodScanCount;
	}
	if (nbrStates > 0) {
	    delete[] stateScanner;
	    delete[] stateScanCount;
	}
    }
    else {
	nbrOverloads= 0;
    }
    superDict= NULL;
}


JCOverloadDictionary::~JCOverloadDictionary(void)
{
    if (nbrOverloads > 0) {
/* ATTN: Is this code always useless ? Or do some compilers can't delete arrays of ?
	for (unsigned int i= 0; i < nbrOverloads; i++) {
	    delete &overloads[i];
	}
*/
	delete[] overloads;
    }
}


void JCOverloadDictionary::linkToSuper(JCOverloadDictionary *aSuper)
{
    if (aSuper == NULL) return;		// Warning: quick exit.
    superDict= aSuper;
    for (unsigned int i= 0; i < nbrOverloads; i++) {
	superDict->fuseOverload(&overloads[i]);
    }
}


void  JCOverloadDictionary::fuseOverload(JCSynonymTable *someSynonyms)
{
    bool hasMatch= false;

    for (unsigned int i= 0; i < nbrOverloads; i++) {
	if (overloads[i].matchSynonym(someSynonyms)) {
	    someSynonyms->linkToSuper(&overloads[i]);
	    hasMatch= true;
	    break;
	}
    }

    if (!hasMatch) {
	if (superDict != NULL) {
	    superDict->fuseOverload(someSynonyms);
	}
    }
}


JCMethod *JCOverloadDictionary::getOverloadOf(JCMethod *aMethod, JCReferencedType **argTypes, unsigned int nbrArgs)
{
    JCSynonymTable *startSyns;
    JCMethod *result= NULL;
    unsigned matchDistance;

    if ((startSyns= aMethod->getSynonyms()) != NULL) {
	matchDistance= startSyns->findMatch(argTypes, nbrArgs, &result);
	if (matchDistance == 0x0FFFFFFFF) {
	    result= NULL;
	}
	else if (matchDistance != 0) {
	    // TODO: Must scan through the args and insert casts.
	}
    }
    return result;
}

