#include <stdint.h>

#include <riva/kernel/interrupts.h>
#include <riva/kernel/kernel.h>

#include <riva/kernel/drv/kb.h>
#include <riva/kernel/drv/vga.h>

#include <riva/api/ports.h>

using namespace riva;

uint8_t kmap_us[128] = {0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0 /*ctrl*/, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0 /*left shift*/, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0 /*right shift*/, '*', 0 /*left alt*/, ' ', 0 /*caps lock*/, 0 /*f1*/, 0 /*f2*/, 0 /*f3*/, 0 /*f4*/, 0 /*f5*/, 0 /*f6*/, 0 /*f7*/, 0 /*f8*/, 0 /*f9*/, 0 /*f10*/, 0 /*num lock*/, 0 /*scroll lock*/, 0 /*home*/, 0 /*up arrow*/, 0 /*page up*/, '-', 0 /*left arrow*/, 0, 0 /*right arrow*/, '+', 0 /*end key*/, 0 /*down arrow*/, 0 /*page down*/, 0 /*insert*/, 0 /*delete*/, 0, 0, 0, 0 /*f11*/, 0 /*f12*/, 0};
uint8_t kmap_uk[128] = {0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0 /*ctrl*/, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0 /*left shift*/, '#', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0 /*right shift*/, '*', 0 /*left alt*/, ' ', 0 /*caps lock*/, 0 /*f1*/, 0 /*f2*/, 0 /*f3*/, 0 /*f4*/, 0 /*f5*/, 0 /*f6*/, 0 /*f7*/, 0 /*f8*/, 0 /*f9*/, 0 /*f10*/, 0 /*num lock*/, 0 /*scroll lock*/, 0 /*home*/, 0 /*up arrow*/, 0 /*page up*/, '-', 0 /*left arrow*/, 0, 0 /*right arrow*/, '+', 0 /*end key*/, 0 /*down arrow*/, 0 /*page down*/, 0 /*insert*/, 0 /*delete*/, 0, 0, 0, 0 /*f11*/, 0 /*f12*/, 0};
uint8_t kmap_uk_shift[128] = {0, 27, '!', '"', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0 /*ctrl*/, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '@', '|', 0 /*left shift*/, '~', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '|', 0 /*right shift*/, '*', 0 /*left alt*/, ' ', 0 /*caps lock*/, 0 /*f1*/, 0 /*f2*/, 0 /*f3*/, 0 /*f4*/, 0 /*f5*/, 0 /*f6*/, 0 /*f7*/, 0 /*f8*/, 0 /*f9*/, 0 /*f10*/, 0 /*num lock*/, 0 /*scroll lock*/, 0 /*home*/, 0 /*up arrow*/, 0 /*page up*/, '-', 0 /*left arrow*/, 0, 0 /*right arrow*/, '+', 0 /*end key*/, 0 /*down arrow*/, 0 /*page down*/, 0 /*insert*/, 0 /*delete*/, 0, 0, 0, 0 /*f11*/, 0 /*f12*/, 0};

extern "C"
{
	void kb_handler(registers *reg)
	{
		//vga::putstr("received keyboard interrupt\n");

		uint8_t scancode = inportb(0x60);

		if(keyboard::enabled)
		{
			if(scancode & 0x80)
			{
				uint8_t nscancode = scancode & ~0x80;

				if(nscancode == 42) keyboard::lshifted = false;
				else if(nscancode == 54) keyboard::rshifted = false;
			}
			else
			{
				if(scancode == 42) keyboard::lshifted = true;
				else if(scancode == 54) keyboard::rshifted = true;
				else vga::putch((keyboard::lshifted || keyboard::rshifted ? kmap_uk_shift : kmap_uk)[scancode]);
			}
		}
//		else vga::putstr("keyboard disabled\n");
	}
}

bool keyboard::enabled = false;
bool keyboard::lshifted = false;
bool keyboard::rshifted = false;

void keyboard::init()
{
	interrupts::irq_set_handler(1, &kb_handler);
}

void keyboard::enable()
{
	enabled = true;
}

void keyboard::disable()
{
	enabled = false;
}

