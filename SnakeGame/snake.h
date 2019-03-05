#pragma once
#include <SDL.h>
#include <list>
#include <random>
#include <time.h>
#include "Texture.h"
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern LTexture gTexture;
extern LTexture gFoodTexture;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int DOT_WIDTH;
extern const int DOT_HEIGHT;
enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
enum Collision {
	EAT,
	DEAD,
	NOTHING
};


class Dot {
public:
	Dot(int x = 0, int y = 0);
	void render();
	void setTexture(LTexture& texture);
	int mPosX;
	int mPosY;
	LTexture* texturePtr;
	//The velocity of the dot
};

class Snake  {
public:
	Snake();
	Collision collisionDetection();
	void generateFood();
	void move();
	void handleEvent(SDL_Event& e);
	void render();
	bool isEndGame();
	void reset();
private:
	//Collision mstate = NOTHING;
	std::list<Dot> mSnakeList;
	Direction mHeadDirection;
	static const int DOT_VEL = 20;
	Dot food;
	int mHeadVelX;
	int mHeadVelY;
	bool isDead;
};