#ifndef WINDOW_H
#define WINDOW_H

#include <cstdint>
#include <string>
#include <vector>
#include <gl/glew.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include "Renderable.h"

typedef void (*Callback)();
typedef void (*Setup)(std::string, std::string);

class Window
{
private:
	SDL_Window* gWindow = NULL;
	SDL_GLContext gContext;
	uint32_t width, height;
	std::vector<Renderable*> renderables;

public:
	Window(uint32_t width, uint32_t height);
	~Window();

	void Init();
	void Run();
	void AddRenderable(Renderable* renderable);
};

#endif

