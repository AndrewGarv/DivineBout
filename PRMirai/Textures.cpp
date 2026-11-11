#include "Textures.h"
#include <SDL_image.h>
#include <stdio.h>

/********************************************//**
 *  Textures::loadTex(const std::string& filename, const GameFlow& OBJ)
 * Loads an image file straight into a texture using the renderer owned by the GameFlow object, replacing whatever
 * texture was held before. Transparency comes from the alpha channel of the image itself.
 * This does not do any cutting, it just loads the whole sprite sheet. Loading reads from disk, so call it once
 * when a character is created, never every frame.
 ***********************************************/
bool Textures::loadTex(const std::string& filename, const GameFlow& OBJ)
{
	killTexture();

	HardwareTexture = IMG_LoadTexture(OBJ.mainRender, filename.c_str());
	if (HardwareTexture == nullptr)
	{
		printf("Could not load texture %s: %s\n", filename.c_str(), IMG_GetError());
		return false;
	}

	SDL_QueryTexture(HardwareTexture, nullptr, nullptr, &TextureWidth, &TextureHeight);
	return true;
}

/********************************************//**
 *  Textures::Colourset
 * A simple method that just alters the colour of the texture.
 ***********************************************/
void Textures::Colourset(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(HardwareTexture, r, g, b);
}

/********************************************//**
 *  Textures::BlenderSet
 * A simple method that sets how the texture is blended with what is already on screen
 ***********************************************/
void Textures::BlenderSet(SDL_BlendMode blend)
{
	SDL_SetTextureBlendMode(HardwareTexture, blend);
}

/********************************************//**
 *  Textures::AlphaSet
 * A simple method that sets the alpha of the whole texture, allowing for see-through textures
 ***********************************************/
void Textures::AlphaSet(Uint8 alphaType)
{
	SDL_SetTextureAlphaMod(HardwareTexture, alphaType);
}

/********************************************//**
 *  Textures::render
 * Draws the texture with its top left corner at (x, y). cut selects the part of the sprite sheet to draw, without it
 * the whole texture is drawn. The remaining optional values alter the angle and orientation.
 * This only draws into the current frame. Clearing and presenting the frame is the job of the main loop.
 ***********************************************/
void Textures::render(const GameFlow& OBJ, int x, int y, const SDL_Rect* cut, double angle, const SDL_Point* centre, SDL_RendererFlip flipType) const
{
	if (HardwareTexture == nullptr)
	{
		return;
	}

	SDL_Rect RenderSpace = { x, y, TextureWidth, TextureHeight };
	if (cut != nullptr)
	{
		RenderSpace.w = cut->w;
		RenderSpace.h = cut->h;
	}
	SDL_RenderCopyEx(OBJ.mainRender, HardwareTexture, cut, &RenderSpace, angle, centre, flipType);
}

/********************************************//**
 *  Textures::killTexture()
 * Deallocates the texture when it is no longer in use. For enemies this triggers when their HP runs out.
 * It also resets the height and width to 0
 ***********************************************/
void Textures::killTexture()
{
	if (HardwareTexture != nullptr)
	{
		SDL_DestroyTexture(HardwareTexture);
		HardwareTexture = nullptr;
		TextureHeight = 0;
		TextureWidth = 0;
	}
}

Textures::~Textures()
{
	killTexture();
}
