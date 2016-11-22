#include <string.h>
#include <stddef.h>
#include <string.h>

size_t strlen(const char *str)
{
	size_t result = 0;

	while(*(str++))
	{
		result++;
	}

	return result;
}

void memset(void *ptr, int val, size_t len)
{
	char *charptr = (char *)ptr;

	for(size_t i = 0; i < len; i++)
	{
		charptr[i] = (char)(val & 0xFF);
	}
}

