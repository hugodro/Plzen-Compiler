/**************************************************
* File: instructions.cc.
* Desc: Contains the Java instructions set and related information.
* Module: AkraLog : JavaComp.
* Rev: 23 decembre 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "constants.h"
#include "instructions.h"


unsigned int JCInstrSet::instructionIDs[256]= {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, 32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
    60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
    130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
    140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
    170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 187, 188, 189,
    190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
    200, 201, 202, 209
#if defined(PLZEN_LEVEL_2)
  , 255, 254, 253, 252
#endif
 };

// DEBUG:
const char *const JCInstrSet::instructionNames[256]= {
	"nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1",
	"iconst_2", "iconst_3", "iconst_4", "iconst_5", "lconst_0",
	"lconst_1", "fconst_0", "fconst_1", "fconst_2", "dconst_0",
	"dconst_1", "bipush", "sipush", "ldc1", "ldc2",
	"ldc2w", "iload", "lload", "fload", "dload",
	"aload", "iload_0", "iload_1", "iload_2", "iload_3",
	"lload_0", "lload_1", "lload_2", "lload_3", "fload_0",
	"fload_1", "fload_2", "fload_3", "dload_0", "dload_1",
	"dload_2", "dload_3", "aload_0", "aload_1", "aload_2",
	"aload_3", "iaload", "laload", "faload", "daload",
	"aaload", "baload", "caload", "saload", "istore",
	"lstore", "fstore", "dstore", "astore", "istore_0",
	"istore_1", "istore_2", "istore_3", "lstore_0", "lstore_1",
	"lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2",
	"fstore_3", "dstore_0", "dstore_1", "dstore_2", "dstore_3",
	"astore_0", "astore_1", "astore_2", "astore_3", "iastore",
	"lastore", "fastore", "dastore", "aastore", "bastore",
	"castore", "sastore", "pop", "pop2", "dup",
	"dup_x1", "dup_x2", "dup2", "dup2_x1", "dup2_x2",
	"swap", "iadd", "ladd", "fadd", "dadd",
	"isub", "lsub", "fsub", "dsub", "imul",
	"lmul", "fmul", "dmul", "idiv", "ldiv",
	"fdiv", "ddiv", "irem", "lrem", "frem",
	"drem", "ineg", "lneg", "fneg", "dneg",
	"ishl", "lshl", "ishr", "lshr", "iushr",
	"lushr", "iand", "land", "ior", "lor",
	"ixor", "lxor", "iinc", "i2l", "i2f",
	"i2d", "l2i", "l2f", "l2d", "f2i",
	"f2l", "f2d", "d2i", "d2l", "d2f",
	"int2byte", "int2char", "int2short", "lcmp", "fcmpl",
	"fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne",
	"iflt", "ifge", "ifgt", "ifle", "if_icmpeq",
	"if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple",
	"if_acmpeq", "if_acmpne", "goto_n", "jsr", "ret",
	"tableswitch", "lookupswitch", "ireturn", "lreturn", "freturn",
	"dreturn", "areturn", "vreturn", "getstatic", "putstatic",
	"getfield", "putfield", "invokevirtual", "invokenonvirtual", "invokestatic",
	"invokeinterface", "anew", "newarray", "anewarray", "arraylength",
	"athrow", "checkcast", "instanceof", "monitorenter", "monitorexit",
	"wide", "multianewarray", "ifnull", "ifnonnull", "goto_w",
	"jsr_w", "breakpoint", "ret_w"
#if defined(PLZEN_LEVEL_2)
       , "fire", "firestatic", "firefield", "wait"
#endif
 };


JCInstrSet::OpcodeArgType JCInstrSet::argumentType[256]= {
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, argByte, argShort, argByte, argShort,
	argShort, argByte, argByte, argByte, argByte,
	argByte, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, argByte,
	argByte, argByte, argByte, argByte, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, argShort, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, noArg, noArg,
	noArg, noArg, noArg, argShort, argShort,
	argShort, argShort, argShort, argShort, argShort,
	argShort, argShort, argShort, argShort, argShort,
	argShort, argShort, argShort, argShort, argByte,
	argVarSize, argVarSize, noArg, noArg, noArg,
	noArg, noArg, noArg, argShort, argShort,
	argShort, argShort, argShort, argShort, argShort,
	argInteger, argShort, argByte, argShort, noArg,
	noArg, argShort, argShort, noArg, noArg,
	argByte, arg3Bytes, argShort, argShort, argInteger,
	argInteger, noArg, argShort
#if defined(PLZEN_LEVEL_2)
      , argShort, argShort, argShort, argShort
#endif
 };

unsigned char JCInstrSet::instructionSize[256]= {
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 3, 2, 3, 3,
	2, 2, 2, 2, 2,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2,
	1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1,
	3, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 3, 3,
	3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3,
	3, 2,
	16, 12,		// Minimum size !
	1, 1, 1, 1, 1, 1,
	3, 3, 3, 3, 3, 3, 3,
	5, 3, 2, 3, 1, 1, 3,
	3, 1, 1, 2, 4, 3, 3, 5,
	5, 1, 3
#if defined(PLZEN_LEVEL_2)
      , 3, 3, 3, 3
#endif
 };


char JCInstrSet::stackUse[256]= {
	0, 1, 1, 1, 1,
	1, 1, 1, 1, 2,
	2, 1, 1, 1, 2,
	2, 1, 1, 1, 1,
	2, 1, 2, 1, 2,
	1, 1, 1, 1, 1,
	2, 2, 2, 2, 1,
	1, 1, 1, 2, 2,
	2, 2, 1, 1, 1,
	1, 1, 2, 1, 2,
	1, 1, 1, 1, -1,
	-2, -1, -2, -1, -1,
	-1, -1, -1, -2, -2,
	-2, -2, -1, -1, -1,
	-1, -2, -2, -2, -2,
	-1, -1, -1, -1, -1,
	-2, -1, -2, -1, -1,
	-1, -1, -1, -2, 1,
	1, 1, 2, 2, 2,
	0, -1, -2, -1, -2,
	-1, -2, -1, -2, -1,
	-2, -1, -2, -1, -2,
	-1, -2, -1, -2, -1,
	-2, 0, 0, 0, 0,
	-1, -2, -1, -2, -1,
	-2, -1, -2, -1, -2,
	-1, -2, 0, 1, 0,
	2, -1, -1, 0, 0,
	1, 1, -1, 0, -1,
	0, 0, 0, -3, -1,
	-1, -3, -3, -1, -1,
	-1, -1, -1, -1, -2,
	-2, -2, -2, -2, -2,
	-2, -2, 0, 1, 0,
	-1, -1, -1, -2, -1,
	-2, -1, 0, -1, 1,
	-1, 1, -1, -1, 0,
	-1, 1, 0, 0, 0,
	0, 0, 0, -1, -1,
	0, 1, -1, -1, 0,
	1, 0, 0
#if defined(PLZEN_LEVEL_2)
      , -1, -1, -1, 0
#endif
};


/**************************************************
* Implementation: JCInstrSet.
**************************************************/

