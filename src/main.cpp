#include <stdio.h>
#include <stdlib.h>
#include "axbserver.h"
#include "common.h"
#include "string.h"
#include "glog/logging.h"
int main(int argc,char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	ServerConf conf;
	strcpy(conf.port,"8080");
	conf.maxconn=1024;
	conf.requestBufferSize=1024;
	conf.requestBufferSize=1024;
	AxbServer server;
	server.start(conf);
}
