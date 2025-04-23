#ifndef _CHAIN_OF_RESPONSIBILITY_H_
#define _CHAIN_OF_RESPONSIBILITY_H_

#include <imgui.h>

#include "Example.h"

namespace _ChainOfResponsibilityPattern
{
	class ClickHandler
	{
	protected:
		ClickHandler* next = nullptr;

	public:
		virtual ~ClickHandler() = default;

		virtual void Handle() = 0;
		virtual void OnUpdate() = 0;

		void SetNext(ClickHandler* _next)
		{
			next = _next;
		}
	};

	class ChildWindow : public ClickHandler
	{
	private:
		int id;
		ImVec2 size;
		ImVec4 color;
		ImVec2 offset;

	public:
		ChildWindow(int _id, const ImVec4& _color, const ImVec2& _size, const ImVec2& _offset)
			: id(_id), color(_color), size(_size), offset(_offset) { }
		~ChildWindow() = default;

		void Handle() override;
		void OnUpdate() override;
	};
}

class ChainOfResponsibilityPattern : public Example
{
private:
	_ChainOfResponsibilityPattern::ChildWindow window01, window02, window03;

public:
	ChainOfResponsibilityPattern();
	~ChainOfResponsibilityPattern() = default;

	void OnUpdate(float) override;
};

#endif