JCInstrSet::Instructions JCInstrSet::getOptimizedVersion(Instructions aCode, unsigned int anIndex) {
    unsigned int codeIndex;
    static Instructions optVersions[4][10]= {
	{ iload_0, fload_0, lload_0, dload_0, aload_0,
		istore_0, fstore_0, lstore_0, dstore_0, astore_0 },
	{ iload_1, fload_1, lload_1, dload_1, aload_1,
		istore_1, fstore_1, lstore_1, dstore_1, astore_1 },
	{ iload_2, fload_2, lload_2, dload_2, aload_2,
		istore_2, fstore_2, lstore_2, dstore_2, astore_2 },
	{ iload_3, fload_3, lload_3, dload_3, aload_3,
		istore_3, fstore_3, lstore_3, dstore_3, astore_3 }
    };

    if (anIndex > 3) return nop;		// Warning: quick exit.
    if (aCode == iload) codeIndex= 0;
    else if (aCode == fload) codeIndex= 1;
    else if (aCode == lload) codeIndex= 2;
    else if (aCode == dload) codeIndex= 3;
    else if (aCode == aload) codeIndex= 4;
    else if (aCode == istore) codeIndex= 5;
    else if (aCode == fstore) codeIndex= 6;
    else if (aCode == lstore) codeIndex= 7;
    else if (aCode == dstore) codeIndex= 8;
    else if (aCode == astore) codeIndex= 9;
    else return nop;		// Warning: quick exit.

    return optVersions[anIndex][codeIndex];
};


