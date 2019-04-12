//
// Created by Andrey Andriyaynen on 05/04/2019.
//

#ifndef SNAKE_CONTROL_H
#define SNAKE_CONTROL_H

#include "View.h"
#include "Game.h"

class Control
{
public:
	Snake * snake;
	void setmodel(Snake * s)
	{
		snake = s;
	}
	
	Control(Snake * s);
	~Control();
};

class Human : public Control, public KeyPressable
{
public:
	void onkey(int key);
	Human(Snake * s);
	~Human();
};

#endif //SNAKE_CONTROL_H