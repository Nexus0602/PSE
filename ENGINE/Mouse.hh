#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "Vec2.hh"

struct Mouse{

    Vec2 pos;
    Vec2 prevPos;
    bool rightButtonPressed = false;
    bool leftButtonPressed = false;

    Mouse() = default;
    ~Mouse() = default;

    const Vec2& GetPosition() const {return pos;}
    const Vec2& GetPrevPosition() const {return prevPos;}
    void UpdatePosition(int x, int y);
} ;
#endif // __MOUSE_H__