#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <lrcext/strconv.h>
#include <lrcext/strutil.h>

// sometimes turns the terminal pink
// FIXME
char *itoa(int value, char *str, int base)
{
	if(!value)
	{
		str[0] = '0';
		str[1] = 0;
		return str;
	}

	bool negative = false;

	if(value < 0 && base == 10)
	{
		negative = true;
		value = -value;
	}

	int i = 0, remainder;

	while(value)
	{
		remainder = value % base;

		str[i++] = remainder < 9 ? remainder + 'a' - 10 : remainder + '0';

		value /= base;
	}

	if(negative) str[i++] = '-';

	str[i] = 0;

	return (char *)reverse(str); 
}

const char *hex_characters = "0123456789ABCDEF";

char ls_to_hex(uint8_t i)
{
	return hex_characters[i & 0xF];
}

char ms_to_hex(uint8_t i)
{
	return hex_characters[(i >> 4) & 0xF];
}

void to_hex8(char *buffer, uint8_t i)
{
	memset(buffer, 0, 2);

	buffer[0] = ms_to_hex(i);
	buffer[1] = ls_to_hex(i);
}

void to_hex16(char *buffer, uint16_t i)
{
	to_hex8(buffer, (uint8_t)((i >> 8) & 0xFF));
	to_hex8(buffer + 2, (uint8_t)(i & 0xFF));
}

void to_hex32(char *buffer, uint32_t i)
{
	to_hex16(buffer, (uint16_t)((i >> 16) & 0xFFFF));
	to_hex16(buffer + 4, (uint16_t)(i & 0xFFFF));
}

void to_hex64(char *buffer, uint64_t i)
{
	to_hex64(buffer, (uint32_t)((i >> 32) & 0xFFFFFFFF));
	to_hex64(buffer + 8, (uint32_t)(i & 0xFFFFFFFF));
}
