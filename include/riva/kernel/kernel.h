#ifndef __RIVA_KERNEL_H_
#define __RIVA_KERNEL_H_

#include <stdint.h>

namespace riva
{
	struct registers
	{
		uint32_t gs, fs, es, ds;
		uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
		uint32_t interrupt, error;
		uint32_t eip, cs, eflags, useresp, ss;
	};

	class kernel
	{
		public:
			static void init();
			static void start();
			static void __attribute__((noreturn)) fatal(const char *error);
	};
}

#endif // __RIVA_KERNEL_H_

