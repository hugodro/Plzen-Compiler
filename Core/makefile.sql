#/************************************************
#* File: makefile.
#* Desc: Building definitions for the Java Compiler.

VPATH= ..
AKRAHOME= /Users/hugo/AkraLog/Projets

SRCS= jc.cc extGram.cc extGram.ycc extTokens.l extTokens.c lexhelp.c \
	package.cc typing.cc variables.cc identifiers.cc \
	actions.cc expressions.cc compileObjects.cc \
	compiler.cc sourceFile.cc strUtils.c \
	nameSpace.cc lists.cc \
	outClassFile.cc outConstant.cc attributes.cc

OBJS= jc.o extGram.o extTokens.o lexhelp.o \
	package.o typing.o variables.o identifiers.o \
	actions.o expressions.o compileObjects.o \
	compiler.o sourceFile.o strUtils.o \
	nameSpace.o lists.o \
	outClassFile.o outConstant.o attributes.o

TESTOBJS= test.o runClass.o

INC= -I$(AKRAHOME) -I..

LIBS= -lg++
CFLAGS= -g -DDEBUG_NS
CC= cc
.SUFFIXES: .cc
all: jc

jc: $(OBJS)
	$(CC)  $(CFLAGS) -o jc $(OBJS) $(LIBS)

testCF: $(TESTOBJS)
	$(CC) $(INC) $(CFLAGS) -o testCF $(TESTOBJS) $(LIBS)

.c.o:
	$(CC) $(INC) $(CFLAGS) -c  $<

.cc.o:
	$(CC) $(INC) $(CFLAGS) -c  $<

extGram.cc: extGram.ycc
	yacc -dv extGram.ycc
	mv y.tab.c $(VPATH)/extGram.cc
	mv y.tab.h $(VPATH)

extTokens.c: extTokens.l
	lex extTokens.l
	mv lex.yy.c $(VPATH)/extTokens.c

extTokens.cc: extTokens.lcc
	lex extTokens.lcc
	mv lex.yy.c $(VPATH)/extTokens.cc

