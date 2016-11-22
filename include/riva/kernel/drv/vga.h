#ifndef __RIVA_VGA_H_
#define __RIVA_VGA_H_

#include <stdint.h>
#include <stddef.h>

namespace riva
{
	enum vga_colour
	{
		VGA_BLACK = 0,
		VGA_BLUE = 1,
		VGA_GREEN = 2,
		VGA_CYAN = 3,
		VGA_RED = 4,
		VGA_MAGENTA = 5,
		VGA_BROWN = 6,
		VGA_LIGHT_GREY = 7,
		VGA_DARK_GREY = 8,
		VGA_LIGHT_BLUE = 9,
		VGA_LIGHT_GREEN = 10,
		VGA_LIGHT_CYAN = 11,
		VGA_LIGHT_RED = 12,
		VGA_LIGHT_MAGENTA = 13,
		VGA_LIGHT_BROWN = 14,
		VGA_WHITE = 15
	};

	const size_t VGA_WIDTH = 80;
	const size_t VGA_HEIGHT = 25;

	class vga
	{
		public:
			static void init();
			static void putch(char c);
			static void putstr(const char *str);
			static void set_colour(enum vga_colour fg, enum vga_colour bg);
			static void clear();

		private:
			static uint16_t *buffer;
			static size_t x, y;
			static uint8_t colour;

			static inline uint8_t create_colour(enum vga_colour fg, enum vga_colour bg);
			static inline uint16_t create_entry(char c, uint8_t colour);
			static inline size_t index(size_t x, size_t y);
			static void write(const char *data, size_t len);
			static void set(char c, uint8_t colour, size_t x, size_t y);
			static void update_cursor();
	};
}

#endif // __RIVA_VGA_H_

