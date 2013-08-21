#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#include <iostream>
using namespace std;

#ifdef _DEBUG
#define NEW ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW new
//�ڴ��nedmalloc��ʹ�� 
#ifdef COMPILE_NEDMALLOC
extern "C"
{
//���ͷ�ļ������޸��ˣ�����Ӧvc2005
#include "nedmalloc.h"
};
#endif //CUSTOMALLOC

void *operator new(std::size_t count) throw(std::bad_alloc);
void *operator new(std::size_t count, const std::nothrow_t&) throw();
void *operator new(std::size_t count, int blockUse, const char * szFileName, int nLine) throw(std::bad_alloc);
void *operator new(std::size_t count, int blockUse, const char * szFileName, int nLine, const std::nothrow_t&) throw();
void *operator new[](std::size_t count) throw(std::bad_alloc);
void *operator new[](std::size_t count, const std::nothrow_t&) throw();
void operator delete(void* mem);
void operator delete(void* mem, size_t size);
void operator delete[](void* mem);
void operator delete[](void* mem, size_t size);

#endif //_DEBUG
#endif //MEMORYPOOL_H
