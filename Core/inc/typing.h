#ifndef _TYPING_H_
#define _TYPING_H_
/**************************************************
* File: typing.h.
* Desc: Typing support related functions.
* Module: AkraLog : JavaKit.
* Rev: 29 avril 1996 : REV 0 : Hugo DesRosiers : Creation.
* Rev: 5 juin 1996 : REV 1 : Hugo DesRosiers : Divided typing as 'definition' of type
*	 (compilerObjects.h), and 'referencing' of types (this file).
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"


class JCIdentifier;
class JCResolved;
class JCCteClass;
class JCType;
class JCNamedExpr;
class JCNameSpace;
class JCUnresolved;

class JCReferencedType : public AkObject {
  public:
    enum PopularType {
	popVoid= 0,
	popBoolean, popByte, popChar, popShort, popInteger, popFloat, popLong, popDouble
	, popThrowable, popString, popNullObject
	, nbrPopular
    };

  protected:	// Class variables.
    static JCReferencedType *populars[nbrPopular];

  public:
    static PopularType letterToPopType(char aLetter);

  protected:
    JCReferencedType *next;
    unsigned int kind;
    unsigned int primitiveType;
    unsigned int nbrDimensions;		// If this type is array, nbr of dimensions of the array definition.
    JCIdentifier *typeName;
    JCReferencedType *subType;		// Attention: always a final type, not an array.
    JCResolved *resolver;	// The way to find out what the type refers to.
    JCNameSpace *tmpNameSpace;	// Temporary name space while the JCType is not yet available.

  public:		// Class methods.
    static void initPopularType(void);
    static JCReferencedType *getVoidType(void);
    static JCReferencedType *getPopularType(PopularType aType);
    static int typeCompatibility(JCReferencedType *first, JCReferencedType *second);    // Compute type compatibility, returns -1, 0, 1.
    static JCReferencedType *binaryPromotion(JCReferencedType *first, JCReferencedType *second);	// Compute promoted type for binary arithmetic operations.
    static JCReferencedType *unaryPromotion(JCReferencedType *aType);	// Compute promoted type for unary arithmetic operations.

  public:		// Instance methods.
    JCReferencedType::JCReferencedType(void);
    JCReferencedType::JCReferencedType(unsigned int aPrimitive);
    JCReferencedType(JCType *aType);
    JCReferencedType(char *aFullName, unsigned int nameLength);
    JCReferencedType(unsigned int aKind, JCIdentifier *aName, JCResolved *aResolver);
    virtual void setNext(JCReferencedType *nextElement);
    virtual JCReferencedType *getNext(void);
    virtual bool setKind(unsigned int aKind);
    virtual bool setTypeName(JCIdentifier *aName);
    virtual bool setOfPrimitiveType(unsigned int aBType);
    virtual bool setOfReferencedType(JCReferencedType *aType);
    virtual void incrementNbrDimensions(void);	// Increment the dimensions count of an array type.
    virtual void incNbrDimBy(unsigned int aSize);
    virtual void setNbrDimensions(unsigned int aSize);
    virtual bool isPrimitive(void);	// Returns true on scalar and vectorial primitives.
    virtual bool isArray(void);
    virtual bool isVoid(void);
    virtual bool isResolved(void);
    virtual JCIdentifier *getTypeName(void);
    virtual void setResolution(JCResolved *aResolver);
    virtual JCResolved *resolution(void);
    virtual unsigned int getNbrDimensions(void);
    virtual unsigned int composeSignature(char *aBuffer);
    virtual JCCteClass *getTypeShadow();
    virtual JCType *getRealType(void);
    virtual unsigned int getPrimitiveType(void);
    virtual bool is64Bits(void);		// Return true on scalar long and double.
    virtual bool isArithmetic(void);	// Return true on scalar arithmetic types.
    virtual bool isInstance(void);    // Returns true on class and arrays.
    virtual bool isIntegral(void);	// Return true on scalar integral types.
    virtual bool isBoolean(void);	// Return true on scalar boolean types.
    virtual bool isChar(void);	// Return true on scalar char types.
    virtual bool isString(void);	// Return true on scalar string types.
    virtual void addUser(JCNamedExpr *anExpression);
    virtual JCReferencedType *getArrayBaseType(void);    // For arrays, to return their internal type.
    virtual void importUnknown(JCUnresolved *unresList);
    virtual bool isParameterCompatible(JCReferencedType *aRefType);
    virtual bool isInterfaceImplemented(JCReferencedType *aRefType);
    virtual bool isGE(JCReferencedType *aType);    // Find if a complex type is greater or equal to another one.
 };

#endif	/* _TYPING_H_ */
