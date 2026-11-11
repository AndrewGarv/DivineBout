#include "GameTimer.h"

void GameTimer::Begin()
{
	startState = true;
	pauseState = false;
	startTicks = SDL_GetTicks();
	endTicks = 0;
}

void GameTimer::Pause()
{
	if (startState && !pauseState)
	{
		pauseState = true;
		endTicks = SDL_GetTicks() - startTicks;
	}
}

void GameTimer::Unpause()
{
	if (startState && pauseState)
	{
		pauseState = false;
		startTicks = SDL_GetTicks() - endTicks;//Shift the start forward so the paused time is skipped
		endTicks = 0;
	}
}

void GameTimer::Stop()
{
	startState = false;
	pauseState = false;
	startTicks = 0;
	endTicks = 0;
}

Uint32 GameTimer::getTicks() const
{
	if (!startState)
	{
		return 0;
	}
	return pauseState ? endTicks : SDL_GetTicks() - startTicks;
}
