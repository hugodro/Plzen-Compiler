/**************************************************
* File: jc.cc.
* Desc: Module principal du compilateur de Java.
* Module: AkraLog : JavaKit.
* Rev: 23 avril 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include "compiler.h"
#include "package.h"

extern "C" {
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
}

/* Prototypes of external functions used in this module. */


extern int yydebug;
extern FILE *yyin;


void describe(int, char **);


#define NBR_LEVELS	2

JCCompiler *compiler;		// Tmp: the compiler unit.
static int majorVersion= 0;
static int minorVersion= 0;
static unsigned int nbrLevels= NBR_LEVELS;


/* The Code. */

main(int argc, char **argv)
{
    char sourceFileName[255];

    yydebug= 0;
    yyin= stdin;

    if (argc >1 ) {
	strcpy(sourceFileName, argv[argc-1]);
	if (argc > 2) {
	    yydebug= atoi(argv[argc-2]);
	    if ((yydebug != 0) && (yydebug != 1)) yydebug= 0;
	 }
     }
    else {
	describe(argc, argv);
	exit(0);
     }

    compiler= new JCCompiler;
    if (compiler->boot(argc-1, argv)) {
	compiler->compileFile(sourceFileName);
    }
}


void describe(int argc, char **argv)
{
    cout  << "AkraLog's Plzen compiler, version " << majorVersion << "." << minorVersion << ".\n";
    cout << "Levels available: ";
    for (unsigned int i= 0; i <= nbrLevels; i++) {
	cout << i;
	if (i < nbrLevels) {
	    cout << ", ";
	}
	else {
	    cout << ".\n";
	}
    }
    cout  << "Usage: <options> <class-file>.\n";
    cout << "Options: none.\n";

}


#if defined(_WIN32)	    // MODNT-971218.
#include <iostream.h>
void FakeWinNT1(void)
{
    ostream *gaga;
    gaga->fail();
}

void FakeWinNT2(void)
{
    strncmp(NULL, NULL, 0);
}
#endif
