#ifndef _CONCRETE_FACTORY_HPP_
#define _CONCRETE_FACTORY_HPP_

#include "ConcreteProductA.hpp"
#include "ConcreteProductB.hpp"

//生产品牌1（产品族1）的所有不同种类（不同产品等级结构）的产品
class ConcreteFactory1
{
public:
    //生产品牌1的A产品
    ConcreteProductA1* CreateProductA();
    //生产品牌1的B产品
    ConcreteProductB1* CreateProductB();
};

//生产品牌2（产品族2）的所有不同种类（不同产品等级结构）的产品
class ConcreteFactory2
{
public:
    //生产品牌2的A产品
    ConcreteProductA2* CreateProductA();
    //生产品牌2的B产品
    ConcreteProductB2* CreateProductB();
};

ConcreteProductA1* ConcreteFactory1::CreateProductA()
{
    return new ConcreteProductA1();
}

ConcreteProductB1* ConcreteFactory1::CreateProductB()
{
    return new ConcreteProductB1();
}

ConcreteProductA2* ConcreteFactory2::CreateProductA()
{
    return new ConcreteProductA2();
}

ConcreteProductB2* ConcreteFactory2::CreateProductB()
{
    return new ConcreteProductB2();
}

#endif