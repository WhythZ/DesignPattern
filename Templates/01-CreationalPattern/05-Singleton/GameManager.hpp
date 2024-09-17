#ifndef _GAME_MANAGER_HPP_
#define _GAME_MANAGER_HPP_

//引入其它依赖库
// #include ...
#include <iostream>
//用于继承基类
#include "Manager.hpp"

//游戏主管理器
class GameManager : public Manager<GameManager>
{
	//授予Manager基类的GetInstance函数权限以调用GameManager类的构造函数
	friend class Manager<GameManager>;

private:
	//私有成员变量

public:
    //对外开放的接口函数
	int Run();

protected:
	//构造函数，构造了什么就要释放什么
	GameManager();
	
	//析构函数，析构的顺序应当与构造的顺序相反，因为构造的顺序暗含依赖的关系，被依赖项不该被先释放
	~GameManager();

private:
	//内部需要用到的函数实现
};

int GameManager::Run()
{
	std::cout << "GamaManager Run Success\n";
	return 0;
}

GameManager::GameManager()
{
    //...
}

GameManager::~GameManager()
{
    //...
}

#endif
