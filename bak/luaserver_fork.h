#include "luaserver.h"
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "luaengine.h"
#include "request.h"
#include "luascript.h"
#include "responsemanager.h"
#define BACKLOG 10
int LuaServer::initServer(int port)
{
	signal(SIGCHLD,SIG_IGN);
	printf("init server...\n");
	serverSocket=makeServerSocket(port);
	manager=new ResponseManager();
	if(serverSocket == -1)
	{
		printf("can't create socket!\n");
		return -1;
	}

	return 0;
}
int LuaServer::makeServerSocket(int port)
{
	struct sockaddr_in serverAddr;
	int tempSockId;
	tempSockId=socket(AF_INET,SOCK_STREAM,0);
	if(tempSockId==-1)
	{
		return -1;
	}
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(port);
	serverAddr.sin_addr.s_addr=inet_addr("192.168.1.147");
	memset(&(serverAddr.sin_zero),'\0',8);
	if(bind(tempSockId,(struct sockaddr *)&serverAddr,sizeof(serverAddr))== -1)
	{
		printf("binding error!\n");
		return -1;
	}
	if(listen(tempSockId,BACKLOG) == -1)
	{
		printf("listen error\n");
		return -1;
	}
	return tempSockId;

}
void LuaServer::start()
{
	struct sockaddr_in userSocket;
	int acceptSocket;
	socklen_t socketSize=sizeof(struct sockaddr_in);
	//main loop
	for(;;)
	{
		acceptSocket=accept(serverSocket,(struct sockaddr *)&userSocket,&socketSize);
		//		printf("got request\n");
		int fr=fork();
		if(fr==0)
		{	

			close(serverSocket);
			doResponse(acceptSocket);
			//shutdown(acceptSocket,SHUT_RDWR);
			close(acceptSocket);
			exit(0);
		}
		else
		{
			close(acceptSocket);
		}
	}
}
char* LuaServer::doResponse(int clientSocket)
{
	int numbytes;
	char buffer[MAX_BUF+1];
	bzero(buffer,MAX_BUF);
	if((numbytes = recv(clientSocket,buffer,MAX_BUF,0)) == -1)
	{
		perror("recv");
		exit(1);
	}
	Request request(buffer,numbytes);
	manager->doResponse(request,clientSocket);
		//const char *response="a";
		//printf("receved message:%s\n",buffer);
}

