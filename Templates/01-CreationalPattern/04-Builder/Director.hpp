#pragma once

#include <iostream>
#include "Builder.hpp"

class Director
{
private:
    //以指针的方式存储，Director根据设置的具体Builder的不同，会生产出不同的产品
    Builder* builder = nullptr;

public:
    //设置具体Builder
    void SetBuilder(Builder*);
    //获取产品
    Product* GetProduct();
};

void Director::SetBuilder(Builder* _builder)
{
    builder = _builder;
}

Product* Director::GetProduct()
{
    //在使用Director前，需要先设置具体Builder
    if (builder == nullptr)
        throw std::invalid_argument("ERROR: No Concrete Builder Available For Director");

    //按照顺序使用具体Builder进行零件的生产
    builder->ConstructPart1();
    builder->ConstructPart2();
    builder->ConstructPart3();

    //返回最终成品
    return builder->GetBuilding();
}