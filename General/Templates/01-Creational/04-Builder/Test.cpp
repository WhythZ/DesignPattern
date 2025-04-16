#include "Director.hpp"
#include "ConcreteBuilderA.hpp"
#include "ConcreteBuilderB.hpp"

int main()
{
    //准备两个不同的具体Builder，由于Director接收的是指针类型Builder，故而使用指针
    ConcreteBuilderA* ba = new ConcreteBuilderA();
    ConcreteBuilderB* bb = new ConcreteBuilderB();

    //准备一个Director应对客户端的需求
    Director drt;

    //生产A加工型产品
    drt.SetBuilder(ba);
    Product* pa = drt.GetProduct();
    pa->Use();
    //Use Product: {[A Part1], [A Part2], [A Part3]}

    //生产B加工型产品
    drt.SetBuilder(bb);
    Product* pb = drt.GetProduct();
    pb->Use();
    //Use Product: {[B Part1], [B Part2], [B Part3]}

    //记得销毁new出来的内存防止泄露
    delete ba;
    delete bb;
    //具体Builder返回的产品指针是开辟在堆区的，所以要销毁
    delete pa;
    delete pb;
}