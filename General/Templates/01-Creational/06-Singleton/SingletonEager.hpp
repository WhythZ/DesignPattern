#ifndef _SINGLETON_EAGER_HPP_
#define _SINGLETON_EAGER_HPP_

template <typename T>
class Manager
{
protected:
	static T* manager;

public:
    static T* GetInstance();

protected:
    Manager() = default;
	~Manager() = default;
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
};

//在程序启动时就初始化，这是饿汉式实现
template <typename T>
T* Manager<T>::manager = new T();

template <typename T>
T* Manager<T>::GetInstance()
{
    //直接返回在程序刚开始时就初始化好的manager
    return manager;
}

#endif