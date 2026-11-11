#include "Dummy.h"

namespace
{
	//Where each pose sits on the DummyEnemy.png sprite sheet
	const SDL_Rect StandingSprite = { 1, 1, 111, 131 };
	const SDL_Rect AttackSprite = { 114, 1, 103, 143 };
	const SDL_Rect MovingSprite = { 1, 146, 101, 152 };
}

Dummy::Dummy(const GameFlow& OBJ)
{
	Dmy.loadTex("DummyEnemy.png", OBJ);
	DummyTime.Begin();
}

const SDL_Rect& Dummy::currentSprite() const
{
	switch (current)
	{
	case Attacking: return AttackSprite;
	case Moving: return MovingSprite;
	default: return StandingSprite;
	}
}

/********************************************//**
 *  Dummy::update(int playerCentreX)
 * The dummys AI. It walks towards the player until it is close, and every AttackInterval it stops to hold its attack pose.
 * The attack does not hurt the player yet.
 ***********************************************/
void Dummy::update(int playerCentreX)
{
	if (!isAlive())
	{
		return;
	}

	if (current == Attacking)
	{
		if (DummyTime.getTicks() < AttackDuration)
		{
			return;
		}
		current = Standing;
		DummyTime.Begin();
	}

	const int distance = playerCentreX - centreX();
	facingRight = distance > 0;

	if (DummyTime.getTicks() >= AttackInterval)
	{
		current = Attacking;
		DummyTime.Begin();
	}
	else if (distance > StopDistance)
	{
		current = Moving;
		posX += WalkSpeed;
	}
	else if (distance < -StopDistance)
	{
		current = Moving;
		posX -= WalkSpeed;
	}
	else
	{
		current = Standing;
	}
}

void Dummy::reaction(int direction)
{
	DmyHealth -= HitDamage;
	posX += direction * Knockback;

	//Keep the dummy on screen
	if (posX < 0)
	{
		posX = 0;
	}
	else if (posX > GameFlow::ScreenW - currentSprite().w)
	{
		posX = GameFlow::ScreenW - currentSprite().w;
	}

	if (!isAlive())
	{
		Dmy.killTexture();
	}
}

SDL_Rect Dummy::hurtbox() const
{
	const SDL_Rect& sprite = currentSprite();
	const SDL_Rect box = { posX, GameFlow::GroundY - sprite.h, sprite.w, sprite.h };
	return box;
}

/********************************************//**
 *  Dummy::render(const GameFlow& OBJ)
 * Draws the pose matching the current state. The sheet faces left, so it is flipped when facing right.
 ***********************************************/
void Dummy::render(const GameFlow& OBJ) const
{
	if (!isAlive())
	{
		return;
	}
	const SDL_Rect box = hurtbox();
	Dmy.render(OBJ, box.x, box.y, &currentSprite(), 0.0, nullptr, facingRight ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
