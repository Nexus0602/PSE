
class DamageSystem {
public:

void OnCollision (CollisionEvent& event){
    //std::cout<<"DamageSystem"<<std::endl;

    auto entityA = event.entA;
    auto entityB = event.entB;
        
    auto& groupA = event.world->get<NameGroupComponent>(entityA);
    auto& groupB = event.world->get<NameGroupComponent>(entityB);

        if (groupA.group == "enemies" && groupB.group == "enemies") {
            //std::cout << "Enemy hit enemy" << std::endl;
        }

        else if (groupA.group == "player" && groupB.group == "enemies"){
            auto& sound = event.world->get<SoundComponent>(entityB);
            sound.shouldPlay = true;
            auto& health = event.world->get<HealthComponent>(entityA);
            auto& score = event.world->get<ScoreComponent>(entityA);
            health.health -= 1;
            score.score -= 100;
            std::cout << "Enemy hit player. Lives: " << health.health << " Score : " << score.score << std::endl;
            auto& transformA = event.world->get<TransformComponent>(entityA);
            transformA.position = Vec2(350,825);
            
            if (health.health <= 0) {
                auto& transformA = event.world->get<TransformComponent>(entityA);
                transformA.position = Vec2(550,850);
                score.score = 0;
                event.world->remove<GridMovementComponent>(entityA);
                std::cout << "Player killed. Score: "<< score.score<< std::endl;
            }

        }

        else if (groupA.group == "enemies" && groupB.group == "player"){
            auto& sound = event.world->get<SoundComponent>(entityA);
            sound.shouldPlay = true;
            auto& health = event.world->get<HealthComponent>(entityA);
            auto& score = event.world->get<ScoreComponent>(entityA);
            health.health -= 1;
            score.score -= 100;
            std::cout << "Enemy hit player. Lives: " << health.health << " Score : " << score.score << std::endl;
            auto& transformA = event.world->get<TransformComponent>(entityA);
            transformA.position = Vec2(350,825);
            
            if (health.health <= 0) {
                auto& transformA = event.world->get<TransformComponent>(entityA);
                transformA.position = Vec2(550,850);
                score.score = 0;
                event.world->remove<GridMovementComponent>(entityA);
                std::cout << "Player killed. Score: "<< score.score<< std::endl;
            }

        }

        else if (groupA.group == "player" && groupB.group == "amigos"){
            auto& kinematicA = event.world->get<KinematicComponent>(entityA);
            auto& kinematicB = event.world->get<KinematicComponent>(entityB);

            kinematicA.velocity=kinematicB.velocity;

        }

        else if (groupA.group == "player" && groupB.group == "scenarios"){
            //std::cout<<"ESCENARIO"<<std::endl;
            auto& kinematicA = event.world->get<KinematicComponent>(entityA);
            kinematicA.velocity = Vec2(0,0);

        }

        else if (groupA.group == "player" && groupB.group == "water"){
            //std::cout<<"WATER"<<std::endl;
            auto& sound = event.world->get<SoundComponent>(entityB);
            sound.shouldPlay = true;
            auto& health = event.world->get<HealthComponent>(entityA);
            auto& score = event.world->get<ScoreComponent>(entityA);
            health.health -= 1;
            score.score -= 100;
            std::cout << "The frog fell into the river. Lives: " << health.health << " Score : " << score.score << std::endl;
            auto& transformA = event.world->get<TransformComponent>(entityA);
            transformA.position = Vec2(350,375);
            
            if (health.health <= 0) {
                auto& transformA = event.world->get<TransformComponent>(entityA);
                transformA.position = Vec2(550,850);
                score.score = 0;
                std::cout << "Player killed. Score: "<< score.score<< std::endl;
                event.world->remove<GridMovementComponent>(entityA);
            }
            

        }


}

};
