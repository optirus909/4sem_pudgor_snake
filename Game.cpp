//
// Created by Andrey Andriyaynen on 29/03/2019.
//

#include <fstream>
#include "Game.h"

static std::ofstream fout("log.txt");

void Game::visit(SnakePainter p)
{
	fout << "game paint before fors --------------------" << std::endl;
	fout << "snakes count =" << snakes.size() << std::endl;
	for(const auto &s: snakes)
	{
		fout << "game paint for snakes" << std::endl;
		bool first = false;
		for (const auto &c: s->body)
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


Game::Game()
{
	//auto a = new Snake;
	//snakes.push_back(a);
	//fout << "dir1 = "<< snakes.end()->direction << std::endl;
	Snake s;
	snakes.push_back(&s);
}


Game::~Game()
{
}


Snake::Snake()
{
	direction = UP;
	body.push_back(Coord(33, 3));
	body.push_back(Coord(33, 4));
	body.push_back(Coord(33, 5));///TODO rabbits
	body.push_back(Coord(34, 5));
}


Snake::~Snake()
{}