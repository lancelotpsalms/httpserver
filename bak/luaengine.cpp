#include "luaengine.h"
#include "luascript.h"
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define MAX_BUF 1024
LuaEngine* LuaEngine::instance=NULL;
LuaEngine* LuaEngine::getInstance()
{
	if(instance == NULL)
		instance=new LuaEngine();
	return instance;
}

LuaScript* LuaEngine::loadScript(char *filePath)
{
	int fd=open(filePath,O_RDONLY);		
	char buffer[MAX_BUF+1];
	bzero(buffer,MAX_BUF);
	LuaScript *script=new LuaScript();
	while(read(fd,buffer,MAX_BUF)>0)
		script->loadScript(buffer);
	close(fd);
	return script;
}
LuaScript* LuaEngine::createScript()
{
	return NULL;
}
