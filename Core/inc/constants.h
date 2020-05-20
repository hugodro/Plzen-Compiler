#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
/**************************************************
* File: constants.h.
* Desc: Some constant definitions used by the Compiler and Engine.
* Module: AkraLog : JavaKit.
* Rev: 4 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

/* Access flags for various class file components. */
/* Meanings of protection for fields:
  public: accessible everywhere where the class name is accessible.
  protected: accessible for subclasses declared within the same package.
  private: accessible only in the class body where the field is declared.
  nothing: the field is 
*/
#define ACC_PUBLIC				0x0001
#define ACC_PRIVATE				0x0002
#define ACC_PROTECTED			0x0004
#define ACC_STATIC				0x0008
#define ACC_FINAL				0x0010
#define ACC_SYNCHRONIZED		0x0020
#define ACC_VOLATILE			0x0040
#define ACC_TRANSIENT			0x0080
#define ACC_NATIVE				0x0100
#define ACC_INTERFACE			0x0200
#define ACC_ABSTRACT			0x0400


/* Constant types. */
#define CONSTANT_Class			7
#define CONSTANT_FieldRef		9
#define CONSTANT_MethodRef		10
#define CONSTANT_InterfaceMethodRef	11
#define CONSTANT_String			8
#define CONSTANT_Integer			3
#define CONSTANT_Float			4
#define CONSTANT_Long			5
#define CONSTANT_Double		6
#define CONSTANT_NameAndType	12
#define CONSTANT_Utf8			1
#define CONSTANT_Unicode		2
// Akra addition.
#define CONSTANT_Bool			13
#define CONSTANT_Char			14


/* Pre-assignment operators defined in Java. */
#define SIMPLEASS_OPER		1
#define PLUSASS_OPER		2
#define MINUSASS_OPER		3
#define TIMEASS_OPER		4
#define DIVIDEASS_OPER		5
#define ANDASS_OPER		6
#define ORASS_OPER			7
#define NOTASS_OPER		8
#define MODASS_OPER		9
#define LSASS_OPER			10
#define RSASS_OPER			11
#define URSASS_OPER		12

/* Logical binary operators. */
#define OROR_OPER			13
#define ANDAND_OPER		14

/* Bitwise binary operators. */
#define OR_OPER				15
#define AND_OPER			16
#define XOR_OPER			17

/* Comparaison operators. */
#define NE_OPER				18
#define EQ_OPER				19
#define ISA_OPER				20
#define LE_OPER				21
#define GE_OPER				22
#define GT_OPER				23
#define LT_OPER				24

/* Bit movers. */
#define URS_OPER			25
#define RS_OPER				26
#define LS_OPER				27

/* General binary operators. */
#define SUBST_OPER			28
#define ADD_OPER			29
#define MODULO_OPER		30
#define DIVIDE_OPER			31
#define MULTIPLY_OPER		32

/* General unary operators. */
#define CAST_OPER			33
#define BITFLIP_OPER			34
#define NOT_OPER			35
#define PREINCR_OPER		36
#define PREDECR_OPER		37
#define POSTINCR_OPER		38
#define POSTDECR_OPER		39
#define NEGATE_OPER		40
#define POSATE_OPER		41


// Definition of the types that are internal to the J-Machine.
#define JVM_TYPE_VOID				'V'
#define JVM_TYPE_BOOLEAN			'Z'
#define JVM_TYPE_SIGNED_BYTE		'B'
#define JVM_TYPE_CHAR				'C'
#define JVM_TYPE_UNSIGNED_SHORT	'S'
#define JVM_TYPE_INTEGER			'I'
#define JVM_TYPE_FLOAT				'F'
#define JVM_TYPE_LONG				'J'
#define JVM_TYPE_DOUBLE			'D'
#define AKR_TYPE_STRING			's'
// Meta-types for the type definitions.
#define TYPE_BASIC		(1 << 0)
#define TYPE_CLASS		(1 << 1)
#define TYPE_ARRAY		(1 << 2)
#define TYPE_INTERFACE	(1 << 9)


/* Attribute types. */
#define ATTR_GENERIC		1
#define ATTR_SRCFILE		2
#define ATTR_CONSTANT		3
#define ATTR_CODE			4
#define ATTR_EXCEPTION		5
#define ATTR_LINENUMBER	6
#define ATTR_LOCALVAR		7

#endif	/* _BYTECODE_H_ */

