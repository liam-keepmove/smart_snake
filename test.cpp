#include<iostream>
#include<curses.h>
#include<unistd.h>

int main(){
    initscr();
    move(5,5);
    printw("input:");
    //cbreak();  禁用行缓冲
    //halfdelay(20);  禁用行缓冲并且最多阻塞(args/10)秒,args取值1~255
    //nodelay(stdscr,true);  禁用行缓冲,某窗口(args1)开启或关闭异步输入.
    halfdelay(20);
    noecho();
    //nocbreak();
    int ch=getch();
    while(ch!='q'){
        if(ch!=ERR){
            printw("%c|",ch);
        }else{
            printw("ERR|");
        }
        refresh();
        ch=getch();
    }
    getch();
    refresh();
    endwin();

}
