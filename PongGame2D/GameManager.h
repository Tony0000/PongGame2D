#pragma once
#include<iostream>
#include "Ball.h"
#include "Paddle.h"

class GameManager
{
private:
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
	int SCORE_P1, SCORE_P2;
	char p1up, p1dw, p2up, p2dw;
	bool quit;
	Ball *ball;
	Paddle *p1;
	Paddle *p2;


public:
	GameManager(int w, int h);
	~GameManager();
	void scoreUp(Paddle *p);
	void logic();
	void draw();
};