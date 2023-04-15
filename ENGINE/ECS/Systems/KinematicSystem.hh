
class KinematicSystem{
    public:

    void Update(const double dt, entt::registry& world){
        int width = 700;
        auto view = world.view<TransformComponent, KinematicComponent>();
        for(auto entity:view){
            auto& transform = view.get<TransformComponent>(entity);
            auto& kinematic = view.get<KinematicComponent>(entity);

            //Semi-implicit euler --> linear motion
            kinematic.velocity += kinematic.acceleration * dt;
            transform.position += kinematic.velocity * dt;

            if (transform.position.x + 50<= 0 && kinematic.velocity.x < 0)
                transform.position.x  = width + 50;

            if (transform.position.x - 50 >= width && kinematic.velocity.x > 0)
                transform.position.x  = -50;
                
        
            // Angular motion

            kinematic.angularVelocity += kinematic.angularAcceleration *dt;
            transform.rotation += kinematic.angularVelocity * dt;

            if (world.all_of<ColliderComponent>(entity)){
                Shape* shape;
                shape = world.get<ColliderComponent>(entity).shape;
                if (shape ->GetType() == RECTANGLE || shape ->GetType() == POLYGON){
                    PolygonShape* polygonShape = (PolygonShape*) world.get<ColliderComponent>(entity).shape;
                    polygonShape->UpdatePositions(transform.position);
                }
            }

            if (world.all_of<RigidBodyComponent>(entity)){
                Shape* shape;
                shape = world.get<RigidBodyComponent>(entity).shape;
                if (shape ->GetType() == RECTANGLE || shape ->GetType() == POLYGON){
                    PolygonShape* polygonShape = (PolygonShape*) world.get<RigidBodyComponent>(entity).shape;
                    polygonShape->UpdateVertices(transform.rotation,transform.position); 
                }
            }

            
        }
    }

};