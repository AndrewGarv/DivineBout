#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "GameFlow.h"
#include "Textures.h"
#include "Sprites.h"
#include "GameTimer.h"
class Dummy
{
public:
	static const int MaxVel = 15;
	static const int MaxJmp = 370;
	static const int PlrW = 0;
	static const int PlrH = 0;
	SDL_Rect StandingSprite[1];
	int DmyHealth;
	SDL_Rect AttackSprite[1];
	SDL_Rect MovingSprite[1];
	SDL_RendererFlip type;
	Dummy(const GameFlow& OBJ);
	void movement(const GameFlow& OBJ, int PlayerX, int PlayerY);
	void left(const GameFlow& OBJ);
	void right(const GameFlow& OBJ);
	void reaction();
	std::vector<SDL_Rect> attack(const GameFlow& OBJ);
	void render(const GameFlow& OBJ);
	Textures Dmy;

private:
	int spdX, spdY;
	int posX, posY;
	std::vector<SDL_Rect> AtkHitbox;
	enum State { Moving, Attacking, Standing };
	State current;
	GameTimer DummyTime;
};

