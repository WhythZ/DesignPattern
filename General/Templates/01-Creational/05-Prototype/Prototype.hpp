#ifndef _PROTOTYPE_HPP_
#define _PROTOTYPE_HPP_

//原型接口，所有需实现复制功能的产品类都应继承该接口，核心是该接口的复制方法
class Prototype
{
private:
    int id = 0;

public:
    virtual Prototype* Clone() const = 0;     //复制方法
    virtual Prototype* ShowID() const = 0;    //显示信息
};

#endif