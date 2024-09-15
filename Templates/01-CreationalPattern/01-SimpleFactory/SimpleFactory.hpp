#pragma once

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
    Product* CreatProduct(ProductType);  //通过传入参数创建某个产品
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