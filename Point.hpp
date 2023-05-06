#pragma once

class Point{
private:
    int x;
    int y;
public:
    int getX()const;
    int getY()const;
    void setX(int x);
    void setY(int y);
    Point();
    Point(int x,int y);
    bool operator==(const Point& right)const;
};
