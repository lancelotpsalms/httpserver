#include "luaserver.h"
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "luaengine.h"
#include "request.h"
#include "luascript.h"
#include "responsemanager.h"
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

#define BACKLOG 10
	static int
make_socket_non_blocking (int sfd)
{
	int flags, s;

	flags = fcntl (sfd, F_GETFL, 0);
	if (flags == -1)
	{
		perror ("fcntl");
		return -1;
	}

	flags |= O_NONBLOCK;
	s = fcntl (sfd, F_SETFL, flags);
	if (s == -1)
	{
		perror ("fcntl");
		return -1;
	}

	return 0;
}
int LuaServer::initServer(char* port)
{
	signal(SIGCHLD,SIG_IGN);
	printf("init server...\n");
	serverSocket=makeServerSocket(port);
	manager=new ResponseManager();
	if(serverSocket == -1)
	{
		printf("can't create socket!\n");
		return -1;
	}

	return 0;
}
int LuaServer::makeServerSocket(char* port)
{
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s, sfd;

	memset (&hints, 0, sizeof (struct addrinfo));
	hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
	hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
	hints.ai_flags = AI_PASSIVE;     /* All interfaces */

	s = getaddrinfo (NULL, port, &hints, &result);
	if (s != 0)
	{
	//	fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
		return -1;
	}

	for (rp = result; rp != NULL; rp = rp->ai_next)
	{
		sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
		if (s == 0)
		{
			/* We managed to bind successfully! */
			break;
		}

		close (sfd);
	}

	if (rp == NULL)
	{
		fprintf (stderr, "Could not bind\n");
		return -1;
	}

	freeaddrinfo (result);

	return sfd;
}
void LuaServer::start()
{
	struct sockaddr_in userSocket;
	int acceptSocket;
	struct epoll_event event;
	struct epoll_event *events;
	int efd;
	int s;
	s = make_socket_non_blocking (serverSocket);
	if (s == -1)
		abort ();

	s = listen (serverSocket, SOMAXCONN);
	if (s == -1)
	{
		perror ("listen");
		abort ();
	}
	efd=epoll_create1(0);
	event.data.fd=serverSocket;
	event.events=EPOLLIN|EPOLLET;
	s=epoll_ctl(efd,EPOLL_CTL_ADD,serverSocket,&event);
	events=(epoll_event *)calloc(64,sizeof(event));
	socklen_t socketSize=sizeof(struct sockaddr_in);
	//main loop
	for(;;)
	{
		int n,i;
		n=epoll_wait(efd,events,64,-1);
		for(i=0;i<n;i++)
		{
	//		printf("event comes:%d\n",events[i].data.fd);
			if((events[i].events&EPOLLERR)||
					(events[i].events&EPOLLHUP)||
					(!(events[i].events&EPOLLIN)))
			{
				//error
				fprintf (stderr, "epoll error\n");
				close (events[i].data.fd);
				continue;
			}
			else if(serverSocket==events[i].data.fd)
			{
				while (1)
				{
					struct sockaddr in_addr;
					socklen_t in_len;
					int infd;
					char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

					in_len = sizeof in_addr;
					infd = accept (serverSocket, &in_addr, &in_len);
					//printf("infd:%d\n",infd);
					if (infd == -1)
					{
						if ((errno == EAGAIN) ||
								(errno == EWOULDBLOCK))
						{
							/* We have processed all incoming
							 *                              connections. */
							break;
						}
						else
						{
							perror ("accept");
							break;
						}
					}

					s = getnameinfo (&in_addr, in_len,
							hbuf, sizeof hbuf,
							sbuf, sizeof sbuf,
							NI_NUMERICHOST | NI_NUMERICSERV);
					if (s == 0)
					{
						//printf("Accepted connection on descriptor %d "
							//	"(host=%s, port=%s)\n", infd, hbuf, sbuf);
					}

					/* Make the incoming socket non-blocking and add it to the
					 *                      list of fds to monitor. */
					s = make_socket_non_blocking (infd);
					if (s == -1)
						abort ();

					event.data.fd = infd;
					event.events = EPOLLIN | EPOLLET;
					s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
					if (s == -1)
					{
						perror ("epoll_ctl");
						abort ();
					}
				}
				continue;

			}
			else
			{
				//printf("aaa\n");
				doResponse(events[i].data.fd);
				/* Closing the descriptor will make epoll remove it
				 *                      from the set of descriptors which are monitored. */
				close (events[i].data.fd);
			}
		}
	}
}
//	acceptSocket=accept(serverSocket,(struct sockaddr *)&userSocket,&socketSize);
//	//		printf("got request\n");
//	int fr=fork();
//	if(fr==0)
//	{	
//
//		close(serverSocket);
//		//shutdown(acceptSocket,SHUT_RDWR);
//		close(acceptSocket);
//		exit(0);
//	}
//	else
//	{
//		close(acceptSocket);
//	}
//}
//}
char* LuaServer::doResponse(int clientSocket)
{
	int numbytes;
	char buffer[MAX_BUF+1];
	bzero(buffer,MAX_BUF);
	if((numbytes = recv(clientSocket,buffer,MAX_BUF,0)) == -1)
	{
		perror("recv");
		exit(1);
	}
	Request request(buffer,numbytes);
	manager->doResponse(request,clientSocket);
	//const char *response="a";
	//printf("receved message:%s\n",buffer);
}

