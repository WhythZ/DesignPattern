#include "Adapter.h"

#include <fstream>
#include <sstream>

#include <imgui.h>
#include <cJSON.h>
#include <pugixml.hpp>

using namespace _AdapterPattern;

bool JSONLoader::Load(GameObjectList& _dst, const std::string& _path)
{
	std::ifstream _file(_path);
	if (!_file.good())
		return false;

	std::stringstream _strStream;
	_strStream << _file.rdbuf(); _file.close();

	cJSON* _jsonRoot = cJSON_Parse(_strStream.str().c_str());
	if (!_jsonRoot) return false;

	cJSON* _jsonGameObject = nullptr;
	cJSON_ArrayForEach(_jsonGameObject, _jsonRoot)
	{
		cJSON* _jsonRect = cJSON_GetObjectItem(_jsonGameObject, "rect");
		cJSON* _jsonTexture = cJSON_GetObjectItem(_jsonGameObject, "texture");
		cJSON* _jsonRotation = cJSON_GetObjectItem(_jsonGameObject, "rotation");
		SDL_Rect rect =
		{
			cJSON_GetObjectItem(_jsonRect, "x")->valueint, cJSON_GetObjectItem(_jsonRect, "y")->valueint,
			cJSON_GetObjectItem(_jsonRect, "w")->valueint, cJSON_GetObjectItem(_jsonRect, "h")->valueint,
		};
		_dst.emplace_back(ResourcesManager::Instance()->findTexture(_jsonTexture->valuestring), rect, _jsonRotation->valuedouble);
	}

	cJSON_Delete(_jsonRoot);
	return true;
}

bool _AdapterPattern::XMLLoader::Load(GameObjectList& _dst, const std::string& _path)
{
	pugi::xml_document _doc;
	if (!_doc.load_file(_path.c_str())) return false;

	pugi::xml_node _xmlRoot = _doc.child("Scene");
	for (const pugi::xml_node& _xmlGameObject : _xmlRoot.children("GameObject"))
	{
		const pugi::xml_node& _xmlRect = _xmlGameObject.child("Rect");
		double _rotation = _xmlGameObject.attribute("rotation").as_double();
		SDL_Texture* _texture = ResourcesManager::Instance()->findTexture(_xmlGameObject.attribute("texture").as_string());
		SDL_Rect _rect =
		{
			_xmlRect.attribute("x").as_int(), _xmlRect.attribute("y").as_int(),
			_xmlRect.attribute("w").as_int(), _xmlRect.attribute("h").as_int(),
		};
		_dst.emplace_back(_texture, _rect, _rotation);
	}

	return true;
}

AdapterPattern::AdapterPattern(SDL_Renderer* _renderer)
{
	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 768, 768);
}

AdapterPattern::~AdapterPattern()
{
	SDL_DestroyTexture(textureTarget);
}

void AdapterPattern::OnUpdate(float _delta)
{
	if (ImGui::Button(u8"加载 \"Data/Scene.json\" 场景文件", { ImGui::GetContentRegionAvail().x / 2, 35 }))
	{
		ReloadScene(&jsonLoader, "Data/Scene.json");
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"加载 \"Data/Scene.xml\" 场景文件", { ImGui::GetContentRegionAvail().x, 35 }))
	{
		ReloadScene(&xmlLoader, "Data/Scene.xml");
	}

	ImGui::BeginChild("scene", ImGui::GetContentRegionAvail());
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::EndChild();
}

void AdapterPattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
	SDL_RenderClear(_renderer);

	for (const GameObject& _go : gameObjectList)
	{
		SDL_RenderCopyEx(_renderer, _go.texture, nullptr, 
			&_go.rect, _go.rotation, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	}

	SDL_SetRenderTarget(_renderer, nullptr);
}

void AdapterPattern::ReloadScene(_AdapterPattern::LoaderImpl* _loader, const std::string& _path)
{
	gameObjectList.clear();

	if (!_loader->Load(gameObjectList, _path))
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"Reload Failed",
			u8"重新加载场景文件失败，请检查文件是否存在及文件内容是否符合标准", nullptr);
	}
}
