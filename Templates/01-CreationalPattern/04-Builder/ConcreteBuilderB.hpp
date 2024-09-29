#ifndef _CONCRETE_BUILDER_B_HPP_
#define _CONCRETE_BUILDER_B_HPP_

#include "Builder.hpp"

//为了生产特定产品的具体Builder，是对抽象Builder的一种实现
class ConcreteBuilderB :public Builder
{
public:
    //需要实现父类中的所有纯虚函数，包括纯虚析构函数，否则此类仍为抽象类
    ~ConcreteBuilderB();

    //对各抽象制造步骤的具体实现
    void ConstructPart1();
    void ConstructPart2();
    void ConstructPart3();

    //返回最终产品
    Product* GetBuilding();
};

ConcreteBuilderB::~ConcreteBuilderB() {}

void ConcreteBuilderB::ConstructPart1()
{
    product.SetPart1("B Part1");
}

void ConcreteBuilderB::ConstructPart2()
{
    product.SetPart2("B Part2");
}

void ConcreteBuilderB::ConstructPart3()
{
    product.SetPart3("B Part3");
}

Product* ConcreteBuilderB::GetBuilding()
{
    //实际应用中要注意Product类的拷贝构造函数需要设计得安全（深拷贝）
    //因为返回的是一个开辟在堆区的产品，所以需要记得在使用完后清理内存
    return new Product(product);
}

#endif