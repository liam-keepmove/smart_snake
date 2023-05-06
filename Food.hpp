#pragma once

#include"Point.hpp"
#include"RectMap.hpp"
#include"Snake.hpp"
#include<curses.h>
#include<array>
using std::array;

class Food{ 
private:
    static constexpr array<wchar_t,27> iconSet{L'🐏',L'🐸',L'🐷',L'🐔',L'🐟',L'🦢',L'🍕',L'🍔',L'🍞',L'🧀',L'🥟',L'🥣',L'🍵',L'🥛',L'🍇',L'🍉',L'🍋',L'🍊',L'🍌',L'🍎',L'🍓',L'🌽',L'🍏',L'🥕',L'🥑',L'🥦',L'🥔'};
public:
    Point point;

    wchar_t icon;

    static wchar_t getRandomIcon();

    Food(const RectMap& map,const Snake& snake);

    Food(Point point);

    Food(Point point,wchar_t icon);

    void printToWindow(WINDOW* scr=stdscr);
};
