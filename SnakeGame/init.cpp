#include "init.h"

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Eroor:" << SDL_GetError() << std::endl;
		success = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//SDL_WINDOW_SHOWN makes sure the window is shown when it is created.
		gWindow = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
			success = false;
		}
		else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
#ifdef SDL_TTF_H_
				if (TTF_Init() == -1) {
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
#endif // _SDL_TTF_H
			}
		}
	}
	return success;
}

bool load()
{
	bool success = true;
	if (!gTexture.loadFromFile("src/dot.bmp")) {
		printf("Failed to load picture!\n");
		success = false;
	}
	else if (!gFoodTexture.loadFromFile("src/food.png")) {
			printf("Failed to load picture!\n");
			success = false;
		}
	else {
		gFont = TTF_OpenFont("src/lazy.ttf", 28);
		if (gFont == NULL) {
			printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
		}
		else {
			SDL_Color textColor = { 0,0,0 };
			if (!gEndTexture.loadFromRenderedText("Game Over!!!'R' to restart or  'ESC' to EXIT.", textColor)) {
				printf("Failed to render text texture!\n");
				success = false;
			}
		}
	}
	return success;
}

void close() {
		//Destroy window    
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		gRenderer = NULL;

		//Quit SDL subsystems
#ifdef _SDL_MIXER_H
		Mix_Quit();
#endif // _SDL_MIXER_H
		IMG_Quit();
		SDL_Quit();
}
