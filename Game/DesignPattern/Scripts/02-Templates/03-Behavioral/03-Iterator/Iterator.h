#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include <random>
#include <string>
#include <vector>
#include <algorithm>

#include "Example.h"
#include "ResourceManager.h"

namespace _IteratorPattern
{
	class Item
	{
	public:
		enum class Type
		{
			Materials,
			Props,
			Money
		};

		enum class Grade
		{
			Ordinary,
			Rare,
			Legendary
		};

	protected:
		std::string name;
		Type type = Type::Materials;
		Grade grade = Grade::Ordinary;
		SDL_Texture* texture = nullptr;

	public:
		Item() = default;
		virtual ~Item() = default;

		const std::string& GetName() const { return name; }
		Type GetType() const { return type; } 
		Grade GetGrade() const { return grade; }
		SDL_Texture* GetTexture() const { return texture; }
	};

	class MagicBook : public Item
	{
	public:
		MagicBook()
		{
			name = u8"¸½Ä§Êé";
			type = Type::Props;
			grade = Grade::Legendary;
			texture = ResourcesManager::Instance()->FindTexture("book");
		}
		~MagicBook() = default;
	};

	class OrdinaryPotion : public Item
	{
	public:
		OrdinaryPotion()
		{
			name = u8"Ë®Æ¿";
			type = Type::Props;
			grade = Grade::Ordinary;
			texture = ResourcesManager::Instance()->FindTexture("bottle");
		}
		~OrdinaryPotion() = default;
	};

	class Coins : public Item
	{
	public:
		Coins()
		{
			name = u8"½ð±Ò";
			type = Type::Money;
			grade = Grade::Rare;
			texture = ResourcesManager::Instance()->FindTexture("coins");
		}
		~Coins() = default;
	};

	class Scrolls : public Item
	{
	public:
		Scrolls()
		{
			name = u8"ÑòÆ¤¾í";
			type = Type::Props;
			grade = Grade::Rare;
			texture = ResourcesManager::Instance()->FindTexture("scrolls");
		}
		~Scrolls() = default;
	};

	class Stick : public Item
	{
	public:
		Stick()
		{
			name = u8"Ä¾¹÷";
			type = Type::Materials;
			grade = Grade::Ordinary;
			texture = ResourcesManager::Instance()->FindTexture("stick");
		}
		~Stick() = default;
	};

	class Stone : public Item
	{
	public:
		Stone()
		{
			name = u8"Ê¯Í·";
			type = Type::Materials;
			grade = Grade::Ordinary;
			texture = ResourcesManager::Instance()->FindTexture("stone");
		}
		~Stone() = default;
	};

	using ItemList = std::vector<Item*>;

	class Iterator
	{
	protected:
		int idx = 0;
		ItemList cacheList;

	public:
		Iterator(const ItemList& _targetList)
		{
			cacheList = ItemList(_targetList);
		}
		virtual ~Iterator() = default;

		virtual void Reset() { idx = 0; }
		virtual int GetIdx() const { return idx; }
		virtual Item* Next() { return cacheList[idx++]; }
		virtual bool HasNext() const { return idx < cacheList.size(); }
	};

	class RandomIterator : public Iterator
	{
	public:
		RandomIterator(const ItemList& _targetList) : Iterator(_targetList)
		{
			std::shuffle(cacheList.begin(), cacheList.end(), std::mt19937(std::random_device()()));
		}
		~RandomIterator() = default;
	};

	class TypeSortIterator : public Iterator
	{
	public:
		TypeSortIterator(const ItemList& _targetList) : Iterator(_targetList)
		{
			std::sort(cacheList.begin(), cacheList.end(), [](const Item* item01, const Item* item02)
				{
					return item01->GetType() < item02->GetType();
				}
			);
		}
		~TypeSortIterator() = default;
	};

	class GradeSortIterator : public Iterator
	{
	public:
		GradeSortIterator(const ItemList& _targetList) : Iterator(_targetList)
		{
			std::sort(cacheList.begin(), cacheList.end(), [](const Item* item01, const Item* item02)
				{
					return item01->GetGrade() < item02->GetGrade();
				}
			);
		}
		~GradeSortIterator() = default;
	};
}

class IteratorPattern : public Example
{
private:
	SDL_Texture* textureTarget = nullptr;
	_IteratorPattern::ItemList itemList;
	_IteratorPattern::Iterator* currentIterator = nullptr;

	_IteratorPattern::MagicBook sampleMagicBook;
	_IteratorPattern::OrdinaryPotion sampleOrdinaryPotion;
	_IteratorPattern::Coins sampleCoins;
	_IteratorPattern::Scrolls sampleScrolls;
	_IteratorPattern::Stick sampleStick;
	_IteratorPattern::Stone sampleStone;

public:
	IteratorPattern(SDL_Renderer*);
	~IteratorPattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;

private:
	void OnUpdateSample(_IteratorPattern::Item*);
};

#endif
