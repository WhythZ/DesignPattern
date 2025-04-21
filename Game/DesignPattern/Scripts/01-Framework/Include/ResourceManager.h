#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include <string>
#include <vector>
#include <functional>
#include <filesystem>
#include <unordered_map>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "FontWrapper.h"

class ResourcesManager
{
public:
	using ResIDList = std::vector<std::string>;

private:
	static ResourcesManager* manager;
	SDL_Renderer* renderer = nullptr;
	std::unordered_map<std::string, FontWrapper*> fontPool;
	std::unordered_map<std::string, Mix_Chunk*> audioPool;
	std::unordered_map<std::string, SDL_Texture*> texturePool;
	ResIDList fontResIDList, audioResIDList, textureResIDList;
	std::unordered_map<std::string, std::function<void(const std::filesystem::path& path)>> loaderPool;

public:
	static ResourcesManager* Instance();

	void Load(SDL_Renderer*);

	FontWrapper* findFont(const std::string&);
	Mix_Chunk* findAudio(const std::string&);
	SDL_Texture* findTexture(const std::string&);

	const ResIDList& getFontResIDList() const;
	const ResIDList& getAudioResIDList() const;
	const ResIDList& getTextureResIDList() const;

private:
	ResourcesManager();
	~ResourcesManager();
};

#endif
