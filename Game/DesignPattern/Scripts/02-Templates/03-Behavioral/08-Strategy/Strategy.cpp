#include "Strategy.h"

#include <imgui.h>

using namespace _StrategyPattern;

StrategyPattern::StrategyPattern(SDL_Renderer* renderer)
{
	boarList.push_back(new Boar(&player, { 100, 100 }));
	boarList.push_back(new Boar(&player, { 620, 100 }));
	boarList.push_back(new Boar(&player, { 360, 620 }));

	for (Boar* boar : boarList)
		boar->set_strategy(&followStrategy);

	textureTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

StrategyPattern::~StrategyPattern()
{
	for (Boar* boar : boarList)
		delete boar;

	SDL_DestroyTexture(textureTarget);
}

void StrategyPattern::OnInput(const SDL_Event* event)
{
	player.OnInput(event);
}

void StrategyPattern::OnUpdate(float delta)
{
	player.OnUpdate(delta);
	for (Boar* boar : boarList)
		boar->OnUpdate(delta);

	if (ImGui::Button(isUsingFollowStrategy ? u8"切换野猪为 [远离] 策略" : u8"切换野猪为 [跟随] 策略",
		{ ImGui::GetContentRegionAvail().x, 35 }))
	{
		isUsingFollowStrategy = !isUsingFollowStrategy;
		MoveStrategy* _currentStrategy = isUsingFollowStrategy
			? (MoveStrategy*)&followStrategy : (MoveStrategy*)&stayAwayStrategy;
		for (Boar* _boar : boarList)
			_boar->set_strategy(_currentStrategy);
	}

	ImGui::BeginChild("scene", ImGui::GetContentRegionAvail());
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::SetCursorPos({ 10, 10 });
	ImGui::TextColored({ 1.0f, 0.35f, 0.12f, 1.0f }, u8"使用 上/下/左/右 方向键控制角色移动");
	ImGui::EndChild();
}

void StrategyPattern::OnRender(SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, textureTarget);
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, ResourcesManager::Instance()->FindTexture("grassland"), nullptr, nullptr);
	
	for (Boar* boar : boarList)
		boar->OnRender(renderer);
	player.OnRender(renderer);

	SDL_SetRenderTarget(renderer, nullptr);
}
