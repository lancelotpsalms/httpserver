#ifndef _IPOLLER_H_
#define _IPOLLER_H_
class Event;
struct ServerConf;
class IPoller{

	public:
		virtual int poll()=0;
		virtual int handleEvent()=0;
//		virtual Event *nextEvent()=0;
//		virtual int releaseEvent(Event *event)=0;
		virtual int init(ServerConf &conf)=0;
		virtual int start()=0;
		virtual int stop()=0;
};

#endif
