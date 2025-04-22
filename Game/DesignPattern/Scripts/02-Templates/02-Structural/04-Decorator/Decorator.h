#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include "Vector2.h"
#include "Example.h"

#include <vector>
#include <functional>

namespace _DecoratorPattern
{
	class Character
	{
	public:
		virtual ~Character() {};
		virtual void OnInput(const SDL_Event* event) {}
		virtual void OnUpdate(float delta) {}
		virtual void OnRender(SDL_Renderer* renderer) {}

		virtual void set_speed(float speed) { this->speed = speed; }
		virtual void set_size(const Vector2& size) { this->size = size; }
		virtual void set_texture(SDL_Texture* texture) { this->texture = texture; }

		virtual const Vector2& GetSize() const { return size; }
		virtual const Vector2& get_position() const { return position; }

	protected:
		Vector2 size;
		Vector2 position;
		float speed = 2.0f;
		SDL_Texture* texture = nullptr;

	};

	class Player : public Character
	{
	public:
		Player()
		{
			size = { 66, 66 };
			position = { 360, 360 };
			texture = ResourcesManager::Instance()->findTexture("small_plane");
		}

		~Player() = default;

		void OnInput(const SDL_Event* event) override
		{
			switch (event->type)
			{
			case SDL_KEYDOWN:
				switch (event->key.keysym.sym)
				{
				case SDLK_UP:		isMoveUp = true;		break;
				case SDLK_DOWN:		isMoveDown = true;	break;
				case SDLK_LEFT:		isMoveLeft = true;	break;
				case SDLK_RIGHT:	isMoveRight = true;	break;
				default: break;
				}
				break;
			case SDL_KEYUP:
				switch (event->key.keysym.sym)
				{
				case SDLK_UP:		isMoveUp = false;		break;
				case SDLK_DOWN:		isMoveDown = false;	break;
				case SDLK_LEFT:		isMoveLeft = false;	break;
				case SDLK_RIGHT:	isMoveRight = false;	break;
				default: break;
				}
				break;
			default: break;
			}
		}

		void OnUpdate(float delta) override
		{
			Vector2 direction = Vector2((float)(isMoveRight - isMoveLeft), (float)(isMoveDown - isMoveUp)).Normalize();
			position = position + direction * speed;
		}

		void OnRender(SDL_Renderer* renderer) override
		{
			SDL_FRect rect =
			{
				position.x - size.x / 2,
				position.y - size.y / 2,
				GetSize().x, GetSize().y
			};
			SDL_RenderCopyF(renderer, texture, nullptr, &rect);
		}

	private:
		bool isMoveUp = false, isMoveDown = false;
		bool isMoveLeft = false, isMoveRight = false;

	};

	class SpeedUpDecorator : public Character
	{
	public:
		SpeedUpDecorator(Character* character)
		{
			this->player = character;
		}

		~SpeedUpDecorator() = default;

		void OnInput(const SDL_Event* event) override { player->OnInput(event); }

		void OnUpdate(float delta) override
		{
			player->set_speed(4.0f);

			player->OnUpdate(delta);
		}

		void OnRender(SDL_Renderer* renderer) override { player->OnRender(renderer); }

		void set_speed(float speed) override { player->set_speed(speed); }
		void set_size(const Vector2& size) override { player->set_size(size); }
		void set_texture(SDL_Texture* texture) override { player->set_texture(texture); }

		const Vector2& GetSize() const override { return player->GetSize(); }
		const Vector2& get_position() const override { return player->get_position(); }

	private:
		Character* player = nullptr;

	};

	class SizeGrownDecorator : public Character
	{
	public:
		SizeGrownDecorator(Character* character)
		{
			this->player = character;
		}

		~SizeGrownDecorator() = default;

		void OnInput(const SDL_Event* event) override { player->OnInput(event); }

		void OnUpdate(float delta) override
		{
			player->set_size({ 96, 96 });

			player->OnUpdate(delta);
		}

		void OnRender(SDL_Renderer* renderer) override { player->OnRender(renderer); }

		void set_speed(float speed) override { player->set_speed(speed); }
		void set_size(const Vector2& size) override { player->set_size(size); }
		void set_texture(SDL_Texture* texture) override { player->set_texture(texture); }

		const Vector2& GetSize() const override { return player->GetSize(); }
		const Vector2& get_position() const override { return player->get_position(); }

	private:
		Character* player = nullptr;

	};

	class AppearanceChangedDecorator : public Character
	{
	public:
		AppearanceChangedDecorator(Character* character)
		{
			this->player = character;
		}

		~AppearanceChangedDecorator() = default;

		void OnInput(const SDL_Event* event) override { player->OnInput(event); }

		void OnUpdate(float delta) override
		{
			player->set_texture(ResourcesManager::Instance()->findTexture("large_plane"));

			player->OnUpdate(delta);
		}

		void OnRender(SDL_Renderer* renderer) override { player->OnRender(renderer); }

		void set_speed(float speed) override { player->set_speed(speed); }
		void set_size(const Vector2& size) override { player->set_size(size); }
		void set_texture(SDL_Texture* texture) override { player->set_texture(texture); }

		const Vector2& GetSize() const override { return player->GetSize(); }
		const Vector2& get_position() const override { return player->get_position(); }

	private:
		Character* player = nullptr;

	};

	class Prop
	{
	public:
		using CollideCallback = std::function<void()>;

	public:
		Prop(const Vector2& _position, SDL_Texture* _texture, CollideCallback _callback)
			: position(_position), texture(_texture), callback(_callback) {}
		~Prop() = default;

		void OnRender(SDL_Renderer* renderer) const
		{
			SDL_FRect rect = { position.x - 16, position.y - 16, 32, 32 };
			SDL_RenderCopyF(renderer, texture, nullptr, &rect);
		}

		void check_collide(const Character* character)
		{
			if (!is_valid) return;

			SDL_FPoint point = { position.x, position.y };
			SDL_FRect rect = 
			{ 
				character->get_position().x - character->GetSize().x / 2, 
				character->get_position().y - character->GetSize().y / 2, 
				character->GetSize().x, character->GetSize().y 
			};
			if (SDL_PointInFRect(&point, &rect))
			{
				callback();
				is_valid = false;
			}
		}

		bool can_remove() const
		{
			return !is_valid;
		}

	private:
		Vector2 position;
		bool is_valid = true;
		CollideCallback callback;
		SDL_Texture* texture = nullptr;

	};
}

class DecoratorPattern : public Example
{
public:
	DecoratorPattern(SDL_Renderer* renderer);
	~DecoratorPattern();

	void OnInput(const SDL_Event* event) override;
	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	SDL_Texture* textureTarget = nullptr;
	_DecoratorPattern::Character* player = nullptr;
	std::vector<_DecoratorPattern::Prop*> prop_list;

};

#endif
