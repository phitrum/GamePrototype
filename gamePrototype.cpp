#include "gamePrototype.h"

GamePrototype::GamePrototype()
{
	//SDL setup up must be initialized before the renderer is used
	sdl_Setup = new SDL_Setup(800,600);
	depth = false;
	kruskal = true;
	mRMaze = new Maze(29, 29);
	compMaze = new CompMaze(13, 13);
	mazeRunner = new Agent(196, 100, mRMaze, sdl_Setup->getRenderer(),2,true);
	tempBackground = new LTexture();
	mRaven = new Button(sdl_Setup->getRenderer(), "images\\ravenButtonSheet.png", 20, 100, 100, 30);
	mMoveButton = new Button(sdl_Setup->getRenderer(), "images\\moveButtonSheet.png", 20, 150, 100, 30);
	mAwesomeButton = new Button(sdl_Setup->getRenderer(), "images\\awesomeButtonSheet.png", 665, 100, 100, 30);
	mKruskalButton = new Button(sdl_Setup->getRenderer(), "images\\kruskalButtonSheet.png", 665, 150, 100, 30);
}

void GamePrototype::loadMedia()
{
	tempBackground->loadFromFile(sdl_Setup->getRenderer(),"images\\blueBack1.png");
}

void GamePrototype::renderAll()
{
	//renderTempBackgrond
	tempBackground->render(sdl_Setup->getRenderer());
	if (depth==true)
		mRMaze->draw(sdl_Setup->getRenderer());
	else if (kruskal==true)
		compMaze->draws(sdl_Setup->getRenderer());
	mazeRunner->draw(sdl_Setup->getRenderer());
	//Buttons
	mRaven->draw(sdl_Setup->getRenderer());
	mMoveButton->draw(sdl_Setup->getRenderer());
	mAwesomeButton->draw(sdl_Setup->getRenderer());
	mKruskalButton->draw(sdl_Setup->getRenderer());
}

GamePrototype::~GamePrototype()
{
	delete mKruskalButton;
	delete mAwesomeButton;
	delete mMoveButton;
	delete mRaven;
	delete tempBackground;
	sdl_Setup->close();
	delete mazeRunner;
	delete mRMaze;
	delete sdl_Setup;
}

void GamePrototype::run()
{

	loadMedia();
	bool quit = false;
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(sdl_Setup->getEvent()) != 0)
		{
			//User requests quit
			if (sdl_Setup->getEvent()->type == SDL_QUIT)
			{
				quit = true;
			}
			if (sdl_Setup->getEvent()->type == SDL_KEYDOWN)// && e->key.repeat == 0)
			{
				switch (sdl_Setup->getEvent()->key.keysym.sym)
				{
					//TEMPORARILLY CREATING A NEW AGENT
					//NEED TO CREATE A RESET POSTION OR SET POSITION
					//MEHTOD!!
				case SDLK_r:
					srand(time(NULL)||Button::buttonChange);
					compMaze = new CompMaze(13, 13);
					mRMaze->resetMaze();
					int runnerType = -1;
					if (mRaven->getActivated())
						runnerType = 2;
					else if (mMoveButton->getActivated())
						runnerType = 1;

					if (mKruskalButton->getActivated())
					{
						depth = false;
						kruskal = true;
						mazeRunner = new Agent(196, 100, compMaze, sdl_Setup->getRenderer(), runnerType,true);
					}
						
					else if (mAwesomeButton->getActivated())
					{
						kruskal = false;
						depth = true;
						mazeRunner = new Agent(196, 100, mRMaze, sdl_Setup->getRenderer(), runnerType, false);
					}
					Button::buttonChange = false;
				}
			}
			//Objects that take input
			mazeRunner->input(sdl_Setup->getEvent());
			mRaven->input(sdl_Setup->getEvent());
			mMoveButton->input(sdl_Setup->getEvent());
			mKruskalButton->input(sdl_Setup->getEvent());
			mAwesomeButton->input(sdl_Setup->getEvent());
		}

		//Updates
		if (mRaven->getActivated())
			mazeRunner->setRaven(mRaven->getActivated());
		else if (mMoveButton->getActivated())
			mazeRunner->setMove(mMoveButton->getActivated());
		mazeRunner->update();
		
		//Clear screen
		SDL_SetRenderDrawColor(sdl_Setup->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		//Clear screen
		SDL_RenderClear(sdl_Setup->getRenderer());


		//Everything to be rendered in this method
		renderAll();

		//Update screen
		SDL_RenderPresent(sdl_Setup->getRenderer());
	}
}