#ifndef __LIBRIVAC_STRING_H_
#define __LIBRIVAC_STRING_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

void *memset(void *ptr, uint8_t val, size_t len);
void *memsetw(void *ptr, uint16_t val, size_t len);

void *memcpy(void *dest, const void *src, size_t len);

size_t strlen(const char *str);

#ifdef __cplusplus
}
#endif

#endif // __LIBRIVAC_STRING_H_
