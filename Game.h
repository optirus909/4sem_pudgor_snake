//
// Created by Andrey Andriyaynen on 29/03/2019.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <utility>
#include <list>
#include <functional>

using Coord = std::pair <int, int>;

using Rabbit = Coord;

enum Dir {BODY, UP, DOWN, LEFT, RIGHT};


class Snake
{
public:
	std::list <Coord> body;
	Dir direction;
	
	Snake();
	~Snake();
};


using SnakePainter = std::function <void (Coord coord, Dir dir)>;


class Game
{
private:
	std::list <Snake  *> snakes;
	std::list <Rabbit *> rabbits;
	
public:
	void visit(SnakePainter p);
	void add(Snake * s);
	Game();
	~Game();
};


#endif //SNAKE_GAME_H
