#include "Product.hpp"

int main()
{
    Product* p1 = new Product("p1", 99);
    //注意此处接收p1克隆体的p2的类型为Prototype*而非Product*
    //这使得在拷贝p1的时候无需知晓p1的具体类型，统一用Prototype*原型接收即可，使得拷贝操作与具体产品类解耦
    Prototype* p2 = p1->Clone();

    p1->ShowInfo();
    //[name=p1], [*attr=99]
    p2->ShowInfo();
    //[name=p1], [*attr=99]
}