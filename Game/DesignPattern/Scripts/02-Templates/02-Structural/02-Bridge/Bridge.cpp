#include "Bridge.h"

#include <imgui.h>

using namespace _BridgePattern;

void BridgePattern::OnUpdate(float _delta)
{
	if (ImGui::Button(u8"创建 EasyX 图形后端的窗口", {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 2}))
	{
		EasyXImpl _easyxImpl;
		Window window(&_easyxImpl);

		window.create(1280, 720);
		window.LoadTheImage("Resources/splash.png");
		window.run();
	}

	if (ImGui::Button(u8"创建 Raylib 图形后端的窗口", ImGui::GetContentRegionAvail()))
	{
		RaylibImpl _raylibImpl;
		Window window(&_raylibImpl);

		window.create(1280, 720);
		window.LoadTheImage("Resources/splash.png");
		window.run();
	}
}
