#include "Agent.h"

Agent::Agent(int x, int y,Maze* maze,SDL_Renderer* gRenderer,int solveType,bool k)
{
	wPos[0] = x,
	wPos[1] = y;
	solved = false;
	mazePos[0] = 1;
	mazePos[1] = 0;
	
	//sets intitial state of runner
	mCurrentState = STOPPED;

	//Init movement pattern to nothing
	mRaven = false;
	mPsychic = false;
	kruskal = k;
	mMaze = maze;
	actorTexture = new LTexture;
	rendererCopy = gRenderer;
	actorTexture->loadFromFile(gRenderer, "images\\mazeRunner.png");
	none = false;

	if (solveType == -1)
	{
		none = true;
	}
	//Solves maze by trial and error
	else if (solveType == 1)
	{
		mRaven = false;
		moveSS.push(DOWN);
		move(mazePos[1] + 1, mazePos[0], NA, 1);
	}
	//Sees into the future to solve
	else if (solveType == 2)
	{
		mPsychic = false;
		smartMove(mazePos[1] + 1, mazePos[0], NA);
		smartStack.push(DOWN);
	}



	path.push_back(new SDL_Rect);
	path.back()->h = 16;
	path.back()->w = 16;
	path.back()->x = wPos[0];
	path.back()->y = wPos[1];
	for (int r = 0; r < mMaze->mRows; r++)
	{
		for (int c = 0; c < mMaze->mColumns; c++)
		{
			std::cout << mMaze->getMaze().at(r)->at(c);
		}std::cout << std::endl;
	}
}

void Agent::update()
{
	if (((!moveStack.empty() || !smartStack.empty()) && mCurrentState != STOPPED) && (mRaven == true || mPsychic==true) && !none)
	{
		nMove nextMove = NA;
		if (mPsychic)
			nextMove = moveStack.front();
		else if (mRaven)
			nextMove = smartStack.top();
		//1 = y
		//0 = x
		if (nextMove == UP)
		{
			wPos[1] -= 16;
		}
		else if (nextMove == LEFT)
		{
			wPos[0] -= 16;
		}
		else if (nextMove == RIGHT)
		{
			wPos[0] += 16;
		}
		else if (nextMove == DOWN)
		{
			wPos[1] += 16;        
		}
			
		
		path.push_back(new SDL_Rect);
		path.back()->h = 16;
		path.back()->w = 16;
		path.back()->x = wPos[0];
		path.back()->y = wPos[1];
		if (mPsychic)
			moveStack.pop();
		else if (mRaven)
			smartStack.pop();
	}mCurrentState = STOPPED;
}

nMove Agent::move(int r, int c,nMove direction,int movesLeft)
{
	if (solved == false && r < (mMaze->mRows - 1) && c < (mMaze->mColumns - 1)
		&& r>0 && c>0 && mMaze->getMaze().at(r)->at(c) != 'H' && mMaze->getMaze().at(r)->at(c) != 'X' 
		|| (r == (mMaze->mRows - 1) && c == (mMaze->mColumns - 3)))
	{	
		mMaze->getMaze().at(r)->at(c) = 'X';
		moveStack.push(direction);

		if (!solved)
		{
			mazePos[0] = c;
			mazePos[1] = r;
		}
		
		if ((r == (mMaze->mRows - 1) && c == (mMaze->mColumns - 3)) || (kruskal == true && (r == (mMaze->mRows - 1) && c == (mMaze->mColumns - 2))))
		{
			solved = true;
			return NA;
		}

		move(r + 1, c, DOWN, movesLeft);
		move(r, c + 1, RIGHT, movesLeft);
		move(r, c - 1, LEFT, movesLeft);
		move(r - 1, c, UP, movesLeft);
			
		/*If runner misteps the opposite direction is pushed 
		 *on a stack*/
		if (!solved)
			moveSS.push(oppositeDirection(direction));
		}
	//Pushes all the misteps in order on to the queue
	while (!moveSS.empty())
	{
		moveStack.push(moveSS.top());
		moveSS.pop();
	}

	return NA;
}

nMove Agent::smartMove(int r, int c, nMove direction)
{
	if (solved == false && r < (mMaze->mRows - 1) && c < (mMaze->mColumns - 1)
		&& r>0 && c>0 && mMaze->getMaze().at(r)->at(c) != 'H' && mMaze->getMaze().at(r)->at(c) != 'X'
		|| (r == (mMaze->mRows - 1) && c == (mMaze->mColumns - 3)))
	{
		mMaze->getMaze().at(r)->at(c) = 'X';
		

		//if (!solved)
		//{
			///mazePos[0] = c;
			//mazePos[1] = r;
		//}

		if ((r == (mMaze->mRows - 1) && c == (mMaze->mColumns - 3)))
		{
			smartStack.push(direction);
			solved = true;
			return NA;
		}

		smartMove(r + 1, c, DOWN);
		smartMove(r, c + 1, RIGHT);
		smartMove(r, c - 1, LEFT);
		smartMove(r - 1, c, UP);

		if (solved)
			smartStack.push(direction);
	}

	return NA;
}

nMove Agent::oppositeDirection(nMove move)
{
	if (move == DOWN)
		move = UP;
	else if (move == UP)
		move = DOWN;
	else if (move == LEFT)
		move = RIGHT;
	else if (move == RIGHT)
		move = LEFT;

	return move;
}

void Agent::draw(SDL_Renderer* gRenderer)
{

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
	for (int i = 0; i != path.size();i++)
	{
		SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(gRenderer, 255, 87, 228, 200);
		SDL_RenderFillRect(gRenderer, path.at(i));
	}
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_NONE);
	actorTexture->render(gRenderer, wPos[0], wPos[1]);
	
}

void Agent::input(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN)// && e->key.repeat == 0)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_SPACE:
				mCurrentState = RUNNING;
		}
	}
	else if (e->type == SDL_KEYUP)// && e->key.repeat == 0)
	{
		switch (e->key.keysym.sym)
		{
		case SDLK_SPACE:
			mCurrentState = STOPPED; break;
		}
	}
}

void Agent::setRaven(bool a)
{
	mRaven = a;
}

void Agent::setMove(bool a)
{
	mPsychic = true;
}

//MIX DELETION PROBLEM!!!!!!!!
Agent::~Agent()
{
	mMaze = NULL;
	delete mMaze;
	delete actorTexture;
	rendererCopy = NULL;
	delete rendererCopy;
}