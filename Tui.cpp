//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#include <sys/ioctl.h>
#include <signal.h>
#include <stdio.h>
#include <string>
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
	tcsetattr(0, TCSAFLUSH, &a);
	
	resize();
	
	onsig();
}



Tui::~Tui()
{
	//printf("\n");
	resize();
	clear_win();
	
	fout << "started - Tui::dtor" << std::endl;
	
	std::string str = "Bye!\n";
	
	for (int i = 0; i < str.length(); ++i)
	{
		gotoxy((winx_ - str.length())/2 + i, winy_/2);
		printf("%c", str[i]);
	}
	
	tcsetattr(0, TCSANOW, &old_);
	
	gotoxy(1, winy_);
	
	//fout << "ended - Tui::dtor" << std::endl;
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


void hdl(int m)
{
	//static int count = 0;
	View * v = View::get();
	v->resize();
	fout << "    resize draw start" << std::endl;
	v->draw();
	fout << "    resize draw start" << std::endl;
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
	
	//fout << "snake paint start" << std::endl;
	game->visit(std::bind(&View::snakepainter, this, _1, _2));
	//fout << "snake paint end\n" << std::endl;
	this->print_version();
	
	this->print_score();
	gotoxy(1,1);
	//printf("x = %d, y = %d\n", winx_, winy_);
	
	fflush(stdout);
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
		
		int ret = poll(fds, fds_size, timeout_.first);
		
		clock_gettime(CLOCK_REALTIME, &end_time);
		
		int dt = (end_time.tv_sec - begin_time.tv_sec) * 1000 + (end_time.tv_nsec - begin_time.tv_nsec) / 1000000;
		fout << "timeout = " << timeout_.first << " ";
		fout << "dt = " << dt << " ";
		timeout_.first -= dt;
		fout << "timeout - dt = " << timeout_.first << " " << std::endl;
		
		if(ret < 0)
		{
			fout << "poll : Achtung!, ret = " << ret << std::endl;
			break;
		}
		
		/*if (ret == 0)
		{
			fout << "start timer event" << std::endl;
			timeout_.second;
		}*/
		else if (ret == 1)
		{
			read(fds->fd, &key, 1);
			if(key == 'q')
				break;
			if (onkey_delegate)
			{
				
				fout << "----------------------------run - key catched" << std::endl;
				onkey_delegate->onkey(key);
			}
		}
		
		if (timeout_.first <= 0)
		{
			fout << "start timer event" << std::endl;
			//timeout_.second;
			game->move();
			//dwset_on_timer(200, timeout_.second);
			fout << "end   timer event" << std::endl;
		}
		// ??game->move();
		this->draw();
		fout << "drawing" << std::endl;
	}
	fout << "exit" << std::endl;
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
	fout << "  resize start" << std::endl;
	struct winsize w_size;
	
	ioctl(1, TIOCGWINSZ, &w_size);
	
	winy_ = w_size.ws_row;
	winx_ = w_size.ws_col;
	
	clear_win();
	fout << "  resize finish" << std::endl;
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