#ifndef _FONT_WRAPPER_H_
#define _FONT_WRAPPER_H_

#include <string>
#include <unordered_map>

#include <SDL_ttf.h>

class FontWrapper
{
private:
	std::string path;
	std::unordered_map<int, TTF_Font*> fontPool;

public:
	FontWrapper(const std::string);
	~FontWrapper();
	TTF_Font* GetFont(int);
};

#endif
