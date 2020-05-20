#ifndef _OPTIONS_H_
#define _OPTIONS_H_
/**************************************************
* File: options.h.
* Desc: Definition of the compilation option classes.
* Module: AkraLog : JavaKit.
* Rev: 11 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>

class JCCompileOptions : public AkObject {
  public:
    enum BasicOptions {
	describeLocalVars, describeLineNumbers
	, nbrBasicOptions
    };

};


#endif		/* _OPTIONS_H_ */
