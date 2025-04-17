#ifndef _FLYWEIGHT_H_
#define _FLYWEIGHT_H_

#include "Example.h"

#include <string>

class FlyweightPattern : public Example
{
public:
	FlyweightPattern() = default;
	~FlyweightPattern() = default;

	void on_update(float delta) override;

private:
	std::string str_text = u8"详见下列文件中的资源管线代码实现：\n\n"
		u8"• framework/Atlas.h \n• framework/Animation.h\n• framework/resources_manager.cpp";

};

#endif // !_FLYWEIGHT_H_
