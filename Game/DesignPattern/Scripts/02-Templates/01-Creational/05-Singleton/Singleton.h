#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "Example.h"
#include "Animation.h"

#include <unordered_map>

namespace _SingletonPattern
{
	class Player
	{
	public:
		Player()
		{
			atlas.Load("helicopter_%d", 2);

			animation.AddFrame(&atlas);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);
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

			animation.OnUpdate(delta);
			animation.SetPosition(position);
			animation.SetFlip(isFacingRight ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		}

		void OnRender(SDL_Renderer* renderer)
		{
			animation.OnRender(renderer);
		}

		void SetPosition(const Vector2& position)
		{
			this->position = position;
		}

		const Vector2& get_posoition() const
		{
			return position;
		}

	private:
		Atlas atlas;
		Vector2 position;
		Animation animation;
		bool isFacingRight = true;
		bool isMoveUp = false, isMoveDown = false;
		bool isMoveLeft = false, isMoveRight = false;

	};

	class Scene
	{
	public:
		Scene(Player* _player) : player(_player) {}
		~Scene() = default;

		virtual void OnEnter() {}

		void OnInput(const SDL_Event* event)
		{
			player->OnInput(event);
		}

		void OnUpdate(float delta)
		{
			player->OnUpdate(delta);

			SDL_FPoint position_player = { player->get_posoition().x, player->get_posoition().y };
			if (SDL_PointInFRect(&position_player, &rect_apron))
				on_reach();
		}

		void OnRender(SDL_Renderer* renderer)
		{
			SDL_RenderCopyF(renderer, texture_background, nullptr, nullptr);
			SDL_RenderCopyF(renderer, ResourcesManager::Instance()->findTexture("apron"), nullptr, &rect_apron);
			player->OnRender(renderer);
		}

	protected:
		Player* player = nullptr;
		SDL_FRect rect_apron = { 0 };
		SDL_Texture* texture_background = nullptr;

	protected:
		virtual void on_reach() = 0;

	};

	class Level_1 : public Scene
	{
	public:
		Level_1(Player* player) : Scene(player)
		{
			rect_apron = { 255, 255, 200, 200 };
			texture_background = ResourcesManager::Instance()->findTexture("level_1");
		}

		~Level_1() = default;

		void OnEnter() override
		{
			player->SetPosition({ 150, 618 });
		}

	protected:
		void on_reach() override;

	};

	class Level_2 : public Scene
	{
	public:
		Level_2(Player* player) : Scene(player)
		{
			rect_apron = { 500, 260, 200, 200 };
			texture_background = ResourcesManager::Instance()->findTexture("level_2");
		}

		~Level_2() = default;

		void OnEnter() override
		{
			player->SetPosition({ 185, 284 });
		}

	protected:
		void on_reach() override;

	};

	class Level_3 : public Scene
	{
	public:
		Level_3(Player* player) : Scene(player)
		{
			rect_apron = { 265, 10, 200, 200 };
			texture_background = ResourcesManager::Instance()->findTexture("level_3");
		}

		~Level_3() = default;

		void OnEnter() override
		{
			player->SetPosition({ 284, 618 });
		}

	protected:
		void on_reach() override;

	};

	class SceneManager
	{
	public:
		static SceneManager* Instance()
		{
			if (!manager)
				manager = new SceneManager();

			return manager;
		}

		void add(const std::string& id, Scene* scene)
		{
			scene_pool[id] = scene;
		}

		void SwitchTo(const std::string& id)
		{
			current_scene = scene_pool[id];

			if (current_scene) 
				current_scene->OnEnter();
		}

		void OnInput(const SDL_Event* event)
		{
			if (!current_scene) return;

			current_scene->OnInput(event);
		}

		void OnUpdate(float delta)
		{
			if (!current_scene) return;

			current_scene->OnUpdate(delta);
		}

		void OnRender(SDL_Renderer* renderer)
		{
			if (!current_scene) return;

			current_scene->OnRender(renderer);
		}

	private:
		static SceneManager* manager;
		Scene* current_scene = nullptr;
		std::unordered_map<std::string, Scene*> scene_pool;

	private:
		SceneManager() = default;
		~SceneManager() = default;

	};
}

class SingletonPattern : public Example
{
public:
	SingletonPattern(SDL_Renderer* renderer);
	~SingletonPattern();

	void OnInput(const SDL_Event* event) override;
	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	_SingletonPattern::Player player;
	SDL_Texture* textureTarget = nullptr;

};

#endif
