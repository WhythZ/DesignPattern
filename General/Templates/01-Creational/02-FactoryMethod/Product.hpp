#ifndef _PRODUCT_HPP_
#define _PRODUCT_HPP_

//产品的抽象类
class Product
{
public:
    virtual ~Product() = 0;
    
    virtual void Use() = 0;
};

//纯虚析构也需实现
Product::~Product() {}

#endif