#ifndef _PROXY_H_
#define _PROXY_H_

#include <string>

#include "Example.h"

class ProxyPattern : public Example
{
public:
	ProxyPattern(SDL_Renderer* renderer);
	~ProxyPattern();

	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	int fontSize = 50;
	bool needUpdate = true;
	SDL_Rect rect_text = { 0 };
	SDL_Texture* textureText = nullptr;
	SDL_Texture* textureTarget = nullptr;
	std::string str_text = "Hello World !";
	float colorText[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

private:
	void UpdateTextureText(SDL_Renderer* renderer);

};

#endif
