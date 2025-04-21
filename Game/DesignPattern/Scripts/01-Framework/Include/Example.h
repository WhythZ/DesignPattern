#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <SDL.h>

#include "ResourceManager.h"

class Example
{
public:
	Example() {}
	virtual ~Example() = default;

	virtual void on_enter() {}
	virtual void on_exit() {}

	virtual void on_input(const SDL_Event* event) {}
	virtual void OnUpdate(float delta) {}
	virtual void OnRender(SDL_Renderer* renderer) {}

};

#endif
