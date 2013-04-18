//****************************************************
//         Author: Axb - uaxb@hotmail.com
//  Create Time: 2013-03-01 11:37
//       Filename: responsebuilderchain.h
//    Description: 
//****************************************************
#ifndef _RESPONSEBUILDERCHAIN_H_
#define _RESPONSEBUILDERCHAIN_H_
#include "iresponsebuilder.h"
#include <list>
using namespace std;
class ResponseBuilderChain:public IResponseBuilder{
	public:
		virtual int buildResponse(HttpConnection *conn);	
	private:
		list<IResponseBuilder*> builderChain;	
};
#endif
