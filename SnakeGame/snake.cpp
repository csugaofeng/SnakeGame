#include "snake.h"
Dot::Dot(int mPosX, int mPosY)
{
	texturePtr = &gTexture;
	this->mPosX = mPosX;
	this->mPosY = mPosY;
}


void Dot::render()
{
	texturePtr->render(mPosX, mPosY);
}

void Dot::setTexture(LTexture& texture) {
	texturePtr = &texture;
}



Snake::Snake() {
	Dot dot1(2*DOT_WIDTH, 0);
	Dot dot2(DOT_WIDTH, 0);
	Dot dot3(0, 0);
	mSnakeList.emplace_back(dot1);
	mSnakeList.emplace_back(dot2);
	mSnakeList.emplace_back(dot3);
	mHeadDirection = RIGHT;
	mHeadVelX = DOT_VEL;
	mHeadVelY = 0;
	food.setTexture(gFoodTexture);
	isDead = false;
}

Collision Snake::collisionDetection() {
	int headX = mSnakeList.front().mPosX;
	int headY = mSnakeList.front().mPosY;
	if (headX == food.mPosX && headY == food.mPosY)
		return EAT;
	if (headX < 0 || headX >= SCREEN_WIDTH || headY < 0 || headY >= SCREEN_HEIGHT) {
		isDead = true;
		return DEAD;
	}
	auto i = mSnakeList.begin();
	++i;
	for (; i != mSnakeList.end(); ++i) {
		if (headX == (*i).mPosX && headY == (*i).mPosY) {
			isDead = true;
			return DEAD;
		}
	}
	return NOTHING;
}


void Snake::generateFood() {
	if (collisionDetection() == EAT) {
		std::default_random_engine random(time(NULL));
		std::uniform_int_distribution<int> foodX(0, SCREEN_WIDTH / DOT_WIDTH - 1);
		std::uniform_int_distribution<int> foodY(0, SCREEN_HEIGHT / DOT_HEIGHT - 1);
		food.mPosX = foodX(random) * DOT_WIDTH;
		food.mPosY = foodY(random) * DOT_HEIGHT;
		
	}
	food.render();
}


void Snake::move() {
	if (!isDead) {
		int headX = mSnakeList.front().mPosX + mHeadVelX;
		int headY = mSnakeList.front().mPosY + mHeadVelY;
		Dot newdot(headX, headY);
		mSnakeList.insert(mSnakeList.begin(), newdot);
		if (collisionDetection() == EAT) {
			return;
		}
		mSnakeList.erase(--mSnakeList.end());
	}
	else {
		return;
	}
}

void Snake::handleEvent(SDL_Event & e) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			if (mHeadDirection != DOWN) {
				mHeadVelX = 0;
				mHeadVelY = -DOT_VEL;
				mHeadDirection = UP;
			}
			break;
		case SDLK_DOWN:
			if (mHeadDirection != UP) {
				mHeadVelX = 0;
				mHeadVelY = DOT_VEL;
				mHeadDirection = DOWN;
			}
			break;
		case SDLK_LEFT:
			if (mHeadDirection != RIGHT) {
				mHeadVelX = -DOT_VEL;
				mHeadVelY = 0;
				mHeadDirection = LEFT;
			}
			break;
		case SDLK_RIGHT:
			if (mHeadDirection != LEFT) {
				mHeadVelX = DOT_VEL;
				mHeadVelY = 0;
				mHeadDirection = RIGHT;
			}
			break;
		}
}

void Snake::render() {
	for (auto i : mSnakeList) {
		i.render();
	}
}

bool Snake::isEndGame()
{
	return isDead;
}

void Snake::reset() {
	mSnakeList.clear();
	Dot dot1(2 * DOT_WIDTH, 0);
	Dot dot2(DOT_WIDTH, 0);
	Dot dot3(0, 0);
	mSnakeList.emplace_back(dot1);
	mSnakeList.emplace_back(dot2);
	mSnakeList.emplace_back(dot3);
	mHeadDirection = RIGHT;
	mHeadVelX = DOT_VEL;
	mHeadVelY = 0;
	food.setTexture(gFoodTexture);
	isDead = false;
}

