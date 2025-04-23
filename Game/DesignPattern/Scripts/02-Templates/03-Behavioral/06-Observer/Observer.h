#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <vector>

#include "Example.h"

namespace _ObserverPattern
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Update(int) = 0;
	};

	class Subject
	{
	protected:
		int state = 0;
		std::vector<Observer*> observerList;

	public:
		virtual ~Subject() = default;

		virtual void Attach(Observer* _observer)
		{
			observerList.push_back(_observer);
		}

		virtual void Notify()
		{
			for (Observer* _observer : observerList)
				_observer->Update(state);
		}
	};

	class ButtonClicked : public Subject
	{
	public:
		void Accumulate()
		{
			state++;
			Notify();
		}
	};

	class Button1ClickedObserver : public Observer
	{
	public:
		void Update(int) override;
	};

	class Button2ClickedObserver : public Observer
	{
	public:
		void Update(int) override;
	};

	struct Achievement
	{
		SDL_Texture* texture = nullptr;

		Achievement(SDL_Texture* _texture) : texture(_texture) {}
		~Achievement() = default;
	};
}

class ObserverPattern : public Example
{
private:
	_ObserverPattern::Button1ClickedObserver button01ClickedObserver;
	_ObserverPattern::Button2ClickedObserver button02ClickedObserver;
	_ObserverPattern::ButtonClicked button01ClickedSubject, button02ClickedSubject;

public:
	ObserverPattern();
	~ObserverPattern() = default;

	void OnUpdate(float) override;
};

#endif
