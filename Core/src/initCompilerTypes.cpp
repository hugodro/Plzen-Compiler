/**************************************************
* File: typing.cc.
* Desc: Typing support related functions.
* Module: AkraLog : JavaKit.
* Rev: 29 avril 1996 : REV 0 : Hugo DesRosiers : Creation.
**************************************************/

void JVType::InitJavaTyping(CompilationInfo *cpInfo)
{
	/* Define 'byte'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("b");
    tmpType->init("byte", tmpSignature);
    cpInfo->typeTable->addType(tmpType);
    
	/* Define 'short'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("s");
    tmpType->init("short", tmpSignature);
    cpInfo->typeTable->addType(tmpType);
    
	/* Define 'int'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("i");
    tmpType->init("int", tmpSignature);
    cpInfo->typeTable->addType(tmpType);

	/* Define 'long'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("l");
    tmpType->init("long", tmpSignature);
    cpInfo->typeTable->addType(tmpType);

	/* Define 'float'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("f");
    tmpType->init("float", tmpSignature);
    cpInfo->typeTable->addType(tmpType);

	/* Define 'double'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("d");
    tmpType->init("double", tmpSignature);
    cpInfo->typeTable->addType(tmpType);

	/* Define 'char'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("c");
    tmpType->init("char", tmpSignature);
    cpInfo->typeTable->addType(tmpType);

	/* Define 'boolean'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("t");
    tmpType->init("boolean", tmpSignature);
    cpInfo->typeTable->addType(tmpType);

	/* Define 'Object'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("o");
    tmpType->init("Object", tmpSignature);
    cpInfo->typeTable->addType(tmpType);

	/* Define 'Array'. */
    tmpType= new JVType;
    tmpSignature= new JVTypeSignature;
    tmpSignature->addBasicMember("a");
    tmpType->init("Array", tmpSignature);
    cpInfo->typeTable->addType(tmpType);
}

