#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <unordered_map>

#include "Example.h"
#include "Animation.h"

namespace _SingletonPattern
{
	class Player
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
			atlas.Load("helicopter_%d", 2);

			animation.AddFrame(&atlas);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);
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

			animation.OnUpdate(_delta);
			animation.SetPosition(position);
			animation.SetFlip(isFacingRight ? SDL_RendererFlip::SDL_FLIP_NONE : SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			animation.OnRender(_renderer);
		}

		void SetPosition(const Vector2& _position)
		{
			this->position = _position;
		}

		const Vector2& GetPosoition() const
		{
			return position;
		}
	};

	class Scene
	{
	protected:
		Player* player = nullptr;
		SDL_FRect rectApron = { 0 };
		SDL_Texture* textureBackground = nullptr;

	public:
		Scene(Player* _player) : player(_player) {}
		~Scene() = default;

		virtual void OnEnter() {}

		void OnInput(const SDL_Event* _event)
		{
			player->OnInput(_event);
		}

		void OnUpdate(float _delta)
		{
			player->OnUpdate(_delta);

			SDL_FPoint _positionPlayer = { player->GetPosoition().x, player->GetPosoition().y };
			if (SDL_PointInFRect(&_positionPlayer, &rectApron))
				OnReach();
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			SDL_RenderCopyF(_renderer, textureBackground, nullptr, nullptr);
			SDL_RenderCopyF(_renderer, ResourcesManager::Instance()->findTexture("apron"), nullptr, &rectApron);
			player->OnRender(_renderer);
		}

	protected:
		virtual void OnReach() = 0;
	};

	class Level01 : public Scene
	{
	public:
		Level01(Player* _player) : Scene(_player)
		{
			rectApron = { 255, 255, 200, 200 };
			textureBackground = ResourcesManager::Instance()->findTexture("level_1");
		}

		~Level01() = default;

		void OnEnter() override
		{
			player->SetPosition({ 150, 618 });
		}

	protected:
		void OnReach() override;
	};

	class Level02 : public Scene
	{
	public:
		Level02(Player* _player) : Scene(_player)
		{
			rectApron = { 500, 260, 200, 200 };
			textureBackground = ResourcesManager::Instance()->findTexture("level_2");
		}

		~Level02() = default;

		void OnEnter() override
		{
			player->SetPosition({ 185, 284 });
		}

	protected:
		void OnReach() override;
	};

	class Level03 : public Scene
	{
	public:
		Level03(Player* _player) : Scene(_player)
		{
			rectApron = { 265, 10, 200, 200 };
			textureBackground = ResourcesManager::Instance()->findTexture("level_3");
		}

		~Level03() = default;

		void OnEnter() override
		{
			player->SetPosition({ 284, 618 });
		}

	protected:
		void OnReach() override;
	};

	class SceneManager
	{
	private:
		static SceneManager* manager;
		Scene* currentScene = nullptr;
		std::unordered_map<std::string, Scene*> scenePool;

	public:
		static SceneManager* Instance()
		{
			if (!manager)
				manager = new SceneManager();
			return manager;
		}

		void Add(const std::string& _id, Scene* _scene)
		{
			scenePool[_id] = _scene;
		}

		void SwitchTo(const std::string& _id)
		{
			currentScene = scenePool[_id];

			if (currentScene) 
				currentScene->OnEnter();
		}

		void OnInput(const SDL_Event* _event)
		{
			if (!currentScene) return;

			currentScene->OnInput(_event);
		}

		void OnUpdate(float _delta)
		{
			if (!currentScene) return;

			currentScene->OnUpdate(_delta);
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			if (!currentScene) return;

			currentScene->OnRender(_renderer);
		}

	private:
		SceneManager() = default;
		~SceneManager() = default;
	};
}

class SingletonPattern : public Example
{
private:
	_SingletonPattern::Player player;
	SDL_Texture* textureTarget = nullptr;

public:
	SingletonPattern(SDL_Renderer*);
	~SingletonPattern();

	void OnInput(const SDL_Event*) override;
	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
