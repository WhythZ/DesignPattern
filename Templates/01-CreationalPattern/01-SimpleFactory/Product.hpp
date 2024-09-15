#pragma once

#include <iostream>

//产品的抽象类
class Product
{
public:
    virtual ~Product() = 0;
    virtual void Use() = 0;
};

//纯虚析构也需要实现
Product::~Product()
{
    delete this;
}