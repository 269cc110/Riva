#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <lrcinternal/alloc.h>

#include <lrcext/strconv.h>

#include <riva/kernel/drv/vga.h>

using namespace riva;

void *next_free = nullptr;
size_t remaining = 0;

void alloc_init(void *start, size_t lim)
{
	next_free = start;
	remaining = lim;

	char buffer[9] = {0};

	to_hex32(buffer, (uint32_t)start);

	vga::putstr("alloc_init(0x");
	vga::putstr(buffer);
	vga::putstr(", 0x");

	to_hex32(buffer, lim);

	vga::putstr(buffer);
	vga::putstr(")\n");
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

