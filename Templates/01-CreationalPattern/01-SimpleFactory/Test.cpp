#include "SimpleFactory.hpp"

int main()
{
    SimpleFactory factory;
    factory.CreatProduct(ProductType::A)->Use();
    factory.CreatProduct(ProductType::B)->Use();
}