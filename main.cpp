#include <iostream>
#include <string>
#include <vector>

#include "Game.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	Game* game = new Game();
	game->Run();
	delete game;

	return 0;
}