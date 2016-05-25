#include "maze.h"

Maze::Maze(const int w, const int h) : mRows(h), mColumns(w)
{
	//Init Maze w/ H's
	srand(time(NULL));
	mMaze.reserve(100);
	for (int r = 0; r < mRows; r++)
	{
		mMaze.push_back(new std::vector<char>);
		for (int c = 0; c < mColumns; c++)
		{
			//if (r == 0 || r == mRows-1)
				mMaze.at(r)->push_back('H');
			///else if (c % 2 == 0)
			//	mMaze.at(r)->push_back('H');
			//else
				//mMaze.at(r)->push_back('X');

		}
			
	}

	//Sets size of walls
	for (int r = 0; r < mRows; r++)
	{
		mWalls.push_back(new std::vector<SDL_Rect*>);
		for (int c = 0; c < mColumns; c++)
		{
			mWalls.at(r)->push_back(new SDL_Rect);
			mWalls.at(r)->at(c)->h = 16;
			mWalls.at(r)->at(c)->w = 16;
			mWalls.at(r)->at(c)->x = c * 16 + 180;
			mWalls.at(r)->at(c)->y = r * 16 + 100;
		}

	}



	//Loops until a possible maze is generated
	while (mMaze.at(0)->at(1) != ' ')
	{	
		//Set starting point to ' '
		mMaze.at(mRows - 1)->at(mColumns - 3) = ' ';

		//Generates (imperfect) random maze
		makeMaze(mRows - 2, mColumns - 3);

		//Checks if it need to reset maze
		if (mMaze.at(0)->at(1) != ' ')
			resetMaze();

		srand(time(NULL));
	}

}

Maze::~Maze()
{
	for (int r = 0; r < mRows; r++)
		delete mMaze.at(r);
}

//Checks if area is available
bool Maze::available(int r, int c)
{
	//Counts open spaces (must be three)
	int openCount = 0;
	
	if (mMaze.at(r + 1)->at(c) != ' ')
		openCount++;
	if (mMaze.at(r)->at(c + 1) != ' ')
		openCount++;
	if (mMaze.at(r)->at(c - 1) != ' ')
		openCount++;
	if (mMaze.at(r - 1)->at(c) != ' ')
		openCount++;

	if (openCount>=3)//(openCount >= 3 )//&& !(openCount >= 4))
	{
		return true;
	}

	return false;
}

std::array<int, 2> Maze::getCenter()
{
	std::array<int, 2> temp;
	temp[0] = 16*(mColumns-1)+200;
	temp[1] = 16 * (mRows) + 100;

	return temp;
}

void Maze::makeMaze(int r, int c)
{
	//Make sure inbounds or is finish
	if ((r < (mRows - 1) && c < (mColumns - 1) && r>0 && c>0 && mMaze.at(r)->at(c) != ' ' )|| (r == (0) && c == (1)))
		{

			//Wall handling (checking order does matter here)
			if (!(r == (0) && c == (1)) && available(r, c))
			{
				mMaze.at(r)->at(c) = ' ';
				Permutater ran(3);// = new Permutater(3);
				while (!ran.nums.empty())
				{
					int rnum = ran.getRandom();
					if (rnum == 2)
					{
						makeMaze(r, c - 1);//left
					}
					if (rnum == 0) //right
					{
						makeMaze(r, c + 1);
					}
					if (rnum == 1)
					{
						makeMaze(r - 1, c); //up
					}

					if (rnum == 3)
						makeMaze(r + 1, c);//down,
					//cout << ran.getRandom()<<endl;
				}
			}
			else if ((r == (0) && c == (1)))
				mMaze.at(r)->at(c) = ' ';
		}
}

void Maze::draw(SDL_Renderer* gRenderer)
{
	for (int r = 0; r < mRows; r++)
	{
		for (int c = 0; c < mColumns; c++)
		{
			if (mMaze.at(r)->at(c) == 'H')
			{
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderFillRect(gRenderer, mWalls.at(r)->at(c));
			}
		}
	}
}

void Maze::resetMaze()
{
	for (int r = 0; r < mRows; r++)
	{
		std::fill(mMaze.at(r)->begin(), mMaze.at(r)->end(), 'H');
	}
	while (mMaze.at(0)->at(1) != ' ')
	{
		//Set starting point to ' '
		mMaze.at(mRows - 1)->at(mColumns - 3) = ' ';

		//Generates (imperfect) random maze
		makeMaze(mRows-2, mColumns -3);

		//Checks if it need to reset maze
		if (mMaze.at(0)->at(1) != ' ')
			resetMaze();


	}
}