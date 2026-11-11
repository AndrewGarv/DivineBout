#include "Player.h"

namespace
{
	//Where each animation frame sits on the Brynild.png sprite sheet
	const int W = 43, H = 69;
	const SDL_Rect StandingSprite[] = { {358, 288, W, H}, {411, 1, W, H}, {411, 72, W, H}, {388, 142, W, H}, {373, 212, W, H}, {416, 212, W, H}, {403, 282, W, H} };
	const SDL_Rect MovingSprite[] = { {207, 359, W, H}, {411, 1, W, H}, {411, 72, W, H}, {315, 359, W, H} };
	const SDL_Rect RisingSprite[] = { {1, 1, W, H}, {42, 1, W, H}, {86, 1, W, H} };
	const SDL_Rect FallingSprite = { 132, 1, W, H };
	const SDL_Rect StartupSprite[] = { {184, 175, W, H}, {252, 175, W, H}, {318, 175, W, H} };
	const SDL_Rect ActiveSprite = { 1, 329, W, H };

	template <int N>
	int countOf(const SDL_Rect(&)[N]) { return N; }
}

/********************************************//**
 *  Player::Player(const GameFlow& OBJ)
 * Loads the sprite sheet once and leaves the player standing on the ground at the leftmost side of the screen
 ***********************************************/
Player::Player(const GameFlow& OBJ)
{
	Brnyld.loadTex("Brynild.png", OBJ);
}

void Player::setState(State next)
{
	current = next;
	frame = 0;
}

/********************************************//**
 *  Player::inputRead(const SDL_Event& e)
 * Handles the inputs that should trigger once per key press. Right now that is only the attack on space.
 * Held keys (moving and jumping) are read from the keyboard state in update instead.
 ***********************************************/
void Player::inputRead(const SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE && onGround())
	{
		spdX = 0;
		hitLanded = false;
		setState(Startup);
	}
}

/********************************************//**
 *  Player::update()
 * Advances the player by one frame: reads the held keys, moves the character and steps through the state machine.
 ***********************************************/
void Player::update()
{
	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	const int direction = (keys[SDL_SCANCODE_RIGHT] ? 1 : 0) - (keys[SDL_SCANCODE_LEFT] ? 1 : 0);
	frame++;

	switch (current)
	{
	case Startup:
		if (frame >= StartupFrames)
		{
			setState(Active);
		}
		break;

	case Active:
		if (frame >= ActiveFrames)
		{
			setState(Neutral);
		}
		break;

	case Rising:
	case Falling:
		posX += direction * AirSpeed;
		posY -= spdY;
		spdY -= Gravity;
		if (posY >= GameFlow::GroundY - SpriteH)
		{
			posY = GameFlow::GroundY - SpriteH;
			spdY = 0;
			setState(Neutral);
		}
		else if (current == Rising && spdY <= 0)
		{
			setState(Falling);
		}
		break;

	case Neutral:
	case Moving:
		if (keys[SDL_SCANCODE_UP])
		{
			spdX = 0;
			spdY = JumpSpeed;
			setState(Rising);
		}
		else if (direction != 0)
		{
			//Build up speed while running, starting over when first moving or turning around
			if (current != Moving || facingLeft != (direction < 0))
			{
				spdX = 0;
				setState(Moving);
			}
			if (spdX < MaxVel)
			{
				spdX++;
			}
			posX += direction * spdX;
		}
		else if (current != Neutral)
		{
			spdX = 0;
			setState(Neutral);
		}
		break;
	}

	//Turn around freely unless in the middle of an attack
	if (direction != 0 && current != Startup && current != Active)
	{
		facingLeft = direction < 0;
	}

	//Keep the player on screen
	if (posX < 0)
	{
		posX = 0;
	}
	else if (posX > GameFlow::ScreenW - SpriteW)
	{
		posX = GameFlow::ScreenW - SpriteW;
	}
}

bool Player::attackHitbox(SDL_Rect& box) const
{
	if (current != Active || hitLanded)
	{
		return false;
	}
	box.x = facingLeft ? posX - AttackReach : posX + SpriteW;
	box.y = posY;
	box.w = AttackReach;
	box.h = SpriteH;
	return true;
}

/********************************************//**
 *  Player::render(const GameFlow& OBJ)
 * Picks the sprite matching the current state and draws it. The sheet faces right, so it is flipped when facing left.
 ***********************************************/
void Player::render(const GameFlow& OBJ) const
{
	const SDL_Rect* cut = &StandingSprite[0];
	switch (current)
	{
	case Neutral:
		cut = &StandingSprite[(frame / AnimDelay) % countOf(StandingSprite)];
		break;

	case Moving:
		cut = &MovingSprite[(frame / AnimDelay) % countOf(MovingSprite)];
		break;

	case Rising:
	{
		//Step through the rising sprites as the jump slows down towards its peak
		int index = (JumpSpeed - spdY) * countOf(RisingSprite) / JumpSpeed;
		if (index >= countOf(RisingSprite))
		{
			index = countOf(RisingSprite) - 1;
		}
		cut = &RisingSprite[index];
		break;
	}

	case Falling:
		cut = &FallingSprite;
		break;

	case Startup:
	{
		int index = frame / AttackAnimDelay;
		if (index >= countOf(StartupSprite))
		{
			index = countOf(StartupSprite) - 1;
		}
		cut = &StartupSprite[index];
		break;
	}

	case Active:
		cut = &ActiveSprite;
		break;
	}

	Brnyld.render(OBJ, posX, posY, cut, 0.0, nullptr, facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
