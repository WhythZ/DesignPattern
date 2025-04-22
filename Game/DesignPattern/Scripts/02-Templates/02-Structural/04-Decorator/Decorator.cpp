#include "Decorator.h"

#include <imgui.h>

using namespace _DecoratorPattern;

DecoratorPattern::DecoratorPattern(SDL_Renderer* renderer)
{
	player = new Player();

	prop_list.push_back(new Prop({ 100, 100 }, ResourcesManager::Instance()->findTexture("coin"), 
		[&]() { player = new SpeedUpDecorator(player); }));
	prop_list.push_back(new Prop({ 620, 100 }, ResourcesManager::Instance()->findTexture("favorites"),
		[&]() { player = new SizeGrownDecorator(player); }));
	prop_list.push_back(new Prop({ 360, 620 }, ResourcesManager::Instance()->findTexture("likes"),
		[&]() { player = new AppearanceChangedDecorator(player); }));

	textureTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

DecoratorPattern::~DecoratorPattern()
{
	delete player;

	for (Prop* prop : prop_list)
		delete prop;

	SDL_DestroyTexture(textureTarget);
}

void DecoratorPattern::OnInput(const SDL_Event* event)
{
	player->OnInput(event);
}

void DecoratorPattern::OnUpdate(float delta)
{
	player->OnUpdate(delta);

	for (Prop* prop : prop_list)
		prop->check_collide(player);

	prop_list.erase(std::remove_if(
		prop_list.begin(), prop_list.end(),
		[](Prop* prop)
		{
			bool can_remove = prop->can_remove();
			if (can_remove) delete prop;
			return can_remove;
		}),
		prop_list.end());

	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());

	ImGui::SetCursorPos({ 15, 15 });
	ImGui::TextColored({ 1.0f, 0.35f, 0.12f, 1.0f }, u8"使用 上/下/左/右 方向键控制飞机拾取道具获得不同属性");
}

void DecoratorPattern::OnRender(SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, textureTarget);
	SDL_SetRenderDrawColor(renderer, 65, 65, 65, 255);
	SDL_RenderClear(renderer);

	for (const Prop* prop : prop_list)
		prop->OnRender(renderer);

	player->OnRender(renderer);

	SDL_SetRenderTarget(renderer, nullptr);
}
