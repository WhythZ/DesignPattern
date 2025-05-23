#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include <iostream>
#include <vector>
#include "Product.hpp"

//工厂的抽象类，下面的A、B均是不同产品等级结构（不同种类）的产品，但属于同一产品族（同一品牌）
class Factory
{
protected:
    std::vector<Product*> products;

public:
    ~Factory();

    //生产该工厂所代表品牌的A产品
    virtual Product* CreateProductA() = 0;
    //生产该工厂所代表品牌的B产品
    virtual Product* CreateProductB() = 0;
};

Factory::~Factory()
{
    for (Product* _product : products)
        delete _product;
}

#endif