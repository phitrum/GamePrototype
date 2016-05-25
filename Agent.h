#pragma once
#include "constants.h"
#include "maze.h"
#include <queue>
#include <vector>
#include <queue>
#include <stack>

//
enum nMove
{
	UP, LEFT, DOWN, RIGHT, 
	NA
};

enum States
{
	RUNNING, STOPPED, UNCHOSEN
};

class Agent
{
protected:

	//X and Y position of agent (world position)
	double wPos[2];

	//pos relative to maze
	int mazePos[2];
	std::vector<SDL_Rect*> path;

	SDL_Renderer* rendererCopy;
	//Agent texture
	LTexture* actorTexture;
	States mCurrentState;
	//Places players moves
	std::queue<nMove> moveStack;
	std::stack<nMove> moveSS;
	std::stack<nMove> smartStack;
	bool solved;
	//copy of maze
	Maze* mMaze;
	nMove oppositeDirection(nMove move);
	nMove move(int r, int c, nMove direction,int movesLeft);
	nMove smartMove(int r, int c, nMove direction);
	//Booleans that determine what movement method the runner will use
	bool mRaven, mPsychic,none,kruskal;
public:

	Agent(int x, int y,Maze* maze,SDL_Renderer* gRenderer,int solveType,bool k);
	~Agent();
	void update();

	//Handles input for player
	void input(SDL_Event* e);

	void draw(SDL_Renderer* gRenderer);

	//Sets movement pattern
	void setRaven(bool a);
	void setMove(bool a);
};