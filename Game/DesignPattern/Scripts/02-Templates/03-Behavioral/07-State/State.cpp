#include "State.h"

#include <imgui.h>

using namespace _StatePattern;

StatePattern::StatePattern(SDL_Renderer* renderer)
{
	state_list[0] = new IdleState();	state_name_list[0] = u8"����";
	state_list[1] = new AttackState();	state_name_list[1] = u8"����";
	state_list[2] = new JumpState();	state_name_list[2] = u8"��Ծ";
	state_list[3] = new RunState();		state_name_list[3] = u8"����";

	player.set_state(state_list[idx_state]);

	texture_target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);
}

StatePattern::~StatePattern()
{
	for (int i = 0; i < 4; i++)
		delete state_list[i];

	SDL_DestroyTexture(texture_target);
}

void StatePattern::OnUpdate(float delta)
{
	player.OnUpdate(delta);

	ImGui::TextUnformatted(u8"�л���ǰ��ɫ״̬Ϊ��"); ImGui::SameLine();
	if (ImGui::Combo(u8"##�л���ǰ��ɫ״̬Ϊ��", &idx_state, state_name_list, 4))
		player.set_state(state_list[idx_state]);

	ImGui::BeginChild("scene", ImGui::GetContentRegionAvail());
	ImGui::Image(texture_target, ImGui::GetContentRegionAvail());
	ImGui::EndChild();
}

void StatePattern::OnRender(SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, texture_target);
	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, ResourcesManager::Instance()->findTexture("Platform"), nullptr, nullptr);

	player.OnRender(renderer);

	SDL_SetRenderTarget(renderer, nullptr);
}
