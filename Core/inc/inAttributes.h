#ifndef _INATTRIBUTES_H_
#define _INATTRIBUTES_H_
/**************************************************
* File: inAttributes.h.
* Desc: Definition of the JCAttributeInfo classes.
* Module: AkraLog : JavaKit.
* Rev: 26 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include "attributes.h"
#include "jvtypes.h"

class istream;
class JCCFConstant;


class JCAttributeInfo : public JCAbstractAttribute {
  public:
    virtual bool read(istream *aStream, JCCFConstant **ctePool, JCAttributeInfo * &readAttribute);
};

#endif		/* _INATTRIBUTES_H_ */
