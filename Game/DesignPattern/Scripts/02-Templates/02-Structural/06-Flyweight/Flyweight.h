#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_

#include "Example.h"

#include <string>

class FlyweightPattern : public Example
{
public:
	FlyweightPattern() = default;
	~FlyweightPattern() = default;

	void OnUpdate(float delta) override;

private:
	std::string str_text = u8"详见下列文件中的资源管线代码实现：\n\n"
		u8"• Framework/Atlas.h \n• Framework/Animation.h\n• Framework/ResourcesManager.cpp";
};

#endif
