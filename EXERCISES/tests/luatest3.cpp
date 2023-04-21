#include "Nexus.hh"
#include <iostream>


    void Test(){

    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.script_file("./../assets/scripts/myfirstscript.lua");

    int someVariableInsideCpp = lua["some_variable"];
    std::cout<<"The value of some_variable in C++ is " << someVariableInsideCpp << std::endl;

    sol::table config = lua["config"];
    int isFullScreen = config["resolution"]["fullscreen"];
    int width = config["resolution"]["width"];
    int height = config["resolution"]["height"];
    std::cout<<"We read the value fullscreen: " << isFullScreen << ", width: " << width << ", height: " << height << std::endl;

    }

int main(int argc, char* argv[]){

    Test();
    return 0;
}