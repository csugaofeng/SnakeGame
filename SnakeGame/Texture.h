#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
class LTexture {
public:
	LTexture();
	~LTexture();
	bool loadFromFile(std::string path);
#ifdef SDL_TTF_H_
	bool loadFromRenderedText(std::string texttureText, SDL_Color textColor);
#endif
	//Deallocates texture
	void free();
	void render(int x, int y, SDL_Rect * clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Renders texture at given point
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setAlpha(Uint8 alpha);
	void setBlenMode(SDL_BlendMode blending);
	int getWidth();
	int getHeight();
private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};