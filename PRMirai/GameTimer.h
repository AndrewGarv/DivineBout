/********************************************//**
 *  GameTimer
 *
 * The games timer. It is used to pace the main loop and to modify the behaviour of enemy AI.
 * Most enemies have their own instance of GameTimer to make use of
 ***********************************************/
#pragma once
#include <SDL.h>

class GameTimer
{
public:
	void Begin();//Starts the timer, or restarts it from 0 if it was already running
	void Pause();
	void Unpause();
	void Stop();
	Uint32 getTicks() const;//Milliseconds counted so far. Time spent paused is not counted
	bool isPaused() const { return pauseState; }
	bool isCounting() const { return startState && !pauseState; }

private:
	Uint32 startTicks = 0;//The program time at which the timer (re)started counting
	Uint32 endTicks = 0;//How much time had been counted at the moment the timer was paused
	bool pauseState = false;
	bool startState = false;
};
