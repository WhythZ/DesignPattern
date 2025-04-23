#include "FactoryMethod.h"

#include <imgui.h>

using namespace _FactoryMethodPattern;

FactoryMethodPattern::FactoryMethodPattern(SDL_Renderer* _renderer)
{
	SwordFactory _swordFactory;
	SlimeFactory _slimeFactory;

	gameObjectList.push_back(_swordFactory.create(Attribute::Ice,	{ 200, 100 }));
	gameObjectList.push_back(_swordFactory.create(Attribute::Grass,	{ 200, 300 }));
	gameObjectList.push_back(_swordFactory.create(Attribute::Fire,	{ 200, 500 }));

	gameObjectList.push_back(_slimeFactory.create(Attribute::Ice,	{ 425, 140 }));
	gameObjectList.push_back(_slimeFactory.create(Attribute::Grass,	{ 425, 340 }));
	gameObjectList.push_back(_slimeFactory.create(Attribute::Fire,	{ 425, 540 }));

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

FactoryMethodPattern::~FactoryMethodPattern()
{
	for (GameObject* _go : gameObjectList)
		delete _go;

	SDL_DestroyTexture(textureTarget);
}

void FactoryMethodPattern::OnUpdate(float _delta)
{
	for (GameObject* _go : gameObjectList)
		_go->OnUpdate(_delta);

	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
}

void FactoryMethodPattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
	SDL_RenderClear(_renderer);

	for (GameObject* _go : gameObjectList)
		_go->OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}
