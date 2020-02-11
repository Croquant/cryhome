#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "player.h"
#include "random.h"

#define DELAY 10000

int WIDTH, HEIGHT;

void drawMap (Player p)
{
	for (int x = -WIDTH/2; x < WIDTH/2; x++) {
		for (int y = -HEIGHT/2; y < HEIGHT/2; y++) {
			SEED = getseed(p.x + x, p.y + y);
			char w[2];
			bool isStar = rnd() % 256 < 4;
			w[0] = randchar();
			mvprintw(y + HEIGHT/2, x + WIDTH/2, isStar ? w : " ");
		}
	}
}

void drawShip (Player p)
{
	mvprintw(HEIGHT / 2, WIDTH / 2, ">");
	SEED = getseed(p.x, p.y);
	if (rnd() % 256 < 4) {
		mvprintw(HEIGHT / 2 - 1, WIDTH / 2, "?");
	}
}

void drawDebug (int posX, int posY, int time)
{
	char debug[50];
	snprintf(debug, 50, "X: %u, Y: %u, Time: %u", posX, posY, time);
	mvprintw(0, 0, debug);
}

int main(int argc, char const *argv[])
{
	int time = 0;
	Player p;
	setpos(&p, 0, 0);

	//ncurses initialization
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	halfdelay(10);
	curs_set(FALSE);

	//GAME LOOP
	while (1) {
		//DRAW LOOP
		getmaxyx(stdscr, HEIGHT, WIDTH); //Update Screen size
		clear();
		drawMap(p);
		drawShip(p);
		drawDebug(p.x, p.y, time);
		refresh();

		//INPUT LOOP
		int in = getch();
		switch (in)
		{
		case KEY_RIGHT:
			p.x += 1;
			break;
		case KEY_LEFT:
			p.x -= 1;
			break;
		case KEY_DOWN:
			p.y += 1;
			break;
		case KEY_UP:
			p.y -= 1;
			break;
		default:
			break;
		}
		if (in == 'q') {
			break;
		}
		time++;
		usleep(DELAY);
	}
	
	endwin();
	return 0;
}