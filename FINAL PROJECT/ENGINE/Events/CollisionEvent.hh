#ifndef COLLISIONEVENT_H_
#define COLLISIONEVENT_H_

struct CollisionEvent {

    entt::entity entA;
    entt::entity entB;
    entt::registry* world;

    
    CollisionEvent(entt::entity entA, entt::entity entB, entt::registry& world) :
        entA(entA), entB(entB), world(&world) {}



};

#endif // __COLLISIONEVENT_H___