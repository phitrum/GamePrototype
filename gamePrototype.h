#pragma once
#include "constants.h"
#include "sdlsetup.h"
#include "maze.h"
#include "Agent.h"
#include "simpleButton.h"
#include "compMaze.h"

class GamePrototype
{
public: 
	//SDL wrapper class
	SDL_Setup* sdl_Setup;

	//Constructor
	GamePrototype();

	//Loads All media FOR NOW
	void loadMedia();

	//Runs Game Loop
	void run();
	~GamePrototype();
private: 
	LTexture* tempBackground;

	//Maze
	Maze* mRMaze;
	CompMaze* compMaze;

	//Raven button
	Button* mRaven;
	//My button
	Button* mMoveButton;
	//My maze
	Button* mAwesomeButton;
	Button* mKruskalButton;

	//Maze Runner
	Agent* mazeRunner;

	//Sets state for maze
	bool kruskal, depth;

	/*Method will contain everything that is to be 
	/*rendered*/
	void renderAll();
};