#include "FontWrapper.h"

FontWrapper::FontWrapper(const std::string path)
{
	this->path = path;
}

FontWrapper::~FontWrapper()
{
	for (auto& pair : font_pool)
		TTF_CloseFont(pair.second);
}

TTF_Font* FontWrapper::get_font(int size)
{
	TTF_Font* font = font_pool[size];

	if (!font)
	{
		font = TTF_OpenFont(path.c_str(), size);
		font_pool[size] = font;
	}

	return font;
}