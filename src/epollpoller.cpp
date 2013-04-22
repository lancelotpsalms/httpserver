//****************************************************
//         Author: Axb - uaxb@hotmail.com
//  Create Time: 2013-02-19 13:28
//       Filename: epollpoller.cpp
//    Description: 
//****************************************************
#include "epollpoller.h"
#include "socketutil.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <queue>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include "httpconnection.h"
#include "slab.h"
#include "typedef.h"
#include "connectionmanager.h"
#include "common.h"
#include "responsebuilderregistry.h"
#define MAX_BUF 1024
int EPollPoller::poll()
{
#ifdef DEBUG
	printf("poll\n");
#endif

	currentIndex=0;	
	eventCount=epoll_wait(epollFd,events,64,-1);
	return eventCount;
}
int EPollPoller::handleEvent()
{
	while(1)
	{
		event->data=&events[currentIndex++];
		epoll_event *epollEvent;	
		epollEvent=(epoll_event *)event->data;
		if(epollEvent->events&EPOLLERR)
		{
			//error
		}
		else if(epollEvent->data.fd == socketFd)
		{
			//handle accept
			//printf("event:%d,count:%d\n",epollEvent->events,eventCount);
			handleAccept(event);
		}
		else
		{
			//handle read or write
			int clientFd=epollEvent->data.fd;
			HttpConnection *conn=connectionManager->get(clientFd);
			event->conn=conn;

			switch(conn->state)
			{
				case READY_READ:handleRead(conn);break;
				case READY_WRITE:handleWrite(conn);break;
				default:
								 printf("unhandled state:%d %d %d\n",conn->state,clientFd,socketFd);break;
			}
		}
		if(eventCount==currentIndex)
			break;
	}
	while(!connQueue.empty())
	{
		HttpConnection *conn=connQueue.front();
		connQueue.pop();
		switch(conn->state)
		{
			case READY_READ:handleRead(conn);break;
			case READY_WRITE:handleWrite(conn);break;
			default: printf("unhandled state:%d %d %d\n",conn->state,conn->clientFd,socketFd);break;
		}
	}
	return 0; 

}
int EPollPoller::stop()
{
	close(socketFd);
}
int EPollPoller::hasNextEvent()
{
	//if(eventCount==currentIndex)
	//	return 0;
	return 0; 
}
int EPollPoller::handleAccept(Event *event)
{
	epoll_event *epollEvent=(epoll_event *)event->data;
	for(;;)
	{
		struct sockaddr in_addr;		
		socklen_t in_len;
		int infd;
		char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
		int s;
		in_len = sizeof in_addr;
		infd = accept (socketFd, &in_addr, &in_len);
		//printf("infd:%d\n",infd);
		if (infd == -1)
		{
			if ((errno == EAGAIN) ||
					(errno == EWOULDBLOCK))
			{
				/* We have processed all incoming
				 *                              connections. */
			//printf("eagain of accept\n");
				break;
			}
			else
			{
				perror ("accept");
				epollEvent->data.fd=socketFd;
				epollEvent->events=EPOLLIN|EPOLLET;
				epoll_ctl(epollFd,EPOLL_CTL_MOD,socketFd,epollEvent);
				break;
			}
		}
		s = getnameinfo (&in_addr, in_len,
				hbuf, sizeof hbuf,
				sbuf, sizeof sbuf,
				NI_NUMERICHOST | NI_NUMERICSERV);
		if (s == 0)
		{
			//printf("Accepted connection on descriptor %d(host=%s, port=%s)\n", infd, hbuf, sbuf);
		}

		/* Make the incoming socket non-blocking and add it to the
		 *                      list of fds to monitor. */
		s = SocketUtil::setNonBlocking(infd);
		if (s == -1)
			abort ();

		epollEvent->data.fd = infd;
		epollEvent->events = EPOLLIN | EPOLLET;
		s = epoll_ctl (epollFd, EPOLL_CTL_ADD, infd, epollEvent);
		if (s == -1)
		{
			perror ("epoll_ctl");
			abort ();
		}
		HttpConnection *conn=connectionManager->create(infd);
		conn->state=READY_READ;
		//	connQueue.push(conn);
		conn->clientFd=infd;
		//	conn->
		conn->setServerContext(NULL);

	}
}
//Event* EPollPoller::nextEvent()
//{
////	event=Slab<Event>::alloc();
//	event->data=&events[currentIndex];
//}
int EPollPoller::init(ServerConf &conf)
{
	int s;
	this->socketFd=SocketUtil::createServerSocket(conf.port);	
	SocketUtil::setNonBlocking(socketFd);
	s = listen (socketFd,conf.maxconn);
	if (s == -1)
	{
		perror ("listen");
		abort ();
	}
	//socklen_t socketSize=sizeof(struct sockaddr_in);
	context.conf=&conf;
	rbr=SResponseBuilderRegistry::getInstance();
}
int EPollPoller::start()
{
	int s;

	epollFd=epoll_create1(0);
	epoll_event epollEvent;
	epollEvent.data.fd=socketFd;
	epollEvent.events=EPOLLIN;
	s=epoll_ctl(epollFd,EPOLL_CTL_ADD,socketFd,&epollEvent);

	event=Slab<Event>::alloc();
	events=(epoll_event *)calloc(64,sizeof(struct epoll_event));
	connectionManager=ConnectionManager::getInstance();
	connectionManager->setServerContext(&context);
}
//int EPollPoller::releaseEvent(Event *event)
//{
//	Slab<Event>::dealloc(event);	
//}
int EPollPoller::handleRead(HttpConnection *conn)
{
	//do read
	printf("handle read\n");
	int numbytes;
	char buffer[MAX_BUF+1];
	bzero(buffer,MAX_BUF);
	int clientSocket=conn->clientFd;
	while((numbytes = recv(clientSocket,buffer,MAX_BUF,0)) >0)
	{
		conn->request.read(buffer,numbytes);
	}
	if(numbytes==0)
	{
		close(clientSocket);
		return 0;
	}
	else if(numbytes==-1)
	{
		//printf("wo cao\n");
	}
	bool receiveFinished=false;
	if(numbytes==0)
	{
		receiveFinished=true;
	}
	else
	{
		if(errno==EAGAIN)
		{
			receiveFinished=true;
			printf("handleRead eagain\n");
	//		epoll_event epollEvent;
	//		epollEvent.data.fd = clientSocket;
	//		epollEvent.events = EPOLLIN | EPOLLET;
	//		int s = epoll_ctl (epollFd, EPOLL_CTL_MOD, clientSocket, &epollEvent);
	//		if (s == -1)
	//		{
	//			perror ("epoll_ctl");
	//			abort ();
	//		}
		}
		else
		{

			perror("recv");
			exit(1);
		}
	}
	//alter status
	if(receiveFinished)
	{
		conn->state=READY_WRITE;
		//try write
		connQueue.push(conn);
	}
	else
	{
	}
}

int EPollPoller::handleWrite(HttpConnection *conn)
{
	//
	int numbytes;
	char buffer[MAX_BUF+1];
	bzero(buffer,MAX_BUF);
//	printf("%d %d\n",connQueue.size(),connectionManager->size());
	int clientSocket=conn->clientFd;
	strcpy(buffer,"test");
	if((numbytes = write(clientSocket,buffer,strlen(buffer))) == -1)
	{
			if(errno==EAGAIN)
			{
				//printf("handleWrite eagain\n");
				epoll_event epollEvent;
				epollEvent.data.fd = clientSocket;
				epollEvent.events = EPOLLOUT | EPOLLET;
				int s = epoll_ctl (epollFd, EPOLL_CTL_MOD, clientSocket, &epollEvent);
				if (s == -1)
				{
					perror ("epoll_ctl");
					abort ();
				}
			}
			else
			{

				perror("write");
				exit(1);
			}
	}
	else
	{
	}
	bool writeFinished=true;
	if(writeFinished)
	{
		conn->state=FINISH;
		connectionManager->release(clientSocket);
		close(clientSocket);
	}
	else
	{
		//add to epoll
	}
}
