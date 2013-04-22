#ifndef _LOOPER_H_
#define _LOOPER_H_
struct ServerConf;
class IPoller;
class Looper{
	public:
		int loop();
		int init(ServerConf &conf);
		void setPoller(IPoller *poller){this->poller=poller;};
	private:
		IPoller *poller;
};
#endif
