//****************************************************
//         Author: Axb - uaxb@hotmail.com
//  Create Time: 2013-02-20 10:18
//       Filename: ../include/connectionmanager.h
//    Description: 
//****************************************************
#ifndef _CONNECTIONMANAGER_H_
#define _CONNECTIONMANAGER_H_
#include <map>
using namespace std;
class ServerContext;
class HttpConnection;
class ConnectionManager{
	public:
		static ConnectionManager* getInstance()
		{
			if(instance==0)
			{
				instance=new ConnectionManager();
			}
			return instance;
		}
		ConnectionManager()
		{
			conns=new map<int,HttpConnection*>();
		}
		HttpConnection* create(int key);
		HttpConnection* get(int key);
		void release(int key);
		void setServerContext(ServerContext *context){this->context=context;};
		int size();
	protected:
		ServerContext *context;
		static ConnectionManager* instance;
		map<int,HttpConnection*> *conns;
};
#endif
