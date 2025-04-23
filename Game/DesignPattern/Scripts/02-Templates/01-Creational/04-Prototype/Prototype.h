#ifndef _PROTOTYPE_H_
#define _PROTOTYPE_H_

#include "Example.h"
#include "Animation.h"

namespace _PrototypePattern
{
	class Prototype
	{
	public:
		virtual Prototype* clone() const = 0;

	};

	class Chicken : public Prototype
	{
	public:
		Chicken()
		{
			animation_weapon.SetLoop(true);
			animation_body.SetLoop(true);
			animation_hat.SetLoop(true);

			animation_weapon.SetInterval(0.1f);
			animation_body.SetInterval(0.1f);
			animation_hat.SetInterval(0.1f);

			Vector2 position;
			position.x = (float)(rand() % 665);
			position.y = (float)(rand() % 590);
			animation_weapon.SetPosition(position);
			animation_body.SetPosition(position);
			animation_hat.SetPosition(position);
		}

		~Chicken() = default;

		void set_weapon(Atlas* atlas)
		{
			atlas_weapon = atlas;
			animation_weapon.AddFrame(atlas);
		}

		void set_body(Atlas* atlas)
		{
			atlas_body = atlas;
			animation_body.AddFrame(atlas);
		}

		void set_hat(Atlas* atlas)
		{
			atlas_hat = atlas;
			animation_hat.AddFrame(atlas);
		}

		void OnUpdate(float delta)
		{
			animation_weapon.OnUpdate(delta);
			animation_body.OnUpdate(delta);
			animation_hat.OnUpdate(delta);
		}

		void OnRender(SDL_Renderer* renderer)
		{
			animation_weapon.OnRender(renderer);
			animation_body.OnRender(renderer);
			animation_hat.OnRender(renderer);
		}

		Chicken* clone() const override
		{
			Chicken* chicken = new Chicken();

			chicken->set_weapon(atlas_weapon);
			chicken->set_body(atlas_body);
			chicken->set_hat(atlas_hat);

			return chicken;
		}

	private:
		Atlas* atlas_weapon = nullptr;
		Atlas* atlas_body = nullptr;
		Atlas* atlas_hat = nullptr;
		Animation animation_weapon;
		Animation animation_body;
		Animation animation_hat;

	};
}

class PrototypePattern : public Example
{
public:
	PrototypePattern(SDL_Renderer* renderer);
	~PrototypePattern();

	void OnEnter() override;
	void OnExit() override;

	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	SDL_Texture* textureTarget = nullptr;
	std::vector<_PrototypePattern::Chicken*> chicken_list;
	_PrototypePattern::Chicken* prototype_chicken = nullptr;
	Atlas atlas_weapon_fork, atlas_weapon_plate, atlas_weapon_spoon;
	Atlas atlas_body_brown, atlas_body_red, atlas_body_white;
	Atlas atlas_hat_crown, atlas_hat_green, atlas_hat_straw;

};

#endif
