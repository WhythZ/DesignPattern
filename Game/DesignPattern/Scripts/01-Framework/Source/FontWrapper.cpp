#include "FontWrapper.h"

FontWrapper::FontWrapper(const std::string path)
{
	this->path = path;
}

FontWrapper::~FontWrapper()
{
	for (auto& pair : fontPool)
		TTF_CloseFont(pair.second);
}

TTF_Font* FontWrapper::GetFont(int size)
{
	TTF_Font* font = fontPool[size];

	if (!font)
	{
		font = TTF_OpenFont(path.c_str(), size);
		fontPool[size] = font;
	}
	return font;
}