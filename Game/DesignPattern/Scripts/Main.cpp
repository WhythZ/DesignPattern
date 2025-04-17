#define SDL_MAIN_HANDLED

//引入应用主循环
#include "Application.h"

//
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

int main(int argc, char** argv)
{
	return Application::instance()->run(argc, argv);
}