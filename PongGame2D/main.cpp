#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#ifdef main
#undef main
#endif
using namespace std;

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int SCORE_WIDTH = 70;
static const int SCORE_HEIGHT = 130;
static const int PADDLE_WIDTH = 15;
static const int PADDLE_HEIGHT = 70;
static const int BALL_SIZE = 15;
static int GAME_OVER = 4;
int BALL_MOVEMENT_X = 1;
int BALL_MOVEMENT_Y = 1;
static const int offset = 100;
static int p1, p2;
static bool running = true;
static int image_width, image_height;
static bool keyPressed[4]{false, false, false, false};

enum dir {
	STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3,
	RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6
};

SDL_Rect paddlePlayer1;
SDL_Rect paddlePlayer2;
SDL_Rect scoreP1;
SDL_Rect scoreP2;
SDL_Rect ball;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *imgScoreP1, *imgScoreP2;
std::vector<SDL_Event> frameEvents;

static const char scoreImg[10][100]{
	"img/zero.png",
	"img/one.png",
	"img/two.png",
	"img/three.png",
	"img/four.png",
	"img/five.png",
	"img/six.png",
	"img/seven.png",
	"img/eight.png",
	"img/nine.png",
};

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);
void init();
void loadGame();
void draw();
void close();
void gameLogic();
void resetPositions();
SDL_Texture * resetScores(int *points);
void keyboardInput();
void processEvents(SDL_Event event);

void playerMoveUp(SDL_Rect *paddle) {
	paddle->y -= 10;
}

void playerMoveDown(SDL_Rect *paddle) {
	paddle->y += 10;
}

int main(int argc, char **argv)
{
	init();
	loadGame();
	resetPositions();

	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			frameEvents.push_back(event);
		}
		processEvents(event);
		keyboardInput();
		gameLogic();
		ball.x += BALL_MOVEMENT_X * 5;
		ball.y += BALL_MOVEMENT_Y * 5;
		draw();
	}

	close();

	return 0;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
	SDL_Surface *image = IMG_Load(file_name);
	SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	return image_texture;
}

void processEvents(SDL_Event event) {

	while (!frameEvents.empty())
	{
		event = frameEvents.back();
		frameEvents.pop_back();

		if (event.type == SDL_QUIT)
		{
			running = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case 'a':
			case 'A':
				keyPressed[0] = true;
				break;
			case 'z':
			case 'Z':
				keyPressed[1] = true;
				break;
			case '[':
				keyPressed[2] = true;
				break;
			case ']':
				keyPressed[3] = true;
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym)
			{
			case 'a':
			case 'A':
				keyPressed[0] = false;
				break;
			case 'z':
			case 'Z':
				keyPressed[1] = false;
				break;
			case '[':
				keyPressed[2] = false;
				break;
			case ']':
				keyPressed[3] = false;
				break;
			}
		}
	}
}

void keyboardInput()
{

	if (keyPressed[0] == true) {
		if(paddlePlayer1.y > 0)
			playerMoveUp(&paddlePlayer1);
	}else if (keyPressed[1] == true) {
		if(paddlePlayer1.y < SCREEN_HEIGHT - PADDLE_HEIGHT)
			playerMoveDown(&paddlePlayer1);
	}

	if (keyPressed[2] == true) {
		if (paddlePlayer2.y > 0)
			playerMoveUp(&paddlePlayer2);
	}else if (keyPressed[3] == true) {
		if (paddlePlayer2.y < SCREEN_HEIGHT - PADDLE_HEIGHT)
			playerMoveDown(&paddlePlayer2);
	}

}

