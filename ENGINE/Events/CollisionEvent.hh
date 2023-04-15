#ifndef COLLISIONEVENT_H_
#define COLLISIONEVENT_H_

struct CollisionEvent {

    entt::entity entA;
    entt::entity entB;
    float time_of_collision_;
    entt::registry* world;

    
    CollisionEvent(entt::entity entA, entt::entity entB, float time_of_collision, entt::registry& world) :
        entA(entA), entB(entB), time_of_collision_(time_of_collision), world(&world) {}



};

#endif // __COLLISIONEVENT_H___