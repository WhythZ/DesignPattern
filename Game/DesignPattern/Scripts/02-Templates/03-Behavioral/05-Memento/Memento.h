#ifndef _MEMENTO_H_
#define _MEMENTO_H_

#include <cJSON.h>

#include "Example.h"
#include "Animation.h"

namespace _MementoPattern
{
	class Serializable
	{
	public:
		virtual ~Serializable() = default;

		virtual cJSON* Dump() = 0;
		virtual void Load(const cJSON*) = 0;
	};

	class Player : public Serializable
	{
	private:
		Atlas atlas;
		Vector2 position;
		Animation animation;
		bool isFacingRight = true;
		bool isMoveUp = false, isMoveDown = false;
		bool isMoveLeft = false, isMoveRight = false;

	public:
		Player()
		{
			atlas.Load("player_right_%d", 5);

			animation.AddFrame(&atlas);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);

			position = { 100, 200 };
		}

		~Player() = default;

		void OnInput(const SDL_Event* _event)
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

		void OnUpdate(float _delta)
		{
			static const float _speed = 2.0f;
			Vector2 _direction = Vector2((float)(isMoveRight - isMoveLeft), (float)(isMoveDown - isMoveUp)).Normalize();
			if (std::abs(_direction.x) > 0.0001f)
				isFacingRight = _direction.x > 0;
			position = position + _direction * _speed;

			if (position.y < 120) position.y = 120;
			if (position.y > 384) position.y = 384;
			if (position.x < 0) position.x = 0;
			if (position.x > 384) position.x = 384;

			animation.OnUpdate(_delta);
			animation.SetPosition(position);
			animation.SetFlip(isFacingRight ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			SDL_FRect _rect = { position.x - 16, position.y + 30, 32, 20 };
			SDL_RenderCopyF(_renderer, ResourcesManager::Instance()->FindTexture("shadow_player"), nullptr, &_rect);

			animation.OnRender(_renderer);
		}

		cJSON* Dump() override
		{
			cJSON* _jsonRoot = cJSON_CreateObject();

			cJSON* _jsonPosition = cJSON_AddObjectToObject(_jsonRoot, "position");
			cJSON_AddNumberToObject(_jsonPosition, "x", position.x);
			cJSON_AddNumberToObject(_jsonPosition, "y", position.y);

			cJSON_AddBoolToObject(_jsonRoot, "facing_right", isFacingRight);

			return _jsonRoot;
		}

		void Load(const cJSON* _json) override
		{
			cJSON* _jsonPosition = cJSON_GetObjectItem(_json, "position");
			position.x = (float)cJSON_GetObjectItem(_jsonPosition, "x")->valuedouble;
			position.y = (float)cJSON_GetObjectItem(_jsonPosition, "y")->valuedouble;

			isFacingRight = cJSON_GetObjectItem(_json, "facing_right")->valueint;
		}
	};

	class Switch : public Serializable
	{
	private:
		bool isOpened = false;

	public:
		Switch() = default;
		~Switch() = default;

		void OnInput(const SDL_Event* _event)
		{
			switch (_event->type)
			{
			case SDL_KEYDOWN:
				switch (_event->key.keysym.sym)
				{
				case SDLK_SPACE: 
					isOpened = !isOpened; 
					Mix_PlayChannel(-1, ResourcesManager::Instance()->FindAudio("switch"), 0);
					break;
				default: break;
				}
				break;
			default: break;
			}
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			static const SDL_FRect _rect = { 215, 250, 122, 88 };
			SDL_RenderCopyF(_renderer, ResourcesManager::Instance()
				->FindTexture(isOpened ? "bar_opened" : "bar_closed"), nullptr, &_rect);
		}

		cJSON* Dump() override
		{
			cJSON* _jsonRoot = cJSON_CreateObject();
			cJSON_AddBoolToObject(_jsonRoot, "opened", isOpened);
			return _jsonRoot;
		}

		void Load(const cJSON* _json) override
		{
			cJSON* _jsonPosition = cJSON_GetObjectItem(_json, "position");
			isOpened = cJSON_GetObjectItem(_json, "opened")->valueint;
		}
	};
}

class MementoPattern : public Example
{
private:
	_MementoPattern::Player player;
	_MementoPattern::Switch mySwitch;
	SDL_Texture* textureTarget = nullptr;

public:
	MementoPattern(SDL_Renderer*);
	~MementoPattern();

	void OnInput(const SDL_Event*) override;
	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;

private:
	void LoadScene();
	void DumpScene();
};

#endif
