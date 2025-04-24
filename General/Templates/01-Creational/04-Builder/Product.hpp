#ifndef _PRODUCT_HPP_
#define _PRODUCT_HPP_

#include <iostream>

//需要被制造的产品，依据制造细节的不同（差异由具体Builder实现），产出不同的产品
class Product
{
protected:
    std::string part1;
    std::string part2;
    std::string part3;

public:
    ~Product();
    
    void SetPart1(std::string);
    void SetPart2(std::string);
    void SetPart3(std::string);

    //用于测试
    void Use();
};

Product::~Product() {}

void Product::SetPart1(std::string _part)
{
    part1 = _part;
}

void Product::SetPart2(std::string _part)
{
    part2 = _part;
}

void Product::SetPart3(std::string _part)
{
    part3 = _part;
}

void Product::Use()
{
    std::cout << "Use Product: {[" << part1 << "], [" << part2 << "], [" << part3 << "]}\n";
}

#endif