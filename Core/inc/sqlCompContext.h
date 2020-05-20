#ifndef _SQLCOMPCONTEXT_H_
#define _SQLCOMPCONTEXT_H_
/**************************************************
* File: sqlCompContext.h.
* Desc: Definition of the JCTokenBuffer and SqlCompileContext..
* Module: AkraLog : Plzen.
* Rev: 21 mai 1998 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include <akra/portableDefs.h>

class JCSqlIdentifier;
class JCIdentifier;
class JCExpression;
class JCCteUtf8;


class JCTokenBlock : public AkObject {
    friend class JCTokenBuffer;
  public:
    enum Constants {
	contentSize= 1024
    };

  protected:
    JCTokenBlock *next;
    unsigned char content[contentSize];

  public:
    JCTokenBlock(void);
    JCTokenBlock(JCTokenBlock *aLink);
};


class JCTokenBuffer : public AkObject {
  protected:
    unsigned int offset;
    unsigned int nbrBlocks;
    JCTokenBlock *head, *current;
    
  public:
    JCTokenBuffer(void);
    virtual ~JCTokenBuffer(void);
    virtual void addByte(unsigned char aByte);
    virtual void addShort(unsigned short aShort);
    virtual void addInteger(unsigned int anInteger);
    virtual unsigned int getLength(void);
    virtual void dumpInto(char *aBuffer);
};


class SqlCompileContext : public AkObject {
  protected:
    JCTokenBuffer *tokenBuffer;
	// TMP: Use simple tables to record important components of statements.
    unsigned int nbrCteIDs;
    JCCteUtf8 *tmpCteIDs[256];	// ATTN: MAX of 256 identifiers per statement.
    unsigned int nbrEmbeddeds;
    JCExpression *tmpEmbeddeds[256];	// ATTN: Max of 256 embedded expressions per statement.
    unsigned int nbrStrings;
    char *strings[256];			// ATTN: Max of 256 strings per statement.

  public:
    SqlCompileContext(void);
    SqlCompileContext(JCTokenBuffer *aBuffer);
    virtual ~SqlCompileContext(void);
    virtual JCTokenBuffer *getBuffer(void);
    virtual void mapIdentifier(JCSqlIdentifier *anIdentifier);  // Cree les ID de ref.
    virtual unsigned short getReferenceID(JCIdentifier *aSimpleIdent);  // Trouve le ID de ref pour l'ident.
    virtual unsigned short getHolderID(JCExpression *anExpression);
    virtual unsigned short getStringID(void *aValue);
    virtual void emitByte(unsigned char aByte);
    virtual void emitShort(unsigned short aShort);
    virtual void emitInteger(unsigned int anInteger);
	// TMP:
    virtual JCExpression **getEmbedded(void);
    virtual unsigned int getEmbeddedCount(void);
    virtual unsigned int saveTokens(char **destination, char *signIn, char *signOut);
};


#endif		/* _SQLCOMPCONTEXT_H_ */

