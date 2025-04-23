#include "Visitor.h"

using namespace _VisitorPattern;

static std::string strOutput;

void InpsectVisitor::visit(const MagicBook& magic_book)
{
	strOutput += u8"���ӵ��� [" + std::to_string(magic_book.get_id()) + u8"]��һ�������ħ���飿\n";
}

void InpsectVisitor::visit(const OrdinaryPotion& ordinary_potion)
{
	strOutput += u8"���ӵ��� [" + std::to_string(ordinary_potion.get_id()) + u8"]��ֻ��һƿ��ͨ��ҩˮ����\n";
}

void InpsectVisitor::visit(const Coins& coins)
{
	strOutput += u8"���ӵ��� [" + std::to_string(coins.get_id()) + u8"]���������ģ�Ǯ�ң�\n";
}

void InpsectVisitor::visit(const Scrolls& scrolls)
{
	strOutput += u8"���ӵ��� [" + std::to_string(scrolls.get_id()) + u8"]����ͨ���޷���͸���а���ľ��ᡣ\n";
}

void InpsectVisitor::visit(const Stick& stick)
{
	strOutput += u8"���ӵ��� [" + std::to_string(stick.get_id()) + u8"]��һ��ľ�����������á���\n";
}

void InpsectVisitor::visit(const Stone& stone)
{
	strOutput += u8"���ӵ��� [" + std::to_string(stone.get_id()) + u8"]�������Ӧ���ӵ�����ʡ�����ռ��ʯͷ��\n";
}

void ApplyVisitor::visit(const MagicBook& magic_book)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(magic_book.get_id()) + u8"]��������ڱ�ħ��Ԫ�س�ӯ��\n";
}

void ApplyVisitor::visit(const OrdinaryPotion& ordinary_potion)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(ordinary_potion.get_id()) + u8"]��ʲô����Ҳû�з�������\n";
}

void ApplyVisitor::visit(const Coins& coins)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(coins.get_id()) + u8"]����ĲƸ�ֵ��������ˣ�\n";
}

void ApplyVisitor::visit(const Scrolls& scrolls)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(scrolls.get_id()) + u8"]���ǻ۵ȼ������޷�����ѧϰ��\n";
}

void ApplyVisitor::visit(const Stick& stick)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(stick.get_id()) + u8"]��ʲô����Ҳû�з�������\n";
}

void ApplyVisitor::visit(const Stone& stone)
{
	strOutput += u8"ʹ�õ��� [" + std::to_string(stone.get_id()) + u8"]��ʲô����Ҳû�з�������\n";
}

VisitorPattern::VisitorPattern() = default;

VisitorPattern::~VisitorPattern() = default;

void VisitorPattern::OnUpdate(float delta)
{
	static const ImVec2 size_dummy = { 33, 0 };

	on_update_item_btn<MagicBook>(magic_book);				ImGui::SameLine(); ImGui::Dummy(size_dummy); ImGui::SameLine();
	on_update_item_btn<OrdinaryPotion>(ordinary_potion);	ImGui::SameLine(); ImGui::Dummy(size_dummy); ImGui::SameLine();
	on_update_item_btn<Coins>(coins);						ImGui::SameLine(); ImGui::Dummy(size_dummy); ImGui::SameLine();
	on_update_item_btn<Scrolls>(scrolls);					ImGui::SameLine(); ImGui::Dummy(size_dummy); ImGui::SameLine();
	on_update_item_btn<Stick>(stick);						ImGui::SameLine(); ImGui::Dummy(size_dummy); ImGui::SameLine();
	on_update_item_btn<Stone>(stone);

	ImGui::InputTextMultiline(u8"##�������", &strOutput, ImGui::GetContentRegionAvail(), ImGuiInputTextFlags_ReadOnly);
}
