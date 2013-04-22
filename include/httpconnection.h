#ifndef _HTTPCONNECTION_H_
#define _HTTPCONNECTION_H_
#include "request.h"
#include "typedef.h"
enum HttpState{CONNECTING,CONNECTTED,READY_READ,READ,READY_WRITE,WRITE,FINISH};
class HttpConnection{
	public:
		HttpConnection():request(this)
		{
			clientFd=0;
			statusNo=0;
			state=CONNECTING;
		}
		void reuse()
		{
			clientFd=0;
			request.reuse();
		};
		//int handleRequest();
		Request request;
		Response response;
		int clientFd;
		HttpState state;
		void setServerContext(ServerContext *context){this->context=context;request.init();};
		ServerContext *getServerContext(){return context;};
	private:
		ServerContext *context;
		int statusNo;
};
#endif
