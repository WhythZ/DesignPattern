#pragma once

#include "Builder.hpp"

//为了生产特定产品的具体Builder，是对抽象Builder的一种实现
class ConcreteBuilderA :public Builder
{
public:
    //
    void ConstructPart1();
    void ConstructPart2();
    void ConstructPart3();
};