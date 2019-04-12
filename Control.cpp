//
// Created by Andrey Andriyaynen on 05/04/2019.
//


#include "Control.h"
#include "View.h"

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
			snake->direction = UP;
			break;
		case 'a':
			snake->direction = LEFT;
			break;
		case 's':
			snake->direction = DOWN;
			break;
		case 'd':
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