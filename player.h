#ifndef PLAYER
#define PLAYER

#include <inttypes.h>

typedef struct Player
{
	uint16_t x;
	uint16_t y;
	uint32_t position;
} Player;

//change player pos
void setpos (Player *p, uint16_t x, uint16_t y)
{
	p->x = x;
	p->y = y;
	p->position = (uint32_t)p->x << 16 | (uint32_t)p->y;
}

uint32_t getseed (uint16_t x, uint16_t y)
{
	return (uint32_t)x << 16 | (uint32_t)y;
}

#endif
