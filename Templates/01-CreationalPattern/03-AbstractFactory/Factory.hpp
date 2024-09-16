#pragma once

#include 

//工厂的抽象类，下面的A、B均是不同产品等级结构（不同种类）的产品，但属于同一产品族（同一品牌）
class Factory
{
public:
    //生产该工厂所代表品牌的A产品
    Product* CreateProductA();
    //生产该工厂所代表品牌的B产品
    Product* CreateProductB();
};