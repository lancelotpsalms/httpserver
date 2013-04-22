#include "axbserver.h"
#include "serverconf.h"
#include <stdio.h>
#include "looper.h"
#include "typedef.h"
void AxbServer::start(ServerConf &conf)
{
	//ResponseBuilderRegistry *rbr=ResponseBuilderRegistry::getInstance();
///	ResponseBuilderChain chain;
//	rbr->registerBuilder(&chain,"exe");
	Looper looper;
	looper.init(conf);
	looper.loop();
}

void AxbServer::stop()
{
}
