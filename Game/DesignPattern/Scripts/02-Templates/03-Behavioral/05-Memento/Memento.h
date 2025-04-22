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

		virtual cJSON* dump() = 0;
		virtual void Load(const cJSON* json) = 0;

	};

	class Player : public Serializable
	{
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

		void OnInput(const SDL_Event* event)
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

		void OnUpdate(float delta)
		{
			static const float speed = 2.0f;
			Vector2 direction = Vector2((float)(isMoveRight - isMoveLeft), (float)(isMoveDown - isMoveUp)).Normalize();
			if (std::abs(direction.x) > 0.0001f)
				isFacingRight = direction.x > 0;
			position = position + direction * speed;

			if (position.y < 120) position.y = 120;
			if (position.y > 384) position.y = 384;
			if (position.x < 0) position.x = 0;
			if (position.x > 384) position.x = 384;

			animation.OnUpdate(delta);
			animation.SetPosition(position);
			animation.SetFlip(isFacingRight ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		}

		void OnRender(SDL_Renderer* renderer)
		{
			SDL_FRect rect = { position.x - 16, position.y + 30, 32, 20 };
			SDL_RenderCopyF(renderer, ResourcesManager::Instance()->findTexture("shadow_player"), nullptr, &rect);

			animation.OnRender(renderer);
		}

		cJSON* dump() override
		{
			cJSON* json_root = cJSON_CreateObject();

			cJSON* json_position = cJSON_AddObjectToObject(json_root, "position");
			cJSON_AddNumberToObject(json_position, "x", position.x);
			cJSON_AddNumberToObject(json_position, "y", position.y);

			cJSON_AddBoolToObject(json_root, "facing_right", isFacingRight);

			return json_root;
		}

		void Load(const cJSON* json) override
		{
			cJSON* json_position = cJSON_GetObjectItem(json, "position");
			position.x = (float)cJSON_GetObjectItem(json_position, "x")->valuedouble;
			position.y = (float)cJSON_GetObjectItem(json_position, "y")->valuedouble;

			isFacingRight = cJSON_GetObjectItem(json, "facing_right")->valueint;
		}

	private:
		Atlas atlas;
		Vector2 position;
		Animation animation;
		bool isFacingRight = true;
		bool isMoveUp = false, isMoveDown = false;
		bool isMoveLeft = false, isMoveRight = false;

	};

	class Switch : public Serializable
	{
	public:
		Switch() = default;
		~Switch() = default;

		void OnInput(const SDL_Event* event)
		{
			switch (event->type)
			{
			case SDL_KEYDOWN:
				switch (event->key.keysym.sym)
				{
				case SDLK_SPACE: 
					is_opened = !is_opened; 
					Mix_PlayChannel(-1, ResourcesManager::Instance()->findAudio("switch"), 0);
					break;
				default: break;
				}
				break;
			default: break;
			}
		}

		void OnRender(SDL_Renderer* renderer)
		{
			static const SDL_FRect rect = { 215, 250, 122, 88 };
			SDL_RenderCopyF(renderer, ResourcesManager::Instance()
				->findTexture(is_opened ? "bar_opened" : "bar_closed"), nullptr, &rect);
		}

		cJSON* dump() override
		{
			cJSON* json_root = cJSON_CreateObject();
			cJSON_AddBoolToObject(json_root, "opened", is_opened);
			return json_root;
		}

		void Load(const cJSON* json) override
		{
			cJSON* json_position = cJSON_GetObjectItem(json, "position");
			is_opened = cJSON_GetObjectItem(json, "opened")->valueint;
		}

	private:
		bool is_opened = false;

	};
}

class MementoPattern : public Example
{
public:
	MementoPattern(SDL_Renderer* renderer);
	~MementoPattern();

	void OnInput(const SDL_Event* event) override;
	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	_MementoPattern::Player player;
	_MementoPattern::Switch _switch;
	SDL_Texture* textureTarget = nullptr;

private:
	void load_scene();
	void dump_scene();

};

#endif
