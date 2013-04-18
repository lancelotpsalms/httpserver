#include <stdio.h>
#include <stdlib.h>
#include "axbserver.h"
#include "common.h"
#include "string.h"
int main(int argc,char* argv[])
{
	ServerConf conf;
	strcpy(conf.port,"8080");
	conf.maxconn=1024;
	conf.requestBufferSize=1024;
	conf.requestBufferSize=1024;
	AxbServer server;
	server.start(conf);
}
