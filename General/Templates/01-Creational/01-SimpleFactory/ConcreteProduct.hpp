#ifndef _CONCRETE_PRODUCT_HPP_
#define _CONCRETE_PRODUCT_HPP_

#include <iostream>
#include "Product.hpp"

//对产品抽象类的其中一种A实现
class ConcreteProductA :public Product
{
public:
    //当基类的析构是虚函数时，派生类析构自动成为虚析构，不必用virtual或override修饰
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