#include <stdio.h>
#include "player.h"
#include "random.h"

void printp (Player p)
{
	printf("x: %#06x\n", p.x);
	printf("y: %#06x\n", p.y);
	printf("pos: %#010x\n", p.position);
}

int main(int argc, char const *argv[])
{
	Player p;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			setpos(&p, i, j);
			SEED = p.position;
			printf("[%c|", rnd() % 256 > 127 ? '0' : '1');
			printf("%c]", rnd() % 256 > 127 ? '0' : '1');
		}
		printf("\n");
	}
	return 0;
}