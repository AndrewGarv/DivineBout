/********************************************//**
 *  Player
 * The player character. It dictates most everything about them: their sprite, their animations and their movement options.
 * Only one Player object exists at a time.
 *
 * Each frame the main loop calls inputRead for every event, then update once, then render once. Nothing in here
 * blocks or presents the frame, so the player can share the screen with enemies.
 ***********************************************/
#pragma once
#include <SDL.h>
#include "GameFlow.h"
#include "Textures.h"

class Player
{
public:
	explicit Player(const GameFlow& OBJ);
	void inputRead(const SDL_Event& e);
	void update();
	void render(const GameFlow& OBJ) const;

	//Fills in the attack hitbox and returns true while an attack is out and has not hit anything yet
	bool attackHitbox(SDL_Rect& box) const;
	//Tell the player their current attack connected, so one swing can only hit once
	void attackLanded() { hitLanded = true; }

	int centreX() const { return posX + SpriteW / 2; }

private:
	static const int SpriteW = 43;//Every cut on the Brynild sprite sheet is this size
	static const int SpriteH = 69;
	static const int MaxVel = 15;//Top running speed in pixels per frame
	static const int AirSpeed = 3;//Sideways speed while jumping
	static const int JumpSpeed = 16;//Upwards speed at the start of a jump. With Gravity this gives a jump of about 130 pixels
	static const int Gravity = 1;
	static const int AnimDelay = 4;//Game frames each idle/moving sprite stays on screen
	static const int AttackAnimDelay = 6;//Game frames each attack startup sprite stays on screen
	static const int StartupFrames = 18;//Attack wind up, before the hitbox comes out
	static const int ActiveFrames = 8;//How long the hitbox stays out
	static const int AttackReach = 20;//How far in front of the sprite the attack hitbox reaches

	enum State { Neutral, Moving, Rising, Falling, Startup, Active };
	void setState(State next);
	bool onGround() const { return current == Neutral || current == Moving; }

	Textures Brnyld;
	State current = Neutral;
	int frame = 0;//Frames spent in the current state. Drives the animations and the attack timing
	int posX = 5;
	int posY = GameFlow::GroundY - SpriteH;//Top left corner of the sprite
	int spdX = 0, spdY = 0;
	bool facingLeft = false;
	bool hitLanded = false;
};
