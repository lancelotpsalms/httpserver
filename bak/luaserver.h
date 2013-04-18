#ifndef _LUASERVER_
#define _LUASERVER_
#include <sys/types.h>
#include <sys/epoll.h>
#define MAX_BUF 1024
#define MAX_PATH 1024
class ResponseManager;
class LuaServer
{
public :
	int initServer(char* port);
	void start();
private:
	int makeServerSocket(char* port);
	char* doResponse(int clientSocket);
	int serverSocket;
	ResponseManager *manager;
};
#endif

