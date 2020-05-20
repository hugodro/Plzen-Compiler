#ifndef _JACLASSFILE_H_
#define _JACLASSFILE_H_
/**************************************************
* File: classFile.h.
* Desc: Definition of the compiled JAClassFile class and associated classes.
* Module: JavaKit : Compiler.
* Rev: 21 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>

#include <akra/AkObject.h>
#include "jvtypes.h"


class JACFConstant;
class istream;

class JAClassFile : public AkObject {
  public:
    enum AccessFlags {
	afPublic= 0x0001, afPrivate= 0x0002, afProtected= 0x0004,
	afStatic= 0x0008, afFinal= 0x0010, afSynchronized= 0x0020,
	afVolatile= 0x0040, afTransient= 0x0080, afNative= 0x0100,
	afInterface= 0x0200, afAbstract= 0x0400
    };

  protected:
    unsigned int magic;				// 0x0CAFEBABE.
    unsigned int version_minor;		// version of java compiler used to compile.
    unsigned int version_major;		// version of java compiler used to compile.
    unsigned int ctePoolSize;			// Size of constant pool.
    unsigned int accessFlags;			// Flags of the class definition.
    unsigned int thisClass;			// Index to the class in the constant_pool.
    unsigned int superClass;			// Index to the super-class inthe constant_pool.
    unsigned int interfaceCount;		// Number of interfaces implemented by the class.
    unsigned int *interfaces; 			 // Indexes of the interfaces implemented (in the constant_pool).
    unsigned int fieldCount;			// Number of fields (variables) defined in the class (current layer only).
    unsigned int methodCount;			// Number of methods defined in the class (current layer only).
    unsigned int attributeCount;		// Number of optional attributes given to the class.
    // NOTE: The actual components types of {constants, fields, methods, attributes} are defined
    // by the subclasses, since the compile and run-time versions are quite different in nature.

  public:
    JAClassFile(void);
    virtual bool isInterface(void);
};


class JALoadedObject : public AkObject {
  protected:
    bool isResolved;

  public:
    JALoadedObject();
    virtual bool read(istream *aStream)= 0;
 };


class JAComponentInfo : public JALoadedObject {
  protected:
    unsigned int accessFlags;		// Access flags of the field.
    unsigned int nameIndex;			// Index of the name in constant_pool.
    JAClassFile *owner;				// Owner of the info object.

  public:
    virtual bool read(istream *aStream);
    virtual bool read(istream *aStream, JACFConstant **ctePool);
    virtual bool isNamed(char *aName, JACFConstant **ctePool);
    virtual void setOwner(JAClassFile *classFile);
    virtual JAClassFile *getOwner(void);
    virtual bool isStatic(void);
};


class JAMemberInfo : public JAComponentInfo {
  protected:
    unsigned int signatureIndex;		// Index of the signature name in constant_pool.
    unsigned int attributeCount;		// Number of optional attributes for the field.

  public:
    virtual bool read(istream *aStream, JACFConstant **ctePool);
    virtual bool readAttributes(istream *aStream, JACFConstant **ctePool);
};


class JAFieldInfo : public JAMemberInfo {
  protected:
  public:
};


class JAMethodInfo : public JAMemberInfo {
  protected:

  public:
    virtual bool read(istream *aStream, JACFConstant **ctePool);
    virtual bool isFromInterface(void);
 };


class JACFConstant : public JALoadedObject {
  public:
    enum ConstantTypes {
	ctClass= 7, ctFieldRef= 9, ctMethodRef= 10, ctInterfaceMethodRef= 11,
	ctString= 8, ctInteger= 3, ctFloat= 4, ctLong= 5, ctDouble= 6, ctNameAndType= 12,
	ctUtf8= 1, ctUnicode= 2
	, ctUnknown= 255
    };

  protected:
    unsigned int index;		// Index in constant_pool of the main object related to the Constant.

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void)= 0;
};

class JACFString : public JACFConstant {
  protected:
  public:
    virtual bool isStrEqual(char *aStr);
};


#endif		/* _JACLASSFILE_H_ */
