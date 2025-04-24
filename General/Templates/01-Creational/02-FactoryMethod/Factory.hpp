#ifndef _FACTORY_HPP_
#define _FACTORY_HPP_

#include <vector>
#include "Product.hpp"

//抽象的工厂类
class Factory
{
protected:
    std::vector<Product*> products;

public:
    //销毁开辟在堆区的产品的虚析构函数
    virtual ~Factory();
    
    virtual Product* CreateProduct() = 0;
};

Factory::~Factory()
{
    for (Product* _product : products)
        delete _product;
}

#endif