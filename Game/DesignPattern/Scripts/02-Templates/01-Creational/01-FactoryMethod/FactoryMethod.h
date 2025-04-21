#ifndef _FACTORY_METHOD_H_
#define _FACTORY_METHOD_H_

#include "Example.h"
#include "Animation.h"

namespace _FactoryMethodPattern
{
	enum class Attribute { Ice, Grass, Fire };

	class GameObject
	{
	public:
		GameObject(const Vector2& _position) : position(_position) {}

		virtual void OnUpdate(float delta) = 0;
		virtual void OnRender(SDL_Renderer* renderer) = 0;

	protected:
		Vector2 position;

	};

	class Sword : public GameObject
	{
	public:
		Sword(const Vector2& _position) : GameObject(_position) {}

		void OnUpdate(float delta) override {}
		void OnRender(SDL_Renderer* renderer) override
		{
			SDL_FRect rect = { position.x, position.y, 64, 64 };
			SDL_RenderCopyF(renderer, texture, nullptr, &rect);
		}

	protected:
		SDL_Texture* texture = nullptr;

	};

	class Slime : public GameObject
	{
	public:
		Slime(const Vector2& _position) : GameObject(_position) {}

		void OnUpdate(float delta) override
		{
			animation.OnUpdate(delta);
			animation.SetPosition(position);
		}

		void OnRender(SDL_Renderer* renderer) override
		{
			animation.OnRender(renderer);
		}

	protected:
		Atlas atlas;
		Animation animation;

	};

	class IceSword : public Sword
	{
	public:
		IceSword(const Vector2& _position) : Sword(_position)
		{
			texture = ResourcesManager::Instance()->findTexture("BlueSword");
		}

	};

	class GrassSword : public Sword
	{
	public:
		GrassSword(const Vector2& _position) : Sword(_position)
		{
			texture = ResourcesManager::Instance()->findTexture("GreenSword");
		}

	};

	class FireSword : public Sword
	{
	public:
		FireSword(const Vector2& _position) : Sword(_position)
		{
			texture = ResourcesManager::Instance()->findTexture("RedSword");
		}

	};

	class IceSlime : public Slime
	{
	public:
		IceSlime(const Vector2& _position) : Slime(_position)
		{
			atlas.Load("MegaSlimeBlue_0%d", 6);
			animation.AddFrame(&atlas);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);
		}

	};

	class GrassSlime : public Slime
	{
	public:
		GrassSlime(const Vector2& _position) : Slime(_position)
		{
			atlas.Load("MegaSlimeGreen_0%d", 6);
			animation.AddFrame(&atlas);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);
		}

	};

	class FireSlime : public Slime
	{
	public:
		FireSlime(const Vector2& _position) : Slime(_position)
		{
			atlas.Load("MegaSlimeRed_0%d", 6);
			animation.AddFrame(&atlas);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);
		}

	};

	class SwordFactory
	{
	public:
		Sword* create(Attribute attribute, const Vector2& position)
		{
			switch (attribute)
			{
			case _FactoryMethodPattern::Attribute::Ice:
				return new IceSword(position);
				break;
			case _FactoryMethodPattern::Attribute::Grass:
				return new GrassSword(position);
				break;
			case _FactoryMethodPattern::Attribute::Fire:
				return new FireSword(position);
				break;
			default:
				return nullptr;
				break;
			}
		}
	};

	class SlimeFactory
	{
	public:
		Slime* create(Attribute attribute, const Vector2& position)
		{
			switch (attribute)
			{
			case _FactoryMethodPattern::Attribute::Ice:
				return new IceSlime(position);
				break;
			case _FactoryMethodPattern::Attribute::Grass:
				return new GrassSlime(position);
				break;
			case _FactoryMethodPattern::Attribute::Fire:
				return new FireSlime(position);
				break;
			default:
				return nullptr;
				break;
			}
		}
	};
}

class FactoryMethodPattern : public Example
{
public:
	FactoryMethodPattern(SDL_Renderer* renderer);
	~FactoryMethodPattern();

	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	SDL_Texture* texture_target = nullptr;
	std::vector<_FactoryMethodPattern::GameObject*> game_obj_list;

};

#endif
