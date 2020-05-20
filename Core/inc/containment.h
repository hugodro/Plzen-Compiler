#ifndef _CONTAINMENT_H_
#define _CONTAINMENT_H_
/**************************************************
* File: containment.h.
* Desc: Contains the definition of the JCContainer class.
* Module: Plzen : Compiler.
* Rev: 21 octobre 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>


class JCContainer : public AkObject {
  public:
    enum ContType {
	action, expression
    };

  public:
    JCContainer(void);
    virtual unsigned int getContainerType(void)= 0;
    virtual unsigned int getStartLine(void)= 0;
    virtual unsigned int getEndLine(void)= 0;
};


#endif		/* _CONTAINMENT_H_ */
