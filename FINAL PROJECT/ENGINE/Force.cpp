#include "Force.hh"

Vec2 Force::GenerateGravitationalVector(Vec2 positionA, Vec2 positionB, float massA, float massB, float G, float minDistance, float maxDistance){
    
    Vec2 d = (positionA - positionB);

    float distanceSquared = d.MagnitudeSquared();

    distanceSquared = std::clamp(distanceSquared, minDistance, maxDistance);

    Vec2 attractionDirection = d.UnitVec();

    float attractionMagnitude = G * (massA * massB) / distanceSquared;

    Vec2 attractionForce = attractionDirection * attractionMagnitude;

    return attractionForce;
}

Vec2 Force::GenerateDragVector(float k, Vec2 v){
    Vec2 dragForce = Vec2(0,0);

    if (v.MagnitudeSquared()>0){

        Vec2 dragDirection = v.UnitVec() * -1.0;
        float dragMagnitude = k * v.MagnitudeSquared();
        dragForce = dragDirection * dragMagnitude;
    }
    return dragForce;
}

Vec2 Force::GenerateFrictionVector(float k, Vec2 v)
{
    Vec2 frictionForce = Vec2(0,0);

    if (v.Magnitude() > 1)
    {
        Vec2 frictionDirection = v.UnitVec() * -1.0;

        float frictionMagnitude = k;

        frictionForce = frictionDirection * frictionMagnitude;

    }
    return frictionForce;
}
Vec2 Force::GenerateSpringVector(Vec2 position, Vec2 anchor, float restLength, float k)
{

    // -kx - bv
    Vec2 d = position - anchor;
    float displacement = d.Magnitude() - restLength;
    Vec2 springDirection = d.UnitVec();
    //float springMagnitude =(-k * displacement );
    float springMagnitude =(-k * displacement )/100;
    Vec2 springForce = springDirection * springMagnitude ;

    return springForce;
    
}


