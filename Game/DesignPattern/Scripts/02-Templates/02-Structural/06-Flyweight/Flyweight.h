#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_

#include <string>

#include "Example.h"

class FlyweightPattern : public Example
{
private:
	std::string strText = u8"详见下列文件中的资源管线代码实现\n\n"
		u8"Framework/Atlas.h \nFramework/Animation.h\nFramework/ResourcesManager.cpp";

public:
	FlyweightPattern() = default;
	~FlyweightPattern() = default;

	void OnUpdate(float) override;
};

#endif
