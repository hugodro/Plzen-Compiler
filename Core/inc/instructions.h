#ifndef _JCINSTRUCTIONS_H_
#define _JCINSTRUCTIONS_H_
/**************************************************
* File: instructions.h.
* Desc: Contains the definition of the Java instructions set and related information.
* Module: AkraLog : JavaComp.
* Rev: 23 decembre 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"

class JCInstrSet : public AkObject {
  public:
    enum OpcodeArgType {
	noArg= 0, argByte, argShort, arg3Bytes, argInteger, argVarSize
    };
    enum Instructions {
	nop, aconst_null, iconst_m1, iconst_0, iconst_1,
	iconst_2, iconst_3, iconst_4, iconst_5, lconst_0,
	lconst_1, fconst_0, fconst_1, fconst_2, dconst_0,
	dconst_1, bipush, sipush, ldc1, ldc2,
	ldc2w, iload, lload, fload, dload,
	aload, iload_0, iload_1, iload_2, iload_3,
	lload_0, lload_1, lload_2, lload_3, fload_0,
	fload_1, fload_2, fload_3, dload_0, dload_1,
	dload_2, dload_3, aload_0, aload_1, aload_2,
	aload_3, iaload, laload, faload, daload,
	aaload, baload, caload, saload, istore,
	lstore, fstore, dstore, astore, istore_0,
	istore_1, istore_2, istore_3, lstore_0, lstore_1,
	lstore_2, lstore_3, fstore_0, fstore_1, fstore_2,
	fstore_3, dstore_0, dstore_1, dstore_2, dstore_3,
	astore_0, astore_1, astore_2, astore_3, iastore,
	lastore, fastore, dastore, aastore, bastore,
	castore, sastore, pop, pop2, dup,
	dup_x1, dup_x2, dup2, dup2_x1, dup2_x2,
	swap, iadd, ladd, fadd, dadd,
	isub, lsub, fsub, dsub, imul,
	lmul, fmul, dmul, idiv, ldiv,
	fdiv, ddiv, irem, lrem, frem,
	drem, ineg, lneg, fneg, dneg,
	ishl, lshl, ishr, lshr, iushr,
	lushr, iand, land, ior, lor,
	ixor, lxor, iinc, i2l, i2f,
	i2d, l2i, l2f, l2d, f2i,
	f2l, f2d, d2i, d2l, d2f,
	int2byte, int2char, int2short, lcmp, fcmpl,
	fcmpg, dcmpl, dcmpg, ifeq, ifne,
	iflt, ifge, ifgt, ifle, if_icmpeq,
	if_icmpne, if_icmplt, if_icmpge, if_icmpgt, if_icmple,
	if_acmpeq, if_acmpne, goto_n, jsr, ret,
	tableswitch, lookupswitch, ireturn, lreturn, freturn,
	dreturn, areturn, vreturn, getstatic, putstatic,
	getfield, putfield, invokevirtual, invokenonvirtual, invokestatic,
	invokeinterface, anew, newarray, anewarray, arraylength,
	athrow, checkcast, instanceof, monitorenter, monitorexit,
	wide, multianewarray, ifnull, ifnonnull, goto_w,
	jsr_w, breakpoint, ret_w
#if defined(PLZEN_LEVEL_2)
      , fire, firestatic, firefield, wait
#endif
    };

  public:
    static unsigned int instructionIDs[256];

  private:
    static OpcodeArgType argumentType[256];
    static unsigned char instructionSize[256];
    static char stackUse[256];
    // DEBUG:
    static const char * const instructionNames[256];


  public:	// Class methods.
    static Instructions getOptimizedVersion(Instructions aCode, unsigned int anIndex);
    static Instructions getTypedOp(Instructions aCode, unsigned int aPrimaryType);
    static unsigned int getSizeOf(Instructions aCode);
    static int getStackUseOf(Instructions aCode);
    static const char * const getName(Instructions aCode);
    static const unsigned int primaryTypeToByteCode(unsigned int aPrimaryType);
    static bool isAReturn(Instructions aCode);
};

#endif		/* _JCINSTRUCTIONS_H_ */
