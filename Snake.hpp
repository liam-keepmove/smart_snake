#pragma once 

#include"Tools.hpp"
#include"Point.hpp"
#include"RectMap.hpp"
#include<curses.h>
#include<list>
using std::list;

class Snake{
private:
    wchar_t iconHead=L'😀';
    wchar_t iconBody=L'🔘';
public:
    //蛇的生死状态值.
    bool isDead=false;

    //蛇的方向
    Tools::Direct direct=Tools::Direct::none;

    //加入节点时请确保不重复,第一个节点为头,其余为身子
    list<Point> pointList; 

    //给出map,在map空间内生成蛇
    Snake(const RectMap& map);

    //给出地图的行列数和源点,在这个空间内生成蛇
    Snake(int rows,int cols,int originY,int originX,int initLen=5);

    //获取蛇的头节点
    Point getHeadPoint()const;

    //获取蛇的长度
    int getLen()const;

    void printToWindow(WINDOW* scr=stdscr)const;
};
