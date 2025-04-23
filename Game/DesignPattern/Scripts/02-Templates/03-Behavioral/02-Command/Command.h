#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "Example.h"
#include "Animation.h"

namespace _CommandPattern
{
	struct Map
	{
		enum class GridType
		{
			Goal,
			Accessible,
			Inaccessible
		};

		std::vector<std::vector<GridType>> grids;
	};

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute() = 0;
	};

	class Player
	{
	private:
		Map* map = nullptr;
		Timer replayTimer;
		bool isReplaying = false;
		bool isAchievedGoal = false;

		int cmdIdx = 0;
		std::vector<Command*> cmdList;

		Atlas atlas;
		Animation animation;
		SDL_Point mapGridIdx = { 0 };

	public:
		Player(Map* _map) : map(_map)
		{
			Reset();
		
			replayTimer.SetWaitTime(0.25f);
			replayTimer.SetOneShot(false);
			replayTimer.SetOnTimeout([&]()
				{
					if (isReplaying && cmdIdx < cmdList.size())
					{
						cmdList[cmdIdx]->Execute();
						cmdIdx++;
					}
				});

			atlas.Load("Warrior_Idle_%d", 6);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);
			animation.AddFrame(&atlas);
		}
		~Player()
		{
			for (Command* _cmd : cmdList)
				delete _cmd;
		}

		void OnInput(const SDL_Event* _event)
		{
			if (isReplaying) return;

			switch (_event->type)
			{
			case SDL_KEYDOWN:
				switch (_event->key.keysym.sym)
				{
				case SDLK_UP:		OnMove({ 0, -1 });		break;
				case SDLK_DOWN:		OnMove({ 0, 1 });		break;
				case SDLK_LEFT:		OnMove({ -1, 0 });		break;
				case SDLK_RIGHT:	OnMove({ 1, 0 });		break;
				default: break;
				}
				break;
			default: break;
			}
		}

		void OnUpdate(float _delta)
		{
			Vector2 _position =
			{
				mapGridIdx.x * 48.0f + 24.0f,
				mapGridIdx.y * 48.0f + 24.0f - 30.0f 
			};
			animation.SetPosition(_position);
			animation.OnUpdate(_delta);

			replayTimer.OnUpdate(_delta);
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			animation.OnRender(_renderer);
		}

		void OnMove(const SDL_Point&);

		void Reset();
		void Replay();

		bool CanReplay() const { return isAchievedGoal; }
	};

	class MoveCommand : public Command
	{
	private:
		Player* player = nullptr;
		SDL_Point direction = { 0 };

	public:
		MoveCommand(Player* _player, const SDL_Point& dir) 
			: player(_player), direction(dir) {}
		~MoveCommand() = default;

		void Execute() override
		{
			player->OnMove(direction);
		}
	};
}

class CommandPattern : public Example
{
private:
	_CommandPattern::Map map;
	SDL_Texture* textureTarget = nullptr;
	_CommandPattern::Player* player = nullptr;

public:
	CommandPattern(SDL_Renderer*);
	~CommandPattern();

	void OnInput(const SDL_Event*) override;
	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
