#include "GameTimer.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

GameTimer::GameTimer()
{
	pauseState = false;
	startState = false;
	startTicks = 0;
	endTicks = 0;
}

void GameTimer::Begin()
{
	startState = true;
	pauseState = false;
	startTicks = SDL_GetTicks();
	endTicks = 0;//Remember that this method will begin a timer AND restart one so it is always necessary to set endTicks to 0
}

void GameTimer::Pause()//Be sure to check if the timer is running or not before attempting to pause
{
	if (startState == true)
	{
		startState = false;
		pauseState = true;
		endTicks = SDL_GetTicks() - startTicks;//Remember that endTicks is where the timer is paused RELATIVE TO WHEN THE TIMER STARTED! 
	}
}

void GameTimer::Unpause()//Be sure to check if the timer is runnong or not before attempting to pause
{
	startState = true;
	pauseState = false;
	startTicks = SDL_GetTicks() - endTicks;//Maintain the time relative to the program time. THIS MAY NOT BE RIGHT! CONSIDER A TEMP VARIABLE
	endTicks = 0;
}//It would appear we want the new startTicks to have a distance relative to the program time that mirrors the time it was paused

void GameTimer::Stop()
{
	startState = false;
	pauseState - false;
	endTicks = 0;
	startTicks = 0;
}

Uint32 GameTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (startState)
	{
		//If the timer is paused
		if (pauseState)
		{
			//Return the number of ticks when the timer was paused
			time = endTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}