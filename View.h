//
// Created by Andrey Andriyaynen on 15/03/2019.
//

#ifndef SNAKE_VIEW_H
#define SNAKE_VIEW_H


class View
{
public:
	void virtual draw () = 0;
	void virtual run  () = 0;
	virtual ~View() = 0;
};


#endif //SNAKE_VIEW_H
