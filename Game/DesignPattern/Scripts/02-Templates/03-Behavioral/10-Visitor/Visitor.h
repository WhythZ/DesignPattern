#ifndef _VISITOR_H_
#define _VISITOR_H_

#include <imgui.h>
#include <imgui_stdlib.h>

#include "Example.h"
#include "ResourceManager.h"

namespace _VisitorPattern
{
	class MagicBook;
	class OrdinaryPotion;
	class Coins;
	class Scrolls;
	class Stick;
	class Stone;

	class Visitor
	{
	public:
		virtual void Visit(const MagicBook&) = 0;
		virtual void Visit(const OrdinaryPotion&) = 0;
		virtual void Visit(const Coins&) = 0;
		virtual void Visit(const Scrolls&) = 0;
		virtual void Visit(const Stick&) = 0;
		virtual void Visit(const Stone&) = 0;
	};

	class Item
	{
	private:
		int id;
		SDL_Texture* texture;

	public:
		Item(int _id, SDL_Texture* _texture) 
			: id(_id), texture(_texture) {}
		virtual ~Item() = default;

		virtual void Accept(Visitor&) = 0;

		int GetID() const { return id; }
		SDL_Texture* GetTexture() const { return texture; }
	};

	class MagicBook : public Item
	{
	public:
		MagicBook() : Item(1, ResourcesManager::Instance()->FindTexture("book")) {}
		~MagicBook() = default;

		void Accept(Visitor& _visitor) override { _visitor.Visit(*this); }
	};

	class OrdinaryPotion : public Item
	{
	public:
		OrdinaryPotion() : Item(2, ResourcesManager::Instance()->FindTexture("bottle")) {}
		~OrdinaryPotion() = default;

		void Accept(Visitor& _visitor) override { _visitor.Visit(*this); }
	};

	class Coins : public Item
	{
	public:
		Coins() : Item(3, ResourcesManager::Instance()->FindTexture("coins")) {}
		~Coins() = default;

		void Accept(Visitor& _visitor) override { _visitor.Visit(*this); }
	};

	class Scrolls : public Item
	{
	public:
		Scrolls() : Item(4, ResourcesManager::Instance()->FindTexture("scrolls")) {}
		~Scrolls() = default;

		void Accept(Visitor& _visitor) override { _visitor.Visit(*this); }
	};

	class Stick : public Item
	{
	public:
		Stick() : Item(5, ResourcesManager::Instance()->FindTexture("stick")) {}
		~Stick() = default;

		void Accept(Visitor& _visitor) override { _visitor.Visit(*this); }
	};

	class Stone : public Item
	{
	public:
		Stone() : Item(6, ResourcesManager::Instance()->FindTexture("stone")) {}
		~Stone() = default;

		void Accept(Visitor& _visitor) override { _visitor.Visit(*this); }
	};

	class InpsectVisitor : public Visitor
	{
	public:
		void Visit(const MagicBook&);
		void Visit(const OrdinaryPotion&);
		void Visit(const Coins&);
		void Visit(const Scrolls&);
		void Visit(const Stick&);
		void Visit(const Stone&);
	};

	class ApplyVisitor : public Visitor
	{
	public:
		void Visit(const MagicBook&);
		void Visit(const OrdinaryPotion&);
		void Visit(const Coins&);
		void Visit(const Scrolls&);
		void Visit(const Stick&);
		void Visit(const Stone&);
	};
}

class VisitorPattern : public Example
{
private:
	_VisitorPattern::MagicBook magicBook;
	_VisitorPattern::OrdinaryPotion ordinaryPotion;
	_VisitorPattern::Stick stick;
	_VisitorPattern::Stone stone;
	_VisitorPattern::Coins coins;
	_VisitorPattern::Scrolls scrolls;

	_VisitorPattern::ApplyVisitor applyVisitor;
	_VisitorPattern::InpsectVisitor inspectVisitor;

public:
	VisitorPattern() = default;
	~VisitorPattern() = default;

	void OnUpdate(float) override;

private:
	template <typename T>
	void OnUpdateItemButton(T& _item)
	{
		ImGui::ImageButton(_item.GetTexture(), { 64, 64 });
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			_item.Accept(inspectVisitor);
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			_item.Accept(applyVisitor);
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::TextDisabled(u8"鼠标左键：检视道具");
			ImGui::TextDisabled(u8"鼠标右键：使用道具");
			ImGui::EndTooltip();
		}
	}
};

#endif
