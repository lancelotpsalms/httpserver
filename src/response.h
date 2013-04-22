//****************************************************
//         Author: Axb - uaxb@hotmail.com
//  Create Time: 2013-03-01 16:10
//       Filename: ../include/response.h
//    Description: 
//****************************************************
#ifndef _RESPONSE_H_
#define _RESPONSE_H_
class Response{
	public:
		int write(char *buffer,int len);
	private:
		
		char* character;
};
#endif
