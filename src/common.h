#ifndef _COMMON_H_
#define _COMMON_H_
#include "glog/logging.h"
class ReuseAble{
	public:
		virtual void reuse()=0;
};
#define DECLARE_SINGLETON_CLASS( type ) \
	friend class Singleton< type >;
template <typename T>
class Singleton
{
	public:
		Singleton()
		{
		}

		virtual ~Singleton()
		{
		}

		static T* getInstance()
		{
			static T instance;
			return &instance;
		}
};
struct ServerConf{
	char port[10];
	int maxconn;	
	int requestBufferSize;
	int responseBufferSize;
};
struct ServerContext{
	ServerConf * conf;
};
#endif
