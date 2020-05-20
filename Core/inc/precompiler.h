#ifndef _PRECOMP_H_
#define _PRECOMP_H_
/**************************************************
* File: precomp.h.
* Desc: Contains the definitions and constants used by the pre-compiler section.
* Module: AkraLog : JavaKit.
* Rev: 23 avril 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#ifndef TRUE
#define TRUE	(1L)
#endif
#ifndef FALSE
#define FALSE (0L)
#endif

#define MKW_DEFINE		1
#define MKW_ELSE		2
#define MKW_ELIF		3
#define MKW_ENDIF		4
#define MKW_IF			5
#define MKW_IFDEF		6
#define MKW_IFNDEF		7
#define MKW_INCLUDE	8
#define MKW_UNDEF		9

struct PreCompiler {
    struct PreCompilerMacro *macroDefinitions;
 };

struct PreCompilerMacro {
    int gaga;	    /* MOD-MSC: Ajoute parce que VC++ ne prend pas une struct vide. */
 };


#endif	/* _PRECOMP_H_ */
