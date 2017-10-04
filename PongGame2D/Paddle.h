#pragma once
#include <iostream>

using namespace std;

class Paddle
{
private:
	int x, y;
	int originX, originY;

public:
	Paddle();
	~Paddle();
	Paddle(int px, int py);
	void reset();
	int getY();
	int getX();
	void moveUp();
	void moveDown();
	void describe();
};