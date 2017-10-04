#include "Paddle.h"

Paddle::Paddle() {
	x = y = 0;
}

Paddle::~Paddle()
{
}

Paddle::Paddle(int px, int py) : Paddle() {
	originY = py;
	originX = px;
	y = py;
	x = px;
};

void Paddle::reset() { y = originY; x = originX; }
int Paddle::getY() { return y; }
int Paddle::getX() { return x; }
void Paddle::moveUp() { y++; }
void Paddle::moveDown() { y--; }

void Paddle::describe() {
	std::cout << "Paddle [" << x << "," << y << "]" << endl;
}