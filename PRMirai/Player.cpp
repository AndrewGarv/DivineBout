#include "Player.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
/********************************************//**
 *  Player::Player()
 * A constructor for the player. It positions the player character to the leftmost side of the screen at the very bototm
 * The sprites are initialized and match their corresponding coordinates on the Brynild.png sprite sheet and the characters state is 
 * set to Neutral
 ***********************************************/
Player::Player()
{
	posX = 5;
	posY = 500;//IMPORTANT This is the characters default position. In other words, it's the ground level. When changing this always make sure it is greater than MaxJmp
	spdX = 0;
	spdY = 0;
	current = Neutral;
	AtkHitbox.resize(3);
	//Standing Sprites initialized
	StandingSprite[0].x = 358;
	StandingSprite[0].y = 288;
	StandingSprite[0].w = 43;
	StandingSprite[0].h = 69;
	StandingSprite[1].x = 411;
	StandingSprite[1].y = 1;
	StandingSprite[1].w = 43;
	StandingSprite[1].h = 69;
	StandingSprite[2].x = 411;
	StandingSprite[2].y = 72;
	StandingSprite[2].w = 43;
	StandingSprite[2].h = 69;
	StandingSprite[3].x = 388;
	StandingSprite[3].y = 142;
	StandingSprite[3].w = 43;
	StandingSprite[3].h = 69;
	StandingSprite[4].x = 373;
	StandingSprite[4].y = 212;
	StandingSprite[4].w = 43;
	StandingSprite[4].h = 69;
	StandingSprite[5].x = 416;
	StandingSprite[5].y = 212;
	StandingSprite[5].w = 43;
	StandingSprite[5].h = 69;
	StandingSprite[6].x = 403;
	StandingSprite[6].y = 282;
	StandingSprite[6].w = 43;
	StandingSprite[6].h = 69;
	//Jumping Sprites initialized
	RisingSprite[0].x = 1;
	RisingSprite[0].y = 1;
	RisingSprite[0].w = 43;
	RisingSprite[0].h = 69;
	RisingSprite[1].x = 42;
	RisingSprite[1].y = 1;
	RisingSprite[1].w = 43;
	RisingSprite[1].h = 69;
	RisingSprite[2].x = 86;
	RisingSprite[2].y = 1;
	RisingSprite[2].w = 43;
	RisingSprite[2].h = 69;
	RisingSprite[3].x = 132;
	RisingSprite[3].y = 1;
	RisingSprite[3].w = 43;
	RisingSprite[3].h = 69;
	//Moving sprites intiialized
	MovingSprite[0].x = 207;
	MovingSprite[0].y = 359;
	MovingSprite[0].w = 43;
	MovingSprite[0].h = 69;
	MovingSprite[1].x = 411;
	MovingSprite[1].y - 1;
	MovingSprite[1].w = 43;
	MovingSprite[1].h = 69;
	MovingSprite[2].x = 411;
	MovingSprite[2].y = 72;
	MovingSprite[2].w = 43;
	MovingSprite[2].h = 69;
	MovingSprite[3].x = 315;
	MovingSprite[3].y = 359;
	MovingSprite[3].w = 43;
	MovingSprite[3].h = 69;
	//Attack Sprites initialized
	AttackingSprite[0].x = 184;
	AttackingSprite[0].y = 175;
	AttackingSprite[0].w = 43;
	AttackingSprite[0].h = 69;
	AttackingSprite[1].x = 252;
	AttackingSprite[1].y = 175;
	AttackingSprite[1].w = 43;
	AttackingSprite[1].h = 69;
	AttackingSprite[2].x = 318;
	AttackingSprite[2].y = 175;
	AttackingSprite[2].w = 43;
	AttackingSprite[2].h = 69;
	AttackingSprite[3].x = 1;
	AttackingSprite[3].y = 329;
	AttackingSprite[3].w = 43;
	AttackingSprite[3].h = 69;
	//Attack Hitbox initialized
	AtkHitbox[0].w = 6;
	AtkHitbox[0].h = 9;
}
/********************************************//**
 *  Player::inputRead(SDL_Event& e, const GameFlow& OBJ
 * This function handles all the possible inputs that are relevant to the player character. If the up key is pressed then the rise function is called and if left or right
 * are press then the movement function is called. The function passes the main GameFlow object to any other class as well as the SDL_Event to the movement function. There is currently
 * nothing to be done with the down key
 ***********************************************/
void Player::inputRead(SDL_Event& e,const GameFlow& OBJ)//Add object to this defintion
{
	Brnyld.loadTex("Brynild.png", OBJ);//Put this in a constructor
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: rise(OBJ, e); break;

		case SDLK_LEFT: type = SDL_FLIP_HORIZONTAL; left(OBJ); break;

		case SDLK_RIGHT: right(OBJ); break;
		}
	}
}

