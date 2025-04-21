#include "Timer.h"

void Timer::SetWaitTime(float val)
{
	waitTime = val;
}

void Timer::SetOneShot(bool flag)
{
	oneShot = flag;
}

void Timer::SetOnTimeout(std::function<void()> onTimeout)
{
	this->onTimeout = onTimeout;
}

void Timer::OnUpdate(float delta)
{
	if (paused) return;

	passTime += delta;
	if (passTime >= waitTime)
	{
		bool can_shot = (!oneShot || (oneShot && !shotted));
		shotted = true;
		if (can_shot && onTimeout)
			onTimeout();
		passTime -= waitTime;
	}
}

void Timer::Restart()
{
	passTime = 0;
	shotted = false;
}

void Timer::Pause()
{
	paused = true;
}

void Timer::Resume()
{
	paused = false;
}