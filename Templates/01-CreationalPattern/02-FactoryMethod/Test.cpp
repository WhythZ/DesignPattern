#include "ConcreteFactory.hpp"

int main()
{
    ConcreteFactoryA fa;
    ConcreteFactoryB fb;
    fa.CreateProduct()->Use();
    fb.CreateProduct()->Use();
}