#ifndef _COMPILEROPTIONS_H_
#define _COMPILEROPTIONS_H_
/**************************************************
* File: compOptions.h.
* Desc: Definition of the run-time options.
* Module: AkraLog : JavaKit.
* Rev: 31 mai 1997 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

#include <akra/AkObject.h>

class PathList;

class JCCompOptions : public AkObject {
    PathList *compiledPath;
    PathList *sourcePath;
    bool verbose;
    bool testMode;
    unsigned int debugSections;
    unsigned int descSections;
    unsigned int nbrClassesToCompile;
    char **classToCompile;
    unsigned int classDbgSection;

  public:
    JCCompOptions(void);
    virtual int scanCommands(char **arguments, unsigned int nbrArgs);
    virtual void setDefaultOptions(void);
    virtual void setDefaultOptions(char *name);
    virtual int setOption(char *name, void *value);
    virtual void *getOption(char *name);

    virtual PathList *getCompiledPath();
    virtual PathList *getSourcePath();
    virtual unsigned int classes(char ***dest);

    virtual void Document(char *progName);
 };


#endif	/* _COMPILEROPTIONS_H_ */
