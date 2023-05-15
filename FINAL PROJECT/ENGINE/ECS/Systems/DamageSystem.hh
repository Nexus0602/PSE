/* WHEN A COLLISION HAPPENS, AN EVENT IS TRIGGERED AND THE DAMAGE SYSTEM LISTENS TO THE EVENT */
/* DEPENDING ON THE ENTITIES INVOVLED IN THE COLLISION THE RESULT WILL CHANGE */
class DamageSystem {
public:

void OnCollision (CollisionEvent& event){
    //std::cout<<"DamageSystem"<<std::endl;

    auto entityA = event.entA;
    auto entityB = event.entB;
        
    auto& groupA = event.world->get<NameGroupComponent>(entityA);
    auto& groupB = event.world->get<NameGroupComponent>(entityB);

    /* IF A CAR HITS THE FROG: 
                - Frog's health updated
                - Frog's score updated
                - Frog's position updated
                - Sound effect played
                */

        if (groupA.group == "player" && groupB.group == "enemies"){
            auto& sound = event.world->get<SoundComponent>(entityB);
            sound.shouldPlay = true;
            auto& health = event.world->get<HealthComponent>(entityA);
            auto& score = event.world->get<ScoreComponent>(entityA);
            health.health -= 1;
            score.score -= 100;
            auto& transformA = event.world->get<TransformComponent>(entityA);
            transformA.position = Vec2(350,825);
            
            /* IF FROG'S HEALTH = 0:
                        - Grid component removed
                        - Frog's position updated
                        */
            if (health.health <= 0) {
                auto& transformA = event.world->get<TransformComponent>(entityA);
                transformA.position = Vec2(550,850);
                score.score = 0;
                event.world->remove<GridMovementComponent>(entityA);
                std::cout << "Player killed. Score: "<< score.score<< std::endl;
            }
            else {            
                std::cout << "A car hit the frog. Lives: " << health.health << " Score : " << score.score << std::endl;
            }

        }

        else if (groupA.group == "enemies" && groupB.group == "player"){
            auto& sound = event.world->get<SoundComponent>(entityA);
            sound.shouldPlay = true;
            auto& health = event.world->get<HealthComponent>(entityA);
            auto& score = event.world->get<ScoreComponent>(entityA);
            health.health -= 1;
            score.score -= 100;
            auto& transformA = event.world->get<TransformComponent>(entityA);
            transformA.position = Vec2(350,825);
            
            if (health.health <= 0) {
                auto& transformA = event.world->get<TransformComponent>(entityA);
                transformA.position = Vec2(550,850);
                score.score = 0;
                event.world->remove<GridMovementComponent>(entityA);
                std::cout << "Player killed. Score: "<< score.score<< std::endl;
            }
            else {            
                std::cout << "A car hit the frog. Lives: " << health.health << " Score : " << score.score << std::endl;
            }
        }

        /* IF THE FROG COLLIDES WITH A WATERLILY: the frog's velocity becomes the same as the waterlily */
        else if (groupA.group == "player" && groupB.group == "amigos"){
            auto& kinematicA = event.world->get<KinematicComponent>(entityA);
            auto& kinematicB = event.world->get<KinematicComponent>(entityB);
            kinematicA.velocity=kinematicB.velocity;

        }

        /* IF THE FROG COLLIDES WITH A SCENARIO: the frog's velocity becomes 0 */
        else if (groupA.group == "player" && groupB.group == "scenarios"){
            //std::cout<<"ESCENARIO"<<std::endl;
            auto& kinematicA = event.world->get<KinematicComponent>(entityA);
            kinematicA.velocity = Vec2(0,0);

        }

        /* IF THE FROG FALLS INTO THE RIVER :
                - Frog's health updated
                - Frog's score updated
                - Frog's position updated
                - Sound effect played
                    */
        else if (groupA.group == "player" && groupB.group == "water"){
            auto& sound = event.world->get<SoundComponent>(entityB);
            sound.shouldPlay = true;
            auto& health = event.world->get<HealthComponent>(entityA);
            auto& score = event.world->get<ScoreComponent>(entityA);
            health.health -= 1;
            score.score -= 100;
            auto& transformA = event.world->get<TransformComponent>(entityA);
            transformA.position = Vec2(350,375);
            
            if (health.health <= 0) {
                auto& transformA = event.world->get<TransformComponent>(entityA);
                transformA.position = Vec2(550,850);
                score.score = 0;
                std::cout << "Player killed. Score: "<< score.score<< std::endl;
                event.world->remove<GridMovementComponent>(entityA);
            }
            else{
            std::cout << "The frog fell into the river. Lives: " << health.health << " Score : " << score.score << std::endl;
            }
            

        }


}

};
