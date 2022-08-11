#include "Dummy.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>

Dummy::Dummy(const GameFlow& OBJ)
{
	Dmy.loadTex("DummyEnemy.png", OBJ);
	DummyTime.Begin();
	posX = 25;
	posY = 500;
	spdX = 0;
	spdY = 0;
	DmyHealth = 1000;
	AtkHitbox.resize(1);
	//Standing Sprite initialized
	StandingSprite[0].x = 1;
	StandingSprite[0].y = 1;
	StandingSprite[0].w = 111;
	StandingSprite[0].h = 131;
	//Attack Sprite initialized
	AttackSprite[0].x = 114;
	AttackSprite[0].y = 1;
	AttackSprite[0].h = 143;
	AttackSprite[0].w = 103;
	//Moving Sprite initialized
	MovingSprite[0].x = 1;
	MovingSprite[0].y = 146;
	MovingSprite[0].h = 152;
	MovingSprite[0].w = 101;
}

void Dummy::movement(const GameFlow& OBJ, int PlayerX, int PlayerY)
{
	if(DummyTime.getTicks() % 8000 == 0)
		if (posX - PlayerX > 5)
		{
			left(OBJ);
			attack(OBJ);
		}
		else if (posX - PlayerX < -5)
		{
			right(OBJ);
			attack(OBJ);
		}//Continue working on general AI. Give it an attack


		
}

void Dummy::left(const GameFlow& OBJ)
{
	current = Moving;
	spdX += 1; posX -= spdX; render(OBJ);
}

void Dummy::right(const GameFlow& OBJ)
{
	current = Moving;
	spdX += 1; posX += spdX; render(OBJ);
}

std::vector<SDL_Rect> Dummy::attack(const GameFlow& OBJ)
{
	current = Attacking;
	render(OBJ);
	AtkHitbox[0].x = posX + 6;
	AtkHitbox[0].y = posY;//Return something
	return AtkHitbox;
}

void Dummy::reaction()
{
	spdX += 9; posX += spdX;
	spdX = 0;
	DmyHealth - 10;

}

void Dummy::render(const GameFlow& OBJ)
{
	switch (current)
	{
	case Attacking:
		SDL_RenderClear(OBJ.mainRender);
		Dmy.render(OBJ, posX, posY, &AttackSprite[0]);
		SDL_RenderPresent(OBJ.mainRender);
		break;

	case Moving:
		SDL_RenderClear(OBJ.mainRender);
		Dmy.render(OBJ, posX, posY, &MovingSprite[0]);
		SDL_RenderPresent(OBJ.mainRender);
		break;

	case Standing:
		SDL_RenderClear(OBJ.mainRender);
		Dmy.render(OBJ, posX, posY, &MovingSprite[0]);
		SDL_RenderPresent(OBJ.mainRender);
	}
}