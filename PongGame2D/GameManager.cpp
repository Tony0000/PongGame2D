#include <cstdlib>
#include "GameManager.h"

GameManager::GameManager(int w, int h)
{
	quit = false;
	p1up = 'w'; p1dw = 's';
	p2up = '['; p2dw = ']';
	WINDOW_WIDTH = w;
	WINDOW_HEIGHT = h;
	SCORE_P1 = SCORE_P2 = 0;
	ball = new Ball(w / 2, h / 2);
	p1 = new Paddle(0, h / 2 - 3);
	p1 = new Paddle(w, h / 2 - 3);
}

GameManager::~GameManager()
{
	delete ball, p1, p2;
}

void GameManager::scoreUp(Paddle *p)
{
	if (p == p1)
		SCORE_P1++;
	else
		SCORE_P2++;

	ball->reset();
	p1->reset();
	p2->reset();
}

void GameManager::logic()
{
	//TODO: game logic
}

void GameManager::draw()
{
	system("cls");
	//TODO: draw game screen
}