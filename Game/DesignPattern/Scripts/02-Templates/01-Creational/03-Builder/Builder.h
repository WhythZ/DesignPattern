#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "Example.h"
#include "Animation.h"

namespace _BuilderPattern
{
	class Chicken
	{
	private:
		Animation animationWeapon;
		Animation animationBody;
		Animation animationHat;

	public:
		Chicken()
		{
			animationWeapon.SetLoop(true);
			animationBody.SetLoop(true);
			animationHat.SetLoop(true);

			animationWeapon.SetInterval(0.1f);
			animationBody.SetInterval(0.1f);
			animationHat.SetInterval(0.1f);

			Vector2 _position = { 166, 148 };
			animationWeapon.SetPosition(_position);
			animationBody.SetPosition(_position);
			animationHat.SetPosition(_position);
		}

		~Chicken() = default;

		void SetWeapon(Atlas* _atlas)
		{
			animationWeapon.AddFrame(_atlas);
		}

		void SetBody(Atlas* _atlas)
		{
			animationBody.AddFrame(_atlas);
		}

		void SetHat(Atlas* _atlas)
		{
			animationHat.AddFrame(_atlas);
		}

		void OnUpdate(float _delta)
		{
			animationWeapon.OnUpdate(_delta);
			animationBody.OnUpdate(_delta);
			animationHat.OnUpdate(_delta);
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			animationWeapon.OnRender(_renderer);
			animationBody.OnRender(_renderer);
			animationHat.OnRender(_renderer);
		}
	};

	class Builder
	{
	protected:
		Atlas atlasWeapon;
		Atlas atlasBody;
		Atlas atlasHat;

	public:
		virtual void InitWeapon() = 0;
		virtual void InitBody() = 0;
		virtual void InitHat() = 0;
		virtual Chicken* Build() = 0;
	};

	class ElizabethChickenBuilder : public Builder
	{
	public:
		void InitWeapon() override
		{
			atlasWeapon.Clear();
			atlasWeapon.Load("weapon_fork_%d", 8);
		}

		void InitBody() override
		{
			atlasBody.Clear();
			atlasBody.Load("white_chicken_%d", 8);
		}

		void InitHat() override
		{
			atlasHat.Clear();
			atlasHat.Load("crown_%d", 8);
		}

		Chicken* Build() override
		{
			Chicken* _chicken = new Chicken();

			_chicken->SetWeapon(&atlasWeapon);
			_chicken->SetBody(&atlasBody);
			_chicken->SetHat(&atlasHat);

			return _chicken;
		}
	};

	class GreenHatOriginalRecipeChickenBuilder : public Builder
	{
	public:
		void InitWeapon() override
		{
			atlasWeapon.Clear();
			atlasWeapon.Load("weapon_plate_%d", 8);
		}

		void InitBody() override
		{
			atlasBody.Clear();
			atlasBody.Load("brown_chicken_%d", 8);
		}

		void InitHat() override
		{
			atlasHat.Clear();
			atlasHat.Load("green_hat_%d", 8);
		}

		Chicken* Build() override
		{
			Chicken* _chicken = new Chicken();

			_chicken->SetWeapon(&atlasWeapon);
			_chicken->SetBody(&atlasBody);
			_chicken->SetHat(&atlasHat);

			return _chicken;
		}
	};

	class CustomChickenBuilder : public Builder
	{
	public:
		void InitWeapon() override;
		void InitBody() override;
		void InitHat() override;
		Chicken* Build() override;
	};
}

class BuilderPattern : public Example
{
private:
	SDL_Texture* textureTarget = nullptr;
	_BuilderPattern::Chicken* chicken = nullptr;
	_BuilderPattern::CustomChickenBuilder customChickenBuilder;
	_BuilderPattern::ElizabethChickenBuilder elizabethChickenBuilder;
	_BuilderPattern::GreenHatOriginalRecipeChickenBuilder greenHatOriginalRecipeChickenBuilder;

public:
	BuilderPattern(SDL_Renderer*);
	~BuilderPattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
