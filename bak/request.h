#ifndef _REQUEST_
#define _REQUEST_
#include <stdlib.h>
#include "common.h"
enum RequestMethod{UNKNOWN,GET,POST};
class Request:public ReuseAble
{
public:
	virtual void reuse();
	inline char* getRequestHost(){return '\0';};
	inline char* getFullPath(){return '\0';};
	inline char* getPath(){return path;};	
	inline RequestMethod getMethod(){return method;};
	Request(ServerContext *context);
	virtual ~Request(){
		free(header);
	};
private:
	Request();
	ServerContext *context;
	void parsePath(char* req);
	char* header;
	char* host;
	char* fullPath;
	char* path;
	char* refer;
	char* useragent;
	RequestMethod method;
	int bufferPos=0;
	int readPos=0;
};
#endif
