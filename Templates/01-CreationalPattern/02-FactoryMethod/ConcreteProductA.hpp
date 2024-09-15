#pragma once

#include "Product.hpp"

//对产品抽象类的其中一种实现
class ConcreteProductA : public Product
{
public:
    ~ConcreteProductA();
    void Use();
};

ConcreteProductA::~ConcreteProductA() {}

void ConcreteProductA::Use()
{
    std::cout << "Use Product A\n";
}
