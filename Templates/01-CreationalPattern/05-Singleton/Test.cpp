#include "GameManager.hpp"

int main()
{   
    //运行游戏主管理器内的主循环方法，并获取返回值
    //注意这里获取的实例是开辟在堆区的，但此处可以不用delete，系统会给你擦屁股（虽说最好处理一下，但是单例模式问题不大）
    return GameManager::GetInstance()->Run();
    //GamaManager Run Success
}