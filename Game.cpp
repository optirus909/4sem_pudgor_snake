#include "Game.h"
#include "View.h"
#include <fstream>

static std::ofstream fout("log.txt");

int SNAKETIMEOUT = 200;
int RABBITTIMEOUT = 500;

void Game::rabbitsVisit(RabbitPainter p)
{
	fout << "start rabbitVisit" << std::endl;
	for(const auto s: rabbits)
	{
		fout << "visitrabbirrabbit :" << s.first << " " << s.second << std::endl;
		p(s);
	}
	fout << "  end rabbitVisit" << std::endl;
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


void Game::move()
{
	fout << "  start game move" << std::endl;
	
	for(const auto &s: snakes)
		s->move();
	
	View::get()->set_on_timer(SNAKETIMEOUT, std::bind(&Game::move, this));
	
	fout << "  end game move" << std::endl;
}


void Snake::move()
{
	auto a = body.front();
	fout << "      start snake move" << std::endl;
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
	
	body.push_front(a);
	body.pop_back();
	
	fout << "        end snake move" << std::endl;
}


Snake::Snake()
{
	direction = RIGHT;
	for (int i = 0; i < 3; ++i)
		body.push_back(Coord(8-i, 8));
}


void Game::newRabbit()
{
	fout << "  start newRabbit" << std::endl;
	srand(time(NULL));
	Coord * c = new Coord;
	View * v = View::get();
	v->set_on_timer(RABBITTIMEOUT, std::bind(&Game::newRabbit, this));
	
	while (true)
	{
		c->first  = getRandomNumber(2, v->getX() - 1);
		c->second = getRandomNumber(2, v->getY() - 1);
		
		if (!isFilled(*c))
		{
			rabbits.push_back(*c);
			break;
		}
	}
	
	fout << "    end newRabbit" << std::endl;
}


bool Game::isFilled(Coord c)
{
	for(const auto &s: snakes)
	{
		for (const auto &sbody: s->body)
		{
			if (c == sbody)
				return false;
		}
	}
	
	for(const auto s: rabbits)
	{
		if(c == s)
			return false;
	}
	
	return true;
}


int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


Game::Game()
{
	View * v = View::get();
	v->set_on_timer(SNAKETIMEOUT, std::bind(&Game::move, this));
	v->set_on_timer(RABBITTIMEOUT, std::bind(&Game::newRabbit, this));
}

Game::~Game()
{}

Snake::~Snake()
{}