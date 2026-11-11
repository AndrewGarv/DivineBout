/********************************************//**
 *  Textures
 * This class is responsible for managing a single texture (usually a whole sprite sheet). It contains the "render" method
 * which is one of the most used methods in the entire program. Every image in the game has a corresponding Textures object.
 * A Textures object owns its SDL_Texture, so it cannot be copied.
 ***********************************************/
#pragma once
#include <string>
#include <SDL.h>
#include "GameFlow.h"

class Textures
{
public:
	Textures() = default;
	~Textures();
	Textures(const Textures&) = delete;
	Textures& operator=(const Textures&) = delete;

	bool loadTex(const std::string& filename, const GameFlow& OBJ);
	void Colourset(Uint8 r, Uint8 g, Uint8 b);
	void BlenderSet(SDL_BlendMode blend);
	void AlphaSet(Uint8 alphaType);
	void render(const GameFlow& OBJ, int x, int y, const SDL_Rect* cut = nullptr, double angle = 0.0, const SDL_Point* centre = nullptr, SDL_RendererFlip flipType = SDL_FLIP_NONE) const;
	void killTexture();
	int getWidth() const { return TextureWidth; }
	int getHeight() const { return TextureHeight; }

private:
	int TextureWidth = 0;
	int TextureHeight = 0;
	SDL_Texture* HardwareTexture = nullptr;
};
