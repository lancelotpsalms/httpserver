#ifndef _REQUEST_
#define _REQUEST_
#include <stdlib.h>
#include <stdio.h>
#include "common.h"
enum RequestMethod{UNKNOWN,GET,POST};
class HttpConnection;
class Request
{
public:
	void reuse();
	inline const char* getRequestHost(){return '\0';};
	inline const char* getFullPath(){return '\0';};
	inline const char* getPath()
	{
		if(path==NULL)
		  printf("a%s\n",path);
		return path;
	};	
	inline const char* getExtension()
	{
		//return extension;
		return "exe";
	}
	Request(){
		bufferPos=0;
		readPos=0;
		header=NULL;
		extension=NULL;
	}
	inline RequestMethod getMethod(){return method;};
	Request(HttpConnection *conn)
	{
		this->conn=conn;
		bufferPos=0;
		readPos=0;
		header=NULL;
	};
	int read(char* requestheader,int len);
	void init();
	virtual ~Request(){
		free(header);
		header=NULL;
	};
private:
	HttpConnection *conn;
	void parsePath(char* req);
	char* header;
	char* host;
	char* fullPath;
	char* path;
	char* refer;
	char* useragent;
	char* extension;
	RequestMethod method;
	int bufferPos;
	int readPos;
};
#endif
