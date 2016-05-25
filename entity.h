#pragma once
#include "constants.h"

class Entity
{
	LTexture* entityTexture;
	int  pos[2];
	//Maze that the actor will read in
	
	virtual void update() = 0;
};