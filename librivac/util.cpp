#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <riva/util/util.h>

using namespace riva;

const char *hex_characters = "0123456789ABCDEF";

char util::ls_to_hex(uint8_t i)
{
	return hex_characters[i & 0xF];
}

char util::ms_to_hex(uint8_t i)
{
	return hex_characters[(i >> 4) & 0xF];
}

void util::to_hex(char *buffer, uint8_t i)
{
	memset(buffer, 0, 2);
	buffer[0] = ms_to_hex(i);
	buffer[1] = ls_to_hex(i);
}

void util::to_hex(char *buffer, uint16_t i)
{
	to_hex(buffer, (uint8_t)((i >> 8) & 0xFF));
	to_hex(buffer + 2, (uint8_t)(i & 0xFF));
}

void util::to_hex(char *buffer, uint32_t i)
{
	to_hex(buffer, (uint16_t)((i >> 16) & 0xFFFF));
	to_hex(buffer + 4, (uint16_t)(i & 0xFFFF));
}

void util::to_hex(char *buffer, uint64_t i)
{
	to_hex(buffer, (uint32_t)((i >> 32) & 0xFFFFFFFF));
	to_hex(buffer + 8, (uint32_t)(i & 0xFFFFFFFF));
}
