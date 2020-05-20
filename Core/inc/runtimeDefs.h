#ifndef _RUNTIMEDEFS_H_
#define _RUNTIMEDEFS_H_
/**************************************************
* File: runtimeDefs.h.
* Desc: Definition of the plate-form dependant values.
* Module: AkraLog : JavaKit.
* Rev: 31 mai 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#if defined(NeXT) || defined(__APPLE__)
#define PATH_SEPARATOR	':'
#define FILE_SEPARATOR		'/'
#define CLASS_EXTENSION	".class"
#define GLASS_EXTENSION	".glass"
#define JAVA_EXTENSION		".java"
#define PLZEN_EXTENSION	".plzn"
#elif defined(_WIN32)
#define PATH_SEPARATOR	';'
#define FILE_SEPARATOR		'\\'
#define CLASS_EXTENSION	".class"
#define GLASS_EXTENSION	".glass"
#define JAVA_EXTENSION		".java"
#define PLZEN_EXTENSION	".plzn"
#elif defined(SYSV) || defined(__linux__)
#define PATH_SEPARATOR	':'
#define FILE_SEPARATOR		'/'
#define CLASS_EXTENSION	".class"
#define GLASS_EXTENSION	".glass"
#define JAVA_EXTENSION		".java"
#define PLZEN_EXTENSION	".plzn"
#elif defined(MSDOS)
#define PATH_SEPARATOR	';'
#define FILE_SEPARATOR		'\\'
#define CLASS_EXTENSION	".class"
#define GLASS_EXTENSION	".glass"
#define JAVA_EXTENSION		".java"
#define PLZEN_EXTENSION	".plzn"
#endif

#define PLZEN_HOME		"PLZENHOME"
#define JAVA_HOME		"JAVAHOME"
#define CLASSPATH		"CLASSPATH"
#define DYNLIBPATH		"DYNLIBPATH"

#endif		/* _RUNTIMEDEFS_H_ */
