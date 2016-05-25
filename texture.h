#pragma once

#include "constants.h"
#include <SDL_image.h>

class LTexture
{
private:
	//actual hardware texture
	SDL_Texture* texture;
	
	int height;
	int width;
public:
	LTexture();

	//Deallocates memory
	~LTexture();

	bool loadFromFile(SDL_Renderer* gRenderer, std::string path);

	//Deallocates texture
	void freeTexture();

	//set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void setBlendMode(Uint8 alpha);

	//renders texture at a given point
	void render(SDL_Renderer* gRenderer, int x =0, int y=0, SDL_Rect* clip = NULL);

	int getWidth();
	int getHeight();
};