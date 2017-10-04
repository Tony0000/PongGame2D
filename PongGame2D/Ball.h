#pragma once
enum dir {
	STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3,
	RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6
};

class Ball
{
private:
	int x, y;
	int originX, originY;

	dir direction;

public:
	Ball(int px, int py);
	void reset();
	inline int getY();
	inline int getX();
	inline dir getDirection();
	void randomDirection();
	void changeDirection(dir d);
	void move();
	void describe();
};