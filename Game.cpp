#include "Game.h"
#include "View.h"
#include <fstream>

static std::ofstream fout("log.txt");

int SNAKETIMEOUT = 100;

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
		s->move();///TODO make snake move with timer
	
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
	direction = UP;
	for (int i = 0; i < 20; ++i)
		body.push_back(Coord(33, 3+i));
		
	
	//body.push_back(Coord(33, 5));///TODO rabbits
	//body.push_back(Coord(34, 5));///TODO check memory, because there is sig fault 11 on sigwinch
}


Game::Game()
{
	View::get()->set_on_timer(SNAKETIMEOUT, std::bind(&Game::move, this));
}

Game::~Game()
{}

Snake::~Snake()
{}