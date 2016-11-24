#include <string.h>

#include <riva/kernel/kernel.h>
#include <riva/kernel/drv/vga.h>
#include <riva/api/ports.h>

using namespace riva;

uint16_t *vga::buffer;
size_t vga::x = 0;
size_t vga::y = 0;
uint8_t vga::colour = 0;

void vga::init()
{
	buffer = (uint16_t *)0xB8000;
	set_colour(VGA_LIGHT_GREY, VGA_BLACK);

	// enable cursor (unset bit 32)
	outportb(0x3D4, 0xA);
	uint8_t csl = inportb(0x3D5);
	//outportb(0x3D4, 0xA);
	outportb(0x3D5, csl & ~0x20);
}

size_t vga::index(size_t x, size_t y)
{
	return (y * VGA_WIDTH) + x;
}

uint8_t vga::create_colour(enum vga_colour fg, enum vga_colour bg)
{
	return (uint8_t)fg | ((uint8_t)bg << 4);
}

uint16_t vga::create_entry(char c, uint8_t colour)
{
	return (uint16_t)c | ((uint16_t)colour << 8);
}

void vga::set_colour(enum vga_colour fg, enum vga_colour bg)
{
	colour = create_colour(fg, bg);
}

void vga::set(char c, uint8_t colour, size_t x, size_t y)
{
	buffer[(y * VGA_WIDTH) + x] = create_entry(c, colour);
}

void vga::putch(char c)
{
	switch(c)
	{
		case '\n':
			y++;
		case '\r':
			x = 0;
			break;
		default:
			set(c, colour, x, y);

			if(++x == VGA_WIDTH)
			{
				x = 0;
				y++;
			}
	}

	update_cursor();
}

void vga::write(const char *data, size_t len)
{
	for(size_t i = 0; i < len; i++)
	{
		putch(data[i]);
	}
}

void vga::putstr(const char *str)
{
	write(str, strlen(str));
}

void vga::clear()
{
	x = y = 0;
	update_cursor();

	uint16_t clear = create_entry(' ', colour);

	for(size_t i = 0; i < (VGA_WIDTH * VGA_HEIGHT); i++)
	{
		buffer[i] = clear;
	}
}

void vga::update_cursor()
{
	size_t cp = index(x, y);

	outportb(0x3D4, 0xE);
	outportb(0x3D5, (cp >> 8) & 0xFF);
	outportb(0x3D4, 0xF);
	outportb(0x3D5, cp & 0xFF);
}

