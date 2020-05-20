#ifndef _ATTRIBUTES_H_
#define _ATTRIBUTES_H_
/**************************************************
* File: attributes.h.
* Desc: Definition of the JCOutAttributes classes.
* Module: AkraLog : JavaKit.
* Rev: 26 novembre 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>

class JCOutClassFile;
class JCSubExceptAttr;
class JCSubLineNbrAttr;
class JCSubLocalVarAttr;
class JCOutCFConstant;
class JCType;
class AttributesList;
class ConstantsList;
class JCVariableDeclaration;
class JCReferencedType;
class JCCodeBuffer;
class VarDbgList;
class HandlerList;
class LineNbrList;
class JCCteNameAndType;
class JCCompilationContext;
class JCTransition;


class JCAbstractAttribute : public AkObject {
  public:
    enum Kind {
	generic= 0, sourceFile, constantValue, code, exceptions,
	lineNumberTable, localVariableTable,		// Within 'Code'.
	handler, lineInfo, localVarInfo			// Subcomponents.
	, stateCode, transitions					// Level 2.
    };

  public:
};


class JCOutAttribute : public JCAbstractAttribute {
  protected:
    unsigned int nameIndex;	// Index to the name stored in 'constant_pool'.

  public:
    virtual unsigned int getSize(void)= 0;		// Size of the attribute, minus the 6 bytes header.
    virtual void writeInto(JCOutClassFile *aClassFile);
};


class JCSrcFileAttr : public JCOutAttribute {
    unsigned int  sourceFileIndex;	// Index to the name of the source file the class was compiled from.

  public:
    virtual unsigned int getSize(void);
};


// Used to indicate the constant numeric value of a field.
class JCConstantAttr : public JCOutAttribute {
  protected:
    unsigned int  constantValueIndex;		// Index in constant_pool of the value.

  public:
    virtual unsigned int getSize(void);
};


/********************************************************
* Class: JCCodeAttr.
* Desc: Manager of the information that is to be saved a 'Code' attribute.
* Class variables:
* Instance variables:
*    - maxStack => [unsigned int] Maximum number of entries that will be put on
*				the operational stack during this method execution.
*    - maxLocals => [unsigned int ] Maximum number of local variables used by the method.
*    - codeBuffer => [JCCodeBuffer *].
*    - handlerTable => [AttributesList *] Exception handlers defined in the method.
*    - attributes => [AttributesList *] Other attributes: LineNumberTable and LocalVariableTable.
* Super-Class: JCOutAttribute.
* Module: JavaKit : Compiler.
********************************************************/

class JCCodeAttr : public JCOutAttribute {
  protected:
    unsigned int maxStack;
    unsigned int maxLocals;
    JCCodeBuffer *codeBuffer;
    HandlerList *handlerTable;
    AttributesList *attributes;

  public:
    JCCodeAttr(JCOutClassFile *outputContext);
    virtual ~JCCodeAttr(void);
    virtual void generateCode(JCOutClassFile *classFile);
    virtual void prepareSpitting(JCCompilationContext *codeContext);
    virtual void doMainJob(JCCompilationContext *codeContext);
    virtual void endSpitting(JCCompilationContext *codeContext);
    virtual void saveCode(JCCompilationContext *codeContext);
    virtual void makeAttributes(JCCompilationContext *codeContext);
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual unsigned int getSize(void);
};


/********************************************************
* Class: JCHandlerAttr.
* Desc: Contains the information about an exception handler present
*	in the byte-code of a method, for the 'Code' attribute.
* Class variables:
* Instance variables:
*    - startPC => [unsigned int ] Start of J-Code where the exception handler
*		is active (offset, inclusive).
*    - endPC => [unsigned int ] End of J-Code where the exception handler
*		is active (offset, exclusive).
*    - handlerPC => [unsigned int ] Start address of the J-Code (offset).
*    - catchType => [unsigned int ] Index in constant_pool of the class of exception
*		to be caught (if zero, catch any).
* Super-Class: JCAbstractAttribute.
* Module: JavaKit : Compiler.
********************************************************/

class JCHandlerAttr : public JCAbstractAttribute {
  public:
    static unsigned int getInstanceSize(void);

  protected:
    unsigned int startPC;
    unsigned int endPC;
    unsigned int handlerPC;
    unsigned int catchType;

  public:
    virtual void writeInto(JCOutClassFile *aClassFile);
};


/********************************************************
* Class: JCExceptionAttr.
* Desc: Manages the information that is to be spit in a 'Exception' attribute,
*	which is the list of exceptions that can be thrown as the result of running
*	a method (the 'throws <...>' section of a method declaration).
* Class variables:
* Instance variables:
* Super-Class: JCOutAttribute.
* Module: JavaKit : Compiler.
********************************************************/

class JCExceptionAttr : public JCOutAttribute {
  protected:
    unsigned int count;
    unsigned int *exceptionTable;

  public:
    JCExceptionAttr(JCReferencedType *typeListHead);
    virtual ~JCExceptionAttr(void);
    virtual unsigned int getCount(void);
    virtual unsigned int getSize(void);
};


