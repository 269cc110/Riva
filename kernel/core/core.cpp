#include <stddef.h>
#include <string.h>

#include <kernel/kernel.h>
#include <kernel/drv/vga.h>

extern uint32_t end_kernel;

using namespace riva;

extern "C"
{
	void kernel_main()
	{
		kernel::init();
		kernel::start();
	}
}

void kernel::init()
{
	vga::init();
}

void kernel::start()
{
	vga::putstr("Riva 0.1\n> ");
//	fatal("test");
}

void kernel::fatal(const char *error)
{
	vga::set_colour(VGA_LIGHT_GREY, VGA_BLUE);
	vga::clear();
	vga::putstr("FATAL ERROR\n\n    ");
	vga::putstr(error);
	vga::putstr("\n\nSYSTEM HALTED");

	// TODO print registers

	asm volatile("cli//hlt");
}
