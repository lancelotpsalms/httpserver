//****************************************************
//         Author: Axb - uaxb@hotmail.com
//  Create Time: 2013-02-20 08:45
//       Filename: slab.h
//    Description: 
//****************************************************
#ifndef _SLAB_H_
#define _SLAB_H_
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include "common.h"
using namespace std;
template <class T>
class Slab:public Singleton < Slab<T> >{
	public:
		using Singleton< Slab<T> >::getInstance;
		static int registerSlab()
		{
			//do nothing
			return 0;
		}
		static int unRegisterSlab()
		{
			//do nothing
			return 0;
		}
		static T* alloc()
		{
			//	return new T; 
			Slab<T> *instance=getInstance();
			if(!instance->dataList.empty())
			{
				list<void*>::iterator it=instance->dataList.begin();
				T *p=(T*)*it;
				instance->dataList.pop_front();
				return p;
			}
			else
			{
				T* p=new T;
				return (T*)p;
			}
		}
		static void dealloc(void *p)
		{
			//	delete((T*) p);
			((T*)p)->reuse();
			Slab<T> *instance=getInstance();
			instance->dataList.push_back(p);
		}
	private:
		list<void *> dataList;
	//	static Slab<T> *instance;
};

#endif
