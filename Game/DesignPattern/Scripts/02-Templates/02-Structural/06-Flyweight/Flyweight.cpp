#include "Flyweight.h"

#include <imgui.h>

void FlyweightPattern::OnUpdate(float _delta)
{
	static const ImVec2 _sizeText = ImGui::CalcTextSize(strText.c_str());
	static const ImVec2 _sizeContent = ImGui::GetContentRegionAvail();
	static const ImVec2 _positionCursor = { (_sizeContent.x - _sizeText.x) / 2, (_sizeContent.y - _sizeText.y) / 2 };

	ImGui::SetCursorPos(_positionCursor);
	ImGui::TextDisabled(strText.c_str());
}