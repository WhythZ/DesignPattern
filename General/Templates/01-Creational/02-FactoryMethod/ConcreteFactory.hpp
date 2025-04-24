#ifndef _CONCRETE_FACTORY_HPP_
#define _CONCRETE_FACTORY_HPP_

#include "Factory.hpp"
#include "ConcreteProduct.hpp"

//通过不同的具体工厂，来返回不同的产品，所以仅如果新增了产品的话，仅需新实现一个对应的具体工厂即可
class ConcreteFactoryA :public Factory
{
public:
    ~ConcreteFactoryA();
    
    Product* CreateProduct() override;
};

class ConcreteFactoryB :public Factory
{
public:
    ~ConcreteFactoryB();
    
    Product* CreateProduct() override;
};

ConcreteFactoryA::~ConcreteFactoryA() {}

Product* ConcreteFactoryA::CreateProduct()
{
    Product* _product = new ConcreteProductA();
    products.emplace_back(_product);
    return _product;
}

ConcreteFactoryB::~ConcreteFactoryB() {}

Product* ConcreteFactoryB::CreateProduct()
{
    Product* _product = new ConcreteProductB();
    products.emplace_back(_product);
    return _product;
}

#endif