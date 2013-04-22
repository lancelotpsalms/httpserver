#ifndef _AXBSERVER_H_
#define _AXBSERVER_H_
struct ServerConf;
class AxbServer{
	public:
		void start(ServerConf &conf);
		void stop();
};
#endif
