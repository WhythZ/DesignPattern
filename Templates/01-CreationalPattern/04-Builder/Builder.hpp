#ifndef _BUILDER_HPP_
#define _BUILDER_HPP_

#include "Product.hpp"

//抽象建造者类，用于被Director调用（传入不同的ConcreteBuilder来获取不同的产品）
class Builder
{
protected:
    //需要被生产出的产品
    Product product;
    
public:
    //纯虚析构函数
    virtual ~Builder() = 0;
    
    //生产完整产品所需要的中间步骤，其实生产的顺序可以依靠Director来调用，但是在Builder内合理排序有助于提升代码可读性
    virtual void ConstructPart1() = 0;
    virtual void ConstructPart2() = 0;
    virtual void ConstructPart3() = 0;
    
    //全部零件生产完成后返回完整产品
    virtual Product* GetBuilding() = 0;
};

//纯虚析构函数需要实现
Builder::~Builder() {}

#endif