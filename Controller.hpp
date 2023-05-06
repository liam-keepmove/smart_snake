#pragma once

#include"RectMap.hpp"
#include"Snake.hpp"
#include"Food.hpp"

class Controller{
private:
    struct HotKey{
        constexpr static int stop=' ',start=' ',restart='r',quit='q',openAI='G';
        constexpr static int empty=ERR;
        int hotkey=0;
        HotKey(int hotkey);
        bool operator==(const int rvalue)const;
        bool operator==(const HotKey& rvalue)const;
    };

    RectMap& map;
    Snake& snake;
    Food& food;
    int moveHz=5; //每秒蛇移动的频率,也是界面刷新的频率,可以用来设定困难等级,频率快移动快
    int score=0;

public:
    Controller(RectMap& map,Snake& snake,Food& food);
    ~Controller();

    //移动和刷新线程
    void moveRefreshThread();

    //调度器
    void scheduler();

    //显示暂停窗口并等待开始
    void stop();

    //显示结算窗口,重开返回true,退出返回false,注意,死亡不一定意味着失败了,也有可能铺满了
    bool whetherToRestart();

    //移动并进行食物碰撞判断和死亡(出界或撞击蛇身)判断,若死亡则修改蛇状态,若吃食物则返回true,否则返回false
    bool snakeMove();

    //开启蛇AI
    void snakeAI();

};
