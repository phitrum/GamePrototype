#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "gamePrototype.h";

int main(int argc, char* args[])
{
	_CrtDumpMemoryLeaks;
	GamePrototype game;
	game.run();
	return 0;
}