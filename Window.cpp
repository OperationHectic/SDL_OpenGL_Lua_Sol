#include "Window.h"
#include <iostream>

Window::Window(uint32_t width, uint32_t height) 
	: width(width), height(height), gContext(NULL)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << '\n';
	}
	else
	{
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				/*if (!initGL(vertexShaderStr, fragmentShaderStr))
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
				else
				{
					std::cout << "Setting up GL\n";
				}*/
			}
		}
	}
}

Window::~Window()
{
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void Window::Init()
{
	//setup(vertexShader, fragmentShader);
	for (auto* renderable : renderables)
	{
		renderable->Create();
	}
}

void Window::Run()
{
	SDL_Event e;
	bool quit = false;

	SDL_StartTextInput();

	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//callback();
		for (auto* renderable : renderables)
		{
			renderable->Render();
		}

		SDL_GL_SwapWindow(gWindow);
	}

	SDL_StopTextInput();
}

void Window::AddRenderable(Renderable* renderable)
{
	renderables.emplace_back(renderable);
}
