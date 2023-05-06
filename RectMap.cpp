#include"RectMap.hpp"
#include<string>
#include<cassert>
using std::string;

RectMap::RectMap(int rows,int cols,int originY,int originX):
    rows(rows),cols(cols),
    origin(originX,originY),
    minX(originX+1),maxX(originX+cols-2),
    minY(originY+1),maxY(originY+rows-2){
        if(originY<0 || originX<0)
            throw string("地图源点不能小于0.");
        if(rows<=5 || cols<=5 )
            throw string("地图行数或列数不能小于等于5.");
}

bool RectMap::outOfBoundsJudgment(vector<Point> pointSet)const{
    for(const auto& point : pointSet){
        auto x=point.getX();
        auto y=point.getY();
        if(y<=origin.getY())  //超出上界
            return true;
        if(y>=origin.getY()+rows)  //超出下界
            return true;
        if(x<=origin.getX())  //超出左界
            return true;
        if(x>=origin.getX()+cols)  //超出右界
            return true;
    }
    return false;
}

int RectMap::getSpace()const{
    return (rows-2)*(cols-2);
}

void RectMap::printToWindow(WINDOW* scr)const{
    assert(scr!=nullptr);
    for(int r=0;r<rows;++r){
        move(origin.getY()+r,origin.getX()*2);
        if(r==0 || r==rows-1){  //打印上下界
            for(int c=0;c<cols;++c){
               waddnwstr(scr,&iconWall,1);
            }
            continue;
        }
        //打印左右界
        waddnwstr(scr,&iconWall,1);
        mvwaddnwstr(scr,r,origin.getX()*2+(cols-1)*2,&iconWall,1);
    }
}
