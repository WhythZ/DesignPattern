#include "Mediator.h"

#include <imgui.h>
#include <imgui_stdlib.h>

using namespace _MediatorPattern;

void User::OnUpdate(float _delta)
{
	animation.OnUpdate(_delta);

	ImGui::Dummy({ 0, 10 });
	ImGui::Text(u8"´óÌüÍæ¼Ò [%d]£º", id);
	ImGui::Image(animation.GetCurrentTexture(), { 224, 128 }, { 0, 0 }, { 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 0.75f });
	ImGui::SameLine();
	{
		ImGui::BeginGroup();
		ImGui::InputTextMultiline((u8"##chat" + std::to_string(id)).c_str(), &strChatBuffer, { ImGui::GetContentRegionAvail().x, 100}, ImGuiInputTextFlags_ReadOnly);
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 100);
		ImGui::InputText((u8"##input" + std::to_string(id)).c_str(), &strInputBuffer); ImGui::SameLine();
		ImGui::BeginDisabled(strInputBuffer.empty());
		if (ImGui::Button((u8"·¢ËÍ##" + std::to_string(id)).c_str(), { ImGui::GetContentRegionAvail().x, 0}))
		{
			Send(strInputBuffer);
			strInputBuffer.clear();
		}
		ImGui::EndDisabled();
		ImGui::EndGroup();
	}
}

MediatorPattern::MediatorPattern()
{
	user01 = new User(&chatRoom, "Swordsman_Blue_0%d");
	user02 = new User(&chatRoom, "Swordsman_Green_0%d");
	user03 = new User(&chatRoom, "Swordsman_Purple_0%d");
	user04 = new User(&chatRoom, "Swordsman_Red_0%d");

	chatRoom.AddColleague(user01);
	chatRoom.AddColleague(user02);
	chatRoom.AddColleague(user03);
	chatRoom.AddColleague(user04);
}

MediatorPattern::~MediatorPattern()
{
	delete user01;
	delete user02;
	delete user03;
	delete user04;
}

void MediatorPattern::OnUpdate(float _delta)
{
	user01->OnUpdate(_delta);
	user02->OnUpdate(_delta);
	user03->OnUpdate(_delta);
	user04->OnUpdate(_delta);
}
