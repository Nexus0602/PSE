#include "Nexus.hh"
#include <random>

int main(int argc, char *argv[]){

    int height = 900;
    int widht = 700;
    Nexus engine = Nexus(700,900);

    const auto frog = engine.world.create();
    engine.world.emplace<TransformComponent>(frog, Vec2(widht/2,height-100));
    engine.world.emplace<GridMovementComponent>(frog,50);

    vector<entt::entity> enemies;
    int totalEnemies = 6;

    for (int i=0; i<totalEnemies; i++){
        int min = -3;
        int max = 3;

    // Crea el generador de números aleatorios y la distribución
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);

        const auto enemy = engine.world.create();
        engine.world.emplace<TransformComponent>(enemy, Vec2(dis(gen)*50,500+dis(gen)*50));
        engine.world.emplace<KinematicComponent>(enemy, Vec2(2*dis(gen)*50,0));

        enemies.push_back(enemy);
    }

    while(engine.NextFrame()){
        engine.Update();

        Graphics::DrawGrid(50);

        auto transform = engine.world.get<TransformComponent>(frog);
        Graphics::DrawFillCircle(
            transform.position.x,
            transform.position.y,
            15,
            Color::White()
        );

        for (auto& enemy: enemies) {
            auto transform2 = engine.world.get<TransformComponent>(enemy);
            Graphics::DrawFillRect(
            transform2.position.x,
            transform2.position.y,
            100,50,Color::Red()
            );

        }
        
        
        engine.Render();

        // CHECK BOUNDARIES

        
    }

    return 0;
}