#ifndef _PRODUCT_HPP_
#define _PRODUCT_HPP_

#include <iostream>
#include "Prototype.hpp"

//可被复制的具体产品类
class Product :public Prototype
{
private:
    std::string name = "";                //只需浅拷贝的属性
    int* attr = nullptr;                  //需要深拷贝的属性

public:
    Product(std::string, int);
    Product(const Product&);              //实现深拷贝的拷贝构造函数
    ~Product();

    Prototype* Clone() const override;    //实现接口中的对象拷贝虚函数
    void ShowInfo() const override;       //实现接口中的信息显示虚函数
};

Product::Product(std::string _name, int _val) :name(_name)
{
    //开辟在堆区的成员，需深拷贝以及析构
    attr = new int(_val);
}

Product::Product(const Product& _other) :name(_other.name)
{
    //深拷贝
    attr = new int(*_other.attr);
}

Product::~Product()
{
    //销毁堆区成员
    delete attr;
    attr = nullptr;
}

Prototype* Product::Clone() const
{
    //此处仅使用拷贝构造函数克隆自身
    return new Product(*this);
    //若有不同的拷贝需求，例如希望只拷贝部分属性值（而其它值使用初始值），则可在此函数内实现，而不是直接修改拷贝构造
}

void Product::ShowInfo() const
{
    std::cout << "[name=" << name << "], [*attr=" << *attr << "]\n";
}

#endif