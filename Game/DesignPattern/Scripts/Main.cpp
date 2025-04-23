#define SDL_MAIN_HANDLED

#include "Application.h"

#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

int main(int _argc, char** _argv)
{
	return Application::Instance()->Run(_argc, _argv);
}