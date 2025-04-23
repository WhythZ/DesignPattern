#include "Atlas.h"
#include "ResourceManager.h"

void Atlas::Load(const char* _pathTemplate, int _num)
{
	for (int i = 0; i < _num; i++)
	{
		char _pathFile[256];
		sprintf_s(_pathFile, _pathTemplate, i + 1);
		SDL_Texture* _texture = ResourcesManager::Instance()->findTexture(_pathFile);
		texList.push_back(_texture);
	}
}

void Atlas::Clear()
{
	texList.clear();
}

void Atlas::AddTexture(SDL_Texture* _texture)
{
	texList.push_back(_texture);
}

SDL_Texture* Atlas::GetTexture(int _idx) const
{
	if (_idx < 0 || _idx >= texList.size())
		return nullptr;
	return texList[_idx];
}

int Atlas::GetSize() const
{
	return (int)texList.size();
}