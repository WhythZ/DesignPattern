#ifndef _MANAGER_HPP_
#define _MANAGER_HPP_

//可继承单例Manager模板类实现
template <typename T>
class Manager
{
protected:
	static T* manager;                              //静态的唯一Manager类对象的指针，在外部初始化

public:
	static T* GetInstance();                        //静态的函数，用于获取Manager类的唯一实例指针

protected:
	Manager() = default;                            //保护构造函数，单例模式的类不应当能被在外部创建对象
	~Manager() = default;                           //保护析构函数
	Manager(const Manager&) = delete;               //拷贝构造函数的调用无效
	Manager& operator=(const Manager&) = delete;    //运算符=的重载的调用无效
};

//初始化静态成员变量（我们也可以将manager实例作为函数GetInstance的局部静态变量，效果一样）
template <typename T>
T* Manager<T>::manager = nullptr;

template <typename T>
T* Manager<T>::GetInstance()
{
	//若manager未被创建，则在堆区创建一个
	if (manager == nullptr)
	{
		manager = new T();
	}

	//这样我们就可以在外部通过Manager* xxxx = Manager::GetInstance();获取内部这个Manager对象的地址，而不是创建一个新的Manager
	return manager;
}

#endif
