#ifndef __RIVA_KERNEL_DT_H_
#define __RIVA_KERNEL_DT_H_

namespace riva
{
	class descriptor_tables
	{
		public:
			static void init_gdt();
			static void init_idt();

			static void gdt_set_gate(int32_t index, uint64_t base, uint32_t limit, uint8_t access, uint8_t granularity);
			static void idt_set_gate(uint8_t index, uint32_t base, uint16_t sel, uint8_t flags);
	};
}

#endif // __RIVA_KERNEL_DT_H_

