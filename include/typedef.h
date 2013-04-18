#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
#include "common.h"
class HttpConnection;
enum IOEventType{READY_FOR_READ,READ_FOR_WRITE};
class Event{
	public:
	void reuse()
	{
		this->data=NULL;
		this->fd=-1;
		this->conn=NULL;
	};
	void *data;
	IOEventType type;
	int fd;	
	HttpConnection* conn;
};
#endif
