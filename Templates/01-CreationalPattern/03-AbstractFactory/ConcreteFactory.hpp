#ifndef _CONCRETE_FACTORY_HPP_
#define _CONCRETE_FACTORY_HPP_

#include "Factory.hpp"
#include "ConcreteProductA.hpp"
#include "ConcreteProductB.hpp"

//生产品牌1（产品族1）的所有不同种类（不同产品等级结构）的产品
class ConcreteFactory1 : public Factory
{
public:
    //生产品牌1的A产品ConcreteProductA1
    Product* CreateProductA() override;
    //生产品牌1的B产品ConcreteProductB1
    Product* CreateProductB() override;
};

//生产品牌2（产品族2）的所有不同种类（不同产品等级结构）的产品
class ConcreteFactory2 : public Factory
{
public:
    //生产品牌2的A产品ConcreteProductA2
    Product* CreateProductA() override;
    //生产品牌2的B产品ConcreteProductB2
    Product* CreateProductB() override;
};

Product* ConcreteFactory1::CreateProductA()
{
    return new ConcreteProductA1();
}

Product* ConcreteFactory1::CreateProductB()
{
    return new ConcreteProductB1();
}

Product* ConcreteFactory2::CreateProductA()
{
    return new ConcreteProductA2();
}

Product* ConcreteFactory2::CreateProductB()
{
    return new ConcreteProductB2();
}

#endif