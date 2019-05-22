//
// Created by Andrey Andriyaynen on 21/05/2019.
//

#ifndef SNAKE_AI_H
#define SNAKE_AI_H

#include "Control.h"

enum Cell {RABBIT, SNAKE, EMPTY, BORDER};

class AI : public Control
{
public:
	void onMove();
	Snake * s;
	void setmodel(Snake * s);
	
	AI(Snake * s);
	~AI();
};


#endif //SNAKE_AI_H
