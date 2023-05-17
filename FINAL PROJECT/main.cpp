#include "Nexus.hh"
#include <random>
#include <iostream>
#include <iomanip>
#include <sstream>

int main(int argc, char *argv[]){

/* ENGINE PARAMS */
    int height = 900;
    int width = 700;
    int engine_counter = 0; // controls that the speed of the objects is initialized only once, see later
    Nexus engine = Nexus(700,900);

    double discountFactor = 3.5;
    string livesVec [6] = {"lives0","lives1", "lives2", "lives3", "lives4", "lives5"}; // sprite array
    vector<entt::entity> carVec; 
    int totalRails = 6;
    int railCounter = 1; // used to manage the sprites depending on the direction
    vector<entt::entity> waterlilyVec;
    vector<entt::entity> waterVec;
    int riverCounter = 0; // used to alternate waterlily sprites --> variety

    /* FROG ENTITY  --> PLAYER */
    auto frog = engine.world.create();
    engine.world.emplace<TransformComponent>(frog, Vec2(width/2,height-75));
    engine.world.emplace<GridMovementComponent>(frog,50);
    engine.world.emplace<KinematicComponent>(frog);
    RectangleShape c = RectangleShape(25,25 , Color::Green(),true);
    engine.world.emplace<ColliderComponent>(frog, c, false);
    engine.world.emplace<SpriteComponent>(frog,"frog",50,50);
    engine.world.emplace<NameGroupComponent>(frog,"player ", "player");
    engine.world.emplace<HealthComponent>(frog,5);
    engine.world.emplace<ScoreComponent>(frog,2000);

    /* SCORE ENTITY --> score marker */
    auto score = engine.world.create();
    SDL_Color color = {0,0,0};
    auto& frogscore = engine.world.get<ScoreComponent>(frog);
    std::string text = "SCORE: " + std::to_string(frogscore.score);
    engine.world.emplace<TextComponent>(score,text,color,engine.font,500,0);

    /* TIMER ENTITY --> timer */
    auto timer = engine.world.create();
    SDL_Color color2 = {0,0,0};
    double time = engine.GetTotalTimeInMilliSeconds();
    std::string text2 = "TIME: 0 s " ;
    engine.world.emplace<TextComponent>(timer,text2,color2,engine.font,275,0);

    /* LIVES ENTITY --> lives marker */
    auto lives = engine.world.create();
    engine.world.emplace<TransformComponent>(lives, Vec2(125, 25));
    engine.world.emplace<SpriteComponent>(lives,"lives5",250,50);
    engine.world.emplace<NameGroupComponent>(lives,"lives ", "live");

    /* SECENARIO 1 */
    auto scenario1 = engine.world.create();
    engine.world.emplace<TransformComponent>(scenario1, Vec2(width/2, height/2-25));
    engine.world.emplace<KinematicComponent>(scenario1);
    RectangleShape s = RectangleShape(width,150, Color::color(176,242,194),true);
    engine.world.emplace<ColliderComponent>(scenario1, s, true);
    engine.world.emplace<NameGroupComponent>(scenario1,"scenario ", "scenarios");

    /* SCENARIO 2 */
    auto scenario2 = engine.world.create();
    engine.world.emplace<TransformComponent>(scenario2, Vec2(width/2, 50));
    engine.world.emplace<KinematicComponent>(scenario2);
    RectangleShape s2 = RectangleShape(width,100, Color::color(176,242,194),true);
    engine.world.emplace<ColliderComponent>(scenario2, s2, true);
    engine.world.emplace<NameGroupComponent>(scenario2,"scenario ", "scenarios");

    /* SCENARIO 3 */
    auto scenario3 = engine.world.create();
    engine.world.emplace<TransformComponent>(scenario3, Vec2(width/2, height-50));
    engine.world.emplace<KinematicComponent>(scenario3);
    RectangleShape s3 = RectangleShape(width,100, Color::color(216,228,199),true);
    engine.world.emplace<ColliderComponent>(scenario3, s3, true);
    engine.world.emplace<NameGroupComponent>(scenario3,"scenario ", "scenarios");

    /* VEHICLE GENERATION*/
    for (int i=0; i<totalRails; i++){

        /* Random position generator*/
        int min = 1;
        int max = 3;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);

        /* ensure vehicles do not overlap */
        int dx1 = dis(gen)*300;
        int dx2 = (dx1 + 100 + dis(gen)*50 )% width;

        /* Used before asignig sprites */
        /*Color color1 = Color::Blue();
        Color color2 = Color::Red();*/

        /* Sprite manager --> variety */
        string id1 = "bcar"; // blue car right to left
        string id2 = "gcar"; // green car right to left
        string id3 = "bcar2"; // blue car left to right
        string id4 = "gcar2"; // green car left to right

        for (int j = 0; j<2;j++){ // j = number of enemies per rail --> to increase hardness increase j

            /* ENEMY ENTITY */
            auto enemy = engine.world.create();
            // velocity.y --> ensures that the vehicles appear in rails of heigth = 50
            engine.world.emplace<TransformComponent>(enemy, Vec2(dx1,512+52*i)); 
            // we don't give speed yet, rendering is faster than the entity generation and the objects overlap
            engine.world.emplace<KinematicComponent>(enemy);
            RectangleShape r = RectangleShape(83, 43 , Color::Blue(),true);
            engine.world.emplace<ColliderComponent>(enemy, r, false, 0.3);
            engine.world.emplace<NameGroupComponent>(enemy,"enemy ", "enemies");
            engine.world.emplace<SoundComponent>(enemy,engine.carEffect);
            /* MANAGING CAR SPRITE DIRECTION*/
            if (railCounter % 2 == 0){
                engine.world.emplace<SpriteComponent>(enemy,id1,83,43);
            }
            else{
                engine.world.emplace<SpriteComponent>(enemy,id3,83,43);
            }
            carVec.push_back(enemy);
            dx1=dx2; // chaging position for the second car, 
            id1=id2; // chaging car sprite for first condition
            id3=id4; // chaging car sprite for second condition
            //color1=color2;
            
    }
    railCounter ++;
    }

    /* ROAD ENTITY */
    auto road = engine.world.create();
    engine.world.emplace<TransformComponent>(road, Vec2(width/2, 640));
    engine.world.emplace<KinematicComponent>(road);
    //RectangleShape s4 = RectangleShape(width,300, Color::Yellow(),true);
    //engine.world.emplace<ColliderComponent>(road, s4, false, 1000000);
    engine.world.emplace<SpriteComponent>(road,"road",width,325);
    engine.world.emplace<NameGroupComponent>(road,"road ", "road");

    /* RIVER MATRIX */
    /* Instead of generating random positions, we use a matrix where 1 = waterlily, 
    0 = water, to ensure that the game is possible to finish */
    int m[5][15] = {{0, 1 ,0, 0, 0, 1, 1, 1 ,0, 0, 0, 1, 0, 0,0},
                    {1, 0 ,0, 0, 1, 1, 0, 0 ,0, 1, 0, 0, 1, 0,0},
                    {0, 0 ,0, 0, 1, 1, 1, 1 ,0, 0, 0, 1, 0, 0,1},
                    {1, 1 ,0, 0, 0, 1, 1, 0 ,1, 1, 0, 0, 0, 1,0},
                    {0, 0 ,0, 0, 1, 1, 1, 0 ,1, 0, 0, 1, 0, 0,0}};
    
    for (int i = 0; i<5;i++){
        for (int j = 0; j<15;j++){
            if (m[i][j]==1){

                /* AMIGO ENTITY = WATERLILY */
                auto amigo = engine.world.create();
                engine.world.emplace<TransformComponent>(amigo, Vec2(50 * j - 25, 50 * i + 125));
                engine.world.emplace<KinematicComponent>(amigo);
                RectangleShape r = RectangleShape(50,50, Color::Yellow(),true);
                engine.world.emplace<ColliderComponent>(amigo, r, false, 0.3);
                /* MANAGING SPRITES --> Variety */
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
            
                /* WATER ENTITY */
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

    /* RIVER ENTITY */
    auto river = engine.world.create();
    engine.world.emplace<TransformComponent>(river, Vec2(width/2, 225));
    engine.world.emplace<KinematicComponent>(river);
    RectangleShape s5 = RectangleShape(width,300, Color::Yellow(),true);
    engine.world.emplace<ColliderComponent>(river, s5, false, 1000000);
    engine.world.emplace<SpriteComponent>(river,"river",700,255);
    engine.world.emplace<AnimationComponent>(river,7,4);
    engine.world.emplace<NameGroupComponent>(river,"river ", "river");
    
    
    /* GAME LOOP */
    while(engine.NextFrame()){
        engine.Update();

        /* ONCE ENTITY GENERATION IS OVER --> INITIALIZING CAR, WATERLILY AND WATER VELOCITIES */
        if (engine_counter == 0){

        int count = 0; // Used to manage car direction
        int vx = 0;
        int min = 1;
        int max = 3;
        int x = 1; // used to calculate the velocity sign

        for(auto& enemy: carVec){
            
            /* RANDOM SPEED GENERATION */
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
                x *= -1; // changing sign 
            }
            count ++;
        }

        vx = 80; // constant speed for waterlily and water

        for(auto& amigo: waterlilyVec){
            
            auto& kinematic2 =engine.world.get<KinematicComponent>(amigo);
            kinematic2.velocity = Vec2(vx,0);

        }

        for(auto& water: waterVec){

            auto& kinematic3 =engine.world.get<KinematicComponent>(water);
            kinematic3.velocity = Vec2(vx,0);

        }

        engine_counter ++; // ensure this part of the code is only done once

        }

        /* checking the frog's health to update the lives marker --> 
        we don't do this part in the damage system because the lives marker can't collide, 
        so it will never acces to that part of the code. */
        auto& spriteA = engine.world.get<SpriteComponent>(lives);
        auto& spriteB = engine.world.get<SpriteComponent>(frog);
        auto& frogHealth =engine.world.get<HealthComponent>(frog);
        if (frogHealth.health == -1) 
            spriteA.assetId = livesVec[0];
        else
            spriteA.assetId = livesVec[frogHealth.health];


        /* if the health is equals to 0, 
        LOSE ENTITY is generated and health is changed to -1 so that it does not get looped*/
        if (frogHealth.health == 0){
            auto lose = engine.world.create();
            engine.world.emplace<SoundComponent>(lose,engine.loseEffect,true);
            engine.world.emplace<TransformComponent>(lose, Vec2(width/2, height/2-25));
            engine.world.emplace<SpriteComponent>(lose,"lose",300,300);
            spriteB.assetId = "rip";
            frogHealth.health = -1;

        }

        // checking the frog's score to update the score marker
        auto& frogscore =engine.world.get<ScoreComponent>(frog);
        auto& text =engine.world.get<TextComponent>(score);
        text.text = "SCORE: " + std::to_string(frogscore.score);

        //Updating the timer if the game is not over
        
        if (!frogscore.win && frogHealth.health>0){
        auto& timertext = engine.world.get<TextComponent>(timer);
        time = engine.GetTotalTimeInMilliSeconds();
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(0) << time;
        std::string timeString = oss.str();
        timertext.text = "TIME: " + timeString + " s";
        }


        // if the frog crosses the river we will now due to its y posititon
        auto& transformFrog =engine.world.get<TransformComponent>(frog);
        if (transformFrog.position.y < 125 ){
            
            if (!frogscore.win){ // by default, win attribute is set to false
            /* if the frog crosses the river, WIN ENTITY is generated and 
            the win attribute is set to true, so that it does not get looped */
            auto win = engine.world.create();
            engine.world.emplace<SoundComponent>(win,engine.winEffect,true);
            engine.world.emplace<TransformComponent>(win, Vec2(width/2, height/2-25));
            engine.world.emplace<SpriteComponent>(win,"win",300,300);
            engine.world.remove<GridMovementComponent>(frog);
            //calculate final score depending on the time
            frogscore.score = frogscore.score - (time * discountFactor);
            }
            frogscore.win= true;
        }

        //Graphics::DrawFillRect(width/2, 225,width,250,Color::color(64,224,208));
        engine.Render();
    }
    return 0;
}