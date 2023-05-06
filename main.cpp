#include"Snake.hpp"
#include"RectMap.hpp"
#include"Food.hpp"
#include"Controller.hpp"
#include <exception>
#include<iostream>

int main(){
    try{
        RectMap rectMap(15,15,0,0);
        Snake snake(15,15,0,0);
        Food food(rectMap,snake);
        Controller controller(rectMap,snake,food);
        controller.scheduler();
    }catch(const std::string& errStr){
        std::cout<<errStr<<std::endl;
    }catch(const std::exception& error){
        std::cout<<error.what()<<std::endl;
    }
}
