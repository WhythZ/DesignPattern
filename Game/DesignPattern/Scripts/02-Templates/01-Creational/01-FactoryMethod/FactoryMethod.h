#ifndef _FACTORY_METHOD_H_
#define _FACTORY_METHOD_H_

#include "Example.h"
#include "Animation.h"

namespace _FactoryMethodPattern
{
	//���Ĳ�ͬ����
	enum class Attribute { Ice, Grass, Fire };

	class GameObject
	{
	protected:
		Vector2 position;

	public:
		GameObject(const Vector2& _position) : position(_position) {}

		virtual void OnUpdate(float) = 0;
		virtual void OnRender(SDL_Renderer*) = 0;
	};

	class Sword : public GameObject
	{
	protected:
		SDL_Texture* texture = nullptr;

	public:
		Sword(const Vector2& _position) : GameObject(_position) {}

		void OnUpdate(float _delta) override {}
		void OnRender(SDL_Renderer* _renderer) override
		{
			SDL_FRect _rect = { position.x, position.y, 64, 64 };
			SDL_RenderCopyF(_renderer, texture, nullptr, &_rect);
		}
	};

	class Slime : public GameObject
	{
	protected:
		Atlas atlas;
		Animation animation;

	public:
		Slime(const Vector2& _position) : GameObject(_position) {}

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

	class IceSword : public Sword
	{
	public:
		IceSword(const Vector2& _position) : Sword(_position)
		{
			texture = ResourcesManager::Instance()->FindTexture("BlueSword");
		}
	};

	class GrassSword : public Sword
	{
	public:
		GrassSword(const Vector2& _position) : Sword(_position)
		{
			texture = ResourcesManager::Instance()->FindTexture("GreenSword");
		}
	};

	class FireSword : public Sword
	{
	public:
		FireSword(const Vector2& _position) : Sword(_position)
		{
			texture = ResourcesManager::Instance()->FindTexture("RedSword");
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
		Sword* create(Attribute _attribute, const Vector2& _position)
		{
			switch (_attribute)
			{
			case _FactoryMethodPattern::Attribute::Ice:
				return new IceSword(_position);
				break;
			case _FactoryMethodPattern::Attribute::Grass:
				return new GrassSword(_position);
				break;
			case _FactoryMethodPattern::Attribute::Fire:
				return new FireSword(_position);
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
		Slime* create(Attribute _attribute, const Vector2& _position)
		{
			switch (_attribute)
			{
			case _FactoryMethodPattern::Attribute::Ice:
				return new IceSlime(_position);
				break;
			case _FactoryMethodPattern::Attribute::Grass:
				return new GrassSlime(_position);
				break;
			case _FactoryMethodPattern::Attribute::Fire:
				return new FireSlime(_position);
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
private:
	SDL_Texture* textureTarget = nullptr;
	std::vector<_FactoryMethodPattern::GameObject*> gameObjectList;

public:
	FactoryMethodPattern(SDL_Renderer*);
	~FactoryMethodPattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
