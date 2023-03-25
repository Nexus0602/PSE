class DragAndDropImpulseSystem  {

    public:
    
    void Update(entt::registry& world) {
        // get all entities with DragAndDropImpulseComponent
        auto view = world.view<DragAndDropImpulseComponent, TransformComponent, KinematicComponent>();
        
        // update position and velocity of all entities
        for (auto entity : view) {
            auto &drag = view.get<DragAndDropImpulseComponent>(entity);
            auto &transform = view.get<TransformComponent>(entity);
            auto &kinematic = view.get<KinematicComponent>(entity);

            kinematic.velocity.x *= 1.0 - drag.drag;
            kinematic.velocity.y *= 1.0 - drag.drag;

            kinematic.velocity.x += drag.impulse;
            kinematic.velocity.y += drag.impulse;

            transform.position.x += kinematic.velocity.x;
            transform.position.y += kinematic.velocity.y;

        }
    }
};