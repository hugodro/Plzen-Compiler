#ifndef _IMPORTCLASS_H_
#define _IMPORTCLASS_H_
/**************************************************
* File: importClass.h.
* Desc: Defintion of classes dealing with imported Java classes.
* Module: JavaKit : Compiler.
* Rev: 23 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "jvtypes.h"
#include "classFile.h"


class istream;
class JCFieldInfo;
class JCMethodInfo;
class JCAttributeInfo;
class JCCFConstant;
class JCCFUtf8;
class JCCompiler;
class JCField;
class JCMethod;
class JCReferencedType;
class JCImportedClass;


class JCImportClassFile : public JAClassFile {
    friend class JCFieldInfo;
    friend class JCMethodInfo;

  protected:
    JCCFConstant **constantPool;		// Constant values (strings, names, etc).
    JCFieldInfo *fields;				// Field definitions.
    JCMethodInfo *methods;			// Method definitions.
    JCAttributeInfo **attributes;		// Optional attributes attached to the class.
    JCImportedClass *dual;			// The 'JCType' that represents this within the compiler.

  public:
    virtual bool readFromStream(istream *aStream);
    virtual char *getAsciiName(void);
    virtual JCCFUtf8 *getSuper(void);
    virtual JCFieldInfo *getField(JCIdentifier *aName);
    virtual JCMethodInfo *getBaseMethod(JCIdentifier *aName);
    virtual void setDual(JCImportedClass *aClass);
    virtual JCImportedClass *getDual(void);
    virtual JCMethodInfo *getNextMethod(JCMethodInfo *aMethod);
};


class JCFieldInfo : public JAFieldInfo {
  public:	// Class methods.
    static int parseSignature(char *aSignature, JCReferencedType **type);

  protected:
    JCAttributeInfo **attributes;
    JCField *dereference;

  public:	// Instance methods.
    JCFieldInfo(void);
    virtual bool readAttributes(istream *aStream, JACFConstant **ctePool);
    virtual JCField *resolve(JCCompiler *compiler);
    virtual bool isNamed(JCIdentifier *aName, JCCFConstant **ctePool);
};


class JCMethodInfo : public JAMethodInfo {
  public:		// Static method
    int parseArguments(char *aSignature, JCReferencedType ***types);

  protected:
    bool isStateInfo;
    JCAttributeInfo **attributes;
    JCMethod *dereference;

  public:
    JCMethodInfo(void);
    virtual bool read(istream *aStream, JACFConstant **ctePool);
    virtual bool readAttributes(istream *aStream, JACFConstant **ctePool);
    virtual bool isState(void);
    virtual JCMethod *resolve(JCCompiler *compiler);
    virtual bool isNamed(JCIdentifier *aName, JCCFConstant **ctePool);
    virtual bool isSynonym(JCMethodInfo *aMethod, JCCFConstant **ctePool);
};


#endif		/* _IMPORTCLASSFILE_H_ */
