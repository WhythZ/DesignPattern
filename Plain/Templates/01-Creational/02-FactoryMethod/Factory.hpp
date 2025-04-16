#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include "Product.hpp"

//抽象的工厂类
class Factory
{
public:
    virtual Product* CreateProduct() = 0;
};

#endif