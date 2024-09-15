#pragma once

#include "Product.hpp"

//对产品抽象类的其中一种实现
class ConcreteProductB : public Product
{
public:
    ~ConcreteProductB();
    void Use();
};

ConcreteProductB::~ConcreteProductB() {}

void ConcreteProductB::Use()
{
    std::cout << "Use Product B\n";
}
