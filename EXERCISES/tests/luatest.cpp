#include "Nexus.hh"
#include <iostream>


int nativeCppCubeFunction(int n){
    return (n*n*n);
}

void TestLua(){
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua["cube"] = nativeCppCubeFunction;
    lua.script_file("./../assets/scripts/functions-example.lua");

    double someVariableInsideCpp = lua["some_variable"];
    std::cout<<"The value of some_variable in C++ is " << someVariableInsideCpp << std::endl;

    sol::function functionFactorial = lua["factorial"];
    int functionResult = functionFactorial(5);
    std::cout<<"The Lua script calculated 5! as  " << functionResult << std::endl;
}

int main(int argc, char* argv[]){

    TestLua();
    return 0;


}