#ifndef _STRATEGY_H_
#define _STRATEGY_H_

#include "Example.h"
#include "Animation.h"

namespace _StrategyPattern
{
	class MoveStrategy
	{
	public:
		virtual ~MoveStrategy() = default;
		virtual bool need_stop(const Vector2&, const Vector2&) = 0;
		virtual Vector2 cal_direction(const Vector2&, const Vector2&) = 0;
	};

	class FollowStrategy : public MoveStrategy
	{
	public:
		bool need_stop(const Vector2& posTarget, const Vector2& posSelf) override
		{
			return (posTarget - posSelf).Length() <= 150.0f;
		}

		Vector2 cal_direction(const Vector2& posTarget, const Vector2& posSelf) override
		{
			return (posTarget - posSelf).Normalize();
		}
	};

	class StayAwayStrategy : public MoveStrategy
	{
	public:
		bool need_stop(const Vector2& posTarget, const Vector2& posSelf) override
		{
			return (posTarget - posSelf).Length() >= 250.0f;
		}

		Vector2 cal_direction(const Vector2& posTarget, const Vector2& posSelf) override
		{
			return (posSelf - posTarget).Normalize();
		}
	};

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
			atlas.Load("player_right_%d", 5);

			animation.AddFrame(&atlas);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);

			position = { 360, 360 };
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
			if (std::abs(direction.x) > 0.0001f) isFacingRight = direction.x > 0;
			position = position + direction * speed;

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

		const Vector2& get_position() const
		{
			return position;
		}
	};

	class Boar
	{
	private:
		Vector2 position;
		Player* player = nullptr;
		MoveStrategy* moveStrategy = nullptr;

		bool isFacingRight = true;
		Atlas atlasIdle, atlasRun;
		Animation animationIdle, animationRun;
		Animation* currentAnimation = nullptr;

	public:
		Boar(Player* player, Vector2 position)
		{
			this->player = player;
			this->position = position;

			atlasIdle.Load("Boar-Idle%d", 4);
			animationIdle.AddFrame(&atlasIdle);
			animationIdle.SetLoop(true);
			animationIdle.SetInterval(0.1f);

			atlasRun.Load("Boar-Run%d", 6);
			animationRun.AddFrame(&atlasRun);
			animationRun.SetLoop(true);
			animationRun.SetInterval(0.1f);

			currentAnimation = &animationIdle;
		}

		~Boar() = default;

		void OnUpdate(float delta)
		{
			if (moveStrategy->need_stop(player->get_position(), position))
				currentAnimation = &animationIdle;
			else
			{
				static const float speed = 1.0f;
				const Vector2 move_dir = moveStrategy->cal_direction(player->get_position(), position);
				if (std::abs(move_dir.x) > 0.0001f) isFacingRight = move_dir.x > 0;
				position = position + move_dir * speed;
				currentAnimation = &animationRun;
			}

			currentAnimation->OnUpdate(delta);
			currentAnimation->SetPosition(position);
			currentAnimation->SetFlip(isFacingRight ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE);
		}

		void OnRender(SDL_Renderer* renderer)
		{
			SDL_FRect rect = { position.x - 16, position.y + 20, 32, 20 };
			SDL_RenderCopyF(renderer, ResourcesManager::Instance()->findTexture("shadow_player"), nullptr, &rect);

			currentAnimation->OnRender(renderer);
		}

		void set_strategy(MoveStrategy* moveStrategy)
		{
			this->moveStrategy = moveStrategy;
		}
	};
}

class StrategyPattern : public Example
{
private:
	//玩家操控的对象
	_StrategyPattern::Player player;
	SDL_Texture* textureTarget = nullptr;
	//采取不同策略对待玩家的野猪们
	std::vector<_StrategyPattern::Boar*> boarList;

	//野猪们的不同策略
	bool isUsingFollowStrategy = true;
	_StrategyPattern::FollowStrategy followStrategy;
	_StrategyPattern::StayAwayStrategy stayAwayStrategy;

public:
	StrategyPattern(SDL_Renderer*);
	~StrategyPattern();

	void OnInput(const SDL_Event*) override;
	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
