#ifndef _CLASSSOURCE_H_
#define _CLASSSOURCE_H_
/**************************************************
* File: classSource.h.
* Desc: Defintion of the imported Java classes sources.
* Module: JavaKit : Compiler.
* Rev: 24 fevrier 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>

class JCImportClassFile;
class JCCompiler;


class JCClassSource : public AkObject {
  protected:
  public:
    virtual JCImportClassFile *load(JCCompiler *manager)= 0;
};


class JCFileSource : public JCClassSource {
  protected:
    char *fullFilePath;

  public:
    JCFileSource(char *aPath);
    virtual ~JCFileSource(void);
    virtual JCImportClassFile *load(JCCompiler *manager);
};


#endif		/* _CLASSSOURCE_H_ */
