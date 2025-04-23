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
        [&](const std::filesystem::path& _path)
        {
            SDL_Texture* _texture = IMG_LoadTexture(renderer, _path.u8string().c_str());
            textureResIDList.push_back(_path.stem().u8string());
            texturePool[_path.stem().u8string()] = _texture;
        };

    loaderPool[".wav"] = loaderPool[".mp3"] =
        [&](const std::filesystem::path& _path)
        {
            Mix_Chunk* _audio = Mix_LoadWAV(_path.u8string().c_str());
            audioResIDList.push_back(_path.stem().u8string());
            audioPool[_path.stem().u8string()] = _audio;
        };

    loaderPool[".ttf"] = loaderPool[".otf"] =
        [&](const std::filesystem::path& _path)
        {
            FontWrapper* _font = new FontWrapper(_path.u8string().c_str());
            fontResIDList.push_back(_path.stem().u8string());
            fontPool[_path.stem().u8string()] = _font;
        };
}

ResourcesManager::~ResourcesManager()
{
    for (auto& _pair : fontPool)
        delete _pair.second;
    for (auto& _pair : audioPool)
        Mix_FreeChunk(_pair.second);
    for (auto& _pair : texturePool)
        SDL_DestroyTexture(_pair.second);
}

void ResourcesManager::Load(SDL_Renderer* _renderer)
{
    using namespace std::filesystem;

    renderer = _renderer;

    for (const auto& _entry : directory_iterator("Assets"))
    {
        if (_entry.is_regular_file())
        {
            const path& _path = _entry.path();
            auto _iter = loaderPool.find(_path.extension().u8string());
            if (_iter != loaderPool.end())
                _iter->second(_path);
        }
    }
}

FontWrapper* ResourcesManager::findFont(const std::string& _id)
{
    return fontPool[_id];
}

Mix_Chunk* ResourcesManager::findAudio(const std::string& _id)
{
    return audioPool[_id];
}

SDL_Texture* ResourcesManager::findTexture(const std::string& _id)
{
    return texturePool[_id];
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