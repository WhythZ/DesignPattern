#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "Example.h"
#include "Animation.h"

namespace _BuilderPattern
{
	class Chicken
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

			Vector2 position = { 166, 148 };
			animation_weapon.SetPosition(position);
			animation_body.SetPosition(position);
			animation_hat.SetPosition(position);
		}

		~Chicken() = default;

		void set_weapon(Atlas* atlas)
		{
			animation_weapon.AddFrame(atlas);
		}

		void set_body(Atlas* atlas)
		{
			animation_body.AddFrame(atlas);
		}

		void set_hat(Atlas* atlas)
		{
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

	private:
		Animation animation_weapon;
		Animation animation_body;
		Animation animation_hat;

	};

	class Builder
	{
	public:
		virtual void init_weapon() = 0;
		virtual void init_body() = 0;
		virtual void init_hat() = 0;
		virtual Chicken* build() = 0;

	protected:
		Atlas atlas_weapon;
		Atlas atlas_body;
		Atlas atlas_hat;

	};

	class ElizabethChickenBuilder : public Builder
	{
	public:
		void init_weapon() override
		{
			atlas_weapon.Clear();
			atlas_weapon.Load("weapon_fork_%d", 8);
		}

		void init_body() override
		{
			atlas_body.Clear();
			atlas_body.Load("white_chicken_%d", 8);
		}

		void init_hat() override
		{
			atlas_hat.Clear();
			atlas_hat.Load("crown_%d", 8);
		}

		Chicken* build() override
		{
			Chicken* chicken = new Chicken();

			chicken->set_weapon(&atlas_weapon);
			chicken->set_body(&atlas_body);
			chicken->set_hat(&atlas_hat);

			return chicken;
		}

	};

	class GreenHatOriginalRecipeChickenBuilder : public Builder
	{
	public:
		void init_weapon() override
		{
			atlas_weapon.Clear();
			atlas_weapon.Load("weapon_plate_%d", 8);
		}

		void init_body() override
		{
			atlas_body.Clear();
			atlas_body.Load("brown_chicken_%d", 8);
		}

		void init_hat() override
		{
			atlas_hat.Clear();
			atlas_hat.Load("green_hat_%d", 8);
		}

		Chicken* build() override
		{
			Chicken* chicken = new Chicken();

			chicken->set_weapon(&atlas_weapon);
			chicken->set_body(&atlas_body);
			chicken->set_hat(&atlas_hat);

			return chicken;
		}

	};

	class CustomChickenBuilder : public Builder
	{
	public:
		void init_weapon() override;
		void init_body() override;
		void init_hat() override;
		Chicken* build() override;

	};
}

class BuilderPattern : public Example
{
public:
	BuilderPattern(SDL_Renderer* renderer);
	~BuilderPattern();

	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	SDL_Texture* textureTarget = nullptr;
	_BuilderPattern::Chicken* chicken = nullptr;
	_BuilderPattern::CustomChickenBuilder custom_chicken_builder;
	_BuilderPattern::ElizabethChickenBuilder elizabeth_chicken_builder;
	_BuilderPattern::GreenHatOriginalRecipeChickenBuilder green_hat_original_recipe_chicken_builder;

};

#endif
