/**************************************************
* File: classSource.cc.
* Desc: Defintion of the imported Java classes sources.
* Module: JavaKit : Compiler.
* Rev: 24 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <iostream.h>
#include <stdlib.h>	    /* MOD-MSC: Ajoute pour les fonctions strlen, memcpy, etc.*/
#include <string.h>    	    /* MOD-MSC: Ajoute pour les fonctions strlen, memcpy, etc.*/
#include <fstream.h>
#include "compiler.h"
#include "importClass.h"
#include "classSource.h"


/**************************************************
* Implementation: JCClassSource.
**************************************************/


/**************************************************
* Implementation: JCFileSource.
**************************************************/

JCFileSource::JCFileSource(char *aPath)
{
    unsigned int tmpLength;

    tmpLength= strlen(aPath);
    fullFilePath= new char[tmpLength+1];
    strcpy(fullFilePath, aPath);
}


JCFileSource::~JCFileSource(void)
{
    delete[] fullFilePath;
}


JCImportClassFile *JCFileSource::load(JCCompiler *manager)
{
    ifstream *fileStream= NULL;
    JCImportClassFile *result;

	// Create the stream, create a new JCImportClassFile, and read the stream into it.
#if defined(_WIN32)
    fileStream= new ifstream(fullFilePath, ios::in | ios::binary);
#else
    fileStream= new ifstream(fullFilePath, ios::in);
#endif

    if (fileStream->good()) {
	result= new JCImportClassFile();
	if (result->readFromStream(fileStream)) {
	    // ATTN: Got the class.  Anything to do with it ?
	}
	else {
	    delete result;
	    result= NULL;
	}
    }
    return result;
}
