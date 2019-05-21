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
	void gotoxy(int x, int y);
	void xline(int y, char sym);
	void yline(int x, char sym);
	void clear_win();
	void print_score();
	void print_version();
	void onsig();
	struct termios old_;
	int winx_;
	int winy_;
public:
	
	Tui();
	~Tui();
	//View * get();
	int getX();
	int getY();
	void resize();
	void draw ();
	void snakepainter(Coord a, Dir d);
	void rabbitpainter(Coord a);
	void run  ();
};

bool compare (timeout a, timeout b);
void hdl(int m);

#endif //SNAKE_TUI_H