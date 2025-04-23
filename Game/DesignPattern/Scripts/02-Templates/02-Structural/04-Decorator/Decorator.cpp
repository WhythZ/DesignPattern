#include "Decorator.h"

#include <imgui.h>

using namespace _DecoratorPattern;

DecoratorPattern::DecoratorPattern(SDL_Renderer* _renderer)
{
	player = new Player();

	propList.push_back(new Prop({ 100, 100 }, ResourcesManager::Instance()->FindTexture("coin"), 
		[&]() { player = new SpeedUpDecorator(player); }));
	propList.push_back(new Prop({ 620, 100 }, ResourcesManager::Instance()->FindTexture("favorites"),
		[&]() { player = new SizeGrownDecorator(player); }));
	propList.push_back(new Prop({ 360, 620 }, ResourcesManager::Instance()->FindTexture("likes"),
		[&]() { player = new AppearanceChangedDecorator(player); }));

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

DecoratorPattern::~DecoratorPattern()
{
	delete player;

	for (Prop* _prop : propList)
		delete _prop;

	SDL_DestroyTexture(textureTarget);
}

void DecoratorPattern::OnInput(const SDL_Event* _event)
{
	player->OnInput(_event);
}

void DecoratorPattern::OnUpdate(float _delta)
{
	player->OnUpdate(_delta);

	for (Prop* _prop : propList)
		_prop->CheckCollide(player);

	propList.erase(std::remove_if(
		propList.begin(), propList.end(),
		[](Prop* _prop)
		{
			bool CanRemove = _prop->CanRemove();
			if (CanRemove) delete _prop;
			return CanRemove;
		}),
		propList.end());

	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());

	ImGui::SetCursorPos({ 15, 15 });
	ImGui::TextColored({ 1.0f, 0.35f, 0.12f, 1.0f }, u8"使用 上/下/左/右 方向键控制飞机拾取道具获得不同属性");
}

void DecoratorPattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 65, 65, 65, 255);
	SDL_RenderClear(_renderer);

	for (const Prop* _prop : propList)
		_prop->OnRender(_renderer);

	player->OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}
