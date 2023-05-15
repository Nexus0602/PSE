
class KinematicSystem{
    public:

    void Update(const double dt, entt::registry& world){
        int width = 700;
        int height = 900;
        auto view = world.view<TransformComponent, KinematicComponent,NameGroupComponent >();
        for(auto entity:view){
            auto& transform = view.get<TransformComponent>(entity);
            auto& kinematic = view.get<KinematicComponent>(entity);
            auto& n = view.get<NameGroupComponent>(entity);
            

            //Semi-implicit euler --> linear motion
            kinematic.velocity += kinematic.acceleration * dt;
            transform.position += kinematic.velocity * dt;

            /* BOUNDARY CHECK: depeding on the kind of entity and part of the scenario*/
            /* Code that controls that the cars appear again when they dissapear (in a "natural" way)*/
            if (n.group == "enemies"){
            if (transform.position.x + 50<= 0 && kinematic.velocity.x < 0)
                transform.position.x  = width + 50;

            if (transform.position.x - 50 >= width && kinematic.velocity.x > 0)
                transform.position.x  = -50;
            }

            /* Code that controls that the water and the waterlilies appear again when they dissapear (in a "natural" way)*/
            if (n.group == "amigos" ||n.group == "water" ){

            if (transform.position.x - 25 >= width && kinematic.velocity.x > 0)
                transform.position.x  = -25;
            }

            /* Code that controls that the frog is not able to go outside the window*/
            if (n.group == "player"){
                /*If the frog is in the river and goes on a waterlily it appears again*/
                if (transform.position.x - 25 >= width  && transform.position.y <= 325 && transform.position.y > 100 )
                    transform.position.x = -25;

                else if (transform.position.x >= width) {
                    transform.position.x = width - 25 ;

                }
                else if (transform.position.x <= 0) {
                    transform.position.x = 25;

                }
                else if (transform.position.y - 12.5 >= height) {
                    transform.position.y = height - 25;

                }
            }
            
        
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