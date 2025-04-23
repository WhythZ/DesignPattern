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
		virtual Attribute GetAttribute() = 0;
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
		Attribute GetAttribute() override
		{
			return Attribute::Ice;
		}
	};

	class GrassAttributeDef : public AttributeDef
	{
	public:
		Attribute GetAttribute() override
		{
			return Attribute::Grass;
		}
	};

	class FireAttributeDef : public AttributeDef
	{
	public:
		Attribute GetAttribute() override
		{
			return Attribute::Fire;
		}
	};

	class SlimeDefFactory
	{
	public:
		virtual SizeDef* GetSizeDef() = 0;
		virtual AttributeDef* GetAttributeDef() = 0;
	};

	class SmallIceSlimeDefFactory : public SlimeDefFactory
	{
	private:
		SmallSizeDef smallSizeDef;
		IceAttributeDef iceAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &smallSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &iceAttributeDef;
		}
	};

	class MediumIceSlimeDefFactory : public SlimeDefFactory
	{
	private:
		MediumSizeDef mediumSizeDef;
		IceAttributeDef iceAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &mediumSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &iceAttributeDef;
		}
	};

	class LargeIceSlimeDefFactory : public SlimeDefFactory
	{
	private:
		LargeSizeDef largeSizeDef;
		IceAttributeDef iceAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &largeSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &iceAttributeDef;
		}
	};

	class SmallGrassSlimeDefFactory : public SlimeDefFactory
	{
	private:
		SmallSizeDef smallSizeDef;
		GrassAttributeDef grassAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &smallSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &grassAttributeDef;
		}
	};

	class MediumGrassSlimeDefFactory : public SlimeDefFactory
	{
	private:
		MediumSizeDef mediumSizeDef;
		GrassAttributeDef grassAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &mediumSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &grassAttributeDef;
		}
	};

	class LargeGrassSlimeDefFactory : public SlimeDefFactory
	{
	private:
		LargeSizeDef largeSizeDef;
		GrassAttributeDef grassAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &largeSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &grassAttributeDef;
		}
	};

	class SmallFireSlimeDefFactory : public SlimeDefFactory
	{
	private:
		SmallSizeDef smallSizeDef;
		FireAttributeDef fireAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &smallSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &fireAttributeDef;
		}
	};

	class MediumFireSlimeDefFactory : public SlimeDefFactory
	{
	private:
		MediumSizeDef mediumSizeDef;
		FireAttributeDef fireAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &mediumSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &fireAttributeDef;
		}
	};

	class LargeFireSlimeDefFactory : public SlimeDefFactory
	{
	private:
		LargeSizeDef largeSizeDef;
		FireAttributeDef fireAttributeDef;

	public:
		SizeDef* GetSizeDef() override
		{
			return &largeSizeDef;
		}

		AttributeDef* GetAttributeDef() override
		{
			return &fireAttributeDef;
		}
	};

	class Slime
	{
	private:
		Atlas atlas;
		Vector2 position;
		Animation animation;

	public:
		Slime(SlimeDefFactory*, const Vector2&);
		~Slime() = default;

		void OnUpdate(float _delta)
		{
			animation.OnUpdate(_delta);
			animation.SetPosition(position);
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			animation.OnRender(_renderer);
		}
	};
}

class AbstractFactoryPattern : public Example
{
private:
	SDL_Texture* textureTarget = nullptr;
	std::vector<_AbstractFactoryPattern::Slime*> slimeList;

public:
	AbstractFactoryPattern(SDL_Renderer*);
	~AbstractFactoryPattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
