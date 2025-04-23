#include "Visitor.h"

using namespace _VisitorPattern;

static std::string strOutput;

void InpsectVisitor::Visit(const MagicBook& _magicBook)
{
	strOutput += u8"���ӵ��� [" + std::to_string(_magicBook.GetID()) + u8"]��һ�������ħ���飿\n";
}

void InpsectVisitor::Visit(const OrdinaryPotion& _ordinaryPotion)
{
	strOutput += u8"���ӵ��� [" + std::to_string(_ordinaryPotion.GetID()) + u8"]��ֻ��һƿ��ͨ��ҩˮ����\n";
}

void InpsectVisitor::Visit(const Coins& _coins)
{
	strOutput += u8"���ӵ��� [" + std::to_string(_coins.GetID()) + u8"]���������ģ�Ǯ�ң�\n";
}

void InpsectVisitor::Visit(const Scrolls& _scrolls)
{
	strOutput += u8"���ӵ��� [" + std::to_string(_scrolls.GetID()) + u8"]����ͨ���޷���͸���а���ľ��ᡣ\n";
}

void InpsectVisitor::Visit(const Stick& _stick)
{
	strOutput += u8"���ӵ��� [" + std::to_string(_stick.GetID()) + u8"]��һ��ľ�����������á���\n";
}

void InpsectVisitor::Visit(const Stone& _stone)
{
	strOutput += u8"���ӵ��� [" + std::to_string(_stone.GetID()) + u8"]�������Ӧ���ӵ�����ʡ�����ռ��ʯͷ��\n";
}

void ApplyVisitor::Visit(const MagicBook& _magicBook)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(_magicBook.GetID()) + u8"]��������ڱ�ħ��Ԫ�س�ӯ��\n";
}

void ApplyVisitor::Visit(const OrdinaryPotion& _ordinaryPotion)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(_ordinaryPotion.GetID()) + u8"]��ʲô����Ҳû�з�������\n";
}

void ApplyVisitor::Visit(const Coins& _coins)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(_coins.GetID()) + u8"]����ĲƸ�ֵ��������ˣ�\n";
}

void ApplyVisitor::Visit(const Scrolls& _scrolls)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(_scrolls.GetID()) + u8"]���ǻ۵ȼ������޷�����ѧϰ��\n";
}

void ApplyVisitor::Visit(const Stick& _stick)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(_stick.GetID()) + u8"]��ʲô����Ҳû�з�������\n";
}

void ApplyVisitor::Visit(const Stone& _stone)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(_stone.GetID()) + u8"]��ʲô����Ҳû�з�������\n";
}

void VisitorPattern::OnUpdate(float _delta)
{
	static const ImVec2 _sizeDummy = { 33, 0 };

	OnUpdateItemButton<MagicBook>(magicBook);				ImGui::SameLine(); ImGui::Dummy(_sizeDummy); ImGui::SameLine();
	OnUpdateItemButton<OrdinaryPotion>(ordinaryPotion);		ImGui::SameLine(); ImGui::Dummy(_sizeDummy); ImGui::SameLine();
	OnUpdateItemButton<Coins>(coins);						ImGui::SameLine(); ImGui::Dummy(_sizeDummy); ImGui::SameLine();
	OnUpdateItemButton<Scrolls>(scrolls);					ImGui::SameLine(); ImGui::Dummy(_sizeDummy); ImGui::SameLine();
	OnUpdateItemButton<Stick>(stick);						ImGui::SameLine(); ImGui::Dummy(_sizeDummy); ImGui::SameLine();
	OnUpdateItemButton<Stone>(stone);

	ImGui::InputTextMultiline(u8"##�������", &strOutput, ImGui::GetContentRegionAvail(), ImGuiInputTextFlags_ReadOnly);
}
