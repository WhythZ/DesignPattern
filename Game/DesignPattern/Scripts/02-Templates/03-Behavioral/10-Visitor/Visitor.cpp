#include "Visitor.h"

using namespace _VisitorPattern;

static std::string strOutput;

void InpsectVisitor::Visit(const MagicBook& _magicBook)
{
	strOutput += u8"检视道具 [" + std::to_string(_magicBook.GetID()) + u8"]：一本神奇的魔法书？\n";
}

void InpsectVisitor::Visit(const OrdinaryPotion& _ordinaryPotion)
{
	strOutput += u8"检视道具 [" + std::to_string(_ordinaryPotion.GetID()) + u8"]：只是一瓶普通的药水……\n";
}

void InpsectVisitor::Visit(const Coins& _coins)
{
	strOutput += u8"检视道具 [" + std::to_string(_coins.GetID()) + u8"]：亮晶晶的？钱币！\n";
}

void InpsectVisitor::Visit(const Scrolls& _scrolls)
{
	strOutput += u8"检视道具 [" + std::to_string(_scrolls.GetID()) + u8"]：普通人无法参透其中奥妙的卷轴。\n";
}

void InpsectVisitor::Visit(const Stick& _stick)
{
	strOutput += u8"检视道具 [" + std::to_string(_stick.GetID()) + u8"]：一根木棍，或许有用……\n";
}

void InpsectVisitor::Visit(const Stone& _stone)
{
	strOutput += u8"检视道具 [" + std::to_string(_stone.GetID()) + u8"]：你或许应该扔掉来节省背包空间的石头。\n";
}

void ApplyVisitor::Visit(const MagicBook& _magicBook)
{
	strOutput += u8"使用道具 [" + std::to_string(_magicBook.GetID()) + u8"]：你的体内被魔法元素充盈！\n";
}

void ApplyVisitor::Visit(const OrdinaryPotion& _ordinaryPotion)
{
	strOutput += u8"使用道具 [" + std::to_string(_ordinaryPotion.GetID()) + u8"]：什么事情也没有发生……\n";
}

void ApplyVisitor::Visit(const Coins& _coins)
{
	strOutput += u8"使用道具 [" + std::to_string(_coins.GetID()) + u8"]：你的财富值大大增加了！\n";
}

void ApplyVisitor::Visit(const Scrolls& _scrolls)
{
	strOutput += u8"使用道具 [" + std::to_string(_scrolls.GetID()) + u8"]：智慧等级不够无法进行学习！\n";
}

void ApplyVisitor::Visit(const Stick& _stick)
{
	strOutput += u8"使用道具 [" + std::to_string(_stick.GetID()) + u8"]：什么事情也没有发生……\n";
}

void ApplyVisitor::Visit(const Stone& _stone)
{
	strOutput += u8"使用道具 [" + std::to_string(_stone.GetID()) + u8"]：什么事情也没有发生……\n";
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

	ImGui::InputTextMultiline(u8"##输出内容", &strOutput, ImGui::GetContentRegionAvail(), ImGuiInputTextFlags_ReadOnly);
}
