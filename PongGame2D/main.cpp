#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#ifdef main
#undef main
#endif
using namespace std;

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

static const int screenWidth = 800;
static const int screenHeight = 600;
static const int scoreWidth = 100;
static const int scoreHeight = 167;
static const int offset = 100;
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

int main(int argc, char **argv)
{
	int p1, p2;
	p1 = p2 = 0;

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Create a SDL window
	SDL_Window *window = SDL_CreateWindow("Hello, SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

	// Create a renderer (accelerated and in sync with the display refresh rate)
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Initialize support for loading PNG and JPEG images
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	SDL_Texture * imgScoreP1 = initialize_texture_from_file(scoreImg[p1], renderer);
	SDL_Texture * imgScoreP2 = initialize_texture_from_file(scoreImg[p2], renderer);

	int image_width, image_height;

	// Define where on the "screen" we want to draw the texture
	SDL_Rect scoreP1;
	SDL_Rect scoreP2;

	scoreP1.x = screenWidth / 2 - offset - scoreWidth;
	scoreP1.y = 10;
	scoreP1.w = scoreWidth;
	scoreP1.h = scoreHeight;

	SDL_Rect texture_destination;

	scoreP2.x = screenWidth / 2 + offset;
	scoreP2.y = 10;
	scoreP2.w = scoreWidth;
	scoreP2.h = scoreHeight;

	//Players paddle
	SDL_Rect r1;
	r1.x = 0;
	r1.y = screenHeight / 2;
	r1.w = 20;
	r1.h = 60;

	SDL_Rect r2;
	r2.x = screenWidth - 20;
	r2.y = screenHeight / 2;
	r2.w = 20;
	r2.h = 60;

	bool running = true;
	SDL_Event event;
	while (running)
	{
		// Process events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case 'x':
					case 'X':
						imgScoreP1 = initialize_texture_from_file(scoreImg[++p1], renderer);
						break;
					case 'm':
					case 'M':
						imgScoreP2 = initialize_texture_from_file(scoreImg[++p2], renderer);
						break;
				}
			}
		}

		// Clear screen
		SDL_RenderClear(renderer);

		// Draw
		SDL_RenderCopy(renderer, imgScoreP1, NULL, &scoreP1);
		SDL_RenderCopy(renderer, imgScoreP2, NULL, &scoreP2);

		// Show what was drawn
		SDL_RenderPresent(renderer);
	}

	// Release resources
	SDL_DestroyTexture(imgScoreP1);
	SDL_DestroyTexture(imgScoreP2);
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
	SDL_Surface *image = IMG_Load(file_name);
	SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	return image_texture;
}