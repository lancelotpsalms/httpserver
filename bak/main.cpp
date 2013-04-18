#include <stdio.h>
#include <stdlib.h>
#include "luaserver.h"


int main(int argc,char* argv[])
{
	LuaServer *server=new LuaServer();
	int err=server->initServer("8080");
	if(err == -1)
	{
		exit(0);	
	}
	printf("fuck!hello world!\n");
	server->start();
}
