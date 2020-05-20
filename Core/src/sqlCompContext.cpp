/**************************************************
* File: sqlCompContext.cc.
* Desc: Implementation of the JCTokenBuffer and SqlCompileContext..
* Module: AkraLog : Plzen.
* Rev: 22 mai 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(_WIN32)
#include <memory.h>
#endif
#if defined(__linux__) || defined(__WIN32) || defined(__APPLE__)
#include <string.h>
#endif

#include "identifiers.h"
#include "sqlIdentifier.h"
#include "outConstant.h"
#include "constants.h"
#include "sqlCompContext.h"

#define MakeUInt(a, b)	{ \
	    *(a)= ((b) >> 24) & 0x0FF; \
	    *((a)+ 1)= ((b) >> 16) & 0x0FF; \
	    *((a)+ 2)= ((b) >> 8) & 0x0FF; \
	    *((a)+ 3)= (b) & 0x0FF; \
	}


#define MakeUShort(a, b)	{ \
	    *(a)= ((b) >> 8) & 0x0FF; \
	    *((a)+ 1)= (b) & 0x0FF; \
	}


/**************************************************
* Implementation: JCTokenBlock.
**************************************************/

JCTokenBlock::JCTokenBlock(void)
{
    next= NULL;
}


JCTokenBlock::JCTokenBlock(JCTokenBlock *aLink)
{
   aLink->next= this;
}


/**************************************************
* Implementation: JCTokenBuffer.
**************************************************/

JCTokenBuffer::JCTokenBuffer(void)
{
    current= head= new JCTokenBlock();
    offset= 0;
    nbrBlocks= 1;
}


JCTokenBuffer::~JCTokenBuffer(void)
{
    JCTokenBlock *nextBlock, *tmpBlock= head;

    while (tmpBlock != NULL) {
	nextBlock= tmpBlock->next;
	delete tmpBlock;
	tmpBlock= nextBlock;
    }
}


void JCTokenBuffer::addByte(unsigned char aByte)
{
    if (offset == JCTokenBlock::contentSize) {
	offset= 0;
	current= new JCTokenBlock(current);
    }
    current->content[offset++]= aByte;
}


void JCTokenBuffer::addShort(unsigned short aShort)
{
    if (offset < (JCTokenBlock::contentSize-1)) {
	current->content[offset++]= (unsigned char)((aShort >> 8) & 0x0FF);
	current->content[offset++]= (unsigned char)(aShort & 0x0FF);
    }
    else {
	int i= 8;

	if (offset < JCTokenBlock::contentSize) {
	    current->content[offset++]= (unsigned char)((aShort >> 8) & 0x0FF);
	    i-= 8;
	}
	offset= 0;
	current= new JCTokenBlock(current);
	for (; i >= 0;) {
	    current->content[offset++]= (unsigned char)((aShort >> i) & 0x0FF);
	    i-= 8;
	}
    }
}


void JCTokenBuffer::addInteger(unsigned int anInteger)
{
    if (offset < (JCTokenBlock::contentSize-3)) {
	current->content[offset++]= (unsigned char)((anInteger >> 24) & 0x0FF);
	current->content[offset++]= (unsigned char)((anInteger >> 16) & 0x0FF);
	current->content[offset++]= (unsigned char)((anInteger >> 8) & 0x0FF);
	current->content[offset++]= (unsigned char)(anInteger & 0x0FF);
    }
    else {
	int i= 24;

	while (offset < JCTokenBlock::contentSize) {
	    current->content[offset++]= (unsigned char)((anInteger >> i) & 0x0FF);
	    i-= 8;
	}
	offset= 0;
	current= new JCTokenBlock(current);
	for (; i >= 0;) {
	    current->content[offset++]= (unsigned char)((anInteger >> i) & 0x0FF);
	    i-= 8;
	}
    }
}


unsigned int JCTokenBuffer::getLength(void)
{
    return (offset + (nbrBlocks-1) * JCTokenBlock::contentSize);
}


void JCTokenBuffer::dumpInto(char *aBuffer)
{
    JCTokenBlock *tmpBlock= head;
    unsigned int offsetPos= 0;

    do {
	if (tmpBlock->next != NULL) {
	    memcpy(aBuffer+offsetPos, tmpBlock->content, JCTokenBlock::contentSize);
	    offsetPos+= JCTokenBlock::contentSize;
	}
	else {
	    memcpy(aBuffer+offsetPos, tmpBlock->content, offset);
	}
	tmpBlock= tmpBlock->next;
    } while (tmpBlock != NULL);
}


