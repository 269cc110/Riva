#ifndef __RIVA_PORTS_H_
#define __RIVA_PORTS_H_

#include <stdint.h>

namespace riva
{
	uint8_t inportb(uint16_t port);
	void outportb(uint16_t port, uint8_t data);
}

#endif // __RIVA_PORTS_H_

