#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#define DELAY 10000

#define STAR "*"
#define SHIP_RIGHT ">"
#define SHIP_LEFT "<"
	
int WIDTH, HEIGHT;

uint32_t seed = 0;

uint32_t rnd()
{
	//seed += 0xe120fc15;
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
			seed = (x + posX) << 16 | (y + posY);
			bool isStar = rnd() % 256 > 1;
			mvprintw(y, x, isStar ? " " : STAR);
		}
	}
}

void drawDebug (int posX, int posY, int time)
{
	char debug[50];
	snprintf(debug, 50, "X: %u, Y: %u, Time: %u", posX, posY, time);
	mvprintw(0, 0, debug);(0, 0, debug);
}

void setTxt (char *text, size_t size)
{
	char input[100];
	echo();
	mvprintw(HEIGHT - 1, 0, "Enter Message: ");
	getstr(input);
	strncpy(text, input, size - 1);
	text[size - 1] = 0;
	noecho();
}

void drawShip (bool dir)
{
	if (dir) {
		mvprintw(HEIGHT / 2, WIDTH / 2, SHIP_LEFT);
	} else {
		mvprintw(HEIGHT / 2, WIDTH / 2, SHIP_RIGHT);
	}
}

int main (int argc, char *argv[])
{
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	halfdelay(10);
	curs_set(FALSE);

	uint32_t playerX = 0;
	uint32_t playerY = 0;
	uint16_t time = 0;
	bool direction = 0;

	char msg[100];

	while (1) {
		//DRAW LOOP
		getmaxyx(stdscr, HEIGHT, WIDTH);
		clear();

		drawMap(playerX, playerY);

		drawDebug(playerX, playerY, time);
		
		drawShip(direction);

		mvprintw(HEIGHT / 2 - 1, (WIDTH - strlen(msg) + 1)/ 2, msg);
		refresh();

		//INPUT LOOP
		int in = getch();
		if (in == 't') {
			setTxt(msg, sizeof msg / sizeof *msg);
		}
		if (in == KEY_RIGHT) {
			playerX += 1;
			direction = 0;
		}
		if (in == KEY_LEFT) {
			playerX -= 1;
			direction = 1;
		}
		if (in == KEY_DOWN) {
			playerY += 1;
		}
		if (in == KEY_UP) {
			playerY -= 1;
		}
		if (in == 'q') {
			break;
		}
		time++;
		usleep(DELAY);
	}
	endwin();
}


