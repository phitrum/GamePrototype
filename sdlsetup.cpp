#include "sdlsetup.h";

SDL_Setup::SDL_Setup(const int width, const int height) 
	: SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{
	e = new SDL_Event();

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::printf("\nUnable to initialize SDL:  %s\n", SDL_GetError());
	}
	else
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::printf("Warning: Linear texture filtering not enabled!");
		}

	//Create Window
	gWindow = SDL_CreateWindow("Game Prototype", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		std::printf("Window failed to initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create renderer
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer == NULL)
		{
			printf("Renderer failed to initialize! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Sets resolution for all platforms (letter boxing)
			SDL_RenderGetLogicalSize(gRenderer, &resWidth, &resHeight);

			//Intitialize render color
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading 
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			}
		}
	}
}

void SDL_Setup::close()
{
	//Destroy Window
	delete e;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;
}