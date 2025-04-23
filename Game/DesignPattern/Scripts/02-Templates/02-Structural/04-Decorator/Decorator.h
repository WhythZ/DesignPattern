#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include <vector>
#include <functional>

#include "Vector2.h"
#include "Example.h"

namespace _DecoratorPattern
{
	class Character
	{
	protected:
		Vector2 size;
		Vector2 position;
		float speed = 2.0f;
		SDL_Texture* texture = nullptr;

	public:
		virtual ~Character() {};

		virtual void OnInput(const SDL_Event*) {}
		virtual void OnUpdate(float) {}
		virtual void OnRender(SDL_Renderer*) {}

		virtual void SetSpeed(float _speed) { speed = _speed; }
		virtual void SetSize(const Vector2& _size) { size = _size; }
		virtual void SetTexture(SDL_Texture* _texture) { texture = _texture; }

		virtual const Vector2& GetSize() const { return size; }
		virtual const Vector2& GetPosition() const { return position; }
	};

	class Player : public Character
	{
	private:
		bool isMoveUp = false, isMoveDown = false;
		bool isMoveLeft = false, isMoveRight = false;

	public:
		Player()
		{
			size = { 66, 66 };
			position = { 360, 360 };
			texture = ResourcesManager::Instance()->FindTexture("small_plane");
		}
		~Player() = default;

		void OnInput(const SDL_Event* _event) override
		{
			switch (_event->type)
			{
			case SDL_KEYDOWN:
				switch (_event->key.keysym.sym)
				{
				case SDLK_UP:		isMoveUp = true;		break;
				case SDLK_DOWN:		isMoveDown = true;		break;
				case SDLK_LEFT:		isMoveLeft = true;		break;
				case SDLK_RIGHT:	isMoveRight = true;		break;
				default: break;
				}
				break;
			case SDL_KEYUP:
				switch (_event->key.keysym.sym)
				{
				case SDLK_UP:		isMoveUp = false;		break;
				case SDLK_DOWN:		isMoveDown = false;		break;
				case SDLK_LEFT:		isMoveLeft = false;		break;
				case SDLK_RIGHT:	isMoveRight = false;	break;
				default: break;
				}
				break;
			default: break;
			}
		}

		void OnUpdate(float _delta) override
		{
			Vector2 direction = Vector2((float)(isMoveRight - isMoveLeft), (float)(isMoveDown - isMoveUp)).Normalize();
			position = position + direction * speed;
		}

		void OnRender(SDL_Renderer* _renderer) override
		{
			SDL_FRect _rect =
			{
				position.x - size.x / 2,
				position.y - size.y / 2,
				GetSize().x, GetSize().y
			};
			SDL_RenderCopyF(_renderer, texture, nullptr, &_rect);
		}
	};

	class SpeedUpDecorator : public Character
	{
	public:
		SpeedUpDecorator(Character* _character)
		{
			player = _character;
		}

		~SpeedUpDecorator() = default;

		void OnInput(const SDL_Event* _event) override { player->OnInput(_event); }

		void OnUpdate(float _delta) override
		{
			player->SetSpeed(4.0f);

			player->OnUpdate(_delta);
		}

		void OnRender(SDL_Renderer* _renderer) override { player->OnRender(_renderer); }

		void SetSpeed(float _speed) override { player->SetSpeed(_speed); }
		void SetSize(const Vector2& _size) override { player->SetSize(_size); }
		void SetTexture(SDL_Texture* _texture) override { player->SetTexture(_texture); }

		const Vector2& GetSize() const override { return player->GetSize(); }
		const Vector2& GetPosition() const override { return player->GetPosition(); }

	private:
		Character* player = nullptr;

	};

	class SizeGrownDecorator : public Character
	{
	private:
		Character* player = nullptr;

	public:
		SizeGrownDecorator(Character* _character)
		{
			this->player = _character;
		}
		~SizeGrownDecorator() = default;

		void OnInput(const SDL_Event* _event) override { player->OnInput(_event); }

		void OnUpdate(float _delta) override
		{
			player->SetSize({ 96, 96 });

			player->OnUpdate(_delta);
		}

		void OnRender(SDL_Renderer* _renderer) override { player->OnRender(_renderer); }

		void SetSpeed(float _speed) override { player->SetSpeed(_speed); }
		void SetSize(const Vector2& _size) override { player->SetSize(_size); }
		void SetTexture(SDL_Texture* _texture) override { player->SetTexture(_texture); }

		const Vector2& GetSize() const override { return player->GetSize(); }
		const Vector2& GetPosition() const override { return player->GetPosition(); }
	};

	class AppearanceChangedDecorator : public Character
	{
	private:
		Character* player = nullptr;

	public:
		AppearanceChangedDecorator(Character* _character)
		{
			this->player = _character;
		}
		~AppearanceChangedDecorator() = default;

		void OnInput(const SDL_Event* _event) override { player->OnInput(_event); }

		void OnUpdate(float _delta) override
		{
			player->SetTexture(ResourcesManager::Instance()->FindTexture("large_plane"));

			player->OnUpdate(_delta);
		}

		void OnRender(SDL_Renderer* _renderer) override { player->OnRender(_renderer); }

		void SetSpeed(float _speed) override { player->SetSpeed(_speed); }
		void SetSize(const Vector2& _size) override { player->SetSize(_size); }
		void SetTexture(SDL_Texture* _texture) override { player->SetTexture(_texture); }

		const Vector2& GetSize() const override { return player->GetSize(); }
		const Vector2& GetPosition() const override { return player->GetPosition(); }
	};

	class Prop
	{
	public:
		using CollideCallback = std::function<void()>;

	private:
		Vector2 position;
		bool isValid = true;
		CollideCallback callback;
		SDL_Texture* texture = nullptr;

	public:
		Prop(const Vector2& _position, SDL_Texture* _texture, CollideCallback _callback)
			: position(_position), texture(_texture), callback(_callback) {}
		~Prop() = default;

		void OnRender(SDL_Renderer* _renderer) const
		{
			SDL_FRect rect = { position.x - 16, position.y - 16, 32, 32 };
			SDL_RenderCopyF(_renderer, texture, nullptr, &rect);
		}

		void CheckCollide(const Character* _character)
		{
			if (!isValid) return;

			SDL_FPoint _point = { position.x, position.y };
			SDL_FRect _rect = 
			{ 
				_character->GetPosition().x - _character->GetSize().x / 2, 
				_character->GetPosition().y - _character->GetSize().y / 2, 
				_character->GetSize().x, _character->GetSize().y 
			};
			if (SDL_PointInFRect(&_point, &_rect))
			{
				callback();
				isValid = false;
			}
		}

		bool CanRemove() const
		{
			return !isValid;
		}
	};
}

class DecoratorPattern : public Example
{
private:
	SDL_Texture* textureTarget = nullptr;
	_DecoratorPattern::Character* player = nullptr;
	std::vector<_DecoratorPattern::Prop*> propList;

public:
	DecoratorPattern(SDL_Renderer*);
	~DecoratorPattern();

	void OnInput(const SDL_Event*) override;
	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
