#include "responsemanager.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include "request.h"
#include "luaengine.h"
#include "luascript.h"
#define MAX_PATH 2048
#define MAX_BUF 2048
int ResponseManager::doResponse(Request &request,int clientSocket)
{
	
	
	//FILE *clientFP=fdopen(clientSocket,"w");
	char* path;
	char localPath[MAX_PATH+2];
	strcpy(localPath,".");
	strcpy(localPath+1,request.getPath());
//	LuaEngine* engine=LuaEngine::getInstance();
//	LuaScript *script=engine->loadScript(localPath);
//	const char *response=script->getResponse();
	doResponseHeader(request,clientSocket);	
	int fd=open(localPath,O_RDONLY);		
	char buffer[MAX_BUF+1];
	bzero(buffer,MAX_BUF);
	int rv=0;
	while((rv=read(fd,buffer,MAX_BUF))>0)
		write(clientSocket,buffer,rv);
	close(fd);
	//fclose(clientFP);
//	delete(script);	

}
const char* ResponseManager::getMimeType(const char* file)
{
	const char* comp;
	for(comp=file+strlen(file); comp > file;comp--){
		if(comp[0]=='.'){
			comp++;
			if(strcasecmp(comp,"html")==0)return "text/html";
			if(strcasecmp(comp,"gif")==0)return "image/gif";
			if(strcasecmp(comp,"jpg")==0)return "image/jpeg";
			if(strcasecmp(comp,"jpeg")==0)return "image/jpeg";
			if(strcasecmp(comp,"png")==0)return "image/png";
			if(strcasecmp(comp,"css")==0)return "text/css";
			if(strcasecmp(comp,"lua")==0)return "text/html";
			if(strcasecmp(comp,"js")==0)return "text/javascript";
			return "application/octet-stream";
		}
	}
}
int ResponseManager::doResponseHeader(Request &request,int clientFP)
{
	char buffer[MAX_BUF];
	bzero(buffer,MAX_BUF);	
	snprintf(buffer,sizeof(buffer),"HTTP/1.1 200 OK\r\nSerer:AXB\r\nConnection: close\r\nContent-Type:%s; charset=UTF-8\r\n\r\n",getMimeType(request.getPath()));
	write(clientFP,buffer,strlen(buffer));
}
