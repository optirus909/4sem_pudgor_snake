//
// Created by Andrey Andriyaynen on 21/05/2019.
//

#include <random>
#include "AI.h"
#include "View.h"

AI::AI(Snake * s) : Control(s)
{
	View::get()->setOnAI(this);
}


void AI::onMove()
{
	Dir directions[4] = {UP, DOWN, LEFT, RIGHT};
	
	std::random_device rd;
	std::mt19937 g(rd());
	
	Coord r = View::get()->game->near(snake->body.front());
	
	snake->direction = BODY;
	
	bool ok = false;
	
	Game * insgame = View::get()->game;
	
	if(r != Coord(0,0))
	{
		int before = r.distance(snake->body.front());
		
		for (auto p: directions)
		{
			snake->direction = p;
			int next_pos = insgame->isFilled(snake->nextPos(p, snake->body.front()));
			int after = r.distance(snake->nextPos(p, snake->body.front()));
			if(after < before && (next_pos == EMPTY || next_pos == RABBIT))
			{
				ok = true;
				break;
			}
		}
	}
	
	if(!ok)
	{
		for (auto p: directions)
		{
			snake->direction = p;
			Coord c = snake->nextPos(p, snake->body.front());
			if(insgame->isFilled(c) == EMPTY)
			{
				break;
			}
		}
	}
	
}

AI::~AI()
{

}