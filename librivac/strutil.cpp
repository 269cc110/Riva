#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <lrcext/strutil.h>

const char *reverse(const char *str)
{
	size_t len = strlen(str);

	char *buffer = (char *)malloc(len + 1);

	for(size_t i = 0; i < len; i++)
	{
		buffer[i - 1] = str[(len - 1) - i];
	}

	return buffer;
}