/**************************************************
* Implementation: SqlCompileContext.
**************************************************/

SqlCompileContext::SqlCompileContext(void)
{
    tokenBuffer= new JCTokenBuffer();
    nbrCteIDs= 0;
    nbrEmbeddeds= 0;
    nbrStrings= 0;
}


SqlCompileContext::SqlCompileContext(JCTokenBuffer *aBuffer)
{
    tokenBuffer= aBuffer;
    nbrCteIDs= 0;
    nbrEmbeddeds= 0;
    nbrStrings= 0;
}


SqlCompileContext::~SqlCompileContext(void)
{
    delete tokenBuffer;
    // ATTN-980522 [HD]: All the strings and identifiers could also be deleted, since they
    //	are normally copied serially into a single array of byte.
}


JCTokenBuffer *SqlCompileContext::getBuffer(void)
{
    return tokenBuffer;
}


void SqlCompileContext::mapIdentifier(JCSqlIdentifier *anIdentifier)
{
    JCCteUtf8 *utfCte;
    JCIdentifier *simpleIdent;
    unsigned int i;
    // ATTN: Should create an outCte for the identifier, and put in the current constant pool.
    // TMP: Make a simple array of identifiers provided, without duplications.

    simpleIdent= anIdentifier->getSimpleIdentifier();
    while (simpleIdent != NULL) {
	utfCte= simpleIdent->getValue();
	for (i= 0; i < nbrCteIDs; i++) {
	    if (tmpCteIDs[i] == utfCte) break;
	}
	if (i == nbrCteIDs) {
	    tmpCteIDs[nbrCteIDs++]= utfCte;
	}
	simpleIdent= simpleIdent->getComponent();
    }
}


unsigned short SqlCompileContext::getReferenceID(JCIdentifier *aSimpleIdent)
{
    JCCteUtf8 *utfCte;

    // ATTN: This method is a helper for the temporary solution of arrays of CteUtf8.

    utfCte= aSimpleIdent->getValue();
    for (unsigned int i= 0; i < nbrCteIDs; i++) {
	if (tmpCteIDs[i] == utfCte) return (short)i;	// Warning: quick exit.
    }

    return 0;		// TMP: No error management.
}


unsigned short SqlCompileContext::getHolderID(JCExpression *anExpression)
{
    // ATTN: Should make sure that expressions are not duplicated.
    // TMP: For now, simply make an array of everything provided, and return index.

    tmpEmbeddeds[nbrEmbeddeds]= anExpression;
    return nbrEmbeddeds++;
}


unsigned short SqlCompileContext::getStringID(void *aValue)
{
  // ATTN: Should make sure that expressions are not duplicated, use constant pool, etc.
    // TMP: For now, simply make an array of everything provided, and return index.

    strings[nbrStrings]= (char *)aValue;
    return nbrStrings++;
}


void SqlCompileContext::emitByte(unsigned char aByte)
{
    tokenBuffer->addByte(aByte);
}


void SqlCompileContext::emitShort(unsigned short aShort)
{
    tokenBuffer->addShort(aShort);
}


void SqlCompileContext::emitInteger(unsigned int anInteger)
{
    tokenBuffer->addInteger(anInteger);
}


JCExpression **SqlCompileContext::getEmbedded(void)
{
    return tmpEmbeddeds;
}


unsigned int SqlCompileContext::getEmbeddedCount(void)
{
    return nbrEmbeddeds;
}


