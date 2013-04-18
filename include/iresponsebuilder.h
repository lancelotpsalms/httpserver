#ifndef _IRESPONSEBUILDER_H_
#define _IRESPONSEBUILDER_H_
class Response;
class HttpConnection;
class IResponseBuilder{
	public:
		virtual int buildResponse(HttpConnection *conn)=0;
};
#endif
