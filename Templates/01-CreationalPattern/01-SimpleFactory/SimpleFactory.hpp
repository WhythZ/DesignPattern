#ifndef _SIMPLE_FACTORY_HPP_
#define _SIMPLE_FACTORY_HPP_

#include "ConcreteProductA.hpp"
#include "ConcreteProductB.hpp"

enum ProductType
{
    A,
    B
};

class SimpleFactory
{
public:
    //通过传入参数创建某个产品
    Product* CreatProduct(ProductType);
};

Product* SimpleFactory::CreatProduct(ProductType _idx)
{
    //枚举在被switch时会被强制转换为整型来判断
    switch (_idx)
    {
    case ProductType::A:
        return new ConcreteProductA();
        break;
    case ProductType::B:
        return new ConcreteProductB();
        break;
    default:
        return nullptr;
    }
}

#endif