void gameLogic() 
{
	//TODO: if ball collides with floor or ceiling
	if (ball.y + BALL_SIZE == SCREEN_HEIGHT)
		BALL_MOVEMENT_Y *= -1;
	else if (ball.y == 0)
		BALL_MOVEMENT_Y *= -1;
	//TODO: if ball collides with paddles turn direction
	if ((ball.x == paddlePlayer1.x + PADDLE_WIDTH) && (ball.y + BALL_SIZE > paddlePlayer1.y && ball.y < paddlePlayer1.y + PADDLE_HEIGHT)) {
		BALL_MOVEMENT_X *= -1;
	}
	else if ((ball.x + BALL_SIZE == paddlePlayer2.x) && (ball.y + BALL_SIZE > paddlePlayer2.y && ball.y < paddlePlayer2.y + PADDLE_HEIGHT))
		BALL_MOVEMENT_X *= -1;
	//TODO: if ball reaches the goal reset game
	else if (ball.x == SCREEN_WIDTH - 10)
		imgScoreP1 = resetScores(&p1);
	//TODO: Change direction
	else if (ball.x == 0)
		imgScoreP2 = resetScores(&p2);

}

SDL_Texture * resetScores(int *points) {
	if (*(points) == GAME_OVER) {
		p1 = p2 = 0;
		imgScoreP1 = initialize_texture_from_file(scoreImg[p1], renderer);
		imgScoreP2 = initialize_texture_from_file(scoreImg[p2], renderer);
		cout << "Game rebooted! " << endl;

		cout << "player 1: " << p1 << " | player 2: " << p2 << endl;
		resetPositions();

		return initialize_texture_from_file(scoreImg[0], renderer);
	}
	else {
		SDL_Texture * score;
		score = initialize_texture_from_file(scoreImg[++(*points)], renderer);
		cout << "player 1: " << p1 << " | player 2: " << p2 << endl;
		resetPositions();

		return score;
	}
}


void resetPositions()
{
	//Ball 
	ball.x = SCREEN_WIDTH / 2;
	ball.y = SCREEN_HEIGHT / 2;
	ball.w = BALL_SIZE;
	ball.h = BALL_SIZE;

	//Players paddle
	paddlePlayer1.x = 0;
	paddlePlayer1.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
	paddlePlayer1.w = PADDLE_WIDTH;
	paddlePlayer1.h = PADDLE_HEIGHT;

	paddlePlayer2.x = SCREEN_WIDTH - PADDLE_WIDTH;
	paddlePlayer2.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
	paddlePlayer2.w = PADDLE_WIDTH;
	paddlePlayer2.h = PADDLE_HEIGHT;

}

void init() 
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a SDL window
	window = SDL_CreateWindow("Pong 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

	// Create a renderer (accelerated and in sync with the display refresh rate)
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void loadGame()
{
	p1 = p2 = 0;
	imgScoreP1 = initialize_texture_from_file(scoreImg[p1], renderer);
	imgScoreP2 = initialize_texture_from_file(scoreImg[p1], renderer);
	// Initialize support for loading PNG and JPEG images
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	// Define where on the "screen" to draw the score images
	scoreP1.x = SCREEN_WIDTH / 2 - offset - SCORE_WIDTH;
	scoreP1.y = 10;
	scoreP1.w = SCORE_WIDTH;
	scoreP1.h = SCORE_HEIGHT;

	scoreP2.x = SCREEN_WIDTH / 2 + offset;
	scoreP2.y = 10;
	scoreP2.w = SCORE_WIDTH;
	scoreP2.h = SCORE_HEIGHT;
}

void draw()
{
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//Render the ball and players' paddle
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball);
	SDL_RenderFillRect(renderer, &paddlePlayer1);
	SDL_RenderFillRect(renderer, &paddlePlayer2);

	// Draw score images
	SDL_RenderCopy(renderer, imgScoreP1, NULL, &scoreP1);
	SDL_RenderCopy(renderer, imgScoreP2, NULL, &scoreP2);

	// Show what was drawn
	SDL_RenderPresent(renderer);
}

void close()
{
	// Release resources
	SDL_DestroyTexture(imgScoreP1);
	SDL_DestroyTexture(imgScoreP2);
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}