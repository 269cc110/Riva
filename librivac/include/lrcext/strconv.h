#ifndef __LIBRIVAC_LRCEXT_STRCONV_H_
#define __LIBRIVAC_LRCEXT_STRCONV_H_

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

char ls_to_hex(uint8_t i);
char ms_to_hex(uint8_t i);

void to_hex8(char *out, uint8_t i);
void to_hex16(char *out, uint16_t i);
void to_hex32(char *out, uint32_t i);
void to_hex64(char *out, uint64_t i);

#ifdef __cplusplus
}
#endif

#endif // __LIBRIVAC_LRCEXT_STRCONV_H_
