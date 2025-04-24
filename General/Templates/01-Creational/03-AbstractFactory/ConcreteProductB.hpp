#ifndef _CONCRETE_PRODUCT_B_HPP_
#define _CONCRETE_PRODUCT_B_HPP_

#include <iostream>
#include "Product.hpp"

//所有的B产品都属于同一种类（产品等级结构），但其后面的数字代表其属于不同品牌（产品族）
class ConcreteProductB1 : public Product
{
public:
    ~ConcreteProductB1() override;
    void Use() override;
};

class ConcreteProductB2 : public Product
{
public:
    ~ConcreteProductB2() override;
    void Use() override;
};

ConcreteProductB1::~ConcreteProductB1() {}

void ConcreteProductB1::Use()
{
    std::cout << "Use Product B Of Brand 1\n";
}

ConcreteProductB2::~ConcreteProductB2() {}

void ConcreteProductB2::Use()
{
    std::cout << "Use Product B Of Brand 2\n";
}

#endif