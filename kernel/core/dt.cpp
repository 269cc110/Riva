#include <stdint.h>
#include <string.h>

#include <riva/kernel/dt.h>

using namespace riva;

namespace riva
{
	struct gdt_entry
	{
		uint16_t limit_low;
		uint16_t base_low;
		uint8_t base_middle;
		uint8_t access;
		uint8_t granularity;
		uint8_t base_high;
	} __attribute__((packed));

	struct idt_entry
	{
		uint16_t base_low;
		uint16_t sel;
		uint8_t null;
		uint8_t flags;
		uint16_t base_high;
	} __attribute__((packed));

	struct dt_ptr
	{
		uint16_t limit;
		uint32_t base;
	} __attribute__((packed));
}

gdt_entry gdt[3];
idt_entry idt[256];

extern "C"
{
	dt_ptr gdt_ptr;
	dt_ptr idt_ptr;

	extern void _load_gdt();
}

void descriptor_tables::gdt_set_gate(int32_t index, uint64_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
	gdt[index].base_low = base & 0xFFFF;
	gdt[index].base_middle = (base >> 16) & 0xFF;
	gdt[index].base_high = (base >> 24) & 0xFF;

	gdt[index].limit_low = limit & 0xFFFF;
	gdt[index].granularity = (limit >> 16) & 0x0F;
	gdt[index].granularity |= granularity & 0xF0;

	gdt[index].access = access;
}

void descriptor_tables::idt_set_gate(uint8_t index, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt[index].base_low = base & 0xFFFF;
	idt[index].base_high = (base >> 16) & 0xFFFF;

	idt[index].sel = sel;

	idt[index].null = 0;

	idt[index].flags = flags;
}

void descriptor_tables::init_gdt()
{
	gdt_ptr.limit = (sizeof(gdt_entry) * 3) - 1;
	gdt_ptr.base = (uint32_t)&gdt;

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	_load_gdt();
}

void descriptor_tables::init_idt()
{
	idt_ptr.limit = (sizeof(idt_entry) * 256) - 1;
	idt_ptr.base = (uint32_t)&idt;

	memset(&idt, 0, sizeof(idt_entry) * 256);

	asm volatile("lidt [%0]" : : "m" (idt_ptr));
}

