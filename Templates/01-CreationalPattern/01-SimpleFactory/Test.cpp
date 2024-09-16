#include "SimpleFactory.hpp"

int main()
{
    SimpleFactory factory;
    factory.CreatProduct(ProductType::A)->Use();
    //Use Product A
    factory.CreatProduct(ProductType::B)->Use();
    //Use Product B
}