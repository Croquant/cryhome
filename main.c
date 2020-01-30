#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define DELAY 30000

#define STAR "*"
#define SHIP "@"
	
int WIDTH, HEIGHT;

uint32_t nProcGen = 0;

uint32_t rnd()
{
	nProcGen += 0xe120fc15;
	uint64_t tmp;
	tmp = (uint64_t)nProcGen * 0x4a39b70d;
	uint32_t m1 = (tmp >> 32) ^ tmp;
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (tmp >> 32) ^ tmp;
	return m2;
}

int main (int argc, char *argv[])
{
	initscr();
	noecho();
	curs_set(FALSE);

	getmaxyx(stdscr, HEIGHT, WIDTH);

	int16_t xOffset = 0;
	int16_t yOffset = 0;

	char in = '0';

	while (1) {
		clear();
		for (int x = 0; x < WIDTH; x++) {
			for (int y = 0; y < HEIGHT; y++) {
				nProcGen = (y + yOffset) << 16 | (x + xOffset);
				mvprintw(y, x, rnd() % 256 > 8 ? " " : STAR);
			}
		}
		char debug[50];
		snprintf(debug, 50, "X: %u, Y: %u", xOffset, yOffset);
		mvprintw(0, 0, debug);(0, 0, debug);
		mvprintw(HEIGHT / 2, WIDTH / 2, SHIP);
		refresh();

		in = getchar();
		if (in == 'd' || in == 'C') {
			xOffset += 1;
		}
		if (in == 'a' || in == 'D') {
			xOffset -= 1;
		}
		if (in == 's' || in == 'B') {
			yOffset += 1;
		}
		if (in == 'w' || in == 'A') {
			yOffset -= 1;
		}
		if (in == 'q') {
			break;
		}
		usleep(DELAY);
		getmaxyx(stdscr, HEIGHT, WIDTH);
	}

	endwin();
}


