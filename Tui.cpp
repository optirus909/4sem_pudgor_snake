//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#include "Tui.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <string>


Tui :: Tui()
{
	struct winsize w_size;
	
	ioctl(1, TIOCGWINSZ, &w_size);
	
	this->winy = w_size.ws_row;
	this->winx = w_size.ws_col;
	
	gotoxy(1, 1);
	printf("x");
	gotoxy(2, 1);
	printf("y");
	gotoxy(3, 1);
	printf("й");
}


void Tui ::xline(int y, char sym)
{
	for (int i = 1; i <=  this->winx; ++i)
	{
		gotoxy(i, y);
		printf("%c", sym);
	}
}


void Tui ::yline(int x, char sym)
{
	for (int i = 1; i <=  this->winy; ++i)
	{
		gotoxy(x, i);
		printf("%c", sym);
	}
}

void Tui :: draw()
{
	this->clear_win();
	
	this->xline(1, '#');
	this->xline(this->winy, '#');
	
	this->yline(1, '#');
	this->yline(this->winx, '#');
	
	this->print_version();
	
	this->print_score();
}


void Tui ::clear_win()
{
	for (int i = 1; i <= this->winx; ++i)
		for (int j = 1; j <= this->winy; ++j)
		{
			gotoxy(i, j);
			printf(" ");
		}
}

void Tui :: run()
{
	int a;
}


void Tui :: gotoxy(int x, int y)
{
	printf("\e[%d;%dH", y, x);
}


Tui :: ~Tui()
{
	printf("\n");
	gotoxy(1, this->winy);
	//printf("Destroyed\n");
}


View ::~View()
{

}


void Tui ::print_score()
{
	std::string str = "Score: 1";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy(this->winx/2 - str.length() + i, this->winy);
		printf("%c", str[i]);
	}
}

void Tui ::print_version()
{
	std::string str = "Snake 1.0";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy(this->winx / 2 - str.length() + i, 1);
		printf("%c", str[i]);
	}
}