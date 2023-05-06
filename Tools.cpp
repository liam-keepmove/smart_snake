#include"Tools.hpp"
#include<cstdlib>
#include<ctime>
#include<string>
using std::string;

Tools::Direct::Direct(int direct):direct(direct){
    if(direct!=up && direct!=down && direct!=left && direct!=right && direct!=none)
        throw string("Direct error.");
};
bool Tools::Direct::operator==(const int rvalue)const{
    return this->direct==rvalue;
}
bool Tools::Direct::operator==(const Direct& rvalue)const{
    return this->direct==rvalue.direct;
}
Tools::Direct::operator int()const{
    return this->direct;
}


Point Tools::getRandPointInArea(int rows,int cols,int originY,int originX){
    if(originY<0 || originX<0)
        throw string("地图源点不能小于0.");
    if(rows<=1 || cols<=1 )
        throw string("地图行数或列数不能小于等于1.");
    int minX=originX+1,maxX=originX+cols-2;
    int minY=originY+1,maxY=originY+rows-2;
    Point point(range(minX,maxX+1),range(minY,maxY+1));
    return point;
}

bool Tools::JudgmentOfCollision(const vector<Point>& one,const vector<Point>& two){
    for(const auto& point1 : one){
        for(const auto& point2 : two){ //碰撞返回true
            if(point1==point2)
                return true;
        }
    }
    return false;
}

int Tools::range(int lowerBound,int upperBound){
    if(lowerBound>=upperBound){
        throw string("lowerBound must low than upperBound");
    }
    return lowerBound+rand()%(upperBound-lowerBound);
}

