#ifndef _CONCRETE_BUILDER_A_HPP_
#define _CONCRETE_BUILDER_A_HPP_

#include "Builder.hpp"

//为了生产特定产品的具体Builder，是对抽象Builder的一种实现
class ConcreteBuilderA :public Builder
{
public:
    //需要实现父类中的所有纯虚函数，包括纯虚析构函数，否则此类仍为抽象类
    ~ConcreteBuilderA();

    //对各抽象制造步骤的具体实现
    void ConstructPart1() override;
    void ConstructPart2() override;
    void ConstructPart3() override;

    //返回最终产品
    Product* GetBuilding() override;
};

ConcreteBuilderA::~ConcreteBuilderA() {}

void ConcreteBuilderA::ConstructPart1()
{
    product.SetPart1("A Part1");
}

void ConcreteBuilderA::ConstructPart2()
{
    product.SetPart2("A Part2");
}

void ConcreteBuilderA::ConstructPart3()
{
    product.SetPart3("A Part3");
}

Product* ConcreteBuilderA::GetBuilding()
{
    //实际应用中要注意Product类的拷贝构造函数需要设计得安全（深拷贝）
    //因为返回的是一个开辟在堆区的产品，所以需要记得在使用完后清理内存
    return new Product(product);
}

#endif