#ifndef _EPOLLPOLLER_H_
#define _EPOLLPOLLER_H_
#include "ipoller.h"
#include "common.h" 
#include <sys/epoll.h>
#include <queue>
struct ServerConf;
class ConnectionManager;
class Event;
class ResponseBuilderRegistry; 
class HttpConnection;
using namespace std;
class EPollPoller:public IPoller{

	public:
		virtual int poll();
		virtual int handleEvent();
		//virtual Event *nextEvent();
		//virtual int releaseEvent(Event *event);
		virtual int init(ServerConf &conf);
		virtual int start();
		virtual int stop();
	private:
		int epollFd;
		int socketFd;
		struct epoll_event *events;
		int currentIndex;
		int handleAccept(Event *event);
		int handleWrite(HttpConnection *conn);
		int handleRead(HttpConnection *conn);
		int hasNextEvent();
		ConnectionManager* connectionManager;
		int count;
		int eventCount;
		Event *event;
		queue<HttpConnection*> connQueue;
		ServerContext context;
		ResponseBuilderRegistry *rbr;
};
#endif

