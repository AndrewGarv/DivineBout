/********************************************//**
 *  Dummy
 * A simple test enemy. It walks towards the player, strikes an attack pose every so often and can be hit by the players attack.
 * Like the Player, it is updated and rendered once per frame by the main loop.
 ***********************************************/
#pragma once
#include <SDL.h>
#include "GameFlow.h"
#include "Textures.h"
#include "GameTimer.h"

class Dummy
{
public:
	explicit Dummy(const GameFlow& OBJ);
	void update(int playerCentreX);
	void reaction(int direction);//Called when the players attack lands. direction is -1 to be pushed left and 1 to be pushed right
	void render(const GameFlow& OBJ) const;
	SDL_Rect hurtbox() const;
	bool isAlive() const { return DmyHealth > 0; }
	int centreX() const { return posX + currentSprite().w / 2; }

private:
	static const int WalkSpeed = 2;//Pixels per frame
	static const int StopDistance = 80;//The dummy stops walking once it is this close to the player
	static const int Knockback = 9;//How far a hit pushes the dummy
	static const int HitDamage = 10;
	static const Uint32 AttackInterval = 2000;//Milliseconds between attacks
	static const Uint32 AttackDuration = 500;//Milliseconds the attack pose is held

	enum State { Moving, Attacking, Standing };
	const SDL_Rect& currentSprite() const;

	Textures Dmy;
	GameTimer DummyTime;//Counts the time since the current attack started, or since the last one ended
	State current = Standing;
	int posX = 300;//Left edge of the sprite. The feet always rest on GameFlow::GroundY
	int DmyHealth = 1000;
	bool facingRight = false;
};
