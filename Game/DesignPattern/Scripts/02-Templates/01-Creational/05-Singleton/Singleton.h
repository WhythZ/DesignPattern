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

		void on_input(const SDL_Event* event)
		{
			switch (event->type)
			{
			case SDL_KEYDOWN:
				switch (event->key.keysym.sym)
				{
				case SDLK_UP:		is_move_up = true;		break;
				case SDLK_DOWN:		is_move_down = true;	break;
				case SDLK_LEFT:		is_move_left = true;	break;
				case SDLK_RIGHT:	is_move_right = true;	break;
				default: break;
				}
				break;
			case SDL_KEYUP:
				switch (event->key.keysym.sym)
				{
				case SDLK_UP:		is_move_up = false;		break;
				case SDLK_DOWN:		is_move_down = false;	break;
				case SDLK_LEFT:		is_move_left = false;	break;
				case SDLK_RIGHT:	is_move_right = false;	break;
				default: break;
				}
				break;
			default: break;
			}
		}

		void OnUpdate(float delta)
		{
			static const float speed = 2.0f;
			Vector2 direction = Vector2((float)(is_move_right - is_move_left), (float)(is_move_down - is_move_up)).Normalize();
			if (std::abs(direction.x) > 0.0001f)
				is_facing_right = direction.x > 0;
			position = position + direction * speed;

			animation.OnUpdate(delta);
			animation.SetPosition(position);
			animation.SetFlip(is_facing_right ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
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
		bool is_facing_right = true;
		bool is_move_up = false, is_move_down = false;
		bool is_move_left = false, is_move_right = false;

	};

	class Scene
	{
	public:
		Scene(Player* _player) : player(_player) {}
		~Scene() = default;

		virtual void on_enter() {}

		void on_input(const SDL_Event* event)
		{
			player->on_input(event);
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
			SDL_RenderCopyF(renderer, ResourcesManager::instance()->find_texture("apron"), nullptr, &rect_apron);
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
			texture_background = ResourcesManager::instance()->find_texture("level_1");
		}

		~Level_1() = default;

		void on_enter() override
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
			texture_background = ResourcesManager::instance()->find_texture("level_2");
		}

		~Level_2() = default;

		void on_enter() override
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
			texture_background = ResourcesManager::instance()->find_texture("level_3");
		}

		~Level_3() = default;

		void on_enter() override
		{
			player->SetPosition({ 284, 618 });
		}

	protected:
		void on_reach() override;

	};

	class SceneManager
	{
	public:
		static SceneManager* instance()
		{
			if (!manager)
				manager = new SceneManager();

			return manager;
		}

		void add(const std::string& id, Scene* scene)
		{
			scene_pool[id] = scene;
		}

		void switch_to(const std::string& id)
		{
			current_scene = scene_pool[id];

			if (current_scene) 
				current_scene->on_enter();
		}

		void on_input(const SDL_Event* event)
		{
			if (!current_scene) return;

			current_scene->on_input(event);
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

	void on_input(const SDL_Event* event) override;
	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	_SingletonPattern::Player player;
	SDL_Texture* texture_target = nullptr;

};

#endif
