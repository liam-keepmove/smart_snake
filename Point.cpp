#include"Point.hpp"

Point::Point()=default;

Point::Point(int x,int y):x(x),y(y){};

int Point::getX()const{
    return x;
}

int Point::getY()const {
    return y;
}

void Point::setX(int x){
    this->x=x;
}
void Point::setY(int y){
    this->y=y;
}

bool Point::operator==(const Point& right)const{
    if(this->x==right.x && this->y==right.y){
        return true;
    }else{
        return false;
    }
}
