#ifndef RANDOM
#define RANDOM

#include <inttypes.h>

uint32_t SEED = 1;

uint32_t rnd()
{
	SEED += 0xe120fc15;
	uint64_t tmp;
	tmp = (uint64_t)SEED * 0x4a39b70d;
	uint32_t m1 = (tmp >> 32) ^ tmp;
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (tmp >> 32) ^ tmp;
	return m2;
}

#endif // RANDOM
