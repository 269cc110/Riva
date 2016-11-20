#include <riva/kernel/kernel.h>

using namespace riva;

extern "C" void __cxa_pure_virtual()
{
	kernel::fatal("Pure virtual function call");
}
