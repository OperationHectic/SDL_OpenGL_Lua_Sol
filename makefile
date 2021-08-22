compile:
	g++ -std=c++17 -I ./includes *.cpp -lSDL2 -lglut -lGL -lGLEW -lGLU -llua5.3 -o game