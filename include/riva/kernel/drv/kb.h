#ifndef __RIVA_KERNEL_DRV_KB_H_
#define __RIVA_KERNEL_DRV_KB_H_

namespace riva
{
	class keyboard
	{
		public:
			static bool enabled, lshifted, rshifted;
			static void init();
			static void enable();
			static void disable();
	};
}

#endif // __RIVA_KERNEL_DRV_KB_H_

