class DamageSystem {
public:

void OnCollision (CollisionEvent& event){
    //std::cout<<"DamageSystem"<<std::endl;

    auto entityA = event.entA;
    auto entityB = event.entB;
        
        auto& groupA = event.world->get<NameGroupComponent>(entityA);
        auto& groupB = event.world->get<NameGroupComponent>(entityB);

        if (groupA.group == "enemies" && groupB.group == "enemies") {
            std::cout << "Enemy hit enemy" << std::endl;
        }

        else if (groupA.group == "player" && groupB.group == "enemies"){
            auto& health = event.world->get<HealthComponent>(entityA);
            health.health -= 10;
            std::cout << "Enemy hit player. Player health: " << health.health << std::endl;
            auto& transformA = event.world->get<TransformComponent>(entityA);
            transformA.position = Vec2(350,850);
            
            if (health.health <= 0) {
                auto& colliderA = event.world->get<ColliderComponent>(entityA);
                auto& transformA = event.world->get<TransformComponent>(entityA);
                colliderA.renderCollider = false;
                transformA.position = Vec2(550,850);
                std::cout << "Player killed" << std::endl;
            }
        }

        else if (groupA.group == "enemies" && groupB.group == "player"){
            auto& health = event.world->get<HealthComponent>(entityA);
            health.health -= 10;
            std::cout << "Enemy hit player. Player health: " << health.health << std::endl;
            auto& transformA = event.world->get<TransformComponent>(entityA);
            transformA.position = Vec2(350,850);
            
            if (health.health <= 0) {
                auto& colliderA = event.world->get<ColliderComponent>(entityA);
                auto& transformA = event.world->get<TransformComponent>(entityA);
                colliderA.renderCollider = false;
                transformA.position = Vec2(550,850);
                std::cout << "Player killed" << std::endl;
            }
        }
        
}

};