/********************************************************
* Class: JCLocalVarAttr.
* Desc: Manages the list of local variable descriptions for the 'LocalVariableTable'
*	attribute of the 'Code' attribute.
* Class variables:
* Instance variables:
* Super-Class: JCOutAttribute.
* Module: JavaKit : Compiler.
********************************************************/

class JCLocalVarAttr : public JCOutAttribute {
  protected:
    VarDbgList *table;

  public:
    JCLocalVarAttr(JCVariableDeclaration *varHead, unsigned int nbrVars);
    virtual ~JCLocalVarAttr(void);
    virtual void addDeclarations(JCVariableDeclaration *varHead);
    virtual unsigned int getCount(void);
    virtual unsigned int getSize(void);
};


/********************************************************
* Class: JCLineNbrAttr.
* Desc: Manages the list of line to code equivalence for the 'LineNumberTable'
*	attribute of the 'Code' attribute.
* Class variables:
* Instance variables:
* Super-Class: JCOutAttribute.
* Module: JavaKit : Compiler.
********************************************************/

class JCLineNbrAttr : public JCOutAttribute {
  protected:
    LineNbrList *table;

  public:
    JCLineNbrAttr(void);
    virtual ~JCLineNbrAttr(void);
    virtual unsigned int getCount(void);
    virtual unsigned int getSize(void);
};


/********************************************************
* Class: JCSubLineNbrAttr.
* Desc: Contains the mapping between a line of source code and the
*	byte code that corresponds to it, for the 'LineNumberTable' attribute.
* Class variables:
* Instance variables:
* Super-Class: JCAbstractAttribute.
* Module: JavaKit : Compiler.
********************************************************/

class JCSubLineNbrAttr : public JCAbstractAttribute {
  public:
    static unsigned int getInstanceSize(void);

  protected:
    unsigned int startPC;			// Address in J-Code where the line number "begins" (offset).
    unsigned int lineNumber;		// Line number in the source code file.

  public:
    JCSubLineNbrAttr(void);
};


/********************************************************
* Class: JCSubLocalVarAttr.
* Desc: Contains the mapping between a local variable of source code and the
*	byte code where it is used, for the 'LocalVariableTable' attribute.
* Class variables:
* Instance variables:
* Super-Class: JCAbstractAttribute.
* Module: JavaKit : Compiler.
********************************************************/

class JCSubLocalVarAttr : public JCAbstractAttribute {
  public:
    static unsigned int getInstanceSize(void);

  protected:
    unsigned int startPC;			// Beginning of life of local variable (offset).
    unsigned int length;			// Length of life of local variable.
    JCCteNameAndType *varShadow;	// Variable name and signature in constant pool.
    unsigned int slot;			// Index of the local variable in the method's frame table of local variables.

  public:
    JCSubLocalVarAttr(JCVariableDeclaration *varDecl);
};


#if defined(PLZEN_LEVEL_2)


/********************************************************
* Class: JCStateCodeAttr.
* Desc: Manager of the information that is to be saved a 'Code' attribute, for a State.
* Class variables:
* Instance variables:
* Super-Class: JCCodeAttr.
* Module: JavaKit : Compiler.
********************************************************/

class JCStateCodeAttr : public JCCodeAttr {
  public:
    JCStateCodeAttr(JCOutClassFile *aClassFile);
    virtual void endSpitting(JCCompilationContext *codeContext);
    virtual void makeAttributes(JCCompilationContext *codeContext);
};


/********************************************************
* Class: JCTransitionAttr.
* Desc: Contains the information for a state transition definition.
*	in the byte-code of a method, for the 'Code' attribute.
* Class variables:
* Instance variables:
*    - startPC => [unsigned int ] Start of J-Code where the next state parameters can be loaded.
*    - eventFlag => [unsigned int] indicates if 'eventDef' denotes constant pool (0) or local var index (1), or to branch on default (2), and if the nextState is a flag (4) or really an index in the constant pool.
*    - eventRef => [unsigned int] Index in constant_pool or of the local var of the event to trigger on.
*    - nextState => [unsigned int] Index in constant_pool of the definition of the state to branch to (if any), or flag to indicate what to trigger on event.
* Super-Class: JCAbstractAttribute.
* Module: JavaKit : Compiler.
********************************************************/

class JCTransitionAttr : public JCOutAttribute {
  public:
    enum Modifiers {
	implicit= 1, blocking= 2, immediate= 4, parallel= 8
       , push= (1 << 4), pop= (2 << 4), rollback= (4 << 4), passby= (8 << 4), consume= (16 << 4)
       , mDefault= (1 << 9), localVar= (0 << 9), field= (2 << 9)
       , mBreak= (4 << 9)
    };

  protected:	// Instance variables.
    unsigned int modifiers;
    unsigned int event;
    unsigned int destination;
    unsigned int startPC;

  public:		// Instance methods.
    JCTransitionAttr(JCTransition *aTransition, JCCompilationContext *codeContext);
    virtual void writeInto(JCOutClassFile *aClassFile);
    virtual unsigned int getSize(void);
};

#endif

#endif		/* _ATTRIBUTES_H_ */
