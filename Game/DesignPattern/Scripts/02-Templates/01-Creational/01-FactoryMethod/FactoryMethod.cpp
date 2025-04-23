#include "FactoryMethod.h"

#include <imgui.h>

using namespace _FactoryMethodPattern;

FactoryMethodPattern::FactoryMethodPattern(SDL_Renderer* renderer)
{
	SwordFactory sword_factory;
	SlimeFactory slime_factory;

	gameObjectList.push_back(sword_factory.create(Attribute::Ice,	{ 200, 100 }));
	gameObjectList.push_back(sword_factory.create(Attribute::Grass,	{ 200, 300 }));
	gameObjectList.push_back(sword_factory.create(Attribute::Fire,	{ 200, 500 }));

	gameObjectList.push_back(slime_factory.create(Attribute::Ice,	{ 425, 140 }));
	gameObjectList.push_back(slime_factory.create(Attribute::Grass,	{ 425, 340 }));
	gameObjectList.push_back(slime_factory.create(Attribute::Fire,	{ 425, 540 }));

	textureTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

FactoryMethodPattern::~FactoryMethodPattern()
{
	for (GameObject* game_obj : gameObjectList)
		delete game_obj;

	SDL_DestroyTexture(textureTarget);
}

void FactoryMethodPattern::OnUpdate(float delta)
{
	for (GameObject* game_obj : gameObjectList)
		game_obj->OnUpdate(delta);

	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
}

void FactoryMethodPattern::OnRender(SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, textureTarget);
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	SDL_RenderClear(renderer);

	for (GameObject* game_obj : gameObjectList)
		game_obj->OnRender(renderer);

	SDL_SetRenderTarget(renderer, nullptr);
}
