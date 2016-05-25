#pragma once
#include "constants.h"

class SDL_Setup 
{
public:
	//Screen dimensions
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	//SDL event
	SDL_Event* e = NULL;
	
	//Constructor
	SDL_Setup(const int width, const int height);

	//Deconstructs
	void close();


	//Gets renderer
	SDL_Renderer* getRenderer()
	{
		return gRenderer;
	}
	//Gets event
	SDL_Event* getEvent()
	{
		return e;
	}

	//May or may not use
	void onEvent(SDL_Event* Event);

protected:
	//Resolution width and height
	int resWidth = 960;
	int resHeight = 640;

private:
	//What the window will be rendering to
	SDL_Window* gWindow = NULL;

	//Game render will render everything
	SDL_Renderer* gRenderer = NULL;
};
