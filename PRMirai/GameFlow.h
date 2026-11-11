/********************************************//**
 *  GameFlow
 * This class is responsible for creating and maintaining the SDL window and renderer that the game runs in.
 * Only one GameFlow object should exist at a time, so it cannot be copied.
 ***********************************************/
#pragma once
#include <SDL.h>

class GameFlow
{
public:
	static const int ScreenW = 1920;//The screens width and height is set for 1080p
	static const int ScreenH = 1080;
	static const int GroundY = 569;//The line that every characters feet rest on

	GameFlow() = default;
	~GameFlow();
	GameFlow(const GameFlow&) = delete;
	GameFlow& operator=(const GameFlow&) = delete;

	bool init();

	SDL_Window* mainWindow = nullptr;
	SDL_Renderer* mainRender = nullptr;
};
