//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <functional>
#include <fstream>
#include <poll.h>
#include <zconf.h>
#include "Tui.h"


using namespace std::placeholders;

static std::ofstream fout("log.txt");

Tui::Tui()
{
	struct termios a;
	
	tcgetattr(0, &a);
	old_ = a;
	cfmakeraw(&a);
	tcsetattr(0, TCSANOW, &a);
	
	resize();
	onsig();
}



Tui::~Tui()
{
	clear_win();
	
	
	std::string str = "Bye!\n";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy((winx_ - str.length())/2 + i, winy_/2);
		printf("%c", str[i]);
	}
	
	gotoxy(1, winy_);
	tcsetattr(0, TCSAFLUSH, &old_);
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


void hdl(int m)
{
	View * v = View::get();
	v->resize();
	v->draw();
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

void Tui::rabbitpainter(Coord a)
{
	gotoxy(a.first, a.second);
	putchar('@');
}


void Tui::draw()
{
	clear_win();
	
	this->xline(1, '#');
	this->yline(winx_, '#');
	this->xline(winy_, '#');
	this->yline(1, '#');
	
	game->visit(std::bind(&View::snakepainter, this, _1, _2));
	game->rabbitsVisit(std::bind(&View::rabbitpainter, this, _1));
	this->print_version();
	
	this->print_score();
	gotoxy(1,1);
	
	fflush(stdout);
}


bool compare(timeout a, timeout b)
{
	return a.first < b.first;
}


void Tui::run()
{
	char key;
	
	const nfds_t fds_size = 1;
	
	struct timespec begin_time, end_time;
	
	pollfd fds[fds_size];
	fds[0].fd = 0;
	fds[0].events = POLL_IN;
	
	
	while (true)
	{
		clock_gettime(CLOCK_REALTIME, &begin_time);
		
		int ret = poll(fds, fds_size, timeouts_.front().first);
		
		clock_gettime(CLOCK_REALTIME, &end_time);
		
		int dt = (end_time.tv_sec - begin_time.tv_sec) * 1000 + (end_time.tv_nsec - begin_time.tv_nsec) / 1000000;
		int tsize = timeouts_.size();
		for (int i = 0; i < tsize; i++)
		{
			timeout temp = timeouts_.front();
			timeouts_.pop_front();
			temp.first -= dt;
			timeouts_.push_back(temp);
		}
		
		
		if (ret == 1)
		{
			read(fds->fd, &key, 1);
			if(key == 'q')
			{
				break;
			}
			if (onkey_delegate)
			{
				
				onkey_delegate->onkey(key);
			}
		}
		tsize = timeouts_.size();
		for (int i = 0; i < tsize; i++)
		{
			timeout temp = timeouts_.front();
			timeouts_.pop_front();
			
			if (temp.first <= 0)
			{
				temp.second();
			}
			else
			{
				timeouts_.push_back(temp);
			}
		}
		draw();
	}
	gotoxy(1, 1);
}




void Tui::gotoxy(int x, int y)
{
	printf("\e[%d;%dH", y, x);
}



void Tui::clear_win()
{
	printf("\e[H\e[J");
}


int Tui::getX()
{
	return winx_;
}


int Tui::getY()
{
	return winy_;
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
	std::string str = " Score: ";
	
	std::string score = std::to_string(View::get()->game->score_);
	
	str += score;
	str += " ";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy(winx_/2 - str.length()/2 + i, winy_);
		printf("%c", str[i]);
	}
	
}


void Tui::print_version()
{
	std::string str = " Snake 1.0 ";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy(winx_ / 2 - str.length()/2 + i, 1);
		printf("%c", str[i]);
	}
}