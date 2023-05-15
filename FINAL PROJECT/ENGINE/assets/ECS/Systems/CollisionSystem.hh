class CollisionSystem {
    
    public:
    void Update(entt::dispatcher& eventBus, entt::registry& world){
        
        auto view = world.view<TransformComponent, KinematicComponent, ColliderComponent>();
        
        for (auto entity: view){
            auto& collider = view.get<ColliderComponent>(entity);
            collider.isColliding = false;
        }

        for (auto entityA: view) {
            /*auto& colliderFrog = world.get<ColliderComponent>(entityA);
            auto& groupFrog = world.get<NameGroupComponent>(entityA);
                auto& transformFrog = world.get<TransformComponent>(entityA);*/
            for (auto entityB: view) {
                //auto& groupAmigo = world.get<NameGroupComponent>(entityB);
                if (entityA == entityB) {
                    break;
                }

                Contact contact;

                if (Collisions::IsColliding(entityA,entityB,contact,world)){
                    //std::cout<<"Resolve Collision"<<std::endl;
                
                world.get<ColliderComponent>(entityA).isColliding = true;
                world.get<ColliderComponent>(entityB).isColliding = true;

                CollisionEvent collision_event(entityA, entityB,world);
                eventBus.trigger(collision_event);
                //Collisions::ResolveCollision(entityA,entityB,contact,world);
                }

        }
        
    }}

    void Render(entt::registry& world){
        auto view = world.view<TransformComponent, KinematicComponent, ColliderComponent>();
        for (auto entity: view) {
            const auto collider = view.get<ColliderComponent>(entity);
            if (collider.renderCollider){
                const auto transform = view.get<TransformComponent>(entity);
                //std::cout<<"RENDER"<<std::endl;
                collider.shape->Render(transform);
            }
        }
    }

    void OnCollision(CollisionEvent& event) {
       //std::cout << "Collision detected " << std::endl;
    }

};