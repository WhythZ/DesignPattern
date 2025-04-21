#include "ResourceManager.h"
#include <SDL_image.h>

ResourcesManager* ResourcesManager::manager = nullptr;

ResourcesManager* ResourcesManager::Instance()
{
    if (!manager)
        manager = new ResourcesManager();
    return manager;
}

ResourcesManager::ResourcesManager()
{
    loaderPool[".jpg"] = loaderPool[".png"] =
        [&](const std::filesystem::path& path)
        {
            SDL_Texture* texture = IMG_LoadTexture(renderer, path.u8string().c_str());
            textureResIDList.push_back(path.stem().u8string());
            texturePool[path.stem().u8string()] = texture;
        };

    loaderPool[".wav"] = loaderPool[".mp3"] =
        [&](const std::filesystem::path& path)
        {
            Mix_Chunk* audio = Mix_LoadWAV(path.u8string().c_str());
            audioResIDList.push_back(path.stem().u8string());
            audioPool[path.stem().u8string()] = audio;
        };

    loaderPool[".ttf"] = loaderPool[".otf"] =
        [&](const std::filesystem::path& path)
        {
            FontWrapper* font = new FontWrapper(path.u8string().c_str());
            fontResIDList.push_back(path.stem().u8string());
            fontPool[path.stem().u8string()] = font;
        };
}

ResourcesManager::~ResourcesManager()
{
    for (auto& pair : fontPool)
        delete pair.second;
    for (auto& pair : audioPool)
        Mix_FreeChunk(pair.second);
    for (auto& pair : texturePool)
        SDL_DestroyTexture(pair.second);
}

void ResourcesManager::Load(SDL_Renderer* renderer)
{
    using namespace std::filesystem;

    this->renderer = renderer;

    for (const auto& entry : directory_iterator("Assets"))
    {
        if (entry.is_regular_file())
        {
            const path& path = entry.path();
            auto itor = loaderPool.find(path.extension().u8string());
            if (itor != loaderPool.end())
                itor->second(path);
        }
    }
}

FontWrapper* ResourcesManager::findFont(const std::string& id)
{
    return fontPool[id];
}

Mix_Chunk* ResourcesManager::findAudio(const std::string& id)
{
    return audioPool[id];
}

SDL_Texture* ResourcesManager::findTexture(const std::string& id)
{
    return texturePool[id];
}

const ResourcesManager::ResIDList& ResourcesManager::getFontResIDList() const
{
    return fontResIDList;
}

const ResourcesManager::ResIDList& ResourcesManager::getAudioResIDList() const
{
    return audioResIDList;
}

const ResourcesManager::ResIDList& ResourcesManager::getTextureResIDList() const
{
    return textureResIDList;
}