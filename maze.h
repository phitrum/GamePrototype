#pragma once
#include "constants.h"
#include <array>

//Genereator that generates random numbers
struct Permutater
{
	//int num = 0;
	std::vector<int> nums;

	Permutater(int x)
	{
		int copyX = x;
		for (int i = x; i >= 0; i--)
			nums.push_back(i);
	}

	int getRandom()
	{
		if (nums.size() == NULL)
		{
			std::cout << "size = null";
			return 0;
		}

		int ran = rand() % nums.size();
		int rnum = nums.at(ran);
		//cout << nums.size() << endl;
		nums.erase(nums.begin() + ran);
		//cout << rnum<<endl;
		return rnum;
	}
};//*ptr_Muter;

//creates matrix with a vector (This may be slower than it can be)
class Maze
{
protected:

	//SHOULD ATTEMPT TO MAKE SHARED PTR
	std::vector<std::vector<char>*> mMaze;

	//Temporary Walls
	std::vector<std::vector<SDL_Rect*>*> mWalls;

	//Recursive Make maze method
	virtual void makeMaze(int r, int c);
	bool available(int r, int c);
	
public:
	Maze(const int w, const int h);
	Maze() : mRows(0), mColumns(0){}
	Maze(int i, int q, int b) : mRows(i), mColumns(q){ b++; };
	~Maze();
	virtual void draw(SDL_Renderer* gRenderer);

	std::array<int,2> getCenter();
	void testMutate();//?????
	void resetMaze();
	const int mRows;
	const int mColumns;

	//Accessors
	std::vector<std::vector<char>*> getMaze()
	{
		return mMaze;
	}

};