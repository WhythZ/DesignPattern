#ifndef _GAME_MANAGER_HPP_
#define _GAME_MANAGER_HPP_

#include <iostream>
//采用饿汉式实现
#include "SingletonEager.hpp"

//游戏主管理器
class GameManager : public Manager<GameManager>
{
	//授予Manager基类的GetInstance函数权限以调用GameManager类的构造函数
	friend class Manager<GameManager>;

public:
	int Run();

protected:
	GameManager() = default;
	~GameManager() = default;
};

int GameManager::Run()
{
	std::cout << "GamaManager Run Success\n";
	return 0;
}

#endif