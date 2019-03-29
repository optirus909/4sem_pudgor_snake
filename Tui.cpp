//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <string>
#include <functional>
#include <fstream>
#include "Tui.h"
#include "Game.h"

using namespace std::placeholders;

static std::ofstream fout("log.txt");

Tui::Tui()
{
	struct termios a;
	tcgetattr(0, &a);
	old_ = a;
	cfmakeraw(&a);
	tcsetattr(0, TCSAFLUSH, &a);
	
	resize();
	
	onsig();
}



Tui::~Tui()
{
	//printf("\n");
	this->resize();
	clear_win();
	
	fout << "started - Tui::dtor" << std::endl;
	
	std::string str = "Bye!\n";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy((winx_ - str.length())/2 + i, winy_/2);
		printf("%c", str[i]);
	}
	
	tcsetattr(0, TCSAFLUSH, &old_);
	
	gotoxy(1, winy_);
	
	fout << "ended - Tui::dtor" << std::endl;
}



View::~View()
{

}



void Tui::onsig()
{
	struct sigaction act = {0};
	memset(&act, 0, sizeof(struct sigaction));
	act.sa_handler = hdl;
	sigset_t   set;
	sigemptyset(&set);
	sigaddset(&set, SIGWINCH);
	act.sa_mask = set;
	act.sa_flags = SA_RESTART;
	sigaction(SIGWINCH, &act, NULL);
}



View * View::inst;

View * View::get()
{
	if(inst)
		return inst;
	inst = new Tui;
	return inst;
}



void hdl(int m)
{
	//static int count = 0;
	View * v = View :: get();
	v->resize();
	v->draw();
	//printf("\e[%d;%dH", 1, 1);
	//printf("catched %d\n", count);
	//count++;
}



void Tui::xline(int y, char sym)
{
	for (int i = 1; i <=  winx_; ++i)
	{
		gotoxy(i, y);
		printf("%c", sym);
	}
}



void Tui::yline(int x, char sym)
{
	for (int i = 1; i <=  winy_; ++i)
	{
		gotoxy(x, i);
		printf("%c", sym);
	}
}


void Tui::snakepainter(Coord a, Dir d)
{
	gotoxy(a.first, a.second);
	putchar("0^v<>"[d]);
}


void Tui::draw()
{
	clear_win();
	
	this->xline(1, '#');
	this->yline(winx_, '#');
	this->xline(winy_, '#');
	this->yline(1, '#');
	
	fout << "snake paint start" << std::endl;
	game->paint(std::bind(&View::snakepainter, this, _1, _2));
	fout << "snake paint end\n" << std::endl;
	this->print_version();
	
	this->print_score();
	gotoxy(1,1);
	//printf("x = %d, y = %d\n", winx_, winy_);
	
	fflush(stdout);
}



void Tui::run()
{
	while (getchar() != 'q')
	{
		this->draw();
		fout << "drawing" << std::endl;
	}
	
	gotoxy(1, 1);
	fout << "exit - Tui::run" << std::endl;
}



void Tui::gotoxy(int x, int y)
{
	printf("\e[%d;%dH", y, x);
}



void Tui::clear_win()
{
	printf("\e[H\e[J");
}


void Tui::resize()
{
	struct winsize w_size;
	
	ioctl(1, TIOCGWINSZ, &w_size);
	
	winy_ = w_size.ws_row;
	winx_ = w_size.ws_col;
	
	clear_win();
}



void Tui::print_score()
{
	std::string str = "Score: 1";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy(winx_/2 - str.length()/2 + i, winy_);
		printf("%c", str[i]);
	}
}


void Tui::print_version()
{
	std::string str = "Snake 1.0";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy(winx_ / 2 - str.length()/2 + i, 1);
		printf("%c", str[i]);
	}
}