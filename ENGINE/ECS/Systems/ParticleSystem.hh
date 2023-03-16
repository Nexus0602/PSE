
class ParticleSystem {
    public:

    void Update(const double dt, entt::registry& world){
        auto view = world.view<KinematicComponent, ParticleComponent>();


        for (auto entity:view){
            auto& kinematic = view.get<KinematicComponent>(entity);
            auto& rb = view.get<ParticleComponent>(entity);

            kinematic.acceleration = rb.sumForces * rb.invMass;
            rb.ClearForces();
        }

    }

    void Render(entt::registry& world){
        auto view = world.view<TransformComponent, ParticleComponent>();
        
        for (auto entity:view){
        const auto transform = view.get<TransformComponent>(entity);
        const auto particle = view.get<ParticleComponent>(entity);

        Graphics::DrawFillCircle(
            transform.position.x,
            transform.position.y,
            particle.radius,
            particle.color
        );
        }
    }
};