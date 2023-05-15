//#include "Vec2.hh"

struct KinematicComponent {
    Vec2 velocity;
    Vec2 acceleration;

    float angularVelocity;
    float angularAcceleration;

    KinematicComponent(Vec2 velocity = Vec2(0,0), Vec2 acceleration=Vec2(0,0), float angularVelocity = 0.0, float angularAcceleration = 0.0){
        this-> velocity = velocity;
        this->acceleration = acceleration;
        this->angularVelocity = angularVelocity;
        this->angularAcceleration = angularAcceleration;
        
    }

    
};


