/**************************************************
* File: compOptions.cc.
* Desc: Implementation of the JCCompOptions.
* Module: AkraLog : JavaKit.
* Rev: 31 mai 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

extern "C" {
#include <stdlib.h>
#if defined(NeXT)
#include <libc.h>
#endif
#if defined(_WIN32)
#include <stdlib.h>
#include <direct.h>
#endif

// MOD-970507 [JST]: pour getcwd:
#if defined(__linux__)
#include <unistd.h>
#endif

#include <string.h>
 }

#include <iostream.h>

#include <classfile/filePath.h>

#include "runtimeDefs.h"
#include "compOptions.h"


/**************************************************
* Implementation: JCCompOptions.
**************************************************/

JCCompOptions::JCCompOptions(void)
{
    compiledPath= new PathList();
    sourcePath= new PathList();
}


// Scan the command line and set options accordingly.
int JCCompOptions::scanCommands(char **arguments, unsigned int nbrArgs)
{
    int result= 0;		// result == 1001 if we must end program.
    unsigned int i, j, k;
    char *tmpClassName[256];		// Can load up to 256 classes.
    char *tmpArgVal[256];			// Can specify up to 256 arguments.

    for (j= 1, i= 1; i < nbrArgs;) {
      if (arguments[i][0] == '-') {
	switch(arguments[i][j]) {
	   case 'h':    /* Give program documentation. */
	       i= nbrArgs-1; j++;
	       Document(arguments[0]);
	       result= 1001;
	      break;
	    case 'v':    /* Mode VERBOSE. */
		j++;
		verbose= true;
		break;
	   case 't':    /* Test mode. */
		i++;
		testMode= true;
		j= 1;
		break;
	   case 'd':    /* Give the debug level to run at. */
	       i++; j= 1;
	       if (i < nbrArgs) {
		    k= atoi(arguments[i++]);
		    if (k < 32) {
			debugSections|= (1 << (k-1));
		     }
		}
	      else {
		    cout << "option -d: no debugging section was specified.\n";
	      	}
	      break;
	   case 'D':    /* Give the description level to use when debugging or testing. */
	       i++; j= 1;
	       if (i < nbrArgs) {
		    k= atoi(arguments[i++]);
		    if (k < 32) {
			descSections|= (1 << (k-1));
		     }
		}
	      else {
		    cout << "option -D: no description level was specified.\n";
	      	}
	      break;
	   case 'C':    /* Give the description level to use when debugging or testing. */
	       i++; j= 1;
	       if (i < nbrArgs) {
		    k= atoi(arguments[i++]);
		    if (k < 32) {
			classDbgSection|= (1 << (k-1));
		     }
		}
	      else {
		    cout << "option -D: no description level was specified.\n";
	      	}
	      break;
	   default:
	      /* Unknown option ! */
		cout << "Unknown option [" << arguments[i] << "].\n";
		j++;
		result= -1;
		break;
	 }
        if (i < nbrArgs) {
	    if (!arguments[i][j]) {
		i++;
		j= 1;
	     }
	 }
       }	// End of the scan of a '-' something.
      else {	// We got something else than an option spec.
	    // For now, assume that it is a class to load.
	tmpClassName[nbrClassesToCompile]= new char[strlen(arguments[i]) +1];
	strcpy(tmpClassName[nbrClassesToCompile], arguments[i]);
	nbrClassesToCompile++;
	j= 1; i++;
       }
    }	/* Fin du for nbrArgs. */


    if (nbrClassesToCompile > 0) {
	classToCompile= new char*[nbrClassesToCompile];
	for (i= 0; i < nbrClassesToCompile; i++) {
	    classToCompile[i]= tmpClassName[i];
	 }
     }
    return 0;
}


// Set the options to their default values.
void JCCompOptions::setDefaultOptions(void)
{
    char currentPath[1024], *envPath, fileSeparator[2]= { FILE_SEPARATOR, '\0' };

    
    envPath = getenv( CLASSPATH );
    if ( envPath != NULL ) { // parse colon separated list
      char destroyEnv[1024];
      char *tok;
      char pathSeparator[2]= { PATH_SEPARATOR, '\0' };

      strncpy( destroyEnv, envPath, 1023 );
      destroyEnv[1023] = '\0';
      tok = strtok( destroyEnv, pathSeparator );
      while ( tok != NULL ) {
	strcpy( currentPath, "file:" ); // reuse currentPath
	strcat( currentPath, tok );
	strcat( currentPath, fileSeparator );
	compiledPath->addPath( currentPath );
	tok = strtok( NULL, pathSeparator );
      }
    }

    strcpy(currentPath, "file:");

#ifdef NeXT
    getwd(currentPath+5);
#else
    getcwd(currentPath+5, 1024 - 5);
#endif
    strcat(currentPath, fileSeparator);

    compiledPath->addPath(currentPath);

    verbose= false;
    testMode= false;
    descSections= 0;
    debugSections= 0;
    classDbgSection= 0;
    nbrClassesToCompile= 0;
}

// Set option 'name' to its default value.
void JCCompOptions::setDefaultOptions(char *name)
{
// TODO.
}


// Set option 'name' to the value 'value'.
int JCCompOptions::setOption(char *name, void *value)
{
// TODO.
    return 0;
}


// Get value of option 'name'.
void * JCCompOptions::getOption(char *name)
{
    switch (*name) {
	case 'v': return (void *)verbose;
	case 't': return (void *)testMode;
	case 'd': return (void *)debugSections;
	case 'D': return (void *)descSections;
	case 'C': return (void *)classDbgSection;
	default: break;
     }
    return 0;
}


PathList *JCCompOptions::getCompiledPath()
{
    return compiledPath;
}


PathList *JCCompOptions::getSourcePath()
{
    return sourcePath;
}


unsigned int JCCompOptions::classes(char ***dest)
{
    if (nbrClassesToCompile > 0) *dest= classToCompile;
    return nbrClassesToCompile;
}


void JCCompOptions::Document(char *progName)
{
    cout << "Program: " << progName << " [options] <classNames>\n";
    cout << "Options are:\n";
    cout << "-h: give this documentation only.\n";
    cout << "-v: turn on verbose mode.\n";
    cout << "-t: do a test run.\n";
    cout << "-d <n>: turn on debugging section <n>.\n";
    cout << "-D <n>: give description on component <n> when loading a class.\n";
    cout << "-C <n>: turn on class debugging section <n>.\n";
    cout << "-g puts run-time debugging information in compiled file.\n";
}


