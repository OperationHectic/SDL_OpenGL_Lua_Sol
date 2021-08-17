/*#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <gl/glew.h>
#include <SDL/SDL_opengl.h>
#include <string>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

//#pragma comment(lib, "liblua53.a")

void RunSDL(std::string text);

int main(int argc, char* argv[])
{
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script_file("./scripts/lua/test.lua");
    std::string val = lua["a"];

    RunSDL(val);

	return EXIT_SUCCESS;
}

void RunSDL(std::string text)
{
    SDL_Window* window = NULL;

    SDL_Surface* screenSurface = NULL;

    SDL_Renderer* renderer = NULL;

    SDL_Texture* texture = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (TTF_Init() == -1)
            {
                std::cout << "TTF Failed\n";
            }
            else
            {
                TTF_Font* font = TTF_OpenFont("arial.ttf", 25);


                SDL_Color color = { 0, 255, 0 };
                SDL_Surface* surface = TTF_RenderText_Solid(font,
                    text.c_str(), color);

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

                TTF_CloseFont(font);

                int texW = 0;
                int texH = 0;
                SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
                SDL_Rect dstrect = { 0, 0, texW, texH };

                screenSurface = SDL_GetWindowSurface(window);

                //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
                texture = SDL_CreateTextureFromSurface(renderer, surface);

                //SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderCopy(renderer, texture, NULL, &dstrect);
                SDL_RenderPresent(renderer);

                //SDL_UpdateWindowSurface(window);

                SDL_Delay(2000);

                SDL_DestroyTexture(texture);
                SDL_FreeSurface(surface);

                TTF_Quit();
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}*/

#include <iostream>
#include <string>
#include <vector>

#include "LuaManager.h"
#include "Window.h"
#include "Renderable.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    LuaManager* luaMgr = new LuaManager();
    luaMgr->SetActiveScript("./scripts/lua/test.lua");
	std::string vertexShaderStr = luaMgr->GetString("vertex");
	std::string fragmentShaderStr = luaMgr->GetString("frag");
    sol::table verticesLua = luaMgr->GetTable("vertices");
    verticesLua.for_each([&](sol::object const& key, sol::object const& value) {
        std::cout << value.as<float>() << '\n';
    });

	Window* window = new Window(640, 480);
	//window->Init(initGL, vertexShaderStr, fragmentShaderStr);
	//window->Run(render);

	std::vector<GLfloat> vertices = {
		-1.0f, -1.0f, 0.0f,
		 1.0f,  -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	Renderable* r = new Renderable(vertices, vertexShaderStr, fragmentShaderStr);
	window->AddRenderable(r);
	window->Init();
	window->Run();

	delete window;

	return 0;
}