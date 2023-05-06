#include"Controller.hpp"
#include"Tools.hpp"
#include<iostream>
#include<curses.h>
#include<thread>
#include<chrono>
#include<functional>
using Tools::Direct;

Controller::HotKey::HotKey(int hotkey):hotkey(hotkey){
    if(hotkey!=stop || hotkey!=start || hotkey!=restart || hotkey!=quit ||
            hotkey!=openAI || hotkey!=empty)
        throw std::string("HotKey errror.");
}
bool Controller::HotKey::operator==(const int rvalue)const{
    return this->hotkey==rvalue;
}
bool Controller::HotKey::operator==(const HotKey& rvalue)const{
    return this->hotkey==rvalue.hotkey;
}

Controller::Controller(RectMap& map,Snake& snake,Food& food):map(map),snake(snake),food(food){
    //关闭回显,禁用行缓冲,默认使用stdscr
    setlocale(LC_ALL, "");
    initscr();
    srand(time(nullptr));
    noecho();
    cbreak();
    halfdelay(10/moveHz);
}

Controller::~Controller(){
    //开启回显,关闭异步输入
    echo();
    nocbreak();
    endwin();
}

void Controller::moveRefreshThread(){
    std::chrono::milliseconds moveCycle((long)(1.0/moveHz*1000)); //将频率转换为周期
    while(true){
        if(snake.isDead==true)
            return;  //蛇死亡则线程结束.
        if(snake.direct!=Direct::none){
            if(snakeMove()){ //增加分数后创建新的食物.
                score++;
                food=Food(map,snake);
            }
            snake.printToWindow();
            food.printToWindow();
            refresh();
        }
        std::this_thread::sleep_for(moveCycle);
    }
}

void Controller::scheduler(){
restart:
    snake.direct=Direct::none;
    std::thread moveRefresh(&Controller::moveRefreshThread,this);
    score=0;
    while(true){
        int in=getch();
        switch(in){
            case Direct::up:case Direct::down:case Direct::left:case Direct::right:
                //蛇不能直接转头哟~如果键入的方向和当前方向相反,则维持当前方向.
                if(snake.direct==Direct::up && in==Direct::down){}
                else if(snake.direct==Direct::down && in==Direct::up){}
                else if(snake.direct==Direct::left && in==Direct::right){}
                else if(snake.direct==Direct::right && in==Direct::left){}
                else snake.direct=in;
                break;
            case HotKey::stop:
                stop();
                break;
            case HotKey::openAI:
                snakeAI();
                break;
            default:
                break;
        }

        if(snake.isDead){
            if(whetherToRestart()){
                moveRefresh.join();  //必须等待线程结束,否则可能引发变量isDead的竞争
                snake=Snake(map.rows,map.cols,map.origin.getY(),map.origin.getX());
                food=Food(map,snake);
                goto restart;
            }else{
                break;  //调度器结束运作
            }
        }
        //每次输入产生的状态有:
        //移动
        //移动->死亡(出界or撞自己)->重开/退出  注意 哪怕是蛇铺满,赢了,也是先死亡进行结算的
        //暂停->继续/退出
        //打开AI
    }
}

//显示暂停窗口并等待开始
void Controller::stop(){
    snake.direct=Direct::none; //让蛇停下
    //TODO 显示暂停窗口
    int in=getch(); 
    while(in!=HotKey::start){
        in=getch(); 
    }
    //TODO 删除暂停窗口

}

//显示结算窗口,重开返回true,退出返回false,注意,死亡不一定意味着失败了,也有可能铺满了
bool Controller::whetherToRestart(){
    //TODO 显示结算窗口
    int in=getch();
    while(true){
        in=getch(); 
        if(in==HotKey::restart){
            return true;
        }else if(in==HotKey::quit){
            return false;
        }
    }
}

//移动并进行食物碰撞判断和死亡(出界或撞击蛇身)判断,若死亡则修改蛇状态,若吃食物则返回true.
bool Controller::snakeMove(){
    bool eat=false;
    if(snake.isDead || snake.direct==Direct::none)
        return false; 
    Direct currDirect=snake.direct;

    //蛇移动一步
    Point node=snake.getHeadPoint();
    if(currDirect==Direct::up){
        node.setY(node.getY()-1);
    }else if(currDirect==Direct::down){
        node.setY(node.getY()+1);
    }else if(currDirect==Direct::left){
        node.setX(node.getX()-1);
    }else if(currDirect==Direct::right){
        node.setX(node.getX()+1);
    }
    snake.pointList.push_front(node);
    node=snake.pointList.back();  //保留尾巴副本,吃到食物了还要加回尾巴
    snake.pointList.pop_back(); 

    if(map.outOfBoundsJudgment(vector<Point>(snake.pointList.begin(),snake.pointList.end()))){  //越界蛇死亡
        snake.isDead=true;
    }else if(Tools::JudgmentOfCollision({snake.getHeadPoint()},{++snake.pointList.begin(),snake.pointList.end()})){  //没越界但头节点和自身碰撞,非头节点不可能碰撞.
        snake.isDead=true;
    }else if(snake.getHeadPoint()==food.point){  //没越界且和食物碰撞,吃到食物了
        snake.pointList.push_front(node);  //加入尾巴 
        eat=true;
    }
    return eat;
}

void Controller::snakeAI(){
    //TODO AI
}


