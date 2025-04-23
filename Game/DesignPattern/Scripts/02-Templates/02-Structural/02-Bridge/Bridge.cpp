#include "Bridge.h"

#include <imgui.h>

using namespace _BridgePattern;

void BridgePattern::OnUpdate(float _delta)
{
	if (ImGui::Button(u8"���� EasyX ͼ�κ�˵Ĵ���", {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 2}))
	{
		EasyXImpl _easyxImpl;
		Window window(&_easyxImpl);

		window.create(1280, 720);
		window.LoadTheImage("Resources/splash.png");
		window.run();
	}

	if (ImGui::Button(u8"���� Raylib ͼ�κ�˵Ĵ���", ImGui::GetContentRegionAvail()))
	{
		RaylibImpl _raylibImpl;
		Window window(&_raylibImpl);

		window.create(1280, 720);
		window.LoadTheImage("Resources/splash.png");
		window.run();
	}
}
