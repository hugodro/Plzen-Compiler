#ifndef _OUTCLASSFILE_H_
#define _OUTCLASSFILE_H_
/**************************************************
* File: outClassFile.h.
* Desc: Definition of the JCOutClassFile class.
* Module: AkraLog : JavaKit.
* Rev: 25 novembre 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"

class JCType;
class JCOutCFConstant;
class JCCteUtf8;
class JCCompilationContext;
class ConstantsList;
class AttributesList;
class JCMethod;
class ofstream;


class JCOutClassFile : public AkObject {
  protected:
    JCType *myClass;
    ofstream *outStream;
    bool isOpened;
    unsigned int magicNumber;
    unsigned int majorVersion, minorVersion;
    ConstantsList *constantPool;	// Constant values (strings, names, etc).
    unsigned int classNameIndex, superClassNameIndex;
    unsigned int sourceFileNameIndex;
    JCCompilationContext *compileCtxt;
    AttributesList *attributes;	// This file attributes (should be only SourceCode for now).


  private:

  public:
    JCOutClassFile(JCCompilationContext *aCompCtxt, JCType *aType);		// Generate a short name internally.
    JCOutClassFile(JCCompilationContext *aCompCtxt, char *aName, JCType *aType);    // Make file at path.
    virtual ~JCOutClassFile(void);
    virtual void init(char *aName, JCType *aType);
    virtual void save(void);
    virtual void saveFileHeader(void);
    virtual bool buildConstantPool(void);
    virtual void saveConstantPool(void);
    virtual void saveTypeHeader(void);
    virtual void saveAttributes(void);
    void writeUInteger(unsigned int aNumber);
    void writeUShort(unsigned int aNumber);
    virtual bool opened(void);
    virtual ConstantsList *getConstantPool(void);
    virtual void writeUByte(unsigned char aByte);
    virtual void writeByteArray(unsigned char *buffer, unsigned int length);
    virtual void startCodeContext(JCMethod *aMethod);
    virtual void closeCodeContext(void);
    virtual JCCompilationContext *getCodeContext(void);
    virtual void dumpConstantPool(void);
};

#endif		/* _OUTCLASSFILE_H_ */