#include "Game.h"

#include <iostream>
#include <vector>

Game::Game()
{
	luaMgr = new LuaManager();
	luaMgr->SetActiveScript("./scripts/lua/appSettings.lua");
	window = new Window(luaMgr->GetInteger("WIN_WIDTH"), luaMgr->GetInteger("WIN_HEIGHT"));

	std::vector<GLfloat> vertices;
	luaMgr->SetActiveScript("./scripts/lua/test.lua");
	std::string vertexShaderStr = luaMgr->GetString("vertex");
	std::string fragmentShaderStr = luaMgr->GetString("frag");
	sol::table verticesLua = luaMgr->GetTable("vertices");
	verticesLua.for_each([&](sol::object const& key, sol::object const& value) {
		vertices.emplace_back(value.as<float>());
	});

	
	Renderable* r = new Renderable(vertices, vertexShaderStr, fragmentShaderStr);
	window->AddRenderable(r);
	window->Init();
}

Game::~Game()
{
	delete window;
	delete luaMgr;
}

void Game::Run()
{
	window->Run();
}

void Game::Input()
{
}

void Game::Update()
{
}

void Game::Render()
{
}
