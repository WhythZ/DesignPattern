#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include <lua.hpp>
#include <imgui.h>
#include <TextEditor.h>

#include "Example.h"

class InterpreterPattern : public Example
{
public:
	InterpreterPattern(SDL_Renderer* renderer);
	~InterpreterPattern();

	void OnUpdate(float delta) override;

private:
	TextEditor code_editor;
	ImFont* font_code = nullptr;
	SDL_Texture* textureTarget = nullptr;

};

#endif
