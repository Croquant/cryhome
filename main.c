#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

#define STAR "."
#define SHIP ">"
	
int WIDTH, HEIGHT;

uint32_t seed = 0;

uint32_t rnd()
{
	seed += 0xe120fc15;
	uint64_t tmp;
	tmp = (uint64_t)seed * 0x4a39b70d;
	uint32_t m1 = (tmp >> 32) ^ tmp;
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (tmp >> 32) ^ tmp;
	return m2;
}

void drawMap (int posX, int posY)
{
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			seed = (y + posY) << 16 | (x + posX);
			mvprintw(y, x, rnd() % 256 > 1 ? " " : STAR);
		}
	}
}

void drawDebug (int posX, int posY)
{
	char debug[50];
	snprintf(debug, 50, "X: %u, Y: %u", posX, posY);
	mvprintw(0, 0, debug);(0, 0, debug);
}

int main (int argc, char *argv[])
{
	initscr();
	noecho();
	curs_set(FALSE);

	int16_t playerX = 1320;
	int16_t playerY = 1320;

	char in = '0';

	while (1) {
		//DRAW LOOP
		getmaxyx(stdscr, HEIGHT, WIDTH);
		clear();

		drawMap(playerX, playerY);

		drawDebug(playerX, playerY);
		
		mvprintw(HEIGHT / 2, WIDTH / 2, SHIP);
		refresh();

		//INPUT LOOP
		in = getchar();
		if (in == 'f' || in == 'C') {
			playerX += 1;
		}
		if (in == 's' || in == 'D') {
			playerX -= 1;
		}
		if (in == 'd' || in == 'B') {
			playerY += 1;
		}
		if (in == 'e' || in == 'A') {
			playerY -= 1;
		}
		if (in == 'q') {
			break;
		}
		usleep(DELAY);
	}

	endwin();
}


