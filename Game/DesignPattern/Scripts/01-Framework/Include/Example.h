#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include <SDL.h>

#include "ResourceManager.h"

class Example
{
public:
	Example() = default;
	virtual ~Example() = default;

	virtual void OnEnter();
	virtual void OnExit();

	virtual void OnInput(const SDL_Event*);
	virtual void OnUpdate(float);
	virtual void OnRender(SDL_Renderer*);
};

#endif
