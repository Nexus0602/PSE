#ifndef _VEC2_H__
#define _VEC2_H__

#include <iostream>

struct Vec2{
    float x;
    float y;


Vec2();
Vec2(float x, float y);
~Vec2() = default;

void SetVec(float x, float y);

void Add(const Vec2& v);
void Sub(const Vec2& v);
void Scale(const float n);
void Scale(const Vec2& v);
Vec2 Rotate(const float angle) const; 

float Magnitude() const; //modulo
float MagnitudeSquared() const;
float Angle();
float AngleBetween(const Vec2& v);

Vec2& Normalize();
Vec2 UnitVec() const;
Vec2 Normal() const;

float Dot(const Vec2& v) const;
float Cross(const Vec2& v) const;

static Vec2 Lerp(Vec2 a, Vec2 b, float t);

friend std::ostream& operator<<(std::ostream& os, const Vec2& v){
    os << "(" << v.x << ", " << v.y << ")"; 
    return os;
}

Vec2& operator = (const Vec2& v);
bool operator == (const Vec2& v) const;
bool operator != (const Vec2& v) const;

Vec2 operator + (const Vec2& v) const{
    return Vec2(x + v.x, y + v.y);
}
Vec2 operator - (const Vec2& v) const{
    return Vec2(x - v.x, y - v.y);
}
Vec2 operator * (const float n) const{
    return Vec2(x * n, y * n);
}
Vec2 operator / (const float n) const{    
    return Vec2(x / n, y / n);

}
Vec2 operator - (); //? convertir a negativo?? 

Vec2& operator += (const Vec2& v);
Vec2& operator -= (const Vec2& v);
Vec2& operator *= (const float n);
Vec2& operator /= (const float n);

};
#endif // _VEC2_H