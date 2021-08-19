#ifndef GAME_H
#define GAME_H

#include "LuaManager.h"
#include "Window.h"
#include "Renderable.h"

class Game
{
private:
	Window* window;
	LuaManager* luaMgr;

public:
	Game();
	~Game();

	void Run();
	void Input();
	void Update();
	void Render();
};

#endif

