#define SDL_MAIN_HANDLED

#include "Application.h"

#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

int main(int argc, char** argv)
{
	return Application::Instance()->Run(argc, argv);
}