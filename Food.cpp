#include"Food.hpp"
#include"Tools.hpp"
#include<cstdlib>
#include<cassert>

wchar_t Food::getRandomIcon(){
    wchar_t icon=iconSet[rand()%iconSet.size()];
    return icon;
}

Food::Food(const RectMap& map,const Snake& snake){
    if(map.getSpace()-snake.getLen() > 0){  //map内有空间存放食物
        this->icon=Food::getRandomIcon();
        while(true){  //穷举一个没和蛇碰撞,没出界的食物出来.
            this->point=Tools::getRandPointInArea(map.rows,map.cols,map.origin.getY(),map.origin.getX());
            if(!Tools::JudgmentOfCollision(std::vector<Point>(snake.pointList.begin(),snake.pointList.end()),{this->point}))
                break;
        }
    }else{
        throw std::string("map内无空间存储食物.");
    }
}


Food::Food(Point point){
    Food(point,getRandomIcon());
}

Food::Food(Point point,wchar_t icon):icon(icon){
    if(point.getX()<0 || point.getY()<0){
        throw std::string("食物位置不能小于0.");
    }else
        this->point=point;
}

void Food::printToWindow(WINDOW* scr){
    assert(scr!=nullptr);
    mvwaddnwstr(scr,point.getY(),point.getX()*2,&icon,1);
}
