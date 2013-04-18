#include "luascript.h"
#include "include/lua.hpp"
lua_State* LuaScript::lua=NULL;
LuaScript::LuaScript()
{
	if(lua!=NULL)
	{
		lua_close(lua);
	}
	lua=luaL_newstate();
	luaL_openlibs(lua);
	
}
int LuaScript::loadScript(char* script)
{
	luaL_dostring(lua,script);	
	return 0;
}
int LuaScript::doResponse()
{
	return 0;
}
const char* LuaScript::getResponse()
{
	lua_getglobal(lua,"response");
	return lua_tostring(lua,-1);
//	return "a";
}
