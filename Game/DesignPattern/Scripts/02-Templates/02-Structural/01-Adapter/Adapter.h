#ifndef _ADAPTER_H_
#define _ADAPTER_H_

#include <string>
#include <vector>

#include "Example.h"

namespace _AdapterPattern
{
	struct GameObject
	{
		double rotation = 0;
		SDL_Rect rect = { 0 };
		SDL_Texture* texture = nullptr;

		GameObject(SDL_Texture* _texture, const SDL_Rect& _rect, double _rotation)
			: texture(_texture), rect(_rect), rotation(_rotation) {}
	};

	using GameObjectList = std::vector<GameObject>;

	class LoaderImpl
	{
	public:
		virtual bool Load(GameObjectList&, const std::string&) = 0;
	};

	class JSONLoader : public LoaderImpl
	{
	public:
		bool Load(GameObjectList&, const std::string&) override;
	};

	class XMLLoader : public LoaderImpl
	{
	public:
		bool Load(GameObjectList&, const std::string&) override;
	};
}

class AdapterPattern : public Example
{
private:
	SDL_Texture* textureTarget = nullptr;
	_AdapterPattern::XMLLoader xmlLoader;
	_AdapterPattern::JSONLoader jsonLoader;
	_AdapterPattern::GameObjectList gameObjectList;

public:
	AdapterPattern(SDL_Renderer*);
	~AdapterPattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;

private:
	void ReloadScene(_AdapterPattern::LoaderImpl*, const std::string&);
};

#endif
