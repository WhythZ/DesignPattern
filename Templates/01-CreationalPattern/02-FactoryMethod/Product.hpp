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
    //产品都是通过new开辟到堆区实例化的（这需要在工厂的实现中被保证），故这里可直接delete
    delete this;
}