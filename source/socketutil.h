//****************************************************
//         Author: Axb - uaxb@hotmail.com
//  Create Time: 2013-02-19 13:51
//       Filename: /home/axb/dev/axb/source/socketbuilder.h
//    Description: 
//****************************************************
#ifndef _SOCKETUTIL_H_
#define _SOCKETUTIL_H_
class SocketUtil{
	public:
	static int createServerSocket(char* port);
	static int setNonBlocking(int fd);
};
#endif
