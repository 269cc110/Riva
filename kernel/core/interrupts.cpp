#include <stdint.h>

#include <riva/api/ports.h>

#include <riva/kernel/dt.h>
#include <riva/kernel/kernel.h>
#include <riva/kernel/interrupts.h>

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
	irq_remap();

#define GATE(a) descriptor_tables::idt_set_gate(a, (uint32_t)_isr##a, 0x08, 0x8E);

	// ISRs
	GATE(0)
	GATE(1)
	GATE(2)
	GATE(3)
	GATE(4)
	GATE(5)
	GATE(6)
	GATE(7)
	GATE(8)
	GATE(9)
	GATE(10)
	GATE(11)
	GATE(12)
	GATE(13)
	GATE(14)
	GATE(15)
	GATE(16)
	GATE(17)
	GATE(18)
	GATE(19)
	GATE(20)
	GATE(21)
	GATE(22)
	GATE(23)
	GATE(24)
	GATE(25)
	GATE(26)
	GATE(27)
	GATE(28)
	GATE(29)
	GATE(30)
	GATE(31)

#define GATE(a, b) descriptor_tables::idt_set_gate(a, (uint32_t)_irq##b, 0x08, 0x8E);

	// IRQs
	GATE(32, 0)
	GATE(33, 1)
	GATE(34, 2)
	GATE(35, 3)
	GATE(36, 4)
	GATE(37, 5)
	GATE(38, 6)
	GATE(39, 7)
	GATE(40, 8)
	GATE(41, 9)
	GATE(42, 10)
	GATE(43, 11)
	GATE(44, 12)
	GATE(45, 13)
	GATE(46, 14)
	GATE(47, 15)

#undef GATE
}

const char *interrupts::uc_exception_messages[] =
{
	"DIVISION BY ZERO",
	"DEBUG",
	"NON MASKABE INTERRUPT",
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

		if((handler = interrupts::irq_handlers[reg->interrupt - 32])) handler(reg);

		if(reg->interrupt >= 40) outportb(0xA0, 0x20);

		outportb(0x20, 0x20);
	}

	void _fault_handler(registers *reg)
	{
		if(reg->interrupt < 32) kernel::fatal(interrupts::uc_exception_messages[reg->interrupt]);
	}
}

