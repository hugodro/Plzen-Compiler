#ifndef _SOURCEFILE_H_
#define _SOURCEFILE_H_
/**************************************************
* File: sourceFile.h.
* Desc: Contains the definition input files management.
* Module: AkraLog : JavaComp.
* Rev: 10 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <fstream.h>
#include <iostream.h>
#include <akra/AkObject.h>
#include "jvtypes.h"
extern "C" {
#include <stdio.h>
}


class SourceFile : public AkObject {
  protected:
    char *filePath;
    unsigned int lineNumber;
    FILE *fileStream;	// ATTN: To be changed for ifstream.

  public:
    SourceFile(char *aFile);
    FILE *getFIO(void);
 };


#endif	/* _SOURCEFILE_H_ */
