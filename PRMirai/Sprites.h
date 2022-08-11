/********************************************//**
 *  Sprites
 * A prototype class, it is currently not used in the project. Most if not all of its functionality was instead folded into the individual character objects.
 ***********************************************/
#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Sprites
{
public:
	Sprites();//Initialize this with something 
	bool SpriteInit;
	SDL_Rect Brynild[7];
	void BrynEvents(SDL_Event& e);//We are going to get rid of the Spirtes class and fold everything into a character object.
	void BrynildInit();
};