#ifndef _JVTYPES_H_
#define _JVTYPES_H_

#if !defined(_WIN32) && !defined(__linux__) && !defined(__GNUC__)
typedef unsigned char bool;
#endif
typedef unsigned short wchar;

#ifndef NULL
#define NULL		(0L)
#endif

typedef unsigned int javaU4;
typedef unsigned short javaU2;
typedef unsigned char javaU1;

#endif	/* _JVTYPES_H_ */
