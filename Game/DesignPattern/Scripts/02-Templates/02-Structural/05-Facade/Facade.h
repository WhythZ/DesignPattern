#ifndef _FACADE_H_
#define _FACADE_H_

#include <string>

#include "Example.h"

class FacadePattern : public Example
{
public:
	FacadePattern() = default;
	~FacadePattern() = default;

	void OnUpdate(float delta) override;

private:
	std::string str_text = u8"详见Framework/Application.cpp中的代码实现";

};

#endif
