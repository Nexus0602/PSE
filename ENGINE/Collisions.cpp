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

    if (aIsPolygon && bIsCircle){
        return IsCollidingPolygonCircle(a,b,contact,world);
    }

    if (aIsCircle && bIsPolygon){
        return IsCollidingPolygonCircle(a,b,contact,world);
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

bool Collisions::IsCollidingPolygonCircle(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world) {


    bool aIsCircle = world.get<ColliderComponent>(a).shape->GetType()== CIRCLE;
    bool bIsCircle = world.get<ColliderComponent>(b).shape->GetType()== CIRCLE;
    bool aIsPolygon = world.get<ColliderComponent>(a).shape->GetType()== RECTANGLE;
    bool bIsPolygon = world.get<ColliderComponent>(b).shape->GetType()==RECTANGLE;

    const CircleShape* aCircleShape = (CircleShape*)world.get<ColliderComponent>(a).shape;

    const auto aTransform = world.get<TransformComponent>(a);
    const auto bTransform = world.get<TransformComponent>(b);

    if (aIsPolygon && bIsCircle){
        const CircleShape* bCircleShape = (CircleShape*)world.get<ColliderComponent>(b).shape;
        PolygonShape* aPolygonShape = (PolygonShape*)world.get<ColliderComponent>(a).shape;

        float cx = bTransform.position.x;
        float cy = bTransform.position.y;
        const float r = bCircleShape->radius;

        float rx1 = aPolygonShape->worldVertices[3].x;
        float ry1 = aPolygonShape->worldVertices[3].y;

        float rx2 = aPolygonShape->worldVertices[1].x;
        float ry2 = aPolygonShape->worldVertices[1].y;

        float dx = max(rx1 - cx, max(0.0f, cx - rx2)) ;
        float dy = max(ry1 - cy, max(0.0f, cy - ry2)) ;
        float distancia = sqrt(dx*dx+dy*dy);

        return distancia<= r;

    }

    if (aIsCircle && bIsPolygon){
        return IsCollidingPolygonCircle(a,b,contact,world);
    }

    // Calcular la separación mínima entre el círculo y el polígono

    return true;

    }




bool Collisions::IsCollidingPolygonPolygon(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world) {
    PolygonShape* aPolygonShape = (PolygonShape*)world.get<ColliderComponent>(a).shape;
    PolygonShape* bPolygonShape = (PolygonShape*)world.get<ColliderComponent>(b).shape;

    Vec2 aAxis, bAxis;
    Vec2 aPoint, bPoint;

    float abSeparation = aPolygonShape->FindMinSeparation(bPolygonShape,aAxis,aPoint);
    //std::cout<<abSeparation<<std::endl;
    if (abSeparation >= 0){
        return false;
    }
    
    float baSeparation = bPolygonShape->FindMinSeparation(aPolygonShape,bAxis,bPoint);
    //std::cout<<baSeparation<<std::endl;
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

    return true;
}

void Collisions::ResolvePenetration(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world) {
    auto rigidBodyA = world.get<ColliderComponent>(a);
    auto rigidBodyB = world.get<ColliderComponent>(b);
    auto& transformA = world.get<TransformComponent>(a);
    auto& transformB = world.get<TransformComponent>(b);

    if (rigidBodyA.IsStatic() && rigidBodyB.IsStatic()){
        
        return;
    }

    //std::cout<<"HOLA2"<<std::endl;
    float da = contact.depth / (rigidBodyA.invMass + rigidBodyB.invMass) * rigidBodyA.invMass;
    float db = contact.depth / (rigidBodyA.invMass + rigidBodyB.invMass)*rigidBodyB.invMass;
    
    transformA.position -= contact.normal * da;
    transformB.position += contact.normal * db;

}

void Collisions::ResolveCollision(entt::entity& a, entt::entity& b, Contact& contact, entt::registry& world) {
    ResolvePenetration(a,b,contact,world);

    auto const rigidBodyA = world.get<ColliderComponent>(a);
    auto const rigidBodyB = world.get<ColliderComponent>(b);
    auto& kinematicA = world.get<KinematicComponent>(a);
    auto& kinematicB = world.get<KinematicComponent>(b);

    float e = std::min(rigidBodyA.restitution, rigidBodyB.restitution);

    const Vec2 vrel = (kinematicA.velocity - kinematicB.velocity);

    float vrelDotNormal = vrel.Dot(contact.normal);

    const Vec2 impulseDirection = contact.normal;
    const float impulseMagnitude = -(1 + e)* vrelDotNormal / (rigidBodyA.invMass + rigidBodyB.invMass);

    Vec2 jn = impulseDirection * impulseMagnitude;
    
    kinematicA.velocity += jn * rigidBodyA.invMass;
    kinematicB.velocity -= jn * rigidBodyB.invMass;



}