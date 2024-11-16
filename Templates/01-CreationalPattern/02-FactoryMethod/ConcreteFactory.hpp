#ifndef _CONCRETE_FACTORY_HPP_
#define _CONCRETE_FACTORY_HPP_

#include "Factory.hpp"
#include "ConcreteProduct.hpp"

//通过不同的具体工厂，来返回不同的产品，所以仅如果新增了产品的话，仅需新实现一个对应的具体工厂即可
class ConcreteFactoryA :public Factory
{
public:
    Product* CreateProduct() override;
};

class ConcreteFactoryB :public Factory
{
public:
    Product* CreateProduct() override;
};

Product* ConcreteFactoryA::CreateProduct()
{
    return new ConcreteProductA();
}

Product* ConcreteFactoryB::CreateProduct()
{
    return new ConcreteProductB();
}

#endif