unsigned int SqlCompileContext::saveTokens(char **destination, char *signIn, char *signOut)
{
    unsigned int *tmpStringLength;
    unsigned int i, j, totalLength, lngInSign, lngOutSign;
    unsigned char *tmpArray, *arrayCursor;

    totalLength= 0;
    if (signIn != NULL) {
	lngInSign= strlen(signIn);
    }
    else {
	lngInSign= 1;
    }
    if (signOut != NULL) {
	lngOutSign= strlen(signOut);
    }
    else {
	lngOutSign= 1;
    }
    totalLength+= lngInSign + lngOutSign;

    for (i= 0; i < nbrCteIDs; i++) {
	totalLength+= tmpCteIDs[i]->asciiLength();
    }

    if (nbrStrings > 0) {
	tmpStringLength= new unsigned int[nbrStrings];    

	for (i= 0; i < nbrStrings; i++) {
	    tmpStringLength[i]= strlen(strings[i]);
	    totalLength+= tmpStringLength[i];
	}
    }
	// Format: <length:uint> <version:byte> 
	//		<nbrIdent:ushort> {<lengthIdent:ushort><ident:charArray>}*
	//		<nbrCtes:ushort> {<lengthCte:ushort><cte:charArray>}*
	//		<lengthTokens:ushort> <tokens:charArray>
	//		<lengthSignIn:ushort> <signatureIn:charArray>
	//		<lengthSignOut:ushort><signatureOut:charArray>
    totalLength+= 15 + (nbrStrings + nbrCteIDs) * 2;

    arrayCursor= tmpArray= new unsigned char[totalLength + tokenBuffer->getLength()];
    MakeUInt(arrayCursor, totalLength - 10 - lngInSign - lngOutSign);	// This gives the offset of the beginning of the code chunk.
    arrayCursor+= sizeof(unsigned int);
    *arrayCursor++= (unsigned char)0x01;	// SQL Version (SQL92: [1-129], SQL3: [129-255]).
    MakeUShort(arrayCursor, (unsigned short)(nbrCteIDs));
    arrayCursor+= sizeof(unsigned short);
    MakeUShort(arrayCursor, (unsigned short)(nbrStrings));
    arrayCursor+= sizeof(unsigned short);
    for (i= 0; i < nbrCteIDs; i++) {
	j= tmpCteIDs[i]->asciiLength();
	MakeUShort(arrayCursor, j);
	arrayCursor+= sizeof(unsigned short);
	memcpy(arrayCursor, tmpCteIDs[i]->asciiString(), j);
	arrayCursor+= j;
    }
    for (i= 0; i < nbrStrings; i++) {
	MakeUShort(arrayCursor, tmpStringLength[i]);
	arrayCursor+= sizeof(unsigned short);
	memcpy(arrayCursor, strings[i], tmpStringLength[i]);
	arrayCursor+= tmpStringLength[i];
    }
    MakeUShort(arrayCursor, (unsigned short)(tokenBuffer->getLength()));
    arrayCursor+= sizeof(unsigned short);
    tokenBuffer->dumpInto((char *)arrayCursor);
    totalLength+= tokenBuffer->getLength();	// Correct the total length.
    arrayCursor+= tokenBuffer->getLength();
    MakeUShort(arrayCursor, lngInSign);
    arrayCursor+= sizeof(unsigned short);
    if (signIn != NULL) {
	memcpy(arrayCursor, signIn, lngInSign);
    }
    else {
	*arrayCursor++= JVM_TYPE_VOID;
    }
    arrayCursor+= lngInSign;
    MakeUShort(arrayCursor, lngOutSign);
    arrayCursor+= sizeof(unsigned short);
    if (signOut != NULL) {
	memcpy(arrayCursor, signOut, lngOutSign);
    }
    else {
	*arrayCursor++= JVM_TYPE_VOID;
    }
    arrayCursor+= lngOutSign;

	// ATTN-980522 [HD]: We have to take out the '\0' of the string, since they will make JCCteUtf8 freak out.
	// 	All JCCteUtf8 manipulations must be revised, to see if this limitation on the '\0'
	//	can be taken away.
    for (j= 0, i= 0; i < totalLength; i++) {
	if ((tmpArray[i] == '\0') || (tmpArray[i] == (unsigned char)0x088)) j++;
    }
    if (j != 0) {
	unsigned int k;
	char *escapedArray= new char[totalLength + j];

	for (k= i= 0; i < totalLength; i++, k++) {
	    if ((tmpArray[i] == '\0') || (tmpArray[i] == (unsigned char)0x088)) {
		escapedArray[k++]= (unsigned char)0x088;
		escapedArray[k]= tmpArray[i]+1;
	    }
	    else {
		escapedArray[k]= tmpArray[i];
	    }
	}
	delete tmpArray;
	tmpArray= (unsigned char *)escapedArray;
	totalLength+= j;
    }

    if (nbrStrings > 0) delete tmpStringLength;
    *destination= (char *)tmpArray;
    return totalLength;
}
