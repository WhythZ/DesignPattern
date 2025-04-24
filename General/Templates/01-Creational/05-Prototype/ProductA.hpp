#ifndef _PRODUCT_A_HPP_
#define _PRODUCT_A_HPP_

#include <iostream>
#include "Prototype.hpp"

//可被复制的具体产品类
class ProductA :Prototype
{
private:
    std::string name = 0;                 //只需浅拷贝的属性
    int attr = 0;                         //需要深拷贝的属性

public:
    ProductA(std::string, int);
    ProductA(const ProductA&);            //实现深拷贝的拷贝构造函数
    ProductA& operator=(const ProductA&) = delete;
    ~ProductA();

    Prototype* Clone() const override;    //实现接口中的对象拷贝虚函数
    void ShowInfo() const override;       //实现接口中的信息显示虚函数
};

ProductA::ProductA(std::string _name, int _attr)
{
    name = _name;
    //开辟在堆区的成员，需深拷贝以及析构
    attr = new int(_attr);
}

ProductA::~ProductA()
{
    //销毁堆区成员
    delete attr;
}

#endif