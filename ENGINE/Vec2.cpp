#include "Vec2.hh"
#include <math.h>
#include <iostream>
#include <cmath>

using namespace std;

Vec2::Vec2() : x(0.0), y(0.0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}


void Vec2::SetVec(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vec2::Add(const Vec2 &v)
{
    x += v.x;
    y += v.y;
}
void Vec2::Sub(const Vec2 &v)
{
    x -= v.x;
    y -= v.y;
}
void Vec2::Scale(const float n)
{
    x *= n;
    y *= n;
}

void Vec2::Scale(const Vec2 &v)
{
    x *= v.x;
    y *= v.y;
}

Vec2 Vec2::Rotate(const float angle) const
{
	float rads = (angle * M_PI) / 180; // deg to rad
    return Vec2(x * cosf(rads) - y * sinf(rads),
    x * cosf(rads) + y * sinf(rads) );
}

float Vec2::Magnitude() const{

    return sqrtf(x*x + y*y);

}
float Vec2::MagnitudeSquared() const{
    return (x*x + y*y);

}
float Vec2::Angle(){
    //angulo vector respecto eje horizontal
    return atan2f(y,x);// * 180.0 / M_PI;
}

float Vec2::AngleBetween(const Vec2& v){
    //angulo entre 2 vec
    return atan2(v.y - y, v.x - x) * 180.0 / M_PI;
}

Vec2 Vec2::UnitVec() const{

    return Vec2( x/Magnitude(),  y/Magnitude());

}

Vec2& Vec2::Normalize(){

    float a = x;
    float b = y;

    a /=Magnitude();
    b /= Magnitude();

    x = a;
    y = b;

    return *this;
}

Vec2 Vec2::Normal() const{
    // vector perpendicular
    return Vec2(-x,y);

}

float Vec2::Dot(const Vec2& v) const{
    float a = this->x;
    float b = this->y;
    return (a * v.x + b * v.y);

}
float Vec2::Cross(const Vec2& v) const{
    return (x * v.x - y * v.y);

}

Vec2 Vec2::FromModuleAngle(float module, float angle) {

        return Vec2(module * cos(angle), module * sin(angle));
        // returns cartesian coords given the module and the angle
}


// OPERADORES

Vec2& Vec2::operator= (const Vec2& v){
    x = v.x;
    y = v.y;
    return *this;
}

bool Vec2::operator==(const Vec2& v) const{
    if (x == v.x && y == v.y)
        return true;
    else
        return false;
}

bool Vec2::operator!=(const Vec2& v) const{
    if (x == v.x && y == v.y)
        return false;
    else
        return true;
}

Vec2& Vec2::operator += (const Vec2& v){
    x += v.x;
    y += v.y;
    return *this;

}
Vec2& Vec2::operator -= (const Vec2& v){
    x -= v.x;
    y -= v.y;
    return *this;

}
Vec2& Vec2::operator *= (const float n){
    x *= n;
    y *= n;
    return *this;

}
Vec2& Vec2::operator /= (const float n){
    x /= n;
    y /= n;
    return *this;

}

Vec2 Vec2::Perpendicular() const {
    return Vec2(-y, x);
}





