#include <SDL.h>
#include "init.h"
#include "Texture.h"
#include "snake.h"
#include "Timer.h"
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gTexture;
LTexture gFoodTexture;
LTexture gEndTexture;
TTF_Font* gFont = NULL;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int DOT_WIDTH = 20;
const int DOT_HEIGHT = 20;
const int TIME_PER_FRAME = 120;

int main(int argc, char* argv[]) {
	init();
	load();
	Snake snake;
	LTimer timer;
	bool quit = false;
	SDL_Event e;
	while (!quit) {
		timer.start();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				break;
			}
			else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				if (snake.isEndGame() && e.key.keysym.sym == SDLK_r) {
					snake.reset();
					printf("r is pressed");
					break;
				}
				else if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT) {
					snake.handleEvent(e);
					break;
				}
				else if (snake.isEndGame() && e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
					break;
				}
			}

		}
		snake.move();

		SDL_SetRenderDrawColor(gRenderer, 0xff, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		if (snake.isEndGame()) {
			gEndTexture.render((SCREEN_WIDTH - gEndTexture.getWidth()) / 2, (SCREEN_HEIGHT - gEndTexture.getHeight()) / 2);
		}
		snake.generateFood();
		snake.render();
		SDL_RenderPresent(gRenderer);
		int time = timer.getTicks();
		if (time < TIME_PER_FRAME) {
			SDL_Delay(TIME_PER_FRAME - time);
		}
	}
	close();
	return 0;
}