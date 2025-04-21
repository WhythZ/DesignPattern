#ifndef _FONT_WRAPPER_H_
#define _FONT_WRAPPER_H_

#include <SDL_ttf.h>

#include <string>
#include <unordered_map>

class FontWrapper
{
private:
	std::string path;
	std::unordered_map<int, TTF_Font*> font_pool;

public:
	FontWrapper(const std::string);

	~FontWrapper();

	TTF_Font* get_font(int);
};

#endif
