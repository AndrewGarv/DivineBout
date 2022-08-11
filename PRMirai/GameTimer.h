/********************************************//**
 *  GameTimer
 * 
 * The games timer. This is often used to modify the behaviour of enemy AI. Most enemies will have their own instance of GameTimer to make use of
 ***********************************************/
#pragma once
#ifndef GAMETIMER_H
#define GAMETIMER_H
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class GameTimer
{
public:
	GameTimer();
	void Begin();
	void Pause();
	void Unpause();
	void Stop();
	Uint32 getTicks();
	bool isPaused();
	bool isCounting();

private:
	Uint32 startTicks;//The time when the Start method is called. This variable will always be relative to the program time so make sure that no matter what it maintains that. So if this starts 5 seconds into the program then this variable should always be seconds away from the program time.
	Uint32 endTicks;//The time when the Pause method is called relative to the start. So if I start the timer and then 20 seconds later I pause it then this should be 20.
	bool pauseState;
	bool startState;
};

#endif
