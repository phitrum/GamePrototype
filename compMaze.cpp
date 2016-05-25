#include "compMaze.h"

CompMaze::CompMaze(const int w, const int h)
	: WIDTH(w), HEIGHT(h), Maze(w * 2 + 1, h * 2 + 1)
{
	std::vector<std::pair<int, int> > all_edges;
	std::vector<std::pair<int, int> > mst_edges;
	std::vector<std::pair<int, int> > points;


	matrix.reserve(100);
	CreateEdges(&all_edges);
	srand(time(0));
	ShuffleVector(&all_edges);
	Kruskal(all_edges, &mst_edges);
	ConvertToPaintedPoint(mst_edges, &points);



	//Sets size of walls
	for (int r = 0; r < HEIGHT * 2 + 1; r++)
	{
		mWalls.push_back(new std::vector<SDL_Rect*>);
		for (int c = 0; c < WIDTH * 2 + 1; c++)
		{
			mWalls.at(r)->push_back(new SDL_Rect);
			mWalls.at(r)->at(c)->h = 16;
			mWalls.at(r)->at(c)->w = 16;
			mWalls.at(r)->at(c)->x = c * 16 + 180;
			mWalls.at(r)->at(c)->y = r * 16 + 100;
		}

	}

	for (int r = 0; r < HEIGHT * 2 - 1; r++)
	{
		matrix.push_back(new std::vector<char>);
		for (int c = 0; c < WIDTH * 2 - 1; c++)
		{
			//continue;
			matrix.at(r)->push_back('X');
		}
	}

	for (int r = 0; r < HEIGHT * 2 - 1; r++)
	{
		for (int c = 0; c < WIDTH * 2 - 1; c++)
		{
			if (matrix.at(r)->at(c) != ' ')
			{
				matrix.at(r)->at(c) = ' ';
			}
		}
	}
	
	Draw(points);
	//init maze to be returned
	for (int r = 0; r < HEIGHT * 2 + 1; r++)
	{
		mMaze.push_back(new std::vector<char>);
		for (int c = 0; c < WIDTH * 2 + 1; c++)
		{
				mMaze.at(r)->push_back('H');
		}
	}

	for (int r = 0; r < HEIGHT * 2 + 1; r++)
	{
		for (int c = 0; c < WIDTH * 2 + 1; c++)
		{
			if (r == 0)
			{
				if (c == 1)
					mMaze.at(r)->at(c) = (' ');
				if (c < WIDTH * 2-1)
					mMaze.at(r+1)->at(c+1) = matrix.at(r)->at(c);
			}
			else if (r == HEIGHT * 2)
			{
				if (c == WIDTH * 2 - 1)
					mMaze.at(r)->at(c) = (' ');
			}
			else if (c == 0)
			{
				if (c < WIDTH * 2 - 1 && r < HEIGHT * 2 -1)
					mMaze.at(r + 1)->at(c + 1) = matrix.at(r)->at(c);
			}
			else
			{
				if (c>0 && c < WIDTH * 2 - 1 && r < HEIGHT * 2 - 1)
				{
					mMaze.at(r + 1)->at(c + 1) = matrix.at(r)->at(c);
				}

			}
			
		}
	}
	for (int r = 0; r < HEIGHT * 2 -1; r++)
	{
		for (int c = 0; c < WIDTH * 2 -1; c++)
		{
			std::cout << matrix.at(r)->at(c);
		}std::cout << std::endl;
	}std::cout << std::endl;
	//print matrix
	for (int r = 0; r < HEIGHT*2 +1; r++)
	{
		for (int c = 0; c < WIDTH * 2 + 1; c++)
		{
			std::cout << mMaze.at(r)->at(c);
		}std::cout << std::endl;
	}

}

void CompMaze::draws(SDL_Renderer* gRenderer)
{
	for (int r = 0; r < HEIGHT * 2 + 1; r++)
	{
		for (int c = 0; c < WIDTH * 2 + 1; c++)
		{
			if (mMaze.at(r)->at(c) == 'H')
			{
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
				SDL_RenderFillRect(gRenderer, mWalls.at(r)->at(c));
			}
		}
	}
}