#include "Nexus.hh"

bool Collisions::IsColliding(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world) {
    bool aIsCircle = world.get<ColliderComponent>(a).shape->GetType()== CIRCLE;
    bool bIsCircle = world.get<ColliderComponent>(b).shape->GetType()== CIRCLE;
    bool aIsPolygon = world.get<ColliderComponent>(a).shape->GetType()== RECTANGLE;
    bool bIsPolygon = world.get<ColliderComponent>(b).shape->GetType()==RECTANGLE;

    if (aIsCircle && bIsCircle){
        return IsCollidingCircleCircle(a,b,contact,world);
    }

    if (aIsPolygon && bIsPolygon){
        return IsCollidingPolygonPolygon(a,b,contact,world);
    }

    return false;
}

bool Collisions::IsCollidingCircleCircle(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world) {
    const CircleShape* aCircleShape = (CircleShape*)world.get<ColliderComponent>(a).shape;
    const CircleShape* bCircleShape = (CircleShape*)world.get<ColliderComponent>(b).shape;

    const auto aTransform = world.get<TransformComponent>(a);
    const auto bTransform = world.get<TransformComponent>(b);

    const Vec2 ab= bTransform.position/50 - aTransform.position/50;
    const float radiusSum = aCircleShape->radius/50 + bCircleShape->radius/50;
    bool isColliding = ab.MagnitudeSquared() <= (radiusSum * radiusSum);

    if(!isColliding){
        return false;
    }

    contact.a = a;
    contact.b = b;
    contact.normal = ab;
    contact.normal.Normalize();
    contact.start = bTransform.position/50 - contact.normal * bCircleShape->radius/50;
    contact.end = aTransform.position/50 - contact.normal * aCircleShape->radius/50;
    contact.depth = (contact.end-contact.start).Magnitude();

    return true;

}


bool Collisions::IsCollidingPolygonPolygon(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world) {
    PolygonShape* aPolygonShape = (PolygonShape*)world.get<ColliderComponent>(a).shape;
    PolygonShape* bPolygonShape = (PolygonShape*)world.get<ColliderComponent>(b).shape;

    Vec2 aAxis, bAxis;
    Vec2 aPoint, bPoint;

    float abSeparation = aPolygonShape->FindMinSeparation(bPolygonShape,aAxis,aPoint);
    if (abSeparation >= 0){
        return false;
    }
    
    float baSeparation = bPolygonShape->FindMinSeparation(aPolygonShape,bAxis,bPoint);
    if (baSeparation >= 0){
        return false;
    }

    contact.a = a;
    contact.b = b;

    if (abSeparation>baSeparation){
        contact.depth = -abSeparation;
        contact.normal = aAxis.Normal().Normalize();
        contact.start = aPoint;
        contact.end = aPoint + contact.normal * contact.depth;
    }
    else {
        contact.depth = -baSeparation;
        contact.normal = bAxis.Normal().Normalize();
        contact.start = bPoint + contact.normal * contact.depth;
        contact.end = bPoint; 
    }

    auto aCollider = world.get<ColliderComponent>(a);
    aCollider.isColliding = true;

    return true;
}

