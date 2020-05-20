/**************************************************
* File: strUtils.c.
* Desc: Utilities for string parsing.
* Module: AkraLog : JavaComp.
* Rev: 10 juin 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <ctype.h>
#include <string.h>
#include "jvtypes.h"

#ifndef true
#define true	(1L)
#endif
#ifndef false
#define false 	(0L)
#endif


bool isJava(char *aName)
{
    bool result= false;

    if (aName) {
	if (strcmp(aName, "java") == 0) result= true;
     }

    return result;
}

bool isUpperCase(char *aName)
{
    bool result= true;

    if (aName) {
	while (*aName != '\0') {
	    if (!isupper(*aName)) {
		result= false;
		break;
	     }
	    aName++;
	 }
     }

     return result;

}