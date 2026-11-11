/*This development project was constructed by Ki-jana Garvey
Date of Creation: August 28th 2021 3:47 AM*/
#include <SDL.h>
#include <stdio.h>
#include "GameFlow.h"
#include "GameTimer.h"
#include "Textures.h"
#include "Player.h"
#include "Dummy.h"

namespace
{
	enum Scene { Title, Level, Quit };

	const Uint32 FrameTime = 1000 / 60;//The game logic is written for 60 frames per second

	//Starts a new frame with a blank white screen
	void beginFrame(const GameFlow& game)
	{
		SDL_SetRenderDrawColor(game.mainRender, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(game.mainRender);
	}

	//Shows the finished frame, then waits out whatever is left of it in case vsync is off or the monitor is faster than 60Hz
	void endFrame(const GameFlow& game, GameTimer& frameTimer)
	{
		SDL_RenderPresent(game.mainRender);
		const Uint32 elapsed = frameTimer.getTicks();
		if (elapsed < FrameTime)
		{
			SDL_Delay(FrameTime - elapsed);
		}
		frameTimer.Begin();
	}

	//The title screen. Pressing any key starts the test level
	Scene TitleScreen(const GameFlow& game)
	{
		Textures Titl;
		Titl.loadTex("TitleScreen.png", game);
		GameTimer frameTimer;
		frameTimer.Begin();

		while (true)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					return Quit;
				}
				if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
				{
					return Level;
				}
			}

			beginFrame(game);
			Titl.render(game, (GameFlow::ScreenW - Titl.getWidth()) / 2, (GameFlow::ScreenH - Titl.getHeight()) / 2);
			endFrame(game, frameTimer);
		}
	}

	//The test level: the player against a single Dummy. Backspace goes back to the title screen
	Scene TestLevel(const GameFlow& game)
	{
		Player MainChar(game);
		Dummy Enemy(game);
		GameTimer frameTimer;
		frameTimer.Begin();

		while (true)
		{
			SDL_Event e;
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					return Quit;
				}
				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE)
				{
					return Title;
				}
				MainChar.inputRead(e);
			}

			MainChar.update();
			Enemy.update(MainChar.centreX());

			//Check the players attack against the enemy
			SDL_Rect hitbox;
			if (Enemy.isAlive() && MainChar.attackHitbox(hitbox))
			{
				const SDL_Rect hurtbox = Enemy.hurtbox();
				if (SDL_HasIntersection(&hitbox, &hurtbox))
				{
					Enemy.reaction(Enemy.centreX() < MainChar.centreX() ? -1 : 1);
					MainChar.attackLanded();
				}
			}

			beginFrame(game);
			Enemy.render(game);
			MainChar.render(game);
			endFrame(game, frameTimer);
		}
	}
}

int main(int argc, char* argv[])
{
	GameFlow game;
	if (!game.init())
	{
		printf("Divine Bout could not start\n");
		return 1;
	}

	Scene scene = Title;
	while (scene != Quit)
	{
		scene = (scene == Title) ? TitleScreen(game) : TestLevel(game);
	}
	return 0;
}
