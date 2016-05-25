#include "texture.h"

//Inits vars and objs
LTexture::LTexture()
{
	texture = NULL;
	width = 0;
	height = 0; 
}

LTexture::~LTexture()
{
	freeTexture();
}

void LTexture::freeTexture()
{
	//Free texture if it exists
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

bool LTexture::loadFromFile(SDL_Renderer* gRenderer, std::string path)
{
	//Rid of existing texture
	freeTexture();

	SDL_Texture* newTexture = NULL;

	//Loads image from path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,0, 0xFF, 0xFF));

		//create newtexture from surface
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			std::printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		//Get rid of loaded surface
		SDL_FreeSurface(loadedSurface);

	}
	texture = newTexture;
	return texture!=NULL;
}

void LTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, texture, clip, &renderQuad);
}