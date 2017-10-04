#include "Ball.h"

#include <iostream>
#include <cstdlib>

using namespace std;

Ball::Ball(int px, int py) {
	originX = px;
	originY = py;
	x = px;
	y = py;
	direction = dir::STOP;
}

void Ball::reset() {
	x = originX;
	y = originY;
	direction = dir::STOP;
}

void Ball::changeDirection(dir d) {
	direction = d;
}

void Ball::randomDirection() {
	direction = (dir)((rand() % 6) + 1);
}

inline int Ball::getX() { return x; }
inline int Ball::getY() { return y; }
inline dir Ball::getDirection() { return direction; }

void Ball::move() {
	switch (direction)
	{
	case dir::STOP:
		break;
	case dir::LEFT:
		x--;
		break;
	case dir::RIGHT:
		x++;
		break;
	case dir::UPLEFT:
		x--; y--;
		break;
	case dir::DOWNLEFT:
		x--; y++;
		break;
	case dir::UPRIGHT:
		x++; y--;
		break;
	case dir::DOWNRIGHT:
		x++; y++;
		break;
	default:
		break;
	}
}

void Ball::describe() {
	std::cout << "Ball [" << x << "," << y << "][" << direction << "]" << std::endl;
}

