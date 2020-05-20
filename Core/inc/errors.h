#ifndef _JCERRORS_H_
#define _JCERRORS_H_
/**************************************************
* File: errors.h.
* Desc: Contains the definition of the Error management classes.
* Module: AkraLog : JavaComp.
* Rev: 7 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>
#include "jvtypes.h"

class JCError : public AkObject {
  protected:		// Instance variables.
    unsigned int lineNbr;

  public:		// Instance methods.
};


class JCSyntaxError : JCError {
  protected:		// Instance variables.
  public:		// Instance methods.
};


class JCSymbolError : JCError {
  protected:		// Instance variables.
  public:		// Instance methods.
};

class JCTypingError : JCError {
  protected:		// Instance variables.
  public:		// Instance methods.
};

class JCInternalError : JCError {
  protected:		// Instance variables.
  public:		// Instance methods.
};


#endif	/* _JCERRORS_H_ */
