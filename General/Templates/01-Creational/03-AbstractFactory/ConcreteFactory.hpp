#ifndef _CONCRETE_FACTORY_HPP_
#define _CONCRETE_FACTORY_HPP_

#include "Factory.hpp"
#include "ConcreteProductA.hpp"
#include "ConcreteProductB.hpp"

//生产品牌1（产品族1）的所有不同种类（不同产品等级结构）的产品
class ConcreteFactory1 :public Factory
{
public:
    ~ConcreteFactory1();
    
    //生产品牌1的A产品ConcreteProductA1
    Product* CreateProductA() override;
    //生产品牌1的B产品ConcreteProductB1
    Product* CreateProductB() override;
};

//生产品牌2（产品族2）的所有不同种类（不同产品等级结构）的产品
class ConcreteFactory2 :public Factory
{
public:
    ~ConcreteFactory2();
    
    //生产品牌2的A产品ConcreteProductA2
    Product* CreateProductA() override;
    //生产品牌2的B产品ConcreteProductB2
    Product* CreateProductB() override;
};

ConcreteFactory1::~ConcreteFactory1() {}

Product* ConcreteFactory1::CreateProductA()
{
    Product* _product = new ConcreteProductA1();
    products.emplace_back(_product);
    return _product;
}

Product* ConcreteFactory1::CreateProductB()
{
    Product* _product = new ConcreteProductB1();
    products.emplace_back(_product);
    return _product;
}

ConcreteFactory2::~ConcreteFactory2() {}

Product* ConcreteFactory2::CreateProductA()
{
    Product* _product = new ConcreteProductA2();
    products.emplace_back(_product);
    return _product;
}

Product* ConcreteFactory2::CreateProductB()
{
    Product* _product = new ConcreteProductB2();
    products.emplace_back(_product);
    return _product;
}

#endif