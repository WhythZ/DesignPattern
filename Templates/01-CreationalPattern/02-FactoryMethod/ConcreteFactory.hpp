#pragma once

#include "Factory.hpp"
#include "ConcreteProductA.hpp"
#include "ConcreteProductB.hpp"

//通过不同的具体工厂，来返回不同的产品，所以仅如果新增了产品的话，仅需新实现一个对应的具体工厂即可
class ConcreteFactoryA :public Factory
{
public:
    Product* CreateProduct();
};

class ConcreteFactoryB :public Factory
{
public:
    Product* CreateProduct();
};

Product* ConcreteFactoryA::CreateProduct()
{
    return new ConcreteProductA();
}

Product* ConcreteFactoryB::CreateProduct()
{
    return new ConcreteProductB();
}