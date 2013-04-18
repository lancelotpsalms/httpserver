#ifndef _RESPONSEMANAGER_
#define _RESPONSEMANAGER_
#include <stdio.h>
class Request;

class ResponseManager
{
public:
	int doResponse(Request &request,int socket);
	const char* getMimeType(const char* file);
	int doResponseHeader(Request &request,int clientFP);
};
#endif
