#ifndef _CONCRETE_PRODUCT_HPP_
#define _CONCRETE_PRODUCT_HPP_

#include <iostream>
#include "Product.hpp"

//对产品抽象类的其中一种A实现
class ConcreteProductA :public Product
{
public:
    ~ConcreteProductA();

    void Use() override;
};

//对产品抽象类的其中一种B实现
class ConcreteProductB :public Product
{
public:
    ~ConcreteProductB();

    void Use() override;
};

ConcreteProductA::~ConcreteProductA() {}

void ConcreteProductA::Use()
{
    std::cout << "Use Product A\n";
}

ConcreteProductB::~ConcreteProductB() {}

void ConcreteProductB::Use()
{
    std::cout << "Use Product B\n";
}

#endif