JCInstrSet::Instructions JCInstrSet::getTypedOp(Instructions aCode, unsigned int aPrimaryType)
{
	// ATTN: For which instructions are the short types ever happening ?
    switch(aPrimaryType) {
	case JVM_TYPE_BOOLEAN:
	    switch(aCode) {
		case vreturn: return ireturn;
		case iaload: return iaload;
		case iastore: return iastore;
		case iload: return iload;
		case istore: return istore;
	    }
	    break;
	case JVM_TYPE_SIGNED_BYTE:
	    switch(aCode) {
		case vreturn: return ireturn;
		case iaload: return baload;
		case iastore: return bastore;
		case iload: return iload;
		case istore: return istore;
	    }
	    break;
	case JVM_TYPE_CHAR:
	    switch(aCode) {
		case vreturn: return ireturn;
		case iaload: return caload;
		case iastore: return castore;
		case iload: return iload;
		case istore: return istore;
	    }
	    break;
	case JVM_TYPE_UNSIGNED_SHORT:
	    switch(aCode) {
		case vreturn: return ireturn;
		case iaload: return saload;
		case iastore: return sastore;
		case iload: return iload;
		case istore: return istore;
	    }
	    break;
	case JVM_TYPE_INTEGER:
	    switch(aCode) {
		case vreturn: return ireturn;
		case iadd: return iadd;
		case isub: return isub;
		case imul: return imul;
		case idiv: return idiv;
		case irem: return irem;
		case ineg: return ineg;
		case iaload: return iaload;
		case iastore: return iastore;
		case iload: return iload;
		case istore: return istore;
	    };
	    break;
	case JVM_TYPE_FLOAT:
	    switch(aCode) {
		case vreturn: return freturn;
		case iadd: return fadd;
		case isub: return fsub;
		case imul: return fmul;
		case idiv: return fdiv;
		case irem: return frem;
		case ineg: return fneg;
		case iaload: return faload;
		case iastore: return fastore;
		case iload: return fload;
		case istore: return fstore;
	    };
	    break;
	case JVM_TYPE_LONG:
	    switch(aCode) {
		case vreturn: return lreturn;
		case iadd: return ladd;
		case isub: return lsub;
		case imul: return lmul;
		case idiv: return ldiv;
		case irem: return lrem;
		case ineg: return lneg;
		case iaload: return laload;
		case iastore: return lastore;
		case iload: return lload;
		case istore: return lstore;
	    };
	    break;
	case JVM_TYPE_DOUBLE:
	    switch(aCode) {
		case vreturn: return dreturn;
		case iadd: return dadd;
		case isub: return dsub;
		case imul: return dmul;
		case idiv: return ddiv;
		case irem: return drem;
		case ineg: return dneg;
		case iaload: return daload;
		case iastore: return dastore;
		case iload: return dload;
		case istore: return dstore;
	    };
	    break;
    }
    return nop;
}

unsigned int JCInstrSet::getSizeOf(Instructions aCode)
{
    return (unsigned int)instructionSize[aCode];
}


int JCInstrSet::getStackUseOf(Instructions aCode)
{
    return (int)stackUse[aCode];
}


const char * const JCInstrSet::getName(Instructions aCode)
{
    return instructionNames[aCode];
}


const unsigned int JCInstrSet::primaryTypeToByteCode(unsigned int aPrimaryType)
 {
    switch(aPrimaryType) {
	case JVM_TYPE_UNSIGNED_SHORT:
	    return 9;
	    break;
	case JVM_TYPE_FLOAT:
	    return 6;
	    break;
	case JVM_TYPE_INTEGER:
	    return 10;
	    break;
	case JVM_TYPE_DOUBLE:
	    return 7;
	    break;
	case JVM_TYPE_LONG:
	    return 11;
	    break;
	case JVM_TYPE_CHAR:
	    return 5;
	    break;
	case JVM_TYPE_SIGNED_BYTE:
	    return 8;
	    break;
	case JVM_TYPE_BOOLEAN:
	    return 4;
	    break;
     }
    return 8;		// Default situation.
 }


bool JCInstrSet::isAReturn(Instructions aCode)
{
    return ((aCode == ireturn) || (aCode == lreturn)
    		|| (aCode == freturn) || (aCode == dreturn)
		|| (aCode == areturn) || (aCode == vreturn));
}


