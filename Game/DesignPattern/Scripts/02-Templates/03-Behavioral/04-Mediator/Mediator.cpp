#include "Mediator.h"

#include <imgui.h>
#include <imgui_stdlib.h>

using namespace _MediatorPattern;

void User::OnUpdate(float delta)
{
	animation.OnUpdate(delta);

	ImGui::Dummy({ 0, 10 });
	ImGui::Text(u8"´óÌüÍæ¼Ò [%d]£º", id);
	ImGui::Image(animation.GetCurrentTexture(), { 224, 128 }, { 0, 0 }, { 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 0.75f });
	ImGui::SameLine();
	{
		ImGui::BeginGroup();
		ImGui::InputTextMultiline((u8"##chat" + std::to_string(id)).c_str(), &str_chat_buffer, { ImGui::GetContentRegionAvail().x, 100}, ImGuiInputTextFlags_ReadOnly);
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 100);
		ImGui::InputText((u8"##input" + std::to_string(id)).c_str(), &str_input_buffer); ImGui::SameLine();
		ImGui::BeginDisabled(str_input_buffer.empty());
		if (ImGui::Button((u8"·¢ËÍ##" + std::to_string(id)).c_str(), { ImGui::GetContentRegionAvail().x, 0}))
		{
			send(str_input_buffer);
			str_input_buffer.clear();
		}
		ImGui::EndDisabled();
		ImGui::EndGroup();
	}
}

MediatorPattern::MediatorPattern()
{
	user_1 = new User(&chat_room, "Swordsman_Blue_0%d");
	user_2 = new User(&chat_room, "Swordsman_Green_0%d");
	user_3 = new User(&chat_room, "Swordsman_Purple_0%d");
	user_4 = new User(&chat_room, "Swordsman_Red_0%d");

	chat_room.add_colleague(user_1);
	chat_room.add_colleague(user_2);
	chat_room.add_colleague(user_3);
	chat_room.add_colleague(user_4);
}

MediatorPattern::~MediatorPattern()
{
	delete user_1; delete user_2;
	delete user_3; delete user_4;
}

void MediatorPattern::OnUpdate(float delta)
{
	user_1->OnUpdate(delta);
	user_2->OnUpdate(delta);
	user_3->OnUpdate(delta);
	user_4->OnUpdate(delta);
}
