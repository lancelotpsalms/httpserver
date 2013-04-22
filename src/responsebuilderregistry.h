#ifndef _RESPONSEBUILDERREGISTRY_H_
#define _RESPONSEBUILDERREGISTRY_H_
#include <map>
#include <string>
#include "common.h"
using namespace std;
class IResponseBuilder;
class HttpConnection;
class ResponseBuilderRegistry{
	public:
		IResponseBuilder *getBuilder(HttpConnection *conn);
		void registerBuilder(IResponseBuilder *builder,char *ext);
	protected:
		ResponseBuilderRegistry(){};
		map<string,IResponseBuilder*> builderRegistry;
		DECLARE_SINGLETON_CLASS(ResponseBuilderRegistry);
};
typedef Singleton<ResponseBuilderRegistry> SResponseBuilderRegistry;
#endif

