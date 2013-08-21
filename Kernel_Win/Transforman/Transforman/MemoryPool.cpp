#include "MemoryPool.h"
#ifndef _DEBUG
void *operator new(std::size_t count) throw(std::bad_alloc)
{
    if (count == 0)
    {
        count = 1;
    }
    return nedmalloc(count);
}

void *operator new(std::size_t count, const std::nothrow_t&) throw()
{
    if (count == 0)
    {
        count = 1;
    }
    return nedmalloc(count);
}

void *operator new(std::size_t count, int blockUse, const char * szFileName, int nLine) throw(std::bad_alloc)
{
    if (count == 0)
    {
        count = 1;
    }
    return nedmalloc(count);
}

void *operator new(std::size_t count, int blockUse, const char * szFileName, int nLine, const std::nothrow_t&) throw()
{
    if (count == 0)
    {
        count = 1;
    }
    return nedmalloc(count);
}

void *operator new[](std::size_t count) throw(std::bad_alloc)
{
    if (count == 0)
    {
        count = 1;
    }
    return nedmalloc(count);
}

void *operator new[](std::size_t count, const std::nothrow_t&) throw()
{
    if (count == 0)
    {
        count = 1;
    }
    return nedmalloc(count);
}

void operator delete(void* mem)
{
    if (mem == NULL)
    {
        return;
    }
    nedfree(mem);
}

void operator delete(void* mem, size_t size)
{
    if (mem == NULL)
    {
        return;
    }
    nedfree(mem);
}

void operator delete[](void* mem)
{
    if (mem == NULL)
    {
        return;
    }
    nedfree(mem);
}

void operator delete[](void* mem, size_t size)
{
    if (mem == NULL)
    {
        return;
    }
    nedfree(mem);
}
#endif 