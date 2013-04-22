//****************************************************
//         Author: Axb - uaxb@hotmail.com
//  Create Time: 2013-02-19 13:25
//       Filename: looper.cpp
//    Description: 
//****************************************************
#include <unistd.h>
#include <sys/wait.h>
#include "looper.h"
#include "serverconf.h"
#include "epollpoller.h"
#include "typedef.h"
int Looper::loop()
{
	for(int i=0;i<2;i++)
	{
	//	if(fork()>0)
	//		continue;
		//主循环
		poller->start();
		int n;
		for(;;)
		{
			n=poller->poll();
			//for(int i=0;i<n;i++)
			//{
			//	Event *event=poller->nextEvent();
				while(poller->handleEvent());
			//	poller->releaseEvent(event);
			//}
		}
	}

	poller->stop();
	int status;
	while(1)
		wait(&status);
}

int Looper::init(ServerConf &conf)
{
	this->poller=new EPollPoller();
	poller->init(conf);
}
