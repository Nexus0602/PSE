#include "Nexus.hh"
#include <random>

int main(int argc, char *argv[]){

    int height = 900;
    int width = 700;
    int engine_counter = 0;
    Nexus engine = Nexus(700,900);

    string livesVec [6] = {"lives0","lives1", "lives2", "lives3", "lives4", "lives5"};
    vector<entt::entity> carVec;
    int totalRails = 6;
    int enemyCounter = 1;
    vector<entt::entity> waterlilyVec;
    vector<entt::entity> waterVec;
    int riverCounter = 0;

    auto frog = engine.world.create();
    engine.world.emplace<TransformComponent>(frog, Vec2(width/2,height-75));
    //engine.world.emplace<TransformComponent>(frog, Vec2(width/2,375));
    engine.world.emplace<GridMovementComponent>(frog,50);
    engine.world.emplace<KinematicComponent>(frog);
    RectangleShape c = RectangleShape(25,25 , Color::Green(),true);
    engine.world.emplace<ColliderComponent>(frog, c, false, 1000000);
    engine.world.emplace<SpriteComponent>(frog,"frog",50,50);
    engine.world.emplace<NameGroupComponent>(frog,"player ", "player");
    engine.world.emplace<HealthComponent>(frog,5);
    engine.world.emplace<ScoreComponent>(frog,1000);

    auto score = engine.world.create();
    SDL_Color color = {0,0,0};
    auto& frogscore = engine.world.get<ScoreComponent>(frog);
    std::string text = "SCORE: " + std::to_string(frogscore.score);
    engine.world.emplace<TextComponent>(score,text,color,engine.font,500,0);

    auto lives = engine.world.create();
    engine.world.emplace<TransformComponent>(lives, Vec2(125, 25));
    engine.world.emplace<SpriteComponent>(lives,"lives5",250,50);
    engine.world.emplace<NameGroupComponent>(lives,"lives ", "live");

    auto scenario1 = engine.world.create();
    engine.world.emplace<TransformComponent>(scenario1, Vec2(width/2, height/2-25));
    engine.world.emplace<KinematicComponent>(scenario1);
    RectangleShape s = RectangleShape(width,150, Color::color(176,242,194),true);
    engine.world.emplace<ColliderComponent>(scenario1, s, true, 1000000);
    engine.world.emplace<NameGroupComponent>(scenario1,"scenario ", "scenarios");

    auto scenario2 = engine.world.create();
    engine.world.emplace<TransformComponent>(scenario2, Vec2(width/2, 50));
    engine.world.emplace<KinematicComponent>(scenario2);
    RectangleShape s2 = RectangleShape(width,100, Color::color(176,242,194),true);
    engine.world.emplace<ColliderComponent>(scenario2, s2, true, 1000000);
    engine.world.emplace<NameGroupComponent>(scenario2,"scenario ", "scenarios");

    auto scenario3 = engine.world.create();
    engine.world.emplace<TransformComponent>(scenario3, Vec2(width/2, height-50));
    engine.world.emplace<KinematicComponent>(scenario3);
    RectangleShape s3 = RectangleShape(width,100, Color::color(216,228,199),true);
    engine.world.emplace<ColliderComponent>(scenario3, s3, true, 1000000);
    engine.world.emplace<NameGroupComponent>(scenario3,"scenario ", "scenarios");

    
    for (int i=0; i<totalRails; i++){

        int min = 1;
        int max = 3;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);

        int dx1 = dis(gen)*300;
        int dx2 = (dx1 + 100 + dis(gen)*50 )% width;
        /*Color color1 = Color::Blue();
        Color color2 = Color::Red();*/

        string id1 = "bcar";
        string id2 = "gcar";
        string id3 = "bcar2";
        string id4 = "gcar2";

        for (int j = 0; j<2;j++){

            auto enemy = engine.world.create();
            engine.world.emplace<TransformComponent>(enemy, Vec2(dx1,512+52*i));
            engine.world.emplace<KinematicComponent>(enemy);
            RectangleShape r = RectangleShape(83, 43 , Color::Blue(),true);
            engine.world.emplace<ColliderComponent>(enemy, r, false, 0.3);
            engine.world.emplace<NameGroupComponent>(enemy,"enemy ", "enemies");
            engine.world.emplace<SoundComponent>(enemy,engine.carEffect);
            if (enemyCounter % 2 == 0){
                engine.world.emplace<SpriteComponent>(enemy,id1,83,43);
                //std::cout<<id1<<std::endl;
            }
            else{
                engine.world.emplace<SpriteComponent>(enemy,id3,83,43);
                //std::cout<<id3<<std::endl;
            }

            carVec.push_back(enemy);
            dx1=dx2;
            id1=id2;
            id3=id4;
            //color1=color2;
            
    }
    enemyCounter ++;
    
    }

    auto road = engine.world.create();
    engine.world.emplace<TransformComponent>(road, Vec2(width/2, 640));
    engine.world.emplace<KinematicComponent>(road);
    RectangleShape s4 = RectangleShape(width,300, Color::Yellow(),true);
    engine.world.emplace<ColliderComponent>(road, s4, false, 1000000);
    engine.world.emplace<SpriteComponent>(road,"road",width,325);
    engine.world.emplace<NameGroupComponent>(road,"road ", "road");


    int m[5][15] = {{0, 1 ,0, 0, 0, 1, 1, 1 ,0, 0, 0, 1, 0, 0,0},
                    {1, 0 ,0, 0, 1, 1, 0, 0 ,0, 1, 0, 0, 1, 0,0},
                    {0, 0 ,0, 0, 1, 1, 1, 1 ,0, 0, 0, 1, 0, 0,1},
                    {1, 1 ,0, 0, 0, 1, 1, 0 ,1, 1, 0, 0, 0, 1,0},
                    {0, 0 ,0, 0, 1, 1, 1, 0 ,1, 0, 0, 1, 0, 0,0}};
    
    for (int i = 0; i<5;i++){
        for (int j = 0; j<15;j++){
            if (m[i][j]==1){

                auto amigo = engine.world.create();
                engine.world.emplace<TransformComponent>(amigo, Vec2(50 * j - 25, 50 * i + 125));
                engine.world.emplace<KinematicComponent>(amigo);
                RectangleShape r = RectangleShape(50,50, Color::Yellow(),true);
                engine.world.emplace<ColliderComponent>(amigo, r, false, 0.3);
                if (riverCounter % 2 == 0){
                    engine.world.emplace<SpriteComponent>(amigo,"nenufar",50,50);    
                }
                else if (riverCounter%3 ==0)
                    engine.world.emplace<SpriteComponent>(amigo,"nenufar4",50,50);
                else if (riverCounter%3 ==0)
                    engine.world.emplace<SpriteComponent>(amigo,"nenufar3",50,50);
                    
                else{
                    engine.world.emplace<SpriteComponent>(amigo,"nenufar2",50,50);
                }
                    
                engine.world.emplace<NameGroupComponent>(amigo,"amigo ", "amigos");
                waterlilyVec.push_back(amigo);
                riverCounter++;
            }
            else {

                auto water = engine.world.create();
                engine.world.emplace<TransformComponent>(water, Vec2(50 * j - 25, 50 * i + 125));
                engine.world.emplace<KinematicComponent>(water);
                RectangleShape w = RectangleShape(51,50, Color::Blue(),true);
                engine.world.emplace<ColliderComponent>(water, w, false, 0.3);
                engine.world.emplace<NameGroupComponent>(water,"water ", "water");
                engine.world.emplace<SoundComponent>(water,engine.splashEffect);
                waterVec.push_back(water);

            }
        }
    }

    auto river = engine.world.create();
    engine.world.emplace<TransformComponent>(river, Vec2(width/2, 225));
    engine.world.emplace<KinematicComponent>(river);
    RectangleShape s5 = RectangleShape(width,300, Color::Yellow(),true);
    engine.world.emplace<ColliderComponent>(river, s5, false, 1000000);
    engine.world.emplace<SpriteComponent>(river,"river",700,255);
    engine.world.emplace<AnimationComponent>(river,7,3.2);
    engine.world.emplace<NameGroupComponent>(river,"river ", "river");
    
    
    while(engine.NextFrame()){
        engine.Update();

        if (engine_counter == 0){

            int count = 0;
        int vx = 0;
        int min = 1;
        int max = 3;
        int x = 1;

        for(auto& enemy: carVec){

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(min, max);

            if (count%2==0){
            vx = dis(gen);
            vx *= 130 * x;
            }
            auto& kinematic =engine.world.get<KinematicComponent>(enemy);
            kinematic.velocity = Vec2(vx,0);

            if (count%2==0){
                x *= -1;
            }
            count ++;
        }

        vx = 80;

        for(auto& amigo: waterlilyVec){
            
            auto& kinematic2 =engine.world.get<KinematicComponent>(amigo);
            kinematic2.velocity = Vec2(vx,0);

        }

        for(auto& water: waterVec){

            auto& kinematic3 =engine.world.get<KinematicComponent>(water);
            kinematic3.velocity = Vec2(vx,0);

        }

        engine_counter ++;

        }

        auto& spriteA = engine.world.get<SpriteComponent>(lives);
        auto& frogHealth =engine.world.get<HealthComponent>(frog);
        spriteA.assetId = livesVec[frogHealth.health];

        if (frogHealth.health == 0){
            auto lose = engine.world.create();
            engine.world.emplace<SoundComponent>(lose,engine.loseEffect,true);
            engine.world.emplace<TransformComponent>(lose, Vec2(width/2, height/2-25));
            engine.world.emplace<SpriteComponent>(lose,"lose",300,300);
            frogHealth.health = -1;

        }

        auto& frogscore =engine.world.get<ScoreComponent>(frog);
        auto& text =engine.world.get<TextComponent>(score);
        
        text.text = "SCORE: " + std::to_string(frogscore.score);

        auto& transformFrog =engine.world.get<TransformComponent>(frog);

        if (transformFrog.position.y < 125 ){

            if (!frogscore.win){
            auto win = engine.world.create();
            engine.world.emplace<SoundComponent>(win,engine.winEffect,true);
            engine.world.emplace<TransformComponent>(win, Vec2(width/2, height/2-25));
            engine.world.emplace<SpriteComponent>(win,"win",300,300);
            engine.world.remove<GridMovementComponent>(frog);
            }
            frogscore.win= true;
        }

        Graphics::DrawFillRect(width/2, 225,width,250,Color::color(64,224,208));
        engine.Render();
    }
    return 0;
}