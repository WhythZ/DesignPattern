#ifndef _PROTOTYPE_H_
#define _PROTOTYPE_H_

#include "Example.h"
#include "Animation.h"

namespace _PrototypePattern
{
	class Prototype
	{
	public:
		virtual Prototype* Clone() const = 0;
	};

	class Chicken : public Prototype
	{
	private:
		Atlas* atlasWeapon = nullptr;
		Atlas* atlasBody = nullptr;
		Atlas* atlasHat = nullptr;
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

			Vector2 _position;
			_position.x = (float)(rand() % 665);
			_position.y = (float)(rand() % 590);
			animationWeapon.SetPosition(_position);
			animationBody.SetPosition(_position);
			animationHat.SetPosition(_position);
		}

		~Chicken() = default;

		void SetWeapon(Atlas* _atlas)
		{
			atlasWeapon = _atlas;
			animationWeapon.AddFrame(_atlas);
		}

		void SetBody(Atlas* _atlas)
		{
			atlasBody = _atlas;
			animationBody.AddFrame(_atlas);
		}

		void SetHat(Atlas* _atlas)
		{
			atlasHat = _atlas;
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

		Chicken* Clone() const override
		{
			Chicken* chicken = new Chicken();

			chicken->SetWeapon(atlasWeapon);
			chicken->SetBody(atlasBody);
			chicken->SetHat(atlasHat);

			return chicken;
		}
	};
}

class PrototypePattern : public Example
{
private:
	SDL_Texture* textureTarget = nullptr;
	std::vector<_PrototypePattern::Chicken*> chickenList;
	_PrototypePattern::Chicken* prototypeChicken = nullptr;
	Atlas atlasWeaponFork, atlasWeaponPlate, atlasWeaponSpoon;
	Atlas atlasBodyBrown, atlasBodyRed, atlasBodyWhite;
	Atlas atlasHatCrown, atlasHatGreen, atlasHatStraw;

public:
	PrototypePattern(SDL_Renderer*);
	~PrototypePattern();

	void OnEnter() override;
	void OnExit() override;

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
