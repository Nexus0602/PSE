struct ColliderComponent {

    Shape* shape;
    bool renderCollider;
    bool isColliding;
    float mass;
    float invMass;
    float restitution = 1;


    ColliderComponent(CircleShape shape, bool renderCollider, float mass = 0.0){
        this->shape=shape.Clone();
        this->renderCollider=renderCollider;
        this->isColliding=false;
        this->mass=mass;
        if(mass != 0.0)
        {
            this->invMass=1.0/mass;


        }else{

            this->invMass=0.0;

        }
}

    ColliderComponent(RectangleShape shape, bool renderCollider, float mass = 0.0){
        this->shape=shape.Clone();
        this->renderCollider=renderCollider;
        this->isColliding=false;
        this->mass=mass;
        if(mass != 0.0)
        {
            this->invMass=1.0/mass;


        }else{

            this->invMass=0.0;

        }
    }

    bool IsStatic(){
    const float epsilon = 0.005f;
    return fabs(invMass - 0.0) < epsilon;
}
};