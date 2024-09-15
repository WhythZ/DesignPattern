#pragma once

#include "Factory.hpp"
#include "ConcreteProductA.hpp"
#include "ConcreteProductB.hpp"

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