//
// Created by Andrey Andriyaynen on 29/03/2019.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <utility>
#include <list>
#include <functional>

//#include "View.h"

struct Coord : public std::pair <int, int>
{
	using Base = std::pair<int, int>;
	using Base::Base;
};

using Rabbit = Coord;

enum Dir {BODY, UP, DOWN, LEFT, RIGHT};


class Snake
{
public:
	std::list <Coord> body;
	Dir direction;
	
	void move();
	Snake();
	~Snake();
};

using SnakePainter = std::function <void (Coord coord, Dir dir)>;
using RabbitPainter = std::function <void (Coord coord)>;

class Game
{
private:
	std::list <Snake  *> snakes;
	std::list <Rabbit> rabbits;
	
public:
	void rabbitsVisit(RabbitPainter p);
	void visit(SnakePainter p);
	void add(Snake * s);
	void move();
	void newRabbit();
	bool isFilled(Coord c);
	Game();
	~Game();
};

int getRandomNumber(int min, int max);

#endif //SNAKE_GAME_H
