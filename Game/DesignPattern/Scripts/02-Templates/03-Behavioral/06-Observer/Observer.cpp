#include "Observer.h"

#include <imgui.h>

#include "ResourceManager.h"

using namespace _ObserverPattern;

static std::vector<Achievement> unlockedAchievementList;

void Button1ClickedObserver::Update(int _state)
{
	switch (_state)
	{
	case 1:
		unlockedAchievementList.push_back(Achievement(ResourcesManager::Instance()->FindTexture("achievement_btn_1_1")));
		Mix_PlayChannel(-1, ResourcesManager::Instance()->FindAudio("unlock"), 0);
		break;
	case 10:
		unlockedAchievementList.push_back(Achievement(ResourcesManager::Instance()->FindTexture("achievement_btn_1_10")));
		Mix_PlayChannel(-1, ResourcesManager::Instance()->FindAudio("unlock"), 0);
		break;
	default: break;
	}
}

void Button2ClickedObserver::Update(int _state)
{
	switch (_state)
	{
	case 1:
		unlockedAchievementList.push_back(Achievement(ResourcesManager::Instance()->FindTexture("achievement_btn_2_1")));
		Mix_PlayChannel(-1, ResourcesManager::Instance()->FindAudio("unlock"), 0);
		break;
	case 10:
		unlockedAchievementList.push_back(Achievement(ResourcesManager::Instance()->FindTexture("achievement_btn_2_10")));
		Mix_PlayChannel(-1, ResourcesManager::Instance()->FindAudio("unlock"), 0);
		break;
	default: break;
	}
}

ObserverPattern::ObserverPattern()
{
	button01ClickedSubject.Attach(&button01ClickedObserver);
	button02ClickedSubject.Attach(&button02ClickedObserver);
}

void ObserverPattern::OnUpdate(float _delta)
{
	static const ImVec2 _sizeButton = { ImGui::GetContentRegionAvail().x, 35 };
	if (ImGui::Button(u8"芝士按钮 [1] 点我解锁更多成就！", _sizeButton))
		button01ClickedSubject.Accumulate();
	if (ImGui::Button(u8"芝士按钮 [2] 点我解锁更多成就！", _sizeButton))
		button02ClickedSubject.Accumulate();
	
	ImGui::BeginChild("achievement", ImGui::GetContentRegionAvail(), ImGuiChildFlags_Border);
	for (const Achievement& _achievement : unlockedAchievementList)
		ImGui::Image(_achievement.texture, { ImGui::GetContentRegionAvail().x, 135 });
	ImGui::Separator();
	ImGui::TextDisabled(u8"* 已解锁成就 %d/4", (int)unlockedAchievementList.size());
	ImGui::EndChild();
}
