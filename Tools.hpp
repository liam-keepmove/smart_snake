#pragma once

#include"Point.hpp"
#include<string>
#include<vector>
using std::vector;

namespace Tools{
    struct Direct{
        constexpr static int up='w',down='s',left='a',right='d',none=-1;
        int direct=0;
        Direct(int direct);
        bool operator==(const int rvalue)const;
        bool operator==(const Direct& rvalue)const;
        operator int()const;
    };


    //随机获取一个矩形区域内的一个点,默认矩形有边界,边界点不能获取
    Point getRandPointInArea(int rows,int cols,int originY,int originX);

    //碰撞判断,碰撞返回true,没碰撞返回false
    bool JudgmentOfCollision(const vector<Point>& one,const vector<Point>& two);

    //获取随机数字,包含下界不包含上界,[lowerBound,upperBound)
    int range(int lowerBound,int upperBound);

};
