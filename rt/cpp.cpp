#include <stddef.h>
#include <stdlib.h>

#include <riva/kernel/kernel.h>

void *operator new(size_t size)
{
	return malloc(size);
}

void operator delete(void *ptr)
{
	free(ptr);
}

void *operator new[](size_t size)
{
	return malloc(size);
}

void operator delete[](void *ptr)
{
	free(ptr);
}
