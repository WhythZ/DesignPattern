#include "Timer.h"

void Timer::SetWaitTime(float _val)
{
	waitTime = _val;
}

void Timer::SetOneShot(bool _flag)
{
	oneShot = _flag;
}

void Timer::SetOnTimeout(std::function<void()> _onTimeout)
{
	onTimeout = _onTimeout;
}

void Timer::OnUpdate(float _delta)
{
	if (paused) return;

	passTime += _delta;
	if (passTime >= waitTime)
	{
		bool _canShot = (!oneShot || (oneShot && !shotted));
		shotted = true;
		if (_canShot && onTimeout)
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