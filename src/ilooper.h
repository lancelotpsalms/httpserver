#ifndef _ILOOPER_H_
#define _ILOOPER_H_
#include "common.h"
struct ServerConf;
class ILooper{
	public:
		int loop();
		int init(ServerConf &conf);
		
}

#endif
