#ifndef __LIBRIVAC_STDLIB_H_
#define __LIBRIVAC_STDLIB_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

void *malloc(size_t size);
void *calloc(size_t size);
void free(void *ptr);

char *itoa(int value, char *str, int base);

#ifdef __cplusplus
}
#endif

#endif
