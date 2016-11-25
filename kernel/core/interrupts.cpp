#include <stdint.h>

#include <riva/api/ports.h>

#include <riva/kernel/dt.h>
#include <riva/kernel/kernel.h>
#include <riva/kernel/interrupts.h>

#include <lrcext/strconv.h>
#include <riva/kernel/drv/vga.h>

using namespace riva;

extern "C"
{
#define ISR(a) extern void _isr##a();

	ISR(0)
	ISR(1)
	ISR(1)
	ISR(2)
	ISR(3)
	ISR(4)
	ISR(5)
	ISR(6)
	ISR(7)
	ISR(8)
	ISR(9)
	ISR(10)
	ISR(11)
	ISR(12)
	ISR(13)
	ISR(14)
	ISR(15)
	ISR(16)
	ISR(17)
	ISR(18)
	ISR(19)
	ISR(20)
	ISR(21)
	ISR(22)
	ISR(23)
	ISR(24)
	ISR(25)
	ISR(26)
	ISR(27)
	ISR(28)
	ISR(29)
	ISR(30)
	ISR(31)

#undef ISR

#define IRQ(a) extern void _irq##a();

	IRQ(0)
	IRQ(1)
	IRQ(2)
	IRQ(3)
	IRQ(4)
	IRQ(5)
	IRQ(6)
	IRQ(7)
	IRQ(8)
	IRQ(9)
	IRQ(10)
	IRQ(11)
	IRQ(12)
	IRQ(13)
	IRQ(14)
	IRQ(15)

#undef IRQ
}

irq_handler_t interrupts::irq_handlers[16] = {0};

void interrupts::irq_set_handler(uint32_t irq, irq_handler_t handler)
{
	char buffer[9] = {0};
	to_hex32(buffer, irq);
	vga::putstr("irq_set_handler(0x");
	vga::putstr(buffer);
	to_hex32(buffer, (uint32_t)handler);
	vga::putstr(", 0x");
	vga::putstr(buffer);
	vga::putstr(")\n");

	irq_handlers[irq] = handler;
}

void interrupts::irq_remove_handler(uint32_t irq)
{
	irq_handlers[irq] = 0;
}

void interrupts::irq_remap()
{
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
}

void interrupts::init_interrupts()
{
#define ISR_GATE(a) descriptor_tables::idt_set_gate(a, (uint32_t)_isr##a, 0x08, 0x8E);

	// ISRs
	ISR_GATE(0)
	ISR_GATE(1)
	ISR_GATE(2)
	ISR_GATE(3)
	ISR_GATE(4)
	ISR_GATE(5)
	ISR_GATE(6)
	ISR_GATE(7)
	ISR_GATE(8)
	ISR_GATE(9)
	ISR_GATE(10)
	ISR_GATE(11)
	ISR_GATE(12)
	ISR_GATE(13)
	ISR_GATE(14)
	ISR_GATE(15)
	ISR_GATE(16)
	ISR_GATE(17)
	ISR_GATE(18)
	ISR_GATE(19)
	ISR_GATE(20)
	ISR_GATE(21)
	ISR_GATE(22)
	ISR_GATE(23)
	ISR_GATE(24)
	ISR_GATE(25)
	ISR_GATE(26)
	ISR_GATE(27)
	ISR_GATE(28)
	ISR_GATE(29)
	ISR_GATE(30)
	ISR_GATE(31)

#undef ISR_GATE

#define IRQ_GATE(a, b) descriptor_tables::idt_set_gate(a, (uint32_t)_irq##b, 0x08, 0x8E);

	irq_remap();

	// IRQs
	IRQ_GATE(32, 0)
	IRQ_GATE(33, 1)
	IRQ_GATE(34, 2)
	IRQ_GATE(35, 3)
	IRQ_GATE(36, 4)
	IRQ_GATE(37, 5)
	IRQ_GATE(38, 6)
	IRQ_GATE(39, 7)
	IRQ_GATE(40, 8)
	IRQ_GATE(41, 9)
	IRQ_GATE(42, 10)
	IRQ_GATE(43, 11)
	IRQ_GATE(44, 12)
	IRQ_GATE(45, 13)
	IRQ_GATE(46, 14)
	IRQ_GATE(47, 15)

#undef GATE
}

const char *interrupts::uc_exception_messages[] =
{
	"DIVISION BY ZERO",
	"DEBUG",
	"NON-MASKABLE INTERRUPT",
	"BREAKPOINT",
	"INTO DETECTED OVERFLOW",
	"OUT OF BOUNDS",
	"INVALID OPCODE",
	"NO COPROCESSOR",
	"DOUBLE FAULT",
	"COPROCESSOR SEGMENT OVERRUN",
	"BAD TSS",
	"SEGMENT NOT PRESENT",
	"STACK FAULT",
	"GENERAL PROTECTION FAULT",
	"PAGE FAULT",
	"UNKNOWN INTERRUPT",
	"COPROCESSOR FAULT",
	"ALIGNMENT CHECK",
	"MACHINE CHECK",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED",
	"RESERVED"
};

extern "C"
{
	void _irq_handler(registers *reg)
	{
		irq_handler_t handler;

		/*char buffer[9] = {0};
		to_hex32(buffer, reg->interrupt - 32);

		vga::putstr("received IRQ 0x");
		vga::putstr(buffer);
		vga::putstr("\n");*/

		if((handler = interrupts::irq_handlers[reg->interrupt - 32])) handler(reg);

		if(reg->interrupt >= 40) outportb(0xA0, 0x20);

		outportb(0x20, 0x20);
	}

	void _fault_handler(registers *reg)
	{
		if(reg->interrupt < 32) kernel::fatal(interrupts::uc_exception_messages[reg->interrupt]);
	}
}

