#include "ConcreteFactory.hpp"

int main()
{
    //测试创建品牌1（产品族1）的不同产品并使用
    ConcreteFactory1 cf1;
    cf1.CreateProductA()->Use();
    //Use Product A Of Brand 1
    cf1.CreateProductB()->Use();
    //Use Product B Of Brand 1

    //测试创建品牌2（产品族2）的不同产品并使用
    ConcreteFactory2 cf2;
    cf2.CreateProductA()->Use();
    //Use Product A Of Brand 2
    cf2.CreateProductB()->Use();
    //Use Product B Of Brand 2
}