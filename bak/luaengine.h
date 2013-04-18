#ifndef _LUAENGINE_
#define _LUAENGINE_
#include <stdlib.h>
class LuaScript;
class LuaEngine
{
public:
	static	LuaEngine* getInstance();	
	LuaScript* loadScript(char *filePath);
	LuaScript* createScript();
protected:
	static LuaEngine *instance;
};
#endif
