#ifndef __RIVA_KERNEL_H_
#define __RIVA_KERNEL_H_

namespace riva
{
	class kernel
	{
		public:
			static void init();
			static void start();
			static void __attribute__((noreturn)) fatal(const char *error);
	};
}

#endif // __RIVA_KERNEL_H_
