#ifndef _FACADE_H_
#define _FACADE_H_

#include <string>

#include "Example.h"

class FacadePattern : public Example
{
private:
	std::string strText = u8"���Framework/Application.cpp�еĴ���ʵ��";

public:
	FacadePattern() = default;
	~FacadePattern() = default;

	void OnUpdate(float) override;
};

#endif
