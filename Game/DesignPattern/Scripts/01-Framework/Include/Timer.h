#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>

class Timer
{
private:
	float passTime = 0;
	float waitTime = 0;
	bool paused = false;
	bool shotted = false;
	bool oneShot = false;
	std::function<void()> onTimeout;

public:
	Timer() = default;
	~Timer() = default;
	void SetWaitTime(float);
	void SetOneShot(bool);
	void SetOnTimeout(std::function<void()>);

	void OnUpdate(float);
	
	void Restart();
	void Pause();
	void Resume();
};

#endif