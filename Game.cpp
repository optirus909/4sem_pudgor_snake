#include "Game.h"
#include "View.h"
#include "AI.h"
#include <fstream>

static std::ofstream fout("log.txt");

int SNAKETIMEOUT = 80;
int RABBITTIMEOUT = 3000;


void Game::rabbitsVisit(RabbitPainter p)
{
	//fout << "start rabbitVisit" << std::endl;
	for(const auto s: rabbits)
	{
	//	fout << "visitrabbirrabbit :x = " << s.first << " y = " << s.second << std::endl;
		p(s);
	}
	//fout << "  end rabbitVisit" << std::endl;
}

void Game::visit(SnakePainter p)
{
	//fout << "game paint before fors --------------------" << std::endl;
	//fout << "snakes count =" << snakes.size() << std::endl;
	for(const auto &s: snakes)
	{
	//	fout << "game paint for snakes" << std::endl;
		bool first = false;
		for (const auto &c: s->body)
		{
	//		fout << "game paint for bodies" << std::endl;
			p(c, first ? BODY : s->direction);
			first = true;
		}
	}
	//fout << "game paint after fors --------------------" << std::endl;
}


void Game::add(Snake * s)
{
	snakes.push_back(s);
}


Coord Game::near(Coord c)
{
	if(rabbits.size() == 0)
		return Coord(0, 0);
	
	Coord r(0,0);
	int min = rabbits.front().distance(c);
	r = rabbits.front();
	
	for(const auto s: rabbits)
	{
		if(min > s.distance(c))
		{
			min = s.distance(c);
			r = s;
		}
	}
	
	return r;
}

Coord Snake::nextPos(Dir d, Coord c)
{
	switch(d)
	{
		case UP:
			c.second--;
			break;
		case LEFT:
			c.first--;
			break;
		case DOWN:
			c.second++;
			break;
		case RIGHT:
			c.first++;
			break;
	}
	
	return c;
}


int Coord::distance(const Coord &c) const
{
	return abs(c.first - first) + abs(c.second - second);
}

void Game::move()
{
	bool all_die = true;
	//fout << "  start game move" << std::endl;
	
	for(const auto &s: snakes)
	{
		if (s->alive_)
		{
			all_die = false;
			s->move();
		}
	}
	
	if(all_die)
	{
		View::get()->~View();
	}
	
	View::get()->ai_delegate->onMove();
	View::get()->set_on_timer(SNAKETIMEOUT, std::bind(&Game::move, this));
	//fout << "  end game move" << std::endl;
}


void Snake::move()
{
	
	
	auto a = body.front();
	//fout << "      start snake move" << std::endl;
	switch(direction)
	{
		case UP:
			a.second--;
			break;
		case LEFT:
			a.first--;
			break;
		case DOWN:
			a.second++;
			break;
		case RIGHT:
			a.first++;
			break;
	}
	
	switch (View::get()->game->isFilled(a))
	{
		case RABBIT:
		{
			View::get()->game->killRabbit(a);
			View::get()->game->score_++;
			body.push_front(a);
			break;
		}
		case SNAKE:
			alive_ = false;
			break;
		case BORDER:
			alive_ = false;
			break;
		case EMPTY:
		{
			body.push_front(a);
			body.pop_back();
			break;
		}
	}
	
	
	
	//fout << "        end snake move" << std::endl;
}


void Game::killRabbit(Coord c)
{
	for(const auto s: rabbits)
	{
		if(c == s)
		{
			rabbits.remove(s);
			break;
		}
	}
}


Snake::Snake()
{
	direction = RIGHT;
	for (int i = 0; i < 2; ++i)
		body.push_back(Coord(8-i, 8));
}


int getRandomNumber(int minv, int maxv)
{
	int temp = 0;
	do
	{
		temp = rand() % maxv;
		//fout << "rand number = " << temp << std::endl;
	} while (temp < minv || temp > maxv);
	
	//fout << "               returned rand number = " << temp << std::endl;
	return temp;
}

void Game::newRabbit()
{
	//fout << "  start newRabbit" << std::endl;
	Coord * c = new Coord;
	View * v = View::get();
	v->set_on_timer(RABBITTIMEOUT, std::bind(&Game::newRabbit, this));
	
	while (true)
	{
		c->first  = getRandomNumber(2, v->getX() - 1);
		c->second = getRandomNumber(2, v->getY() - 1);
		
		if (isFilled(*c) == EMPTY)
		{
			rabbits.push_back(*c);
			break;
		}
	}
	
	//fout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<rabbits_cnt = " << rabbits.size() << std::endl;
	
	//fout << "    end newRabbit" << std::endl;
}


int Game::isFilled(Coord c)
{
	for(const auto &s: snakes)
	{
		for (const auto &sbody: s->body)
		{
			if (c == sbody)
				return SNAKE;
		}
	}
	
	for(const auto s: rabbits)
	{
		if(c == s)
			return RABBIT;
	}
	
	if((c.first == 1) || (c.second == 1) || (c.first == View::get()->getX()) || (c.second == View::get()->getY()))
		return BORDER;
	
	return EMPTY;
}


Game::Game()
{
	srand(time(NULL));
	
	View * v = View::get();
	v->set_on_timer(SNAKETIMEOUT, std::bind(&Game::move, this));
	v->set_on_timer(RABBITTIMEOUT, std::bind(&Game::newRabbit, this));
}

Game::~Game()
{

}

Snake::~Snake()
{}