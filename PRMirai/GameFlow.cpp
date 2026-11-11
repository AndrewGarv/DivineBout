#include "GameFlow.h"
#include <SDL_image.h>
#include <stdio.h>

/********************************************//**
 *  GameFlow::init()
 * Starts SDL, creates the "Divine Bout" window and its renderer, then makes sure PNG loading is available.
 * Returns false (after printing the reason) if any step fails. Whatever was created before the failure is
 * cleaned up by the destructor.
 ***********************************************/
bool GameFlow::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error in starting SDL: %s\n", SDL_GetError());
		return false;
	}

	//The game is designed around linear scaling. It still runs without it, so this is only a warning
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: linear texture filtering is not enabled\n");
	}

	mainWindow = SDL_CreateWindow("Divine Bout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_SHOWN);
	if (mainWindow == nullptr)
	{
		printf("Error in creating window: %s\n", SDL_GetError());
		return false;
	}

	mainRender = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mainRender == nullptr)
	{
		printf("Error in creating renderer: %s\n", SDL_GetError());
		return false;
	}

	const int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) != imgFlags)
	{
		printf("Error in starting PNG loading: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

/********************************************//**
 *  GameFlow::~GameFlow()
 * Destructor. Tears down the renderer, the window and SDL itself. Every texture has to be destroyed before this runs.
 ***********************************************/
GameFlow::~GameFlow()
{
	if (mainRender != nullptr)
	{
		SDL_DestroyRenderer(mainRender);
	}
	if (mainWindow != nullptr)
	{
		SDL_DestroyWindow(mainWindow);
	}
	IMG_Quit();
	SDL_Quit();
}
