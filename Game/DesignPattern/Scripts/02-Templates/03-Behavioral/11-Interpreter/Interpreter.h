#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <lua.hpp>
#include <imgui.h>
#include <TextEditor.h>

#include "Example.h"

class InterpreterPattern : public Example
{
private:
	TextEditor codeEditor;
	ImFont* fontCode = nullptr;
	SDL_Texture* textureTarget = nullptr;

public:
	InterpreterPattern(SDL_Renderer*);
	~InterpreterPattern();

	void OnUpdate(float) override;
};

#endif
