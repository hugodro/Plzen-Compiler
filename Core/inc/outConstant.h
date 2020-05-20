#ifndef _OUTCONSTANT_H_
#define _OUTCONSTANT_H_
/**************************************************
* File: outConstant.h.
* Desc: Definition of the JCOutCFConstant and sub-classes.
*	NOTE: Should be merged with RunTime/constantPool.h.
* Module: AkraLog : JavaKit.
* Rev: 25 novembre 1995 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"

class ofstream;
class ConstantsList;
class JCCteUtf8;
class JCCteNameAndType;
class JCOutClassFile;

class AkHashManager;

class JCOutCFConstant : public AkObject {
  private:
    static ConstantsList *allInstances;

  protected:
    unsigned int myPoolIndex;

  public:		// Class methods.
    static void resetIndexes(void);

  public:		// Intance methods.
    enum Kind {
	kClass= 7, fieldRef= 9, methodRef= 10, interfaceMethodRef= 11,
	string= 8, integer= 3, kFloat= 4, kLong= 5, kDouble= 6,
	nameAndType= 12, utf8= 1, unicode= 2, general= 0
    };

    JCOutCFConstant(void);
    virtual ~JCOutCFConstant(void);
    virtual void write(JCOutClassFile *aClassFile);
    virtual Kind getType(void);
    virtual void resetIndex(void);
    virtual void setIndex(unsigned int aPos);
    virtual unsigned int getIndex(void);
    virtual bool hasNullIndex(void);
    virtual void addToPool(ConstantsList *aPool);
    virtual void unassemble(char *outBuffer)= 0;
};


class JCDoubleFiller : public JCOutCFConstant {
    void unassemble(char *outBuffer);
};

class JCCteClass : public JCOutCFConstant {
  protected:
    JCCteUtf8 *refName;		// Index to name (utf8).
    
  public:
    JCCteClass(JCCteUtf8 *aCteName);
    virtual Kind getType(void);
    virtual void addToPool(ConstantsList *aPool);
    virtual void write(JCOutClassFile *aClassFile);
    virtual void unassemble(char *outBuffer);
};


class JCReference : public JCOutCFConstant {
  protected:
    JCCteClass *typeIndex;		// Class in which this is defined (kClass).
    JCCteNameAndType *nameType;		// Name and type of this field (nameAndType).

  public:
    JCReference(JCCteClass *aClass, JCCteNameAndType *aNameType);
    virtual void addToPool(ConstantsList *aPool);
    virtual void writeNameType(JCOutClassFile *aClassFile);
    virtual void write(JCOutClassFile *aClassFile);
    virtual JCCteNameAndType * getNameType(void);
    virtual void unassemble(char *outBuffer);
};


class JCCteFieldRef : public JCReference {

  public:
    JCCteFieldRef(JCCteClass *aClass, JCCteNameAndType *aNameType) : JCReference(aClass, aNameType) {};
    virtual Kind getType(void);
    virtual void unassemble(char *outBuffer);
};


class JCCteMethodRef : public JCReference {
  protected:

  public:
    JCCteMethodRef(JCCteClass *aClass, JCCteNameAndType *aNameType) : JCReference(aClass, aNameType) {};
    virtual Kind getType(void);
    virtual void unassemble(char *outBuffer);
};


class JCCteInterfaceMethodRef : public JCReference {
  protected:

  public:
    JCCteInterfaceMethodRef(JCCteClass *aClass, JCCteNameAndType *aNameType) : JCReference(aClass, aNameType) {};
    virtual Kind getType(void);
    virtual void unassemble(char *outBuffer);
};


class JCCteNameAndType : public JCOutCFConstant {
  protected:
    JCCteUtf8 *name;		// name of the field, class' or interface's method (utf8).
    JCCteUtf8 *signature;	// Type signature. (utf8).

  public:
    JCCteNameAndType(JCCteUtf8 *aName, JCCteUtf8 *aType);
    virtual Kind getType(void);
    virtual void addToPool(ConstantsList *aPool);
    virtual void write(JCOutClassFile *aClassFile);
    virtual void writeIndexes(JCOutClassFile *aClassFile);
    virtual void unassemble(char *outBuffer);
};


class JCCteString : public JCOutCFConstant {
  protected:	// Class variables.
    static ConstantsList *uniqueStringValues;

  public:
    static JCCteString *addUnique(JCCteUtf8 *aValue);

  protected:
    JCCteUtf8 *valueIndex;		// Actual value (utf8).

  public:
    JCCteString(JCCteUtf8 *aUtf8);
    virtual Kind getType(void);
    virtual void addToPool(ConstantsList *aPool);
    virtual void write(JCOutClassFile *aClassFile);
    virtual void unassemble(char *outBuffer);
    virtual bool isEqual(JCCteUtf8 *aUtfCte);
};


class JCWord : public JCOutCFConstant {
  public:
    enum SpecialWordCte {
	scIntZero= 0, scIntOne, scIntMinusOne,
	scFloatZero, scFloatOne, scFloatMinusOne
	, nbrSpecialWordCtes
    };

  protected:
    static ConstantsList *uniqueIntValues;
    static ConstantsList *uniqueFloatValues;
    static JCWord *specialWordCte[nbrSpecialWordCtes];

  protected:
    static void initSpecialCte(void);

  public:
    static JCWord *addUnique(int aValue);
    static JCWord *addUnique(float aValue);
    static JCWord *getSpecialCte(SpecialWordCte anCte);
    static bool isSpecialCte(JCWord *aCte);

  protected:
    unsigned int bytes;		// Actual value of the constant (IEEE 754 for floats).

  public:
    JCWord();
    virtual void write(JCOutClassFile *aClassFile);
    virtual JCWord *arithmeticNegation(void);
};

class JCCteInteger : public JCWord {
  protected:

  public:
    JCCteInteger(int aValue);
    virtual Kind getType(void);
    virtual bool isEqual(int aValue);
    virtual int intValue(void);
    virtual void unassemble(char *outBuffer);
};


class JCCteFloat : public JCWord {
  protected:

  public:
    JCCteFloat(float aValue);
    virtual Kind getType(void);
    virtual bool isEqual(float aValue);
   virtual float floatValue(void);
    virtual void unassemble(char *outBuffer);
};


class JCDoubleWord : public JCOutCFConstant {
  public:
    enum SpecialDblWordCte {
	scLongZero= 0, scLongOne, scLongMinusOne,
	scDoubleZero, scDoubleOne, scDoubleMinusOne
	, nbrSpecialDblWordCtes
    };

  protected:
    static ConstantsList *uniqueLongValues;
    static ConstantsList *uniqueDoubleValues;
    static JCDoubleWord *specialDblWordCte[nbrSpecialDblWordCtes];

  protected:
    static void initSpecialCte(void);

  public:
    static JCDoubleWord *addUnique(unsigned int *aValue);
    static JCDoubleWord *addUnique(double aValue);
    static JCDoubleWord *getSpecialCte(SpecialDblWordCte anCte);
    static bool isSpecialCte(JCDoubleWord *aCte);

  protected:
    unsigned int lowBytes;		// 4 first bytes of the value.
    unsigned int highBytes;		// 4 second bytes of the value.

  public:
    JCDoubleWord();
    virtual void write(JCOutClassFile *aClassFile);
    virtual JCDoubleWord *arithmeticNegation(void);
    virtual void addToPool(ConstantsList *aPool);
};


class JCCteLong : public JCDoubleWord {
  protected:

  public:
    JCCteLong(unsigned int *aValue);
    virtual Kind getType(void);
    virtual bool isEqual(unsigned int *aValue);
    virtual bool isEqual(unsigned int high, unsigned int low);
    virtual void longValue(unsigned int *aValue);
    virtual void unassemble(char *outBuffer);
};


class JCCteDouble : public JCDoubleWord {
  protected:

  public:
    JCCteDouble(double aValue);
    virtual Kind getType(void);
    virtual bool isEqual(double aValue);
    virtual double doubleValue(void);
    virtual void unassemble(char *outBuffer);
};


class JCCharString : public JCOutCFConstant {
  protected:
    unsigned int length;		// Number of bytes in the string.
    unsigned char *bytes;	// String (without null-termination, but with UTF8 null char appended).

  public:
    JCCharString(void);
    virtual ~JCCharString(void);
    virtual void write(JCOutClassFile *aClassFile);
    virtual void unassemble(char *outBuffer);
};


class JCCteUtf8 : public JCCharString {
  private:
    static ConstantsList *uniqueInstances;
    static AkHashManager *hashManager;
    static JCCteUtf8 *wellKnownNames;	// List of constant names used often (SourceFile, ConstantValue, etc).

  protected:

  public:
      enum WellKnownNames {
	sourceFile= 0, constantValue, code, exceptions, lineNumTbl, localVarTbl,
	thisIdent, superIdent, initIdent, clinitIdent
#if defined(PLZEN_LEVEL_2)
	, transitions, stateCode, pinitIdent
#endif
#if defined(PLZEN_LEVEL_3)
	, execSql
#endif
	, nbrWellKnownNames
    };

  public:		// Class methods.
    static JCCteUtf8 *addUniqueInstance(unsigned short *byteArray);
    static void initCteUtf8Class(void);
    static JCCteUtf8 *getWellKnownName(WellKnownNames aNameID);

  public:		// Instance methods.
    virtual Kind getType(void);
    virtual void setValue(unsigned short *byteArray);
    virtual char *asciiString(void);
    virtual unsigned int asciiLength(void);
    virtual bool isAsciiEqual(unsigned char *aString);
    virtual bool isEqual(JCCteUtf8 *anUtf8);
    virtual void unassemble(char *outBuffer);
};


class JCCteUnicode : public JCCharString {
  private:
    static ConstantsList *uniqueInstances;

  protected:

  public:
    virtual Kind getType(void);
};


#endif		/* _OUTCONSTANT_H_ */
