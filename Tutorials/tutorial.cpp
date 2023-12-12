//import llframe;
#define __LLFRAME_USE_MODULE__
#include "llframe.hpp"
#include <iostream>
#include <cstdint>
int main()
{
    llframe::Exception a ("aaa");
    std::cout<<a.what()<<std::endl;
}