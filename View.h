//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#ifndef SNAKE_VIEW_H
#define SNAKE_VIEW_H

#include "Game.h"

class View
{
public:
	void virtual draw () = 0;
	void virtual run  () = 0;
	void virtual resize()= 0;
	void virtual snakepainter(Coord a, Dir d) = 0;
	virtual ~View()      = 0;
	
	static View *  get();
	static View * inst;
	
	Game * game;
	
	void set_model(Game * g)
	{
		game = g;
	}
};


#endif //SNAKE_VIEW_H
