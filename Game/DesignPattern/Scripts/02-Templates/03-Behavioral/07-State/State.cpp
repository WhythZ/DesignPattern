#include "State.h"

#include <imgui.h>

using namespace _StatePattern;

StatePattern::StatePattern(SDL_Renderer* _renderer)
{
	stateList[0] = new IdleState();	stateNameList[0] = u8"ÏÐÖÃ";
	stateList[1] = new AttackState();	stateNameList[1] = u8"¹¥»÷";
	stateList[2] = new JumpState();	stateNameList[2] = u8"ÌøÔ¾";
	stateList[3] = new RunState();		stateNameList[3] = u8"±¼ÅÜ";

	player.SetState(stateList[stateIdx]);

	textureTarget = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

StatePattern::~StatePattern()
{
	for (int _i = 0; _i < 4; _i++)
		delete stateList[_i];

	SDL_DestroyTexture(textureTarget);
}

void StatePattern::OnUpdate(float _delta)
{
	player.OnUpdate(_delta);

	ImGui::TextUnformatted(u8"ÇÐ»»µ±Ç°½ÇÉ«×´Ì¬Îª£º"); ImGui::SameLine();
	if (ImGui::Combo(u8"##ÇÐ»»µ±Ç°½ÇÉ«×´Ì¬Îª£º", &stateIdx, stateNameList, 4))
		player.SetState(stateList[stateIdx]);

	ImGui::BeginChild("scene", ImGui::GetContentRegionAvail());
	ImGui::Image(textureTarget, ImGui::GetContentRegionAvail());
	ImGui::EndChild();
}

void StatePattern::OnRender(SDL_Renderer* _renderer)
{
	SDL_SetRenderTarget(_renderer, textureTarget);
	SDL_SetRenderDrawColor(_renderer, 15, 15, 15, 255);
	SDL_RenderClear(_renderer);

	SDL_RenderCopy(_renderer, ResourcesManager::Instance()->FindTexture("Platform"), nullptr, nullptr);

	player.OnRender(_renderer);

	SDL_SetRenderTarget(_renderer, nullptr);
}
