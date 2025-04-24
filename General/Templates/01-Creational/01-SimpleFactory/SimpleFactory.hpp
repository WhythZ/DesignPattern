#ifndef _SIMPLE_FACTORY_HPP_
#define _SIMPLE_FACTORY_HPP_

#include <vector>
#include "ConcreteProduct.hpp"

enum ProductType { A, B };

class SimpleFactory
{
private:
    //存储创建的对象，析构时释放
    std::vector<Product*> products;

public:
    //释放开辟在堆区的对象
    ~SimpleFactory();
    
    //通过传入参数创建某个产品
    Product* CreatProduct(ProductType);
};

SimpleFactory::~SimpleFactory()
{
    for (Product* _product : products)
        delete _product;
}

Product* SimpleFactory::CreatProduct(ProductType _idx)
{
    Product* _product;

    //枚举在被switch时会被强制转换为整型来判断
    switch (_idx)
    {
    case ProductType::A:
        _product = new ConcreteProductA();
        break;
    case ProductType::B:
        _product = new ConcreteProductB();
        break;
    default:
        _product = nullptr;
    }

    //将产品维护到列表内，然后再返回
    products.emplace_back(_product);
    return _product;
}

#endif