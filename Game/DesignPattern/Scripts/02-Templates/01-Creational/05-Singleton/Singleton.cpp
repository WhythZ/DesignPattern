﻿#include "Singleton.h"

#include <imgui.h>

using namespace _SingletonPattern;

SceneManager* SceneManager::manager = nullptr;

void Level01::OnReach()
{
	SceneManager::Instance()->SwitchTo("level_2");
}

void Level02::OnReach()
{
	SceneManager::Instance()->SwitchTo("level_3");
}

void Level03::OnReach()
{
	SceneManager::Instance()->SwitchTo("level_1");
}

SingletonPattern::SingletonPattern(SDL_Renderer* renderer)
{
	SceneManager::Instance()->Add("level_1", new Level01(&player));
	SceneManager::Instance()->Add("level_2", new Level02(&player));
	SceneManager::Instance()->Add("level_3", new Level03(&player));
	SceneManager::Instance()->SwitchTo("level_1");

	textureTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

SingletonPattern::~SingletonPattern()
{
	SDL_DestroyTexture(textureTarget);
}

void SingletonPattern::OnInput(const SDL_Event* event)
{
	SceneManager::Instance()->OnInput(event);
}

void SingletonPattern::OnUpdate(float delta)
{
	SceneManager::Instance()->OnUpdate(delta);

	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());

	ImGui::SetCursorPos({ 15, 15 });
	ImGui::TextColored({ 1.0f, 0.35f, 0.12f, 1.0f }, u8"使用 上/下/左/右 方向键控制直升机达到停机坪完成关卡");
}

void SingletonPattern::OnRender(SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, textureTarget);
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	SDL_RenderClear(renderer);

	SceneManager::Instance()->OnRender(renderer);

	SDL_SetRenderTarget(renderer, nullptr);
}
