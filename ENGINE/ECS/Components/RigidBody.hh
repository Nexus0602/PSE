struct RigidBodyComponent{
//mass
float mass;
float invMass;
float I;
float invI;
float restitution = 0;

//Forces and torques
Vec2 sumForces;
float sumTorques;

Shape* shape;

RigidBodyComponent(int mass, CircleShape& shape){
this->shape= shape.Clone();
this->mass=mass;
if(mass != 0.0)
{
    this->invMass=1.0/mass;


}else{

    this->invMass=0.0;

}
I=shape.GetMomentOfInertia()*mass;
if(I != 0.0)
{

    this->invI=1.0/I;
}else{

    this->invI=0.0;
}

this->sumForces=Vec2(0,0);
this->sumTorques=0.0;
}

RigidBodyComponent(int mass, RectangleShape& shape){
this->shape= shape.Clone();
this->mass=mass;
if(mass != 0.0)
{
    this->invMass=1.0/mass;


}else{

    this->invMass=0.0;

}
I=shape.GetMomentOfInertia()*mass;
if(I != 0.0)
{

    this->invI=1.0/I;
}else{

    this->invI=0.0;
}

this->sumForces=Vec2(0,0);
this->sumTorques=0.0;
}


void AddForce(const Vec2& force){
    sumForces+=force;
}
void ClearForces(){

    sumForces=Vec2(0.0,0.0);
}
void AddTorque(float torque)
{
    sumTorques +=torque;
}

void ClearTorques()
{
    sumTorques=0.0;
}

bool IsStatic(){
    const float epsilon = 0.005f;
    return fabs(invMass - 0.0) < epsilon;
}

};

