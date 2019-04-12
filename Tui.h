//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#ifndef SNAKE_TUI_H
#define SNAKE_TUI_H

#include <termios.h>
#include "View.h"


class Tui : public View
{
private:
	int winx_;
	int winy_;
	void gotoxy(int x, int y);
	void xline(int y, char sym);
	void yline(int x, char sym);
	void clear_win();
	void print_score();
	void print_version();
	void onsig();
	struct termios old_;
	
public:
	Tui();
	~Tui();
	View * get();
	void resize();
	void draw ();
	void snakepainter(Coord a, Dir d);
	void run  ();
};

void hdl(int m);

#endif //SNAKE_TUI_H