#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SDL.h>

class Application
{
private:
	static Application* application;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool isQuit = false;

public:
	static Application* Instance();

	int Run(int argc, char** argv);

private:
	Application();
	~Application();
};

#endif
