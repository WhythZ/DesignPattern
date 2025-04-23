#ifndef  _STATE_H_
#define _STATE_H_

#include "Example.h"
#include "Animation.h"

namespace _StatePattern
{
	class State
	{
	public:
		virtual ~State() = default;

		virtual void OnUpdate(float) = 0;
		virtual void OnRender(SDL_Renderer*) = 0;
	};

	class AnimatedState : public State
	{
	protected:
		Atlas atlas;
		Vector2 position;
		Animation animation;

	public:
		AnimatedState(const char* _atlasTemp, int _num)
		{
			atlas.Load(_atlasTemp, _num);
			animation.AddFrame(&atlas);
			animation.SetInterval(0.1f);
			animation.SetLoop(true);
		}

		virtual void OnUpdate(float _delta)
		{
			animation.SetPosition(position);
			animation.OnUpdate(_delta);
		}

		virtual void OnRender(SDL_Renderer* _renderer)
		{
			animation.OnRender(_renderer);
		}
	};

	class AttackState : public AnimatedState
	{
	public:
		AttackState() : AnimatedState("Role_Attack%d", 6) { position = { 360, 374 }; }
		~AttackState() = default;
	};

	class IdleState : public AnimatedState
	{
	public:
		IdleState() : AnimatedState("Role_Idle%d", 6) { position = { 360, 374 }; }
		~IdleState() = default;
	};

	class JumpState : public AnimatedState
	{
	public:
		JumpState() : AnimatedState("Role_Jump%d", 10) { position = { 360, 374 }; }
		~JumpState() = default;
	};

	class RunState : public AnimatedState
	{
	public:
		RunState() : AnimatedState("Role_Run%d", 8) { position = { 360, 374 }; }
		~RunState() = default;
	};

	class Player
	{
	private:
		State* state = nullptr;

	public:
		Player() = default;
		~Player() = default;

		void OnUpdate(float _delta)
		{
			if (!state) return;

			state->OnUpdate(_delta);
		}

		void OnRender(SDL_Renderer* _renderer)
		{
			if (!state) return;

			state->OnRender(_renderer);
		}

		void SetState(State* _state)
		{
			this->state = _state;
		}
	};

}

class StatePattern : public Example
{
private:
	int stateIdx = 0;
	_StatePattern::Player player;
	const char* stateNameList[4];
	_StatePattern::State* stateList[4];
	SDL_Texture* textureTarget = nullptr;

public:
	StatePattern(SDL_Renderer*);
	~StatePattern();

	void OnUpdate(float) override;
	void OnRender(SDL_Renderer*) override;
};

#endif
