#include "Sprites.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

Sprites::Sprites()
{
	SpriteInit = true;
}

void Sprites::BrynildInit()
{
	//Brynild Standing Sprite
	Brynild[0].x = 358;
	Brynild[0].y = 288;
	Brynild[0].w = 43;
	Brynild[0].h = 69;
	Brynild[1].x = 411;
	Brynild[1].y = 1;
	Brynild[1].w = 43;
	Brynild[1].h = 69;//When animating these, all you need to alter in the Source is the render call. You'll be adding another rect for timing purposes
	Brynild[2].x = 411;
	Brynild[2].y = 72;
	Brynild[2].w = 43;
	Brynild[2].h = 69;
	Brynild[3].x = 388;
	Brynild[3].y = 142;
	Brynild[3].w = 43;
	Brynild[3].h = 69;
	Brynild[4].x = 373;
	Brynild[4].y = 212;
	Brynild[4].w = 43;
	Brynild[4].h = 69;
	Brynild[5].x = 416;
	Brynild[5].y = 212;
	Brynild[5].w = 43;
	Brynild[5].h = 69;
	Brynild[6].x = 403;
	Brynild[6].y = 282;
	Brynild[6].w = 43;
	Brynild[6].h = 69;
}
