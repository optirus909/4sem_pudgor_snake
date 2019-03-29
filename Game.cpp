//
// Created by Andrey Andriyaynen on 29/03/2019.
//

#include "Game.h"
#include <fstream>

static std::ofstream fout("log.txt");

void Game::paint(SnakePainter p)
{
	fout << "game paint before fors --------------------" << std::endl;
	fout << "snakes count =" << snakes.size() << std::endl;
	for(const auto &s: snakes)
	{
		fout << "game paint for snakes" << std::endl;
		bool first = false;
		for (const auto &c: s.body)
		{
			fout << "game paint for bodies" << std::endl;
			p(c, first ? BODY : s.direction);
			first = true;
		}
	}
	fout << "game paint after fors --------------------" << std::endl;
}

Game::Game()
{
	//auto a = new Snake;
	//snakes.push_back(a);
	//fout << "dir1 = "<< snakes.end()->direction << std::endl;
	snakes.push_back(Snake());
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