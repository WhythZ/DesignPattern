#ifndef _TEMPLATE_METHOD_H_
#define _TEMPLATE_METHOD_H_

#include "Example.h"
#include "Animation.h"

namespace _TemplateMethodPattern
{
	class Item
	{
	protected:
		Vector2 position;

	public:
		virtual ~Item() = default;

		virtual void OnUpdate(float _delta) {}
		virtual void OnRender(SDL_Renderer*) = 0;

		void SetPosition(const Vector2& _position)
		{
			this->position = _position;
		}
	};

	class StaticItem : public Item
	{
	private:
		SDL_Texture* texture = nullptr;

	public:
		StaticItem(const std::string& _textureID)
		{
			texture = ResourcesManager::Instance()->FindTexture(_textureID);
		}
		~StaticItem() = default;

		void OnRender(SDL_Renderer* _renderer) override
		{
			SDL_FRect _rect = { position.x - 20, position.y - 20, 40, 40 };
			SDL_RenderCopyF(_renderer, texture, nullptr, &_rect);
		}
	};

	class DynamicItem : public Item
	{
	private:
		Atlas atlas;
		Animation animation;

	public:
		DynamicItem(const std::string& _atlasTemp, int _num)
		{
			atlas.Load(_atlasTemp.c_str(), _num);
			animation.SetLoop(true);
			animation.SetInterval(0.4f / _num);
			animation.AddFrame(&atlas);
		}
		~DynamicItem() = default;

		void OnUpdate(float _delta) override
		{
			animation.OnUpdate(_delta);
			animation.SetPosition(position);
		}

		void OnRender(SDL_Renderer* _renderer) override
		{
			animation.OnRender(_renderer);
		}
	};

	class Chest : public StaticItem
	{
	public:
		Chest() : StaticItem("chest_full_open_anim_f1") {}
		~Chest() = default;
	};

	class Stairs : public StaticItem
	{
	public:
		Stairs() : StaticItem("floor_stairs") {}
		~Stairs() = default;
	};

	class Hole : public StaticItem
	{
	public:
		Hole() : StaticItem("hole") {}
		~Hole() = default;
	};

	class Elf : public DynamicItem
	{
	public:
		Elf() : DynamicItem("elf_f_idle_anim_f%d", 4) {}
		~Elf() = default;
	};

	class Goblin : public DynamicItem
	{
	public:
		Goblin() : DynamicItem("goblin_idle_anim_f%d", 4) {}
		~Goblin() = default;
	};

	class Lizard : public DynamicItem
	{
	public:
		Lizard() : DynamicItem("lizard_f_idle_anim_f%d", 4) {}
		~Lizard() = default;
	};

	class Spikes : public DynamicItem
	{
	public:
		Spikes() : DynamicItem("floor_spikes_anim_f%d", 2) {}
		~Spikes() = default;
	};

	class Map
	{
	private:
		bool needUpdateBackground = true;
		SDL_Texture* textureBackgorund = nullptr;

		std::vector<std::vector<Item*>> grids;
		std::vector<SDL_Point> emptyGridIdxList;

	public:
		Map()
		{
			grids = std::vector<std::vector<Item*>>(15, std::vector<Item*>(16, nullptr));
		}

		~Map()
		{
			for (const std::vector<Item*>& _line : grids)
			{
				for (Item* _item : _line)
					delete _item;
			}
		}

		void AddItem(Item* _item, const SDL_Point& _idx)
		{
			delete grids[_idx.y][_idx.x];
			grids[_idx.y][_idx.x] = _item;

			const Vector2 _position = 
			{ 
				(_idx.x + 1) * 40.f + 20,
				(_idx.y + 2) * 40.f + 20 
			};
			_item->SetPosition(_position);
		}

		const std::vector<SDL_Point>& GetEmptyGrids()
		{
			emptyGridIdxList.clear();

			for (int _y = 0; _y < 15; _y++)
				for (int _x = 0; _x < 16; _x++)
					if (!grids[_y][_x]) emptyGridIdxList.push_back({ _x, _y });

			return emptyGridIdxList;
		}

		void OnUpdate(float _delta)
		{
			for (int _y = 0; _y < 15; _y++)
				for (int _x = 0; _x < 16; _x++)
					if (grids[_y][_x]) grids[_y][_x]->OnUpdate(_delta);
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			if (needUpdateBackground)
			{
				UpdateTextureBackground(_renderer);
				needUpdateBackground = false;
			}

			SDL_RenderCopy(_renderer, textureBackgorund, nullptr, nullptr);
			for (int _y = 14; _y >= 0; _y--)
			{
				for (int _x = 0; _x < 16; _x++)
					if (grids[_y][_x]) grids[_y][_x]->OnRender(_renderer);
			}
			SDL_RenderCopy(_renderer, ResourcesManager::Instance()->FindTexture("dungeon_background"), nullptr, nullptr);
		}

	private:
		void UpdateTextureBackground(SDL_Renderer* _renderer)
		{
			SDL_DestroyTexture(textureBackgorund);
			textureBackgorund = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 720, 720);

			SDL_SetRenderTarget(_renderer, textureBackgorund);
			for (int _y = 0; _y < 15; _y++)
			{
				for (int _x = 0; _x < 16; _x++)
				{
					SDL_Texture* _textureFloor = nullptr;
					if (rand() % 100 < 10)
						_textureFloor = ResourcesManager::Instance()->FindTexture((rand() % 2) ? "floor_2" : "floor_3");
					else
						_textureFloor = ResourcesManager::Instance()->FindTexture("floor_1");

					SDL_Rect _rect = { (_x + 1) * 40, (_y + 2) * 40, 40, 40 };
					SDL_RenderCopy(_renderer, _textureFloor, nullptr, &_rect);
				}
			}
			SDL_SetRenderTarget(_renderer, nullptr);
		}
	};

	class MapGenTemplate
	{
	public:
		virtual ~MapGenTemplate() = default;

		Map* Generate()
		{
			Map* _map = new Map();

			GenerateExit(_map);
			GenerateTrap(_map);
			GenerateReward(_map);

			GenerateNPC(_map);
			GenerateEnemy(_map);
			
			return _map;
		}

	protected:
		virtual void GenerateNPC(Map*) = 0;
		virtual void GenerateExit(Map*) = 0;
		virtual void GenerateTrap(Map*) = 0;
		virtual void GenerateEnemy(Map*) = 0;
		virtual void GenerateReward(Map*) = 0;
	};

	class CustomizedMapGen : public MapGenTemplate
	{
	private:
		int holeNum = 2;
		int spikesNum = 4;
		int goblinNum = 6;
		int lizardNum = 3;
		bool hasNPC = true;
		bool hasExit = true;
		bool hasReward = true;

	public:
		CustomizedMapGen() = default;
		~CustomizedMapGen() = default;

		void OnInspectConfig();

	protected:
		void GenerateNPC(Map*) override;
		void GenerateExit(Map*) override;
		void GenerateTrap(Map*) override;
		void GenerateEnemy(Map*) override;
		void GenerateReward(Map*) override;
	};
}

class TemplateMethodPattern : public Example
{
private:
	SDL_Texture* textureTarget = nullptr;
	_TemplateMethodPattern::Map* map = nullptr;
	_TemplateMethodPattern::CustomizedMapGen mapGenerator;

public:
	TemplateMethodPattern(SDL_Renderer*);
	~TemplateMethodPattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
