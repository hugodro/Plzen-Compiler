/**************************************************
* File: sourceFile.h.
* Desc: Contains the definition input files management.
* Module: AkraLog : JavaComp.
* Rev: 10 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <string.h>
#if defined(NeXT) || defined(__APPLE__)    /* MOD-MSC: sys/malloc.h n'existe pas chez VC++. */
#include <sys/types.h>
#include <sys/malloc.h>
#else
#include <malloc.h>
#endif
#include "sourceFile.h"


SourceFile::SourceFile(char *aFile)
{
    fileStream= fopen(aFile, "r");		// Tmp: We use FILE * instead of ifstream.
    if (fileStream != NULL) {
/* MOD-MSC: remplace le malloc par un new char[].
	filePath= (char *)malloc(strlen(aFile)+1);
*/
	filePath= new char[strlen(aFile)+1];
	strcpy(filePath, aFile);
	lineNumber= 1;
     }
}


FILE *SourceFile::getFIO(void)
{
    return fileStream;
}


