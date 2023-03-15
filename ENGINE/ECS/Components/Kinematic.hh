#ifndef _KINEMATIC_H_
#define _KINEMATIC_H_

#include "Vec2.hh"

struct KinematicComponent {
    Vec2 velocity;
    Vec2 acceleration;

    KinematicComponent(Vec2 velocity, Vec2 acceleration){
        this-> velocity = velocity;
        this->acceleration = acceleration;
    }

    
};

#endif // _KINEMATIC_H_
