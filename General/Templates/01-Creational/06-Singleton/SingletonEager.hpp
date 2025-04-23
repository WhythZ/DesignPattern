#ifndef _SINGLETON_EAGER_HPP_
#define _SINGLETON_EAGER_HPP_

// template <typename T>
// class Manager
// {
// protected:
// 	static T* manager;
//
// public:
//     static T* GetInstance();
//
// protected:
//     Manager() = default;
// 	~Manager() = default;
// 	Manager(const Manager&) = delete;
// 	Manager& operator=(const Manager&) = delete;
// };
//
// //在程序启动时就初始化，这是饿汉式实现
// template <typename T>
// T* Manager<T>::manager = new T();
//
// template <typename T>
// T* Manager<T>::GetInstance()
// {
//     //直接返回在程序刚开始时就初始化好的manager
//     return manager;
// }

//C++11规定局部静态变量的初始化是线程安全的，因此以下方式既实现了饿汉式的特性，又保证了线程安全
template <typename T>
class Manager
{
public:
	static T* GetInstance();

protected:
    Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
};

template <typename T>
T* Manager<T>::GetInstance()
{
    //创建局部静态变量，并返回其引用
    static T manager;
    return &manager;
}

#endif