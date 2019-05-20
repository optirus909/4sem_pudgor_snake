//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#ifndef SNAKE_VIEW_H
#define SNAKE_VIEW_H

#include <functional>
#include "Game.h"

using timeout_fn = std::function<void ()>;
using timeout = std::pair <int, timeout_fn>;

class KeyPressable ///TODO move to model, because it makes cross dependencies
{
public:
	void virtual onkey(int key) = 0;
	virtual ~KeyPressable()     = 0;
};


class View
{
public:
	void virtual draw () = 0;
	void virtual run  () = 0;
	void virtual resize()= 0;
	void virtual snakepainter(Coord a, Dir d) = 0;
	void virtual rabbitpainter(Coord a) = 0;
	virtual ~View()      = 0;
	
	//static View * inst_;
	static View * get();
	static View * inst;
	
	Game * game;
	
	KeyPressable * onkey_delegate;
	
	int virtual getX() = 0;
	int virtual getY() = 0;
	
	void setonkey(KeyPressable * p)
	{
		onkey_delegate = p;
	}
	
	void set_on_timer(int time, timeout_fn t)
	{
		timeout temp;
		temp.first = time;
		temp.second = t;
		timeouts_.push_back(temp);
	}
	
	std::list <timeout> timeouts_;
	
	void set_model(Game * g)
	{
		game = g;
	}
};


#endif //SNAKE_VIEW_H