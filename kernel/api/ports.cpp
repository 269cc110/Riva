#include <stdint.h>

#include <riva/api/ports.h>

uint8_t riva::inportb(uint16_t port)
{
	uint8_t result;
	asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

void riva::outportb(uint16_t port, uint8_t data)
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (data));
}
