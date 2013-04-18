#ifndef _LUASCRIPT_
#define _LUASCRIPT_
class lua_State;
class LuaScript
{
public:
	LuaScript();
	int loadScript(char* script);
	int doResponse();
	const char* getResponse();	
private:
	static lua_State *lua;	
};



#endif
