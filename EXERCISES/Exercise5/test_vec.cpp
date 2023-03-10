#include "Vec2.hh"
#include <iostream>

int main(int argc, char *args[]){
    Vec2 v1(3,4);
    Vec2 v2(-1,7);

    std::cout << "v1 + v2 = " << v1 + v2<< std::endl;
    std::cout << "v1 . v2 = " << v1.Dot(v2)<< std::endl;
    std::cout << "v1 magnitude = = " << v1.Magnitude()<< std::endl;
    std::cout << "v1 magnitude squared = " << v1.MagnitudeSquared()<< std::endl;
    std::cout << "v1 unit vector = " << v1.UnitVec()<< std::endl;
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v1 normalized = " << v1.Normalize()<< std::endl;
    std::cout << "v1 = " << v1 << std::endl;

    return 0;
}