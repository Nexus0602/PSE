//#include "Vec2.hh"
//#include "Color.hh"

struct ParticleComponent {

    float mass;
    float invMass;
    int radius;
    Color color;
    Vec2 sumForces;

    ParticleComponent(float mass = 1.0, int radius = 1, Color color = Color::White()){
        this->mass = mass;
        if (mass != 0.0){
            this->invMass = 1.0/mass;
        }
        else{
            this->invMass = 0.0;
        }

        this->radius = radius;
        this->color = color;
        this->sumForces = Vec2(0,0);

    }

    void AddForce(const Vec2& force){
        sumForces += force;
    }

    void ClearForces(){
        sumForces = Vec2(0.0,0.0);
    }

};