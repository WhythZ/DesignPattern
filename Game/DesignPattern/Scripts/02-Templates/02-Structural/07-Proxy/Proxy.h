#ifndef _PROXY_H_
#define _PROXY_H_

#include <string>

#include "Example.h"

class ProxyPattern : public Example
{
private:
	int fontSize = 50;
	bool needUpdate = true;
	SDL_Rect rectText = { 0 };
	SDL_Texture* textureText = nullptr;
	SDL_Texture* textureTarget = nullptr;
	std::string strText = "Hello World !";
	float colorText[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

public:
	ProxyPattern(SDL_Renderer*);
	~ProxyPattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;

private:
	void UpdateTextureText(SDL_Renderer*);
};

#endif
