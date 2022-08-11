/********************************************//**
 *  Player
 * One of the most important classes there is. This is the player character. It dictates most everything about them from how they are rendered to their animations to their movement options.
 * It is referenced a lot in Source.cpp however only one Player object will ever exist at one point.
 ***********************************************/
#pragma once
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "GameFlow.h"
#include "Textures.h"
#include "Sprites.h"
class Player
{
public:
	int frame = 0;
	int posX, posY;
	static const int MaxVel = 15;
	static const int MaxJmp = 370;//Always make sure this is smaller than PosY. Generally speaking try to make this 130 less than PosY
	static const int PlrW = 0;
	static const int PlrH = 0;//These two need to be adjusted. They are the sprites width and height
	const Uint8* StateKeys = SDL_GetKeyboardState(NULL);
	SDL_Rect StandingSprite[7];//The sprites used when the player character is standing in a neutral position
	SDL_Rect RisingSprite[4];//The sprites used when the player character is in the rising portion of a jump
	SDL_Rect MovingSprite[8];//The sprites used when the player character is moving
	SDL_Rect AttackingSprite[4];//The sprites used when the player attacks
	SDL_RendererFlip type;
	Player();
	void inputRead(SDL_Event& e, const GameFlow& OBJ);
	void movement(const GameFlow& OBJ, SDL_Event& e);
	void left(const GameFlow& OBJ);
	void right(const GameFlow& OBJ);
	void rise(const GameFlow& OBJ, SDL_Event& e);
	void fall(const GameFlow& OBJ);
	void idle(const GameFlow& OBJ);
	std::vector<SDL_Rect> attack(const GameFlow& OBJ, SDL_Event& e);
	void testFunc();
	void render(const GameFlow& OBJ);
	//The attack method will call this when the hitbox appears. Pass to it the attack hitbox and the enemy hurtbox. THINK ABOUT HOW TO DO THIS!
	Textures Brnyld;
	Sprites Plyr;
	//About the Hitbox stuff. Consider this. These methods will be for the specific reactions to hitbox collision. The actual collisionCheck will be placed somewhere else. GIVE IT ITS OWN OBJECT
private: 
	int spdX, spdY;
	enum State {Rising, Falling, Moving, Neutral, Hit, Active, Startup};
	bool jmpflag = false;
	std::vector<SDL_Rect> AtkHitbox;//Assertion failure??? RESIZE THE VECTOR BEFORE INITIALIZING IT!!!
	State current;
};
//Here is the plan. Make the collisionCheck in the Source. It will be called whenever attack runs. Attack will return a Rect. In the main loop, anytime an enemy appears on screen, their hurtbox
//will be placed in an array. collisionCheck will run through the array and check if the attack is colliding with any of them. If it is, then it will send some sort of flag that will be interpreted
//by the individual objects to get specific reactions.