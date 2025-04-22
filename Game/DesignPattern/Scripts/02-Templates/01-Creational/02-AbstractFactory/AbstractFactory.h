#ifndef _ABSTRACT_FACTORY_H_
#define _ABSTRACT_FACTORY_H_

#include "Example.h"
#include "Animation.h"

namespace _AbstractFactoryPattern
{
	enum class Size { Small, Medium, Large };
	enum class Attribute { Ice, Grass, Fire };

	class SizeDef
	{
	public:
		virtual Size GetSize() = 0;

	};

	class AttributeDef
	{
	public:
		virtual Attribute get_attribute() = 0;

	};

	class SmallSizeDef : public SizeDef
	{
	public:
		Size GetSize() override
		{
			return Size::Small;
		}

	};

	class MediumSizeDef : public SizeDef
	{
	public:
		Size GetSize() override
		{
			return Size::Medium;
		}

	};

	class LargeSizeDef : public SizeDef
	{
	public:
		Size GetSize() override
		{
			return Size::Large;
		}

	};

	class IceAttributeDef : public AttributeDef
	{
	public:
		Attribute get_attribute() override
		{
			return Attribute::Ice;
		}

	};

	class GrassAttributeDef : public AttributeDef
	{
	public:
		Attribute get_attribute() override
		{
			return Attribute::Grass;
		}

	};

	class FireAttributeDef : public AttributeDef
	{
	public:
		Attribute get_attribute() override
		{
			return Attribute::Fire;
		}

	};

	class SlimeDefFactory
	{
	public:
		virtual SizeDef* get_size_def() = 0;
		virtual AttributeDef* get_attribute_def() = 0;

	};

	class SmallIceSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &small_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &ice_attribute_def;
		}

	private:
		SmallSizeDef small_size_def;
		IceAttributeDef ice_attribute_def;

	};

	class MediumIceSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &medium_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &ice_attribute_def;
		}

	private:
		MediumSizeDef medium_size_def;
		IceAttributeDef ice_attribute_def;

	};

	class LargeIceSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &large_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &ice_attribute_def;
		}

	private:
		LargeSizeDef large_size_def;
		IceAttributeDef ice_attribute_def;

	};

	class SmallGrassSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &small_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &grass_attribute_def;
		}

	private:
		SmallSizeDef small_size_def;
		GrassAttributeDef grass_attribute_def;

	};

	class MediumGrassSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &medium_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &grass_attribute_def;
		}

	private:
		MediumSizeDef medium_size_def;
		GrassAttributeDef grass_attribute_def;

	};

	class LargeGrassSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &large_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &grass_attribute_def;
		}

	private:
		LargeSizeDef large_size_def;
		GrassAttributeDef grass_attribute_def;

	};

	class SmallFireSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &small_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &fire_attribute_def;
		}

	private:
		SmallSizeDef small_size_def;
		FireAttributeDef fire_attribute_def;

	};

	class MediumFireSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &medium_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &fire_attribute_def;
		}

	private:
		MediumSizeDef medium_size_def;
		FireAttributeDef fire_attribute_def;

	};

	class LargeFireSlimeDefFactory : public SlimeDefFactory
	{
	public:
		SizeDef* get_size_def() override
		{
			return &large_size_def;
		}

		AttributeDef* get_attribute_def() override
		{
			return &fire_attribute_def;
		}

	private:
		LargeSizeDef large_size_def;
		FireAttributeDef fire_attribute_def;

	};

	class Slime
	{
	public:
		Slime(SlimeDefFactory* factory, const Vector2& position);
		~Slime();

		void OnUpdate(float delta)
		{
			animation.OnUpdate(delta);
			animation.SetPosition(position);
		}

		void OnRender(SDL_Renderer* renderer)
		{
			animation.OnRender(renderer);
		}

	private:
		Atlas atlas;
		Vector2 position;
		Animation animation;

	};
}

class AbstractFactoryPattern : public Example
{
public:
	AbstractFactoryPattern(SDL_Renderer* renderer);
	~AbstractFactoryPattern();

	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	SDL_Texture* textureTarget = nullptr;
	std::vector<_AbstractFactoryPattern::Slime*> slime_list;

};

#endif
