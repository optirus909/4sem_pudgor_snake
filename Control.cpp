//
// Created by Andrey Andriyaynen on 05/04/2019.
//


#include "Control.h"

Control::Control(Snake *s)
{
	snake = s;
}


Human::Human(Snake * s) : Control(s)
{
	View::get()->setonkey(this);
}


void Human::onkey(int key)
{
	switch(key)
	{
		case 'w':
			if(snake->direction != DOWN)
				snake->direction = UP;
			break;
		case 'a':
			if(snake->direction != RIGHT)
				snake->direction = LEFT;
			break;
		case 's':
			if(snake->direction != UP)
				snake->direction = DOWN;
			break;
		case 'd':
			if(snake->direction != LEFT)
				snake->direction = RIGHT;
			break;
	}
	//printf("\e[%d;%dH", 50, 50);
	//printf("%c", key);
}

KeyPressable::~KeyPressable()
{}


Control::~Control()
{}


Human::~Human()
{}