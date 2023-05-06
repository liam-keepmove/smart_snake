#include"test.hpp"

int func(){
    test t1;
    auto a=&t1.var;
    return *a+t1.var2;
}
