#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include <iostream>
#include <SDL_ttf.h>
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern LTexture gTexture;
extern LTexture gFoodTexture;
extern TTF_Font* gFont;
extern LTexture gEndTexture;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

bool init();
bool load();
void close();