#ifndef _MEDIATOR_H_
#define _MEDIATOR_H_

#include "Example.h"
#include "Animation.h"

namespace _MediatorPattern
{
	class Colleague;

	class Mediator
	{
	public:
		virtual ~Mediator() = default;
		virtual void Send(const std::string&, Colleague*) = 0;
	};

	class Colleague
	{
	protected:
		Mediator* mediator;

	public:
		Colleague(Mediator* _mediator) : mediator(_mediator) {}
		virtual ~Colleague() = default;

		virtual void OnUpdate(float) = 0;
		virtual void Receive(const std::string&) = 0;
	};

	class ChatRoom : public Mediator
	{
	private:
		std::vector<Colleague*> colleagues;

	public:
		void AddColleague(Colleague* _colleague)
		{
			colleagues.push_back(_colleague);
		}

		void Send(const std::string& _message, Colleague* _sender) override
		{
			for (Colleague* colleague : colleagues)
			{
				if (colleague != _sender)
					colleague->Receive(_message);
			}
		}
	};

	class User : public Colleague
	{
	private:
		int id = 0;
		Atlas atlas;
		Animation animation;
		std::string strChatBuffer;
		std::string strInputBuffer;

	public:
		User(Mediator* _mediator, const char* _atlasPath)
			: Colleague(_mediator)
		{
			static int nextID = 0;
			id = nextID; nextID++;

			atlas.Load(_atlasPath, 6);
			animation.SetLoop(true);
			animation.SetInterval(0.1f);
			animation.AddFrame(&atlas);
		}
		~User() = default;

		void OnUpdate(float) override;

		void Receive(const std::string& _message) override
		{
			strChatBuffer.append("[RECEIVE]: " + _message + "\n");
		}

	private:
		void Send(const std::string& _message)
		{
			mediator->Send(_message, this);
		}
	};
}

class MediatorPattern : public Example
{
private:
	_MediatorPattern::ChatRoom chatRoom;
	_MediatorPattern::Colleague* user01 = nullptr;
	_MediatorPattern::Colleague* user02 = nullptr;
	_MediatorPattern::Colleague* user03 = nullptr;
	_MediatorPattern::Colleague* user04 = nullptr;

public:
	MediatorPattern();
	~MediatorPattern();

	void OnUpdate(float) override;
};

#endif
