#pragma once

#include "Product.hpp"

//所有的A产品都属于同一种类（产品等级结构），但其后面的数字代表其属于不同品牌（产品族）
class ConcreteProductA1 : public Product
{
public:
    ~ConcreteProductA1();
    void Use();
};

class ConcreteProductA2 : public Product
{
public:
    ~ConcreteProductA2();
    void Use();
};

ConcreteProductA1::~ConcreteProductA1() {}

void ConcreteProductA1::Use()
{
    std::cout << "Use Product A Of Brand 1\n";
}

ConcreteProductA2::~ConcreteProductA2() {}

void ConcreteProductA2::Use()
{
    std::cout << "Use Product A Of Brand 2\n";
}
