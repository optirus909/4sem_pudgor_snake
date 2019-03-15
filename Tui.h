//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#ifndef SNAKE_TUI_H
#define SNAKE_TUI_H

#include "View.h"

class Tui : View
{
private:
	int winx;
	int winy;
	void gotoxy(int x, int y);
	void xline(int y, char sym);
	void yline(int x, char sym);
	void clear_win();
	void print_score();
	void print_version();
	
public:
	Tui();
	~Tui();
	void draw ();
	void run  ();
};


#endif //SNAKE_TUI_H
