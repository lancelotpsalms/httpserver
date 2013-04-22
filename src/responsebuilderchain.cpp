#include "responsebuilderchain.h"
int ResponseBuilderChain::buildResponse(HttpConnection *conn)
{
	list<IResponseBuilder*>::iterator it;
	for(it=builderChain.begin();it!=builderChain.end();it++)
	{
		if((*it)->buildResponse(conn)==0)
			return 0;
	}
	return -1;
}

