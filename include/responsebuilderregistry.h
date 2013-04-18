#ifndef _RESPONSEBUILDERREGISTRY_H_
#define _RESPONSEBUILDERREGISTRY_H_
#include <map>
class IResponseBuilder;
class HttpConnection;
class ResponseBuilderRegistry:public Singleton<ResponseBuilderRegistry>{
	public:
		IResponseBuilder *getBuilder(HttpConnection *conn);
		void registerBuilder(IResponseBuilder *builder,char *ext);
	private:
		ResponseBuilderRegistry(){};
		map<char*,IResponseBuilder*> builderRegistry;
};
#endif

