#pragma once 

#include"Point.hpp"
#include<curses.h>
#include<vector>
using std::vector;

class RectMap{
public:
    const Point origin;  //左上角的源点
    const int rows;
    const int cols;
    wchar_t iconWall=L'💩';
    const int minX,maxX;//不算边界的xy值
    const int minY,maxY;

    explicit RectMap(int rows=30,int cols=60,int originY=0,int originX=0);

    //获取除边界外的空间数量
    int getSpace()const;

    //出界判断,出界返回true,否则返回false
    bool outOfBoundsJudgment(vector<Point> pointSet)const;

    void printToWindow(WINDOW* scr=stdscr)const;
};
