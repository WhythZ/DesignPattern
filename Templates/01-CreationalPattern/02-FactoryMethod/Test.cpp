#include "ConcreteFactory.hpp"

int main()
{
    ConcreteFactoryA fa;
    fa.CreateProduct()->Use();
    ConcreteFactoryB fb;
    fb.CreateProduct()->Use();
}