#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <lrcinternal/alloc.h>

void *next_free = nullptr;
size_t remaining = 0;

void alloc_init(void *start, size_t lim)
{
	next_free = start;
	remaining = lim;
}

// the simplest malloc implementation ever don't judge me
// TODO rewrite as a proper implementation

void *malloc(size_t size)
{
	if(!size || size > remaining) return nullptr;

	void *result = next_free;

	next_free += size;
	remaining -= size;

	return result;
}

void *calloc(size_t size)
{
	void *result = malloc(size);

	if(!result) return result;

	memset(result, 0, size);

	return result;
}

void free(void *ptr)
{
	// no-op
}

