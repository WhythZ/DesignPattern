#include "FontWrapper.h"

FontWrapper::FontWrapper(const std::string _path)
{
	this->path = _path;
}

FontWrapper::~FontWrapper()
{
	for (auto& _pair : fontPool)
		TTF_CloseFont(_pair.second);
}

TTF_Font* FontWrapper::GetFont(int _size)
{
	TTF_Font* _font = fontPool[_size];

	if (!_font)
	{
		_font = TTF_OpenFont(path.c_str(), _size);
		fontPool[_size] = _font;
	}
	return _font;
}