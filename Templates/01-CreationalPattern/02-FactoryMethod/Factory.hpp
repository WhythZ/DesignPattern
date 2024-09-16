#pragma once

#include "Product.hpp"

//抽象的工厂类
class Factory
{
public:
    virtual Product* CreateProduct() = 0;
};