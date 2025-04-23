#include "Strategy.h"

#include <imgui.h>

using namespace _StrategyPattern;

StrategyPattern::StrategyPattern(SDL_Renderer* _renderer)
{
	boarList.push_back(new Boar(&player, { 100, 100 }));
	boarList.push_back(new Boar(&player, { 620, 100 }));
	boarList.push_back(new Boar(&player, { 360, 620 }));

	for (Boar* _boar : boarList)
		_boar->set_strategy(&followStrategy);

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

StrategyPattern::~StrategyPattern()
{
	for (Boar* _boar : boarList)
		delete _boar;

	SDL_DestroyTexture(textureTarget);
}

void StrategyPattern::OnInput(const SDL_Event* _event)
{
	player.OnInput(_event);
}

void StrategyPattern::OnUpdate(float _delta)
{
	player.OnUpdate(_delta);
	for (Boar* _boar : boarList)
		_boar->OnUpdate(_delta);

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

void StrategyPattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
	SDL_RenderClear(_renderer);

	SDL_RenderCopy(_renderer, ResourcesManager::Instance()->FindTexture("grassland"), nullptr, nullptr);
	
	for (Boar* _boar : boarList)
		_boar->OnRender(_renderer);
	player.OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}
