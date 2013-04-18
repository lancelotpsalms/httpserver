#include "request.h"
#include "common.h"
#include <stdio.h>
#include <string.h>
Request::Request(ServerContext *context)
{
	int requestBufferSize=context->conf.requestBufferSize;	
	if(header==NULL)
	header=(char *)malloc(sizeof(char)*requestBufferSize);
}
void Request::reuse()
{
	*header='\0';
	host=NULL;
	fullPath=NULL;
	path=NULL;
	refer=NULL;
	useragent=NULL;
	method=UNKNOWN;
	readPos=0;
	bufferPos=0;

}
Request::read(char* requestHeader,int len)
{
	strcpy(header+bufferPos,requestheader);
	char *line;
	int c=0;
	int h=0;
	for(c=readPos;c<len+bufferPos;c++)
	{
		if(header[c]=='\n'){
			header[c]='\0';
			if((c>1) && (header[c-1]=='\r'))header[c-1]='\0';
			if(h != 0){
				line=header+h;
				readPos=line;
				if(strncmp(line,"Referer:",8)==0)refer=line+8;
				if(strncmp(line,"User-Agent:",11)==0)useragent=header+11;
			}
			else
			{

				line=header;
				readPos=line;
				if(strncasecmp(line,"GET",3)==0)
				{
					method=GET;
					parsePath(line);
				}
				else if(strncasecmp(line,"POST",4)==0)
				{
					method=POST;
					parsePath(line);
				}
			}
			h=c+1;
		}	
	}
	bufferPos=len+1;
}
void Request::parsePath(char* req)
{
	int c;
	int len=strlen(req);
	for(c=0;c<len;c++)
	{
		if(req[c]==' ')
		{
			path=req+c+1;
			break;
		}
	}
	for(c=c+1;c<len;c++)
	{
		if(req[c]==' ')
		{
			req[c]='\0';
			break;
		}
	}
}
