#ifndef _INCONSTANT_H_
#define _INCONSTANT_H_
/**************************************************
* File: inConstant.h.
* Desc: Definition of the JCCFConstant, used to read the constant pool of an imported class.
* Module: JavaKit : Compiler.
* Rev: 24 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "classFile.h"


class JCCFConstant : public JACFConstant {
  protected:

  public:
    virtual bool readAttributes(istream *aStream, JACFConstant **ctePool);
    virtual bool read(istream *aStream, JCCFConstant* &realCte);
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFClass : public JCCFConstant {
  protected:

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
    virtual unsigned int getNameIndex(void);
};


class JCCFFieldRef : public JCCFConstant {
  protected:
    unsigned int nameTypeIndex;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFMethodRef : public JCCFConstant {
  protected:
    unsigned int nameTypeIndex;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFString : public JCCFConstant {
  protected:

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFInteger : public JCCFConstant {
  protected:
    unsigned int bytes;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFFloat : public JCCFConstant {
  protected:
    unsigned int bytes;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFLong : public JCCFConstant {
  protected:
    unsigned int bytes;
    unsigned int high_bytes;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFDouble : public JCCFConstant {
  protected:
    unsigned int bytes;
    unsigned int high_bytes;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFInterfaceMethodRef : public JCCFConstant {
  protected:
    unsigned int nameTypeIndex;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFNameAndType : public JCCFConstant {
  protected:
    unsigned int signatureIndex;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


class JCCFUtf8 : public JCCFConstant {
  protected:
    unsigned int length;
    unsigned char *bytes;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
    virtual unsigned char *getAsciiValue(void);
    virtual void writeAsciiValue(unsigned char *aBuffer);
    virtual unsigned int getLength(void);
    bool isEqual(JCCFUtf8 *anUtf);
};


class JCCFUnicode : public JCCFConstant {
  protected:
    unsigned int length;
    unsigned char *bytes;

  public:
    virtual bool read(istream *aStream);
    virtual ConstantTypes type(void);
};


#endif		/*  _INCONSTANT_H_ */