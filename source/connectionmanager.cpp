#include "connectionmanager.h"
#include "httpconnection.h"
#include <stdlib.h>
#include <map>
#include "slab.h"
#include "common.h"
using  namespace std;

ConnectionManager *ConnectionManager::instance=0;
int ConnectionManager::size()
{
	return conns->size();
}
HttpConnection* ConnectionManager::get(int key)
{
	map<int,HttpConnection*>::iterator it=conns->find(key);
	if(it==conns->end())
		return create(key);
	else
		return it->second;
}

void ConnectionManager::release(int key) 
{
	map<int,HttpConnection*>::iterator it=conns->find(key);
	if(it==conns->end())
		return; 
	HttpConnection *conn=it->second;
	Slab<HttpConnection>::dealloc(conn);
	conns->erase(it);
}

HttpConnection* ConnectionManager::create(int key)
{

	map<int,HttpConnection*>::iterator it=conns->find(key);
	if(it!=conns->end())
	{
		it->second->reuse();
		return it->second;
	}
	HttpConnection *conn=Slab<HttpConnection>::alloc();	
	conn->setServerContext(context);
	(*conns)[key]=conn;
	return conn;
}

