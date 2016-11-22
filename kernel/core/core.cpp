#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include <riva/kernel/kernel.h>
#include <riva/kernel/drv/vga.h>

#include <lrcinternal/alloc.h>
#include <lrcext/strconv.h>

using namespace riva;

extern "C"
{
	void kernel_main()
	{
		kernel::init();
		kernel::start();
	}

	extern uint8_t end_kernel, stack_bottom, stack_top;

	void _init_page_dir(uint32_t *pd);
	void _enable_paging();
}

const char *VERSION = "0.1";

uint32_t page_directory[1024] __attribute__((aligned(4096)));

void kernel::init()
{
	vga::init();
	vga::set_colour(VGA_GREEN, VGA_BLACK);
	vga::clear();

	for(int i = 0; i < 1024; i++)
	{
		page_directory[i] = 0x00000002;
	}

	uint32_t initial_page_table[1024] __attribute__((aligned(4096)));

	for(size_t i = 0; i < 1024; i++)
	{
		initial_page_table[i] = (i * 0x1000) | 3;
	}

	page_directory[0] = ((uint32_t)initial_page_table) | 3;

	_init_page_dir(page_directory);
	_enable_paging();

	alloc_init((void *)&end_kernel, (32768 * 1024));// - (uint32_t)&end_kernel);
}

void kernel::start()
{
	vga::putstr("Riva ");
	vga::putstr(VERSION);
	vga::putstr(" (");

	vga::putstr(sizeof(void *) == 4 ? "x86, " : "x64, ");
//	vga::putstr(&stack_top < &stack_bottom ? "stack_top < stack_bottom, " : (&stack_top == &stack_bottom ? "stack_top = stack_bottom, " : "stack_top > stack_bottom, "));

	size_t stack_size = &stack_top - &stack_bottom;

	vga::putstr(stack_size == 32768 ? "stack OK, " : "incorrectly sized stack, ");

	char buffer[9] = {0};

	to_hex32(buffer, stack_size);

//	char stack_size_buffer0[9] = {0};
//	char *stack_size_buffer = itoa(stack_size, stack_size_buffer0, 10);

	vga::putstr("0x");
	vga::putstr(buffer);
	vga::putstr(" bytes");

	vga::putstr(")\n");

	vga::putstr("Kernel ends at 0x");
	to_hex32(buffer, (uint32_t)&end_kernel);
	vga::putstr(buffer);
	vga::putstr("\n> ");
}

__attribute__((noreturn))
void kernel::fatal(const char *error)
{
	vga::set_colour(VGA_LIGHT_GREY, VGA_BLUE);
	vga::clear();
	vga::putstr("FATAL ERROR\n\n    ");
	vga::putstr(error);
	vga::putstr("\n\nSYSTEM HALTED");

	// TODO print registers

	asm volatile("cli//hlt");

	// just in case
	while(true);
}
