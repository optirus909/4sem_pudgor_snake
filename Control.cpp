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
	printf("\e[%d;%dH", 50, 50);
	printf("%c", key);
}

KeyPressable::~KeyPressable()
{

}


Control::~Control()
{}


Human::~Human()
{}