#include "Atlas.h"
#include "ResourceManager.h"

void Atlas::Load(const char* pathTemplate, int num)
{
	for (int i = 0; i < num; i++)
	{
		char path_file[256];
		sprintf_s(path_file, pathTemplate, i + 1);
		SDL_Texture* texture = ResourcesManager::Instance()->findTexture(path_file);
		texList.push_back(texture);
	}
}

void Atlas::Clear()
{
	texList.clear();
}

void Atlas::AddTexture(SDL_Texture* texture)
{
	texList.push_back(texture);
}

SDL_Texture* Atlas::GetTexture(int idx) const
{
	if (idx < 0 || idx >= texList.size())
		return nullptr;
	return texList[idx];
}

int Atlas::GetSize() const
{
	return (int)texList.size();
}