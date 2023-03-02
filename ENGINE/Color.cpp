#include "Color.hh"

Color::Color(){}

Color::Color(int r, int g, int b) : r(r), g(g), b(b){}

Color::Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a){}

Color::Color(uint32_t color){
    r = color & 0xFF;
    g = (color >> 8) & 0xFF;
    b = (color >> 16) & 0xFF;
    a = (color >> 24) & 0xFF;

}


Color Color::Lerp(Color color_1, Color color_2, float t){

    float r = (1.0f - t) * color_1.r + t * color_2.r;
    float g = (1.0f - t) * color_1.g + t * color_2.g;
    float b = (1.0f - t) * color_1.b + t * color_2.b;
    float a = (1.0f - t) * color_1.a + t * color_2.a;

    return Color(r, g, b, a);

}

Color Color::Red(){
    return Color(255,0,0);
}

Color Color::Green(){
    return Color(0,255,0);
}

Color Color::Blue(){
    return Color(0,0,255);
}

Color Color::Yellow(){
    return Color(255,255,0);
}

Color Color::White(){
    return Color(255,255,255);
}

Color Color::Black(){
    return Color(0,0,0);
}