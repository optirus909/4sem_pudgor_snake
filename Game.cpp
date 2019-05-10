//
// Created by Andrey Andriyaynen on 29/03/2019.
//

#include <fstream>
#include "Game.h"
#include "View.h"

static std::ofstream fout("log.txt");

void Game::visit(SnakePainter p)
{
	fout << "game paint before fors --------------------" << std::endl;
	fout << "snakes count =" << snakes.size() << std::endl;
	for(const auto &s: snakes)
	{
		fout << "game paint for snakes" << std::endl;
		bool first = false;
		for (const auto &c: s->body)///ditch - see &
		{
			fout << "game paint for bodies" << std::endl;
			p(c, first ? BODY : s->direction);
			first = true;
		}
	}
	fout << "game paint after fors --------------------" << std::endl;
}


void Game::add(Snake * s)
{
	snakes.push_back(s);
}


void Game::move()
{
	for(const auto &s: snakes)
		s->move();///TODO make snake move with timer
}


void Snake::move()
{
	auto a = body.front();
	
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
}


Snake::Snake()
{
	direction = UP;
	for (int i = 0; i < 10; ++i)
		body.push_back(Coord(33, 3+i));
		
	
	//body.push_back(Coord(33, 5));///TODO rabbits
	//body.push_back(Coord(34, 5));///TODO check memory, because there is sig fault 11 on sigwinch
}


Game::Game()
{
	int SNAKETIMEOUT = 500;
	View::get()->set_on_timer(SNAKETIMEOUT, std::bind(&Game::move, this));
	
}

Game::~Game()
{}

Snake::~Snake()
{}