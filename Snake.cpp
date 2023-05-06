#include"Snake.hpp"
#include"Tools.hpp"
#include<algorithm>
#include<cassert>
#include<string>
using std::string;
using Tools::range;

Snake::Snake(const RectMap& map){
    Snake(map.rows,map.cols,map.origin.getY(),map.origin.getX());
}

Snake::Snake(int rows,int cols,int originY,int originX,int initLen){
    if(initLen<=0)
        throw string("蛇的初始长度不能小于1.");
    if(originY<0 || originX<0)
        throw string("地图源点不能小于0.");
    if(rows<=1 || cols<=1)
        throw string("地图行数或列数不能小于等于1.");

    int minX=originX+1,maxX=originX+cols-2;
    int minY=originY+1,maxY=originY+rows-2;
    Point current;
    current.setX(range(minX,maxX+1));
    current.setY(range(minY,maxY+1));
    pointList.push_back(current);  //生成蛇头
    for(int i=1;i<initLen;){  //生成蛇身子,x和y只能同时动一个.
        int j=0;
        Point temp=current;
        if(int r=range(0,3);r==0){  //随机生成0 1 2,0:x向左,1:x不动,2:x向右
            j=current.getX()-1;
            if(j>=minX && j<=maxX)
                current.setX(j);
            else
                continue;
        }else if(r==2){
            j=current.getX()+1;
            if(j>=minX && j<=maxX)
                current.setX(j);
            else
                continue;
        }else{  //x不动,y就必须动
            r=range(0,2);  //生成0 1,0:y向左,1:y向右
            if(r==0){
                j=current.getY()-1;
                if(j>=minY && j<=maxY)
                    current.setY(j);
                else
                    continue;
            }else{
                j=current.getY()+1;
                if(j>=minY && j<=maxY)
                    current.setY(j);
                else
                    continue;
            }
        }
        if(find(pointList.begin(),pointList.end(),current)==pointList.end()){  //current的xy合理且和其他蛇身体无碰撞
            pointList.push_back(current);
            ++i;
        }else{  //有碰撞
            current=temp;
            continue;
        }
    }
}

//获取蛇的头节点
Point Snake::getHeadPoint()const{
    return pointList.front();
}

int Snake::getLen()const{
    return pointList.size();
}

void Snake::printToWindow(WINDOW* scr)const{
    assert(scr!=nullptr);
    mvwaddnwstr(scr,pointList.front().getY(),pointList.front().getX()*2,&iconHead,1);
    for(auto it=++pointList.begin();it!=pointList.end();++it){
        mvwaddnwstr(scr,(*it).getY(),(*it).getX()*2,&iconBody,1);
    }
}
