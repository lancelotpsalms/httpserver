#include "responsebuilderregistry.h"
#include "iresponsebuilder.h"
#include "httpconnection.h"
IResponseBuilder* ResponseBuilderRegistry::getBuilder(HttpConnection *conn)
{
	map<string,IResponseBuilder*>::iterator it=builderRegistry.find(conn->request.getExtension());
	if(it==builderRegistry.end())
		return NULL;
	else
		return it->second;
}
void ResponseBuilderRegistry::registerBuilder(IResponseBuilder *builder,char *ext)
{
	builderRegistry[ext]=builder;	
}
