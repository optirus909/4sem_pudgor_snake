//
// Created by Andrey Andriyaynen on 29/03/2019.
//

#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <utility>
#include <list>
#include <functional>

struct Coord : public std::pair <int, int>
{
	using Base = std::pair<int, int>;
	int distance(const Coord &c) const;
	using Base::Base;
};

using Rabbit = Coord;

enum Dir {BODY, UP, DOWN, LEFT, RIGHT};
enum Cell {RABBIT, SNAKE, EMPTY, BORDER};

class Snake
{
public:
	std::list <Coord> body;
	Dir direction;
	bool alive_ = true;
	
	Coord nextPos(Dir d, Coord c);
	
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
	int score_ = 0;
	
	void rabbitsVisit(RabbitPainter p);
	void visit(SnakePainter p);
	void add(Snake * s);
	void move();
	void newRabbit();
	void killRabbit(Coord c);
	int isFilled(Coord c);
	Coord near(Coord c);
	Game();
	~Game();
};

int getRandomNumber(int minv, int maxv);

#endif //SNAKE_GAME_H
