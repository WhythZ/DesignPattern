#include "ChainOfResponsibility.h"

#include <imgui_stdlib.h>

using namespace _ChainOfResponsibilityPattern;

static std::string strOutput;
static bool isBubbling = true;

ChainOfResponsibilityPattern::ChainOfResponsibilityPattern():
	window01(1, { 0.65f, 0.2f, 0.2f, 1.0f }, { 679, 575 }, { 0, 0 }),
	window02(2, { 0.2f, 0.65f, 0.2f, 1.0f }, { 425, 350 }, { 50, 50 }),
	window03(3, { 0.2f, 0.2f, 0.65f, 1.0f }, { 200, 175 }, { 100, 100 })
{
	window03.SetNext(&window02);
	window02.SetNext(&window01);
}

void ChildWindow::Handle()
{
	strOutput += u8"�����Ϣ���ݵ� [" + std::to_string(id) + u8"] �Ŵ��ڣ�\n";

	if (next && isBubbling)
		next->Handle();
}

void ChildWindow::OnUpdate()
{
	ImGui::SetCursorPos(offset);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, color);
	ImGui::BeginChild(id, size, ImGuiChildFlags_Border);
	ImGui::Text(u8"���� [%d]", id);
	if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		strOutput.clear(); 
		Handle();
	}
	ImGui::EndChild();
	ImGui::PopStyleColor();
}

void ChainOfResponsibilityPattern::OnUpdate(float delta)
{
	ImGui::TextUnformatted(u8"�����������Ϣð�ݣ�"); ImGui::SameLine();
	ImGui::Checkbox(u8"##�����������Ϣð��", &isBubbling);

	ImGui::BeginChild("region", { ImGui::GetContentRegionAvail().x, 575 });

	window01.OnUpdate();
	window02.OnUpdate();
	window03.OnUpdate();

	ImGui::EndChild();

	ImGui::InputTextMultiline(u8"##�������", &strOutput, ImGui::GetContentRegionAvail(), ImGuiInputTextFlags_ReadOnly);
}
