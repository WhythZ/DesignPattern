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
		virtual void OnUpdate(float delta) = 0;
		virtual void OnRender(SDL_Renderer* renderer) = 0;

	};

	class AnimatedState : public State
	{
	public:
		AnimatedState(const char* atlas_temp, int num)
		{
			atlas.Load(atlas_temp, num);
			animation.AddFrame(&atlas);
			animation.SetInterval(0.1f);
			animation.SetLoop(true);
		}

		virtual void OnUpdate(float delta)
		{
			animation.SetPosition(position);
			animation.OnUpdate(delta);
		}

		virtual void OnRender(SDL_Renderer* renderer)
		{
			animation.OnRender(renderer);
		}

	protected:
		Atlas atlas;
		Vector2 position;
		Animation animation;

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
	public:
		Player() = default;
		~Player() = default;

		void OnUpdate(float delta)
		{
			if (!state) return;

			state->OnUpdate(delta);
		}

		void OnRender(SDL_Renderer* renderer)
		{
			if (!state) return;

			state->OnRender(renderer);
		}

		void set_state(State* state)
		{
			this->state = state;
		}

	private:
		State* state = nullptr;

	};

}

class StatePattern : public Example
{
public:
	StatePattern(SDL_Renderer* renderer);
	~StatePattern();

	void OnUpdate(float delta) override;
	void OnRender(SDL_Renderer* renderer) override;

private:
	int idx_state = 0;
	_StatePattern::Player player;
	const char* state_name_list[4];
	_StatePattern::State* state_list[4];
	SDL_Texture* texture_target = nullptr;

};

#endif
