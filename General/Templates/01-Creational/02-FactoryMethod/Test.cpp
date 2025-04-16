#include "ConcreteFactory.hpp"

int main()
{
    ConcreteFactoryA fa;
    fa.CreateProduct()->Use();
    //Use Product A
    ConcreteFactoryB fb;
    fb.CreateProduct()->Use();
    //Use Product B
}