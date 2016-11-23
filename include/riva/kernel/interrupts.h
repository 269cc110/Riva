#ifndef __RIVA_KERNEL_INTERRUPTS_H_
#define __RIVA_KERNEL_INTERRUPTS_H_

#include <stdint.h>

#include <riva/kernel/kernel.h>

namespace riva
{
	typedef void (*irq_handler_t)(registers *);

	class interrupts
	{
		public:
			static irq_handler_t irq_handlers[16];
			static const char *uc_exception_messages[];

			static void init_interrupts();
			static void irq_set_handler(uint32_t irq, irq_handler_t handler);
			static void irq_remove_handler(uint32_t irq);

		private:
			static void irq_remap();
	};
}

#endif // __RIVA_KERNEL_INTERRUPTS_H_

