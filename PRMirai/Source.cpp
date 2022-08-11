/*This development project was constructed by Ki-jana Garvey
Date of Creation: August 28th 2021 3:47 AM
Last Modified: August 28th 2021 3:47 AM*/
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "GameFlow.h"
#include "Textures.h"
#include "Sprites.h"
#include "Player.h"
#include "Dummy.h"
SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRender = NULL;
bool quit = false;
bool next = false;
SDL_Event e;
int frame = 0;
bool flag = true;
std::vector<SDL_Rect> EnmHurt;//Anytime the render function for an enemy is called, this will fill in by 1
const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
Textures testtex;

bool collisionCheck(std::vector<SDL_Rect> a, std::vector<SDL_Rect> b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	for (int Abox = 0; Abox < a.size(); Abox++)
	{
		//Calculate the sides of rect A
		leftA = a[Abox].x;
		rightA = a[Abox].x + a[Abox].w;
		topA = a[Abox].y;
		bottomA = a[Abox].y + a[Abox].h;

		//Go through the B boxes
		for (int Bbox = 0; Bbox < b.size(); Bbox++)
		{
			//Calculate the sides of rect B
			leftB = b[Bbox].x;
			rightB = b[Bbox].x + b[Bbox].w;
			topB = b[Bbox].y;
			bottomB = b[Bbox].y + b[Bbox].h;

			//If no sides from A are outside of B
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
			{
				//A collision is detected
				return true;
			}
		}
	}
}

void TestLevel(GameFlow tester)
{
	Player MainChar;//Create for loop that waits for input or while loop instead. Do while loop
	Dummy Enemy(tester);
	SDL_Event f;
	next = false;
	while (!next)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_UP: MainChar.inputRead(e, tester); break;
				case SDLK_LEFT: MainChar.inputRead(e, tester); break;
				case SDLK_RIGHT: MainChar.inputRead(e, tester); break;
				case SDLK_DOWN: MainChar.testFunc(); break;
				case SDLK_SPACE: MainChar.frame = 0; 
					if (collisionCheck(MainChar.attack(tester, e), EnmHurt) == true)//Do something with the overlapping hitboxes
					{
						Enemy.reaction();
					}
				case SDLK_BACKSPACE: next = true; break;
				}
			}
		}
		Enemy.movement(tester, MainChar.posX, MainChar.posY);
		MainChar.idle(tester);
	}
}



int main(int argc, char* argv[])
{
	printf("Entry into program succesful\n");
	GameFlow game;
	EnmHurt.resize(1);
	if (game.init() == true)
	{
		Textures Brn;
		Textures Titl;
		Titl.loadTex("TitleScreen.png", game);
		while (!next)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_KEYUP)
				{
					Titl.killTexture();
					SDL_RenderClear(game.mainRender);
					TestLevel(game);
					next = true;
				}
			}
			SDL_SetRenderDrawColor(game.mainRender, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(game.mainRender);
			Titl.render(game, (game.ScreenW / 2), (game.ScreenH / 2));
			SDL_RenderPresent(game.mainRender);
		}
		Titl.killTexture();
		SDL_RenderClear(game.mainRender);
		Sprites Protag;
		Protag.BrynildInit();
		Brn.loadTex("Brynild.png", game);
		printf("If all goes well we are good");
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			SDL_RenderClear(game.mainRender);
			Brn.render(game, (game.ScreenW - Protag.Brynild[frame/4].w), (game.ScreenH - Protag.Brynild[frame/4].h), &Protag.Brynild[frame/4]);
			SDL_RenderPresent(game.mainRender);
			if (flag == true)
			{
				frame++;
			}
			else
			{
				frame--;
			}
			if (frame / 4 >= 6)
			{
				flag = false;
			}
			else if (frame / 4 <= 0)
			{
				flag = true;
			}
		}
	}
	else
	{
		printf("Something went wrong");
	}
	return 0;
}

int simul()
{
	return 0;
}