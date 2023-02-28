#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "Vec2.hh"

struct Mouse{
    Vec2 <int> pos;
    Vec2 <int> prevPos;
    bool rightButtonPressed = false;
    bool leftButtonPressed = false;

    Mouse() = default;
    ~Mouse() = default;

    const Vec2<int>& GetPosition() const {return pos;}
    const Vec2<int>& GetPrevPosition() const {return prevPos;}
    void UpdatePosition(int x, int y);
};
#endif // __MOUSE_H__