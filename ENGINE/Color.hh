#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdint.h>
#include <iostream>

struct Color{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;

    Color();
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    Color(uint32_t color);
    ~Color() = default; 

    uint32_t ToARGB8888();
    Color Darkened(float p);
    Color Lightened(float p);
    Color ApplyFactor(float p);
    static Color Lerp(Color color_1, Color color_2, float t);

    Color operator + (const Color& c) const;

    static Color Red();
    static Color Green();
    static Color Blue();
    static Color Yellow();
    static Color White();
    static Color Black();

    friend std::ostream& operator<<(std::ostream& os, const Color& c){
        os << c << std::endl; 
    return os;
    }
};

#endif // __COLOR_H__