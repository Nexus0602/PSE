#include "Nexus.hh"
#include <random>

int main(int argc, char *argv[]){

    int height = 900;
    int widht = 700;
    Nexus engine = Nexus(700,900);

    auto frog = engine.world.create();
    engine.world.emplace<TransformComponent>(frog, Vec2(widht/2,height-50));
    engine.world.emplace<GridMovementComponent>(frog,50);
    engine.world.emplace<KinematicComponent>(frog);
    RectangleShape c = RectangleShape(24,24 , Color::Green(),true);
    engine.world.emplace<ColliderComponent>(frog, c, true, 1000000);
    engine.world.emplace<NameGroupComponent>(frog,"player ", "player");
    engine.world.emplace<HealthComponent>(frog,40);


    vector<entt::entity> enemies;
    int totalEnemies = 6;
    int x = 1;
    for (int i=0; i<totalEnemies; i++){
        int min = 1;
        int max = 3;
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        int vx = dis(gen);
        vx *= 185 * x;
        for (int j = 0; j<2;j++){
            int dx = dis(gen)*300+j*100;
            //std::cout<<" DX " << dx << std::endl;
            auto enemy = engine.world.create();
            engine.world.emplace<TransformComponent>(enemy, Vec2(dx,500+50*i));
            engine.world.emplace<KinematicComponent>(enemy, Vec2(vx,0));
            RectangleShape r = RectangleShape(100, 40 , Color::Red(),true);
            engine.world.emplace<ColliderComponent>(enemy, r, true, 0.3);
            engine.world.emplace<NameGroupComponent>(enemy,"enemy ", "enemies");
            enemies.push_back(enemy);
    }
    x *= -1;
    }


    while(engine.NextFrame()){
        engine.Update();

        //Graphics::DrawGrid(50);

        Graphics::DrawFillRect(widht/2, height/2-50,widht,100,Color::White());
        Graphics::DrawFillRect(widht/2, 50,widht,100,Color::White());
        Graphics::DrawFillRect(widht/2, height - 50,widht,100,Color::White());
        Graphics::DrawFillRect(widht/2, 225,widht,250,Color::Blue());
        

        engine.Render();

    }
    

    return 0;
}