void Player::rise(const GameFlow& OBJ, SDL_Event& e)
{
	printf("Entry into rise works");
	current = Rising;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	for (int a = 1; posY >= MaxJmp; a++)//YOU ARE DOING MULTIPLE INPUTS NEXT!!!
	{
		spdY += log2(a);
		posY -= spdY;
		if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
			posX+= 3;
		}
		else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
			posX -= 3;
		}
		render(OBJ);
	}
	posY = MaxJmp;
	jmpflag = true;
	render(OBJ);
}

void Player::fall(const GameFlow& OBJ)
{
	for (int a = 1; posY < 500; a++)
	{
		spdY += pow(2.0, a);
		posY += spdY;
		render(OBJ);
	}
}

void Player::left(const GameFlow& OBJ)
{
	current = Moving;
	spdX += 1; posX -= spdX; render(OBJ);
}

void Player::right(const GameFlow& OBJ)
{
	current = Moving;
	spdX += 1; posX += spdX; render(OBJ);
}

void Player::idle(const GameFlow& OBJ)
{
	current = Neutral;
	render(OBJ);
}

void Player::movement(const GameFlow& OBJ, SDL_Event& e)//SCRATCH THIS METHOD! Make a left and right one instead.
{
	current = Moving;
	while (SDL_PollEvent(&e))
	{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			spdX += 5; posX -= spdX; render(OBJ);
		}
		else if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			spdX += 5; posX += spdX; render(OBJ);
		}
		else
		{
			printf("Radical Rebel with a B2 Bomber");
		}
	}
}

std::vector<SDL_Rect> Player::attack(const GameFlow& OBJ, SDL_Event& e)
{
	current = Startup;
	for (int a = 1; a <= 20; a++)
	{
		render(OBJ);
		if (current == Active)
		{
			AtkHitbox[0].x = posX + 3;//Do more research on hitbox
			AtkHitbox[0].y = posY;
			printf("The hitbox spawned");
		}
	}
	frame = 0;
	return AtkHitbox;
}

void Player::testFunc()
{
	printf("It loops!");
}



void Player::render(const GameFlow& OBJ)
{
	switch (current)
	{
		case Rising://Consider this: Render the thing at beginning of the case then have the if statements just be for changing values, this might stop repeating code
			if (posY > 1.1 * MaxJmp)
			{
				SDL_RenderClear(OBJ.mainRender);
				Brnyld.render(OBJ, posX, posY, &RisingSprite[0]);
				SDL_RenderPresent(OBJ.mainRender);
			}
			else if (posY < 1.1 * MaxJmp && posY >= 1.03 * MaxJmp)
			{
				SDL_RenderClear(OBJ.mainRender);
				Brnyld.render(OBJ, posX, posY, &RisingSprite[1]);
				SDL_RenderPresent(OBJ.mainRender);
			}
			else if (posY < 1.03 * MaxJmp && posY >= 1 * MaxJmp && jmpflag == false)
			{
				SDL_RenderClear(OBJ.mainRender);
				Brnyld.render(OBJ, posX, posY, &RisingSprite[2]);
				SDL_RenderPresent(OBJ.mainRender);
			}
			else if (jmpflag == true)
			{
				std::cout << posY << " is equal to " << MaxJmp << " \n";
				SDL_RenderClear(OBJ.mainRender);
				Brnyld.render(OBJ, posX, posY, &RisingSprite[3]);
				SDL_RenderPresent(OBJ.mainRender);
				jmpflag = false;
				fall(OBJ);
			}
			break;
		case Moving:
			if (frame >= 20)
			{
				frame = 0;
			}
			SDL_RenderClear(OBJ.mainRender);
			Brnyld.render(OBJ, (posX), (posY), &MovingSprite[frame / 4]);//Make it render the positions
			SDL_RenderPresent(OBJ.mainRender);
			frame++;
			break;

		case Neutral:
			if (frame >= 30)
			{
				frame = 0;
			}
			SDL_RenderClear(OBJ.mainRender);
			Brnyld.render(OBJ, (posX), (posY), &StandingSprite[frame / 4]);//Figure out some ways to fix the animation errors when moving, otherwise congrats!
			SDL_RenderPresent(OBJ.mainRender);
			frame++;
			std::cout << frame << "\n";
			break;

		case Startup://Remember to set the frame back to 0 and to make an Active case that throws out the hitbox
			printf("Why is this happening??? \n");
			SDL_RenderClear(OBJ.mainRender);
			Brnyld.render(OBJ, (posX), (posY), &AttackingSprite[frame / 6]);
			SDL_RenderPresent(OBJ.mainRender);
			frame++;
			if (frame / 6 == 2)
			{
				current = Active;
			}
			break;

		case Active:
			SDL_RenderClear(OBJ.mainRender);
			printf("OH THIS IS HAPPENING HAPPAPAPAPAPAA OHWEEEEETOOOO!!! \n");
			Brnyld.render(OBJ, (posX), (posY), &AttackingSprite[3]);
			SDL_RenderPresent(OBJ.mainRender);
			frame = 0;
			break;

	}
}