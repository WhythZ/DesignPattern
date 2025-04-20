#ifndef _FACADE_H_
#define _FACADE_H_

#include "Example.h"

#include <string>

class FacadePattern : public Example
{
public:
	FacadePattern() = default;
	~FacadePattern() = default;

	void on_update(float delta) override;

private:
	std::string str_text = u8"详见Framework/Application.cpp中的代码实现";

};

